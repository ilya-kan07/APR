#include "OSC.h"
#include <iostream>

using namespace std;

OSC::OSC()
{
    cout << "The OSC is running!" << endl;
}

void OSC::ContinuityControl(Node& node, string message, SOCKET socket)
{
    string msg;
    if (message == "BREAK") {
        msg = "Breaking continuity";
        #ifdef _WIN32
        send(socket, msg.c_str(), msg.size(), NULL);
        #else
        send(socket, msg.c_str(), msg.size(), 0);
        #endif
        node.SetLosP(true);
        cout << "System Message:" << msg << endl;
    }
    else if (message == "RESTORE") {
        msg = "Restoring continuity";
        #ifdef _WIN32
        send(socket, msg.c_str(), msg.size(), NULL);
        #else
        send(socket, msg.c_str(), msg.size(), 0);
        #endif
        cout << "System Message:" << msg << endl;
        node.RestoreSystem();
    }
}
