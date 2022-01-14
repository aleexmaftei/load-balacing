def SJF_preemptive(processes):
    flags = [False] * len(processes)
    duration_copy = []
    system_time = 0
    completed_processes = 0
    
    for index, process in enumerate(processes):
        duration_copy.append(process.duration)

    while True:
        min = 9999999
        process_index = len(processes)
        if completed_processes == len(processes):
            break

        for index, process in enumerate(processes):
            if process.arrival_time <= system_time and not flags[index] and process.duration < min:
                process_index = index
                min = process.duration

        if process_index == len(processes):
            system_time += 1
        else:
            process = processes[process_index]
            process.duration -= 1
            system_time+= 1

            if process.duration ==0:
                process.completion_time = system_time
                flags[process_index] = True
                completed_processes+= 1

    for index,process in enumerate(processes):
        process.turn_around_time = process.completion_time - process.arrival_time
        process.waiting_time = process.turn_around_time - duration_copy[index]

    return sum(process.waiting_time for process in processes), sum(process.turn_around_time for process in processes)