#include <iostream>
#include "Queue.h"

int main()
{
    Queue Q;
    std::cout << "-----Queue-----\n";
    for (unsigned i = 0; i < 5; ++i)
    {
        std::cout << "Queue push(" << i << ")\n";
        Q.Push(i);
    }
    Queue copy(Q);
    for (unsigned i = 0; i < 5; ++i)
    {
        std::cout << "Queue pop - " << Q.Pop() << '\n';
    }
    for (unsigned i = 0; i < 5; ++i)
    {
        std::cout << "Queue copy pop - " << copy.Pop() << '\n';
    }
    std::cout << "-----PriorityQueue-----\n";
    const unsigned maxPriority = 3;
    PriorityQueue PQ(maxPriority);
    for (unsigned i = 0; i < 5; ++i)
    {
        int priority = std::rand() % maxPriority;
        std::cout << "PriorityQueue push(" << i << ") priority - " << priority << '\n';
        PQ.Push(i, priority);
    }
    for (unsigned i = 0; i < 5; ++i)
    {
        std::cout << "PriorityQueue pop - " << PQ.Pop() << '\n';
    }
}

//../Queue/x64/Debug/Queue.obj