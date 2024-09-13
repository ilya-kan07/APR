#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "NodeTest.h"
#include "LosDetector.h"
#include "OSC.h"

#pragma comment(lib, "ws2_32.lib")
#pragma warning(disable: 4996)
TEST(TestNode, LaserStatusInitialState) {
    Node node;
    NodeTest tnode;
    EXPECT_TRUE(tnode.GetLaserStatus(node));
}

TEST(TestNode, LosOInitialState) {
    Node node;
    NodeTest tnode;
    EXPECT_FALSE(tnode.GetLosO(node));
}

TEST(TestNode, LosPInitialState) {
    Node node;
    NodeTest tnode;
    EXPECT_FALSE(tnode.GetLosP(node));
}

TEST(TestNode, LosDetectorBreak) {
    Node node;
    NodeTest tnode;
    LosDetector detector;
    detector.LosDetect(node, "BREAK");
    EXPECT_FALSE(tnode.GetLaserStatus(node));
    EXPECT_TRUE(tnode.GetLosO(node));
}

TEST(TestNode, RestoreSystem) {
    Node node;
    NodeTest tnode;
    LosDetector detector;
    detector.LosDetect(node, "BREAK");
    node.RestoreSystem();
    EXPECT_TRUE(tnode.GetLaserStatus(node));
    EXPECT_FALSE(tnode.GetLosO(node));
    EXPECT_FALSE(tnode.GetLosP(node));
}

TEST(TestNode, OSCtoBreak) {
    SOCKET socket = 0;
    Node node;
    NodeTest tnode;
    OSC osc;
    osc.ContinuityControl(node, "BREAK", socket);
    EXPECT_TRUE(tnode.GetLosP(node));
}

TEST(TestNode, OSCtoRestore) {
    SOCKET socket = 0;
    Node node;
    NodeTest tnode;
    OSC osc;
    LosDetector detector;
    detector.LosDetect(node, "BREAK");
    osc.ContinuityControl(node, "BREAK", socket);
    osc.ContinuityControl(node, "RESTORE", socket);
    EXPECT_TRUE(tnode.GetLaserStatus(node));
    EXPECT_FALSE(tnode.GetLosO(node));
    EXPECT_FALSE(tnode.GetLosP(node));
}


int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
