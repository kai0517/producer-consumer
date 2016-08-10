#include "message.h"
#include <iostream>
#include <queue>
#include <random>
#include <chrono>
#include <thread>
#include <condition_variable>


std::queue<Message> g_mqueue;

std::mutex g_mmutex;
std::mutex g_exMtxProducer;
std::mutex g_exMtxConsumer;

std::condition_variable g_mcond;
std::condition_variable g_exCvProducer;
std::condition_variable g_exCvConsumer;

void consumer()
{
    std::unique_lock<std::mutex> exlock {g_exMtxConsumer};
    while (g_exCvConsumer.wait_for(exlock, std::chrono::seconds(1)) 
        == std::cv_status::timeout)
    {
        std::unique_lock<std::mutex> mlck {g_mmutex};
        g_mcond.wait(mlck);
        if (!g_mqueue.empty())
        {
            auto msg = g_mqueue.front();
            g_mqueue.pop();
            mlck.unlock();
            msg.Process();
        }
        else
        {
            mlck.unlock();
        }
    }
}

void producer()
{
    int idx = 0;
    
    auto die = std::bind(std::uniform_int_distribution<>{1,10000}, 
        std::default_random_engine{});

    std::unique_lock<std::mutex> exlock {g_exMtxProducer};
    while (g_exCvProducer.wait_for(exlock, std::chrono::seconds(1)) 
        == std::cv_status::timeout)
    {
        Message msg(idx, die());
        std::unique_lock<std::mutex> mlck {g_mmutex};
        g_mqueue.push(msg);
        g_mcond.notify_one();
        ++idx;
    }
}


int main(void)
{
    std::thread t1 { producer };
    std::thread t2 { consumer };

    while (true)
    {
        char ch;
        std::cin >> ch;
        if (ch == 'q' || ch == 'Q')
        {
            std::unique_lock<std::mutex> mlck {g_mmutex};
            g_mcond.notify_one();
            g_exCvConsumer.notify_one();
            g_exCvProducer.notify_one();
            break;
        }
    }

    t1.join();
    t2.join();

#if defined(_MSC_VER)
    system("pause");
#else
    std::cout << "\nPress [Enter] to continue ...";
    std::cin.get();
#endif
}
