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
        send(socket, msg.c_str(), msg.size(), NULL);
        node.SetLosP(true);
        cout << "System Message:" << msg << endl;
    }
    else if (message == "RESTORE") {
        msg = "Restoring continuity";
        send(socket, msg.c_str(), msg.size(), NULL);
        cout << "System Message:" << msg << endl;
        node.RestoreSystem();
    }
}