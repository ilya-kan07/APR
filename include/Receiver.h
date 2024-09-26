#ifndef RECEIVER_H
#define RECEIVER_H
#include "Node.h"

using namespace std;

class Receiver
{
public:
	Receiver();
	void AcceptData(SOCKET socket);
	void ProcessMessages(Node& node, SOCKET socket);
private:
	mutex queue_mtx;
	queue<string> message_queue;
};

#endif // !RECEIVER_H
