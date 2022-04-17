#include "algorithms/cfs/cfs_algorithm.hpp"

#include <cassert>
#include <stdexcept>

#define FMT_HEADER_ONLY
#include "utilities/fmt/format.h"

/*
    Here is where you should define the logic for the MLFQ algorithm.
*/

CFSScheduler::CFSScheduler(int min_granularity) {
    if(min_granularity < 0){
        throw("Error: Minimum Granularity must be positive and nonzero!");
    }else{
        this->min_gran = min_granularity;
    }
}

std::shared_ptr<SchedulingDecision> CFSScheduler::get_next_thread() {
        std::shared_ptr<SchedulingDecision> next(new SchedulingDecision);
        for(int i = 0; i < 10; ++i){
            if(n_queues[i].size() != 0 ){
                next->thread = n_queues[i].top(); 
                int time_slice = pow(2,i);
                next->time_slice = time_slice;
                next->explanation = "Selected from queue " ;  
                this->time_slice = time_slice;
                n_queues[i].pop();   
                return next;
            }
        }
        next->explanation = "No threads available for scheduling";
        return next;
}

void CFSScheduler::add_to_ready_queue(std::shared_ptr<Thread> thread) {
    queue.push(thread->vruntime, std::move(thread)); 
}

size_t CFSScheduler::size() const {
    return this->queue.size();
}
