def fcfs(processes):
    processes.sort(key=lambda process: process.arrival_time)

    for index, process in enumerate(processes):
        if index == 0:
            process.completion_time = process.arrival_time + process.duration
        else:
            if process.arrival_time > processes[index-1].completion_time:
                process.completion_time = process.arrival_time + process.duration
            else:
                process.completion_time = processes[index-1].completion_time + process.duration 

        process.turn_around_time = process.completion_time - process.arrival_time
        process.waiting_time = process.turn_around_time - process.duration


    return sum(processes, lambda x: x.waiting_time), sum(processes, lambda x: x.turn_around_time)