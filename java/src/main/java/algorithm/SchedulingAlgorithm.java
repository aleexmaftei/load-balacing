package algorithm;

import model.Process;

import java.util.List;

public interface SchedulingAlgorithm {
    void apply(List<Process> processes);

    default void display(List<Process> processes, float totalWaitingTime, float totalTurnAroundTime) {
        System.out.println("\nnames | arrivals | durations | completion times | turn around times | waiting times | priorities");
        for (Process process : processes) {
            System.out.format("%1s%8d%10d%16d%18d%18d%16d\n", process.getName(), process.getArrivalTime(), process.getDuration(),
                    process.getCompletionTime(), process.getTurnAroundTime(), process.getWaitingTime(), process.getPriority());
        }

        System.out.println("\nAverage waiting time: " + (totalWaitingTime / processes.size()));
        System.out.println("Average turnaround time: " + (totalTurnAroundTime / processes.size()));
    }
}
