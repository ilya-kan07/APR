#include "Amplifier.h"
#include "Node.h"

using namespace std;

Amplifier::Amplifier()
{
    cout << "The amplifier is running!" << endl;
}

void Amplifier::SendData(Node& node, SOCKET socket)
{
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dist(1, 100);

    string msg;
    {
        if (node.GetLaserStatus()) {
            for (int i = 0; i < 10; i++) {
                msg += to_string(dist(gen)) + " ";
            }
        }
        else {
            msg = "None";
        }
    }

    #ifdef _WIN32
    if (send(socket, msg.c_str(), msg.size(), 0) == SOCKET_ERROR) {
        cerr << "Send failed with error: " << WSAGetLastError() << endl;
        exit(0);
    }
    #else
    if (send(socket, msg.c_str(), msg.size(), 0) == -1) {
        cerr << "Send failed with error: " << strerror(errno) << endl;
        exit(0);
    }
    #endif
}
