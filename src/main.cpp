#include <iostream>

#include "RtMidi.h"
#include <isocline.h>
#include <queue>
#include <string>
#include <thread>
#include <chrono>

std::queue<std::string> messages;
std::mutex messageMutex;


void runMidiThread()
{
    using namespace std::chrono_literals;
    auto midiout = std::make_unique<RtMidiOut>();
    unsigned int nPorts = midiout->getPortCount();
    std::cout << "\nThere are " << nPorts << " MIDI output ports available. Picking 0\n";

    std::string portName = midiout->getPortName(0);
    std::cout << "  Sending : " << portName << '\n';
    midiout->openPort(0);

    while(true)
    {
        std::string msg {};
        int count{0};
        {
            std::lock_guard<std::mutex> g(messageMutex);
            if (!messages.empty())
            {
                msg = messages.back();
                messages.pop();
                count = messages.size();
            }
        }

        if (msg == "quit")
        {
            std::cout << "BYEE" << std::endl;
            return;
        }
        if (msg[0] == '>')
        {
            auto n = std::atoi(msg.c_str() + 1);
            unsigned char mm[4];
            mm[0] = 0x90;
            mm[1] = n;
            mm[2] = 90;
            midiout->sendMessage(mm, 3);
        }
        if (msg[0] == '<')
        {
            auto n = std::atoi(msg.c_str() + 1);
            unsigned char mm[4];
            mm[0] = 0x80;
            mm[1] = n;
            mm[2] = 90;
            midiout->sendMessage(mm, 3);
        }

        if (!msg.empty())
            std::cout << "THREAD " << msg << std::endl;

        if (!count)
            std::this_thread::sleep_for(1ms);
    }
}

int main(int, char **)
{
    std::thread t(runMidiThread);

    ic_set_history(nullptr, -1 /* default entries (= 200) */);
    char *input;
    while ((input = ic_readline("prompt")) != nullptr)
    {
        {
            std::lock_guard<std::mutex> g(messageMutex);
            messages.push(std::string(input));
        };
        if (std::string(input) == "quit" )
        {
            t.join();
            return 0;
        }
        free(input);
    }

    {
        std::lock_guard<std::mutex> g(messageMutex);
        messages.push("quit");
    }

    t.join();
    return 0;
}
