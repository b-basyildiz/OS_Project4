#ifndef FCFS_ALGORITHM_HPP
#define FCFS_ALGORITHM_HPP

#include <memory>
#include "algorithms/scheduling_algorithm.hpp"
#include "utilities/stable_priority_queue/stable_priority_queue.hpp"
#include "utilities/fmt/format.h"

/*
    FCFSScheduler:
        A representation of a scheduling queue that uses first-come, first-served logic.
        
        This is a derived class from the base scheduling algorithm class.

        You are free to add any member functions or member variables that you
        feel are helpful for implementing the algorithm.
*/

class FCFSScheduler : public Scheduler {
public:

    //==================================================
    //  Member variables
    //==================================================

    // MY CODE
    Stable_Priority_Queue<std::shared_ptr<Thread>> queue; //queue of threads
    int order = 0; //integer time in quick a process comes into the queue 

    //==================================================
    //  Member functions
    //==================================================

    FCFSScheduler(int slice = -1);

    std::shared_ptr<SchedulingDecision> get_next_thread();

    void add_to_ready_queue(std::shared_ptr<Thread> thread);

    size_t size() const;

};

#endif
