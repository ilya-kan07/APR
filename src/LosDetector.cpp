#include "LosDetector.h"
#include <iostream>

LosDetector::LosDetector()
{
    cout << "The Los Detector is running!" << endl;
}

void LosDetector::LosDetect(Node& node, string message)
{
    if (message == "BREAK") {
        node.SetLaserStatus(false);
        node.SetLosO(true);
    }
}
