#include "algorithms/spn/spn_algorithm.hpp"

#include <cassert>
#include <stdexcept>

#define FMT_HEADER_ONLY
#include "utilities/fmt/format.h"
#include "types/enums.hpp"
#include <string>
#include <sstream>

/*
    Here is where you should define the logic for the SPN algorithm.
*/

SPNScheduler::SPNScheduler(int slice) {
    if (slice != -1) {
        throw("SPN must have a timeslice of -1");
    }
}

std::shared_ptr<SchedulingDecision> SPNScheduler::get_next_thread() {
    std::shared_ptr<SchedulingDecision> next(new SchedulingDecision);
    if(queue.size() != 0){
        next->thread = queue.top(); 
        next->explanation = next->explanation = "Selected from " + std::to_string(queue.size()) + " threads. Will run to completion of burst.";
        queue.pop();
        return next; 
    }
    else{
        next->explanation = "No threads available for scheduling";
        return next;
    }
}

void SPNScheduler::add_to_ready_queue(std::shared_ptr<Thread> thread) {
    int time = thread->service_time + thread->io_time;
    queue.push(time,thread); 
}

size_t SPNScheduler::size() const {
    return queue.size();
}
