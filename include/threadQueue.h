#ifndef THREADQUEUE_H
#define THREADQUEUE_H

#include <queue>
#include <thread>
#include <mutex>
#include <condition_variable>
#include "fillMap.h"
class threadQueue
{
    public:
        threadQueue();
        virtual ~threadQueue();
        fillMap::structAnswer pop();
        void pop(fillMap::structAnswer& item);
        void push(const fillMap::structAnswer& item);
        void push(fillMap::structAnswer&& item);
        std::queue<fillMap::structAnswer> queue_;
        std::mutex mutex_;
        std::condition_variable cond_;
    protected:
    private:



};

#endif // THREADQUEUE_H
