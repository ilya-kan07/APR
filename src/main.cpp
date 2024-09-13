#include "SocketConnection.h"
#include "Node.h"
#include "Amplifier.h"
#include "LosDetector.h"
#include "OSC.h"
#include "Receiver.h"
#include "FiberFunction.h"

using namespace std;

int main() {
    if (!InitSockets()) {
        cout << "Error initializing sockets" << endl;
        exit(1);
    }

    sockaddr_in addr;
    int sizeofaddr = sizeof(addr);
    addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    addr.sin_port = htons(1111);
    addr.sin_family = AF_INET;

    SocketType connection;

    if (!ConnectToServer(connection, addr)) {
        cout << "Running as server" << endl;
        SocketType sListen;
        StartServer(sListen, addr, sizeofaddr);

        SocketType newConnection = AcceptConnection(sListen, addr, &sizeofaddr);
        if (newConnection == INVALID_SOCKET) {
            cout << "Error accepting connection" << endl;
        }
        else {
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
        }
    }
    else {
        cout << "Running as client" << endl;
        cout << "Connected!" << endl;

        Amplifier amplifier;
        LosDetector detector;
        OSC osc;
        Receiver receiver;
        Node node;

        thread t4(&Receiver::ProcessMessages, &receiver, ref(node), connection);

        while (true) {
            this_thread::sleep_for(chrono::seconds(2));
            thread t1(&Amplifier::SendData, &amplifier, ref(node), connection);
            thread t2(&Receiver::AcceptData, &receiver, connection);
            t1.join();
            t2.detach();
        }
        t4.join();
    }

    CleanupSockets();
    return 0;
}
