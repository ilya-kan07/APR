#include "Receiver.h"
#include "Node.h"
#include "LosDetector.h"

Receiver::Receiver()
{
    cout << "The Receiver is running!" << endl;
}

void Receiver::AcceptData(SOCKET socket)
{
    char msg[50];
    while (true) {
        int result = recv(socket, msg, sizeof(msg) - 1, NULL);

        if (result > 0)
        {
            msg[result] = '\0';

            {
                lock_guard<mutex> lock(queue_mtx);
                message_queue.push(string(msg));
            }
        }
        else if (result == 0)
        {
            break;
        }
        else
        {
            cout << "Connetction closed" << endl;
            exit(0);
        }
    }
}

void Receiver::ProcessMessages(Node& node, SOCKET socket)
{
    while (true) {
        string msg;
        {
            lock_guard<mutex> lock(queue_mtx);
            if (!message_queue.empty()) {
                msg = message_queue.front();
                message_queue.pop();
            }
        }

        if (!msg.empty()) {
            if (strstr(msg.c_str(), "Restoring continuity") != nullptr)
            {
                node.RestoreSystem();
                node.ShowData(msg);
            }
            else if (strstr(msg.c_str(), "Breaking continuity") != nullptr)
            {
                LosDetector detector;
                detector.LosDetect(node, "BREAK");
                node.ShowData(msg);
            }
            else
            {
                node.ShowData(msg);
            }
        }

        this_thread::sleep_for(chrono::milliseconds(200));
    }
}
