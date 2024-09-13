#ifndef AMPLIFIER_H
#define AMPLIFIER_H
#include "Node.h"

class Amplifier
{
public:
	Amplifier();
	void SendData(Node& node, SOCKET socket);
};

#endif // !AMPLIFIER_H
