#ifndef LOSDETECTOR_H
#define LOSDETECTOR_H
#include "Node.h"

class LosDetector
{
public:
	LosDetector();
	void LosDetect(Node& node, string message);
};

#endif // !LOSDETECTOR_H