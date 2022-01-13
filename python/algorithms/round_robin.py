def round_robin(processes):
    processes.sort(key=lambda process: process.arrival_time)

    # quantum = int(input("Introduce quantum: "))
    quantum = 2

    for process in processes:
        process.remaining_duration = process.duration

    currernt_time = 0
    while(True):
        round_robin_completed = True

        for process in processes:
            if process.remaining_duration > 0:
                round_robin_completed = False

                if process.remaining_duration > quantum:
                    currernt_time += quantum
                    process.remaining_duration -= quantum
                else:
                    currernt_time += process.remaining_duration
                    process.waiting_time = currernt_time - process.duration
                    process.turn_around_time = process.waiting_time + process.duration
                    process.remaining_duration = 0
                    
        if round_robin_completed:
            break
    
    return sum(process.waiting_time for process in processes), sum(process.turn_around_time for process in processes)