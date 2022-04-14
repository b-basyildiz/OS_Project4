#include "algorithms/mlfq/mlfq_algorithm.hpp"

#include <cassert>
#include <stdexcept>

#define FMT_HEADER_ONLY
#include "utilities/fmt/format.h"

/*
    Here is where you should define the logic for the MLFQ algorithm.
*/

MFLQScheduler::MFLQScheduler(int slice) {
    if (slice != -1) {
        throw("MLFQ does NOT take a customizable time slice");
    }
}

std::shared_ptr<SchedulingDecision> MFLQScheduler::get_next_thread() {
        std::shared_ptr<SchedulingDecision> next(new SchedulingDecision);
        for(int i = 0; i < 10; ++i){
            if(n_queues[i].size() != 0 ){
                next->thread = n_queues[i].top(); 
                int time_slice = pow(2,i);
                next->time_slice = time_slice;
                next->explanation = "Selected from queue " + std::to_string(i) + " (priority = " + PROCESS_PRIORITY_MAP[next->thread->priority] + ", runtime = " + std::to_string(next->thread->current_accum) + "). Will run for at most " + std::to_string(time_slice) + " ticks.";  
                this->time_slice = time_slice;
                n_queues[i].pop();   
                return next;
            }
        }
        next->explanation = "No threads available for scheduling";
        return next;
}

void MFLQScheduler::add_to_ready_queue(std::shared_ptr<Thread> thread) {
    thread->current_accum += thread->service_time - thread->prev_service_time;
    thread->prev_service_time = thread->service_time;
    if(thread->current_accum >= pow(2,thread->queue_num)){
        thread->queue_num += 1;
        n_queues[thread->queue_num].push(thread->priority,std::move(thread)); 
        thread->current_accum = 0;
    }else{
        n_queues[thread->queue_num].push(thread->priority,std::move(thread)); 
    }
}

size_t MFLQScheduler::size() const {
        int size = 0;
        for(int i = 0; i < 10; ++i){
            size += n_queues[i].size();
        }
        return size; 
}
