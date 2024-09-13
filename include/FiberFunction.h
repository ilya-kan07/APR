#include "Node.h"
#include "LosDetector.h"
#include "OSC.h"

void SimulateFiberStatus(Node& node, LosDetector& detector, OSC& osc, SOCKET socket)
{
    this_thread::sleep_for(chrono::seconds(10));

    while (true)
    {
        this_thread::sleep_for(chrono::seconds(15));
        detector.LosDetect(node, "BREAK");
        osc.ContinuityControl(node, "BREAK", socket);

        this_thread::sleep_for(chrono::seconds(15));
        osc.ContinuityControl(node, "RESTORE", socket);
    }
}