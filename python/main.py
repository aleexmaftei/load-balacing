from os import path
from model.Process import Process
from algorithms.fcfs import *
from algorithms.round_robin import *
from display import display
from algorithms.priority_preemtive import *
from algorithms.priority_nonpreemtive import *
from algorithms.SJF_nonpreemptive import *
from algorithms.SJF_preemptive import *

def read_file(file_path):
    processes = []
    
    basepath = path.dirname(__file__)
    basepath = basepath[:basepath.find('/python')]
    route = basepath + file_path
    file = open(route, "r")

    for index, line in enumerate(file):
        if index != 0:
            line = line.split(",")
            processes.append(Process(line[0],int(line[1]),int(line[2]),int(line[3])))
    return processes

def main():
    processes = []
    data_loaded = False
    while True:
        print("0. Select data file")
        print("1. FCFS")
        print("2. Round robin")
        print("3. Priority nonpreemtive")
        print("4. Priority preemtive")
        print("5. SJF - non preemptive")
        print("6. SJF - preemptive")

        choice = input()

        if choice=="0":
            print("1. 50 processes")
            print("2. 500 processes")
            print("3. 1000 processes")
            print("4. EXIT")

            data_choice = (input())
            if data_choice == "1":
                data_loaded = True
                processes = []
                processes = read_file("/data/data_50.txt")

            elif data_choice == "2":
                data_loaded = True
                processes = []
                processes = read_file("/data/data_500.txt")

            elif data_choice == "3":
                data_loaded = True
                processes = []
                processes = read_file("/data/data_1000.txt")
            else:
                pass
        
        if choice == "1":
            if data_loaded == True:
                total_waiting_time, total_turn_around_time = fcfs(processes)
                display(total_waiting_time, total_turn_around_time, len(processes))
            else:
                print("Please select data file first!")

        if choice == "2":
            if data_loaded == True:
                total_waiting_time, total_turn_around_time = round_robin(processes)
                display(total_waiting_time, total_turn_around_time, len(processes))
            else:
                print("Please select data file first!")

        if choice == "3":
            if data_loaded == True:
                total_waiting_time, total_turn_around_time = priority_nonpreemtive(processes)
                display(total_waiting_time, total_turn_around_time, len(processes))
            else:
                print("Please select data file first!")

        if choice == "4":
            if data_loaded == True:
                total_waiting_time, total_turn_around_time = priority_preemtive(processes)
                display(total_waiting_time, total_turn_around_time, len(processes))
            else:
                print("Please select data file first!")

        if choice=="5":
            if data_loaded == True:
                total_waiting_time, total_turn_around_time = SJF_nonpreemptive(processes)
                display(total_waiting_time, total_turn_around_time, len(processes))
            else:
                print("Please select data file first!")

        if choice=="6":
            if data_loaded == True:
                total_waiting_time, total_turn_around_time = SJF_preemptive(processes)
                display(total_waiting_time, total_turn_around_time, len(processes))
            else:
                print("Please select data file first!")

main()