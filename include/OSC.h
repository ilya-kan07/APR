#ifndef OSC_H
#define OSC_H
#include "Node.h"

class OSC
{
public:
	OSC();
	void ContinuityControl(Node& node, string message, SOCKET socket);
};

#endif // !OSC_H