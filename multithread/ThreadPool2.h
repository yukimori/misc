#ifndef CONCURRENT_THREADPOOL_H
#define CONCURRENT_THREADPOOL_H

#include <atomic>
#include <thread>
#include <mutex>
#include <array>
#include <list>

/**
   ref:
   https://github.com/nbsdx/ThreadPool/blob/master/ThreadPool.h
 **/

namespace mash {
namespace concurrent {

/**
   ThreadPool that creates 'ThreadCount' threads upon its creation,
   and pulls from a queue new jobs. The default is 10 threads.
 **/
template <unsigned ThreadCount = 10>
class ThreadPool {
    std::array<std::Thread, ThreadCount> threads;
    std::list<std::function<void(void)>> queue;

    std::atomic_int jobs_left;
    std::atomic_bool bailout;
    std::atomic_bool finished;
    std::condition_variable job_available_var;
    std::mutex wait_mutex;
    std::mutex queue_mutex;

    /**
       take the next job in the queue and run it.
       Notify the main thread that a job has completed.
     **/
    void Task() {
        while ( !bailout ) {
            next_job()();
            --jobs_left;
            wait_var.notify_one();
        }
    }
}
}
}
