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
    if(queue.size() != 0){
        std::shared_ptr<SchedulingDecision> next; 
        next->thread = queue.top(); 
        std::ostringstream oss;
        oss << "Selected from " << queue.size() << " threads. Will run to completion of burst.";
        next->explanation = oss.str();
        return next; 
    }
    else{
        throw("No threads available for scheduling"); 
    }
}

void SPNScheduler::add_to_ready_queue(std::shared_ptr<Thread> thread) {
    int burst_time = thread->get_next_burst(CPU)->burst_type;
    queue.push(burst_time,thread); 
}

size_t SPNScheduler::size() const {
    //TODo: Implement me
    return 0;
}
