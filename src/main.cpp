#include "Node.h"
#include "Amplifier.h"
#include "LosDetector.h"
#include "OSC.h"
#include "Receiver.h"
#include "FiberFunction.h"

using namespace std;

int main() {

    #ifdef _WIN32
    // Инициализация Winsock для Windows
    WSAData wsaData;
    WORD DLLVersion = MAKEWORD(2, 1);
    if (WSAStartup(DLLVersion, &wsaData) != 0) {
        cout << "Error initializing Winsock" << endl;
        exit(1);
    }
    #endif

    // Настройка адреса сокета
    sockaddr_in addr;
    int sizeofaddr = sizeof(addr);
    addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    addr.sin_port = htons(1111);
    addr.sin_family = AF_INET;

    // Создание сокета
    SOCKET Connection = socket(AF_INET, SOCK_STREAM, 0);
    if (Connection == INVALID_SOCKET) {
        #ifdef _WIN32
        cerr << "Socket creation failed with error: " << WSAGetLastError() << endl;
        #else
        cerr << "Socket creation failed with error: " << strerror(errno) << endl;
        #endif
        exit(1);
    }

    // Подключение или запуск сервера
    if (connect(Connection, (sockaddr*)&addr, sizeof(addr)) != 0) {

        #ifdef _WIN32
        cerr << "Connection failed with error: " << WSAGetLastError() << endl;
        #else
        cerr << "Connection failed with error: " << strerror(errno) << endl;  // Сообщаем точную ошибку
        #endif

        cout << "Running as server" << endl;

        SOCKET sListen = socket(AF_INET, SOCK_STREAM, 0);
        if (sListen == INVALID_SOCKET) {
        #ifdef _WIN32
            cerr << "Socket creation failed with error: " << WSAGetLastError() << endl;
        #else
            cerr << "Socket creation failed with error: " << strerror(errno) << endl;
        #endif
            exit(1);
        }

        if (bind(sListen, (sockaddr*)&addr, sizeof(addr)) == SOCKET_ERROR) {
            #ifdef _WIN32
            cerr << "Bind failed with error: " << WSAGetLastError() << endl;
            #else
            cerr << "Bind failed with error: " << strerror(errno) << endl;
            #endif
            exit(1);
        }

        listen(sListen, SOMAXCONN);
        SOCKET newConnection = accept(sListen, (sockaddr*)&addr, (socklen_t*)&sizeofaddr);

        if (newConnection == INVALID_SOCKET) {
            cout << "Error accepting connection" << endl;
        } else {
            cout << "Client connected!" << endl;
        }

        cout << "Client connected!" << endl;

        Amplifier amplifier;
        LosDetector detector;
        OSC osc;
        Receiver receiver;
        Node node;
        this_thread::sleep_for(chrono::seconds(5));

        thread t3(SimulateFiberStatus, ref(node), ref(detector), ref(osc), newConnection);
        thread t4(&Receiver::ProcessMessages, &receiver, ref(node), newConnection);

        while (true) {
            this_thread::sleep_for(chrono::seconds(2));
            thread t1(&Amplifier::SendData, &amplifier, ref(node), newConnection);
            thread t2(&Receiver::AcceptData, &receiver, newConnection);
            t1.join();
            t2.detach();
        }
        t3.join();
        t4.join();

    } else {
        cout << "Running as client" << endl;
        cout << "Connected!" << endl;

        Amplifier amplifier;
        LosDetector detector;
        OSC osc;
        Receiver receiver;
        Node node;

        thread t4(&Receiver::ProcessMessages, &receiver, ref(node), Connection);

        while (true) {
            this_thread::sleep_for(chrono::seconds(2));
            thread t1(&Amplifier::SendData, &amplifier, ref(node), Connection);
            thread t2(&Receiver::AcceptData, &receiver, Connection);
            t1.join();
            t2.detach();
        }
        t4.join();
    }

#ifdef _WIN32
    WSACleanup();
#endif

    return 0;
}
