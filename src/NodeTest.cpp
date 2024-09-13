#include "NodeTest.h"

bool NodeTest::GetLaserStatus(Node& node)
{
	return node.laser_status;
}

bool NodeTest::GetLosO(Node& node)
{
	return node.los_o;
}

bool NodeTest::GetLosP(Node& node)
{
	return node.los_p;
}