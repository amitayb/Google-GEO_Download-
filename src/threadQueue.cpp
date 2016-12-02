#include "threadQueue.h"

threadQueue::threadQueue()
{
    //ctor

        //threadQueue::queue_();
        //threadQueue::mutex_();
        //threadQueue::cond_();
}

threadQueue::~threadQueue()
{
    //dtor
}
fillMap::structAnswer threadQueue::pop()
  {
    std::unique_lock<std::mutex> mlock(mutex_);
    while (queue_.empty())
    {
      cond_.wait(mlock);
    }
    auto item = queue_.front();
    queue_.pop();
    return item;
  }

void threadQueue::pop(fillMap::structAnswer& item)
  {
    std::unique_lock<std::mutex> mlock(mutex_);
    while (queue_.empty())
    {
      cond_.wait(mlock);
    }
    item = queue_.front();
    queue_.pop();
  }

  void threadQueue::push(const fillMap::structAnswer& item)
  {
    std::unique_lock<std::mutex> mlock(mutex_);
    queue_.push(item);
    mlock.unlock();
    cond_.notify_one();
  }

  void threadQueue::push(fillMap::structAnswer&& item)
  {
    std::unique_lock<std::mutex> mlock(mutex_);
    queue_.push(std::move(item));
    mlock.unlock();
    cond_.notify_one();
  }
