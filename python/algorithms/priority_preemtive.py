import sys


def priority_preemtive(processes):
    processes.sort(key=lambda process: process.arrival_time)
    processes.sort(key=lambda process: process.priority)

    total_waiting_time = 0
    total_turn_around_time = 0
    total_burst_time = sum(process.duration for process in processes)
# TODO: WHY IS WAITING TIME ALWAYS 0.0
    finished_processes = [False] * len(processes)
    i=0
    for time in range(0, total_burst_time):
        if (processes[i].duration > 0) & (processes[i].arrival_time <= time):
            processes[i].duration -= 1

        if processes[i].duration <= 0 & (not finished_processes[i]):

            processes[i].wating_time = time + 1 - processes[i].duration - processes[i].arrival_time
            processes[i].turn_around_time = time + 1 + processes[i].duration
            total_waiting_time += processes[i].waiting_time
            total_turn_around_time += processes[i].turn_around_time
        min_priority = sys.maxsize
        for index, process in enumerate(processes):
            if process.arrival_time <= time + 1 & (not finished_processes[index]):
                if min_priority > processes[i].priority:
                    min_priority = processes[index].priority
                    i = index

    average_waiting_time = total_waiting_time / len(processes)
    average_turn_around_time = total_burst_time / len(processes)
    return average_waiting_time, average_turn_around_time
