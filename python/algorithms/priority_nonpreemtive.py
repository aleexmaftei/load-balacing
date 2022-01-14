def priority_nonpreemtive(processes):
    processes.sort(key=lambda process: process.arrival_time)
    processes.sort(key=lambda process: process.priority)

    total_waiting_time = 0
    total_burst_time = 0

    for index, process in enumerate(processes):
        if index == 0:
            process.waiting_time = 0
            process.turn_around_time = process.duration - process.arrival_time
            continue
        executing_process = processes[index - 1]

        process.wating_time = executing_process.arrival_time + executing_process.duration \
                              + executing_process.waiting_time - process.arrival_time

        process.turn_around_time = process.waiting_time + process.duration

        total_waiting_time += process.waiting_time
        print(process.waiting_time)
        total_burst_time += process.turn_around_time

    average_waiting_time = total_waiting_time / len(processes)
    average_turn_around_time = total_burst_time / len(processes)
    return average_waiting_time, average_turn_around_time
