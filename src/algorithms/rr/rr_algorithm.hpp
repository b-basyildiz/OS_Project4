#ifndef RR_ALGORITHM_HPP
#define RR_ALGORITHM_HPP

#include <memory>
#include <queue>
#include <stdexcept>
#include "algorithms/scheduling_algorithm.hpp"
#include "utilities/stable_priority_queue/stable_priority_queue.hpp"

/*
    RRScheduler:
        A representation of a round robin scheduling algorithm.

        This is a derived class from the base scheduling algorithm class.

        You are free to add any member functions or member variables that you
        feel are helpful for implementing the algorithm.
*/

class RRScheduler : public Scheduler {
public:

    //==================================================
    //  Member variables
    //==================================================

    // MY CODE
    Stable_Priority_Queue<std::shared_ptr<Thread>> queue; //queue of threads
    int order = 0; 

    //==================================================
    //  Member functions
    //==================================================

    RRScheduler(int slice = 3);

    std::shared_ptr<SchedulingDecision> get_next_thread();

    void add_to_ready_queue(std::shared_ptr<Thread> thread);

    size_t size() const;
};

#endif