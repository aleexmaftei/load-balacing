from os import path
from model.Process import Process

basepath = path.dirname(__file__)
route = basepath + "/data/data_50.txt"

def read_file():
    processes = []
    file = open("/home/alex/Desktop/load-balacing/data/data_50.txt", "r")
    for index, line in enumerate(file):
        if index != 0:
            line = line.split(",")
            processes.append(Process(line[0],int(line[1]),int(line[2]),int(line[3])))
    return processes
    
def main():
    processes = read_file()
    fcfs(processes)

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

        total_waiting_time = process.waiting_time
        total_turn_around_time = process.turn_around_time

    print(f'Average waiting time = {total_waiting_time/len(processes)}')
    print(f'Average turn around time = {total_turn_around_time/len(processes)}')

main()

