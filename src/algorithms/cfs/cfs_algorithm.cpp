#include "algorithms/cfs/cfs_algorithm.hpp"

#include <cassert>
#include <stdexcept>

#define FMT_HEADER_ONLY
#include "utilities/fmt/format.h"

/*
    Here is where you should define the logic for the MLFQ algorithm.
*/

CFSScheduler::CFSScheduler(int slice) {
    if(slice < 0){
        this->min_gran = 3;
        this->time_slice = 3; 
    }else{
        this->min_gran = slice;
        this->time_slice = slice; 
    }
}

std::shared_ptr<SchedulingDecision> CFSScheduler::get_next_thread() {
        std::shared_ptr<SchedulingDecision> next(new SchedulingDecision);
        if(queue.size() != 0){
            next->thread = queue.top();
            float sl = 48/float(queue.size());
            int ts = next->thread->weight/float(weight_sum) * sl;
            if(ts < this->min_gran){
                ts = this->min_gran;
            }
            next->time_slice = ts;
            this->time_slice = ts;
            next->explanation = "Selected from " + std::to_string(queue.size()) + " threads (vruntime = " + std::to_string(next->thread->vruntime) + "). Will run for at most " + std::to_string(this->time_slice) + " ticks.";
            queue.pop();
            this->weight_sum -= next->thread->weight; 
            return next;
        }else{
            next->explanation = "No threads available for scheduling";
            return next;
        }
}

void CFSScheduler::add_to_ready_queue(std::shared_ptr<Thread> thread) {
        switch (thread->priority)
        {
        case SYSTEM:
            thread->weight = 88761;
            break;
        case INTERACTIVE:
            thread->weight = 29154;
            break;
        case NORMAL:
            thread->weight = 1024;
            break;
        case BATCH:
            thread->weight = 15;
            break;
        }
        if(thread->current_state == READY){
            weight_sum += thread->weight; 
        }
        thread->vruntime = 1024/float(thread->weight) * thread->service_time; 
        queue.push(thread->vruntime, std::move(thread)); 
}

size_t CFSScheduler::size() const {
    return this->queue.size();
}
