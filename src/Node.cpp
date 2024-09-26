#include "Node.h"
#include "ClearConsole.h"

Node::Node()
{
    laser_status = true;
    los_o = false;
    los_p = false;
    cout << "The Node is running!" << endl;
}

void Node::RestoreSystem()
{
    lock_guard<mutex> lock(mtx);
    laser_status = true;
    los_o = false;
    los_p = false;
}

bool Node::GetLaserStatus()
{
    lock_guard<mutex> lock(mtx);
    return laser_status;
}

void Node::SetLaserStatus(bool status)
{
    lock_guard<mutex> lock(mtx);
    laser_status = status;
}

void Node::SetLosO(bool status)
{
    lock_guard<mutex> lock(mtx);
    los_o = status;
}

void Node::SetLosP(bool status)
{
    lock_guard<mutex> lock(mtx);
    los_p = status;
}

void Node::ShowData(string message)
{
    clearConsole();
    lock_guard<mutex> lock(mtx);

    cout << "\t\tNode State Interface" << endl;
    cout << "---------------------------------------------------------" << endl;
    cout << " Received data:\t\t| " << message << endl;

    cout << "---------------------------------------------------------" << endl;
    if (laser_status) {
        cout << " Linear amplifier:\t| WORKING" << endl;
    }
    else {
        cout << " Linear amplifier:\t| OFF" << endl;
    }

    cout << "---------------------------------------------------------" << endl;
    if (!los_o) {
        cout << " Los-Detector:\t\t| NO LOS" << endl;
    }
    else {
        cout << " Los-Detector:\t\t| LOS PAYLOAD" << endl;
    }

    cout << "---------------------------------------------------------" << endl;
    if (!los_p) {
        cout << " OSC:\t\t\t| CONTINUITY" << endl;
    }
    else {
        cout << " OSC:\t\t\t| DISCONTINUITY" << endl;
    }
}
