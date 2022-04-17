#ifndef CFS_ALGORITHM_HPP
#define CFS_ALGORITHM_HPP

#include <map>
#include <memory>
#include "algorithms/scheduling_algorithm.hpp"
#include "utilities/stable_priority_queue/stable_priority_queue.hpp"

/*
    CFSScheduler:
        A 'Completely Fair Scheduler' that uses a variety of weights and 
        calculations to enumlate a uniform usage of threads
*/


using CFSQQueue = Stable_Priority_Queue<std::shared_ptr<Thread>>;

class CFSScheduler : public Scheduler {
public:
    
    //==================================================
    //  Member variables
    //==================================================

    // TODO: Add any member variables you may need.
    Stable_Priority_Queue<std::shared_ptr<Thread>> queue; //queue of threads
    int min_gran = 0;

    //==================================================
    //  Member functions
    //==================================================

    CFSScheduler(int slice = -1);

    std::shared_ptr<SchedulingDecision> get_next_thread();

    void add_to_ready_queue(std::shared_ptr<Thread> thread);

    size_t size() const;

};

#endif
