#ifndef NODE_H
#define NODE_H
#include <Sockets.h>
#include <iostream>
#include <mutex>
#include <string>
#include <thread>
#include <queue>
#include <random>

class NodeTest;

using namespace std;

class Node
{
	friend class NodeTest;
public:
	Node();
	virtual void RestoreSystem();
	virtual void ShowData(string message);
	virtual bool GetLaserStatus();
	void SetLaserStatus(bool status);
	void SetLosO(bool status);
	void SetLosP(bool status);
private:
	bool laser_status;
	bool los_o;
	bool los_p;
	mutex mtx;
};

#endif // !NODE_H
