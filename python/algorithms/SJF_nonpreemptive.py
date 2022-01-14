def SJF_nonpreemptive(processes):
    flags = [False] * len(processes)
    system_time = 0
    completed_processes = 0
    
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
            process.completion_time = system_time + process.duration
            system_time = process.duration
            
            flags[process_index] = True
            completed_processes += 1

    for index,process in enumerate(processes):
        process.turn_around_time = process.completion_time - process.arrival_time
        process.waiting_time = process.turn_around_time - process.duration

    return sum(process.waiting_time for process in processes), sum(process.turn_around_time for process in processes)