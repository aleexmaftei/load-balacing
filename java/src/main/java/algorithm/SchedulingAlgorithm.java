package algorithm;

import model.Process;

import java.util.Comparator;
import java.util.List;

public interface SchedulingAlgorithm {
    void apply(List<Process> processes);

    default void display(List<Process> processes, float totalWaitingTime, float totalTurnAroundTime, double startTime, double endTime) {
        int maxLength = processes.stream()
                .max(Comparator.comparingInt(a -> a.getName().length())).orElseThrow()
                .getName().length();

        System.out.println("\nnames     | arrivals | durations | completion times | turn around times | waiting times | priorities");
        for (Process process : processes) {
            int space = maxLength - process.getName().length() + 6;
            String format = "%1s%" + space + "d%12d%16d%18d%18d%16d\n";
            System.out.format(format, process.getName(), process.getArrivalTime(), process.getDuration(),
                    process.getCompletionTime(), process.getTurnAroundTime(), process.getWaitingTime(), process.getPriority());
        }

        System.out.println("\nReal time: " + ((endTime - startTime) / 1000));
        System.out.println("Average waiting time: " + (totalWaitingTime / processes.size()));
        System.out.println("Average turnaround time: " + (totalTurnAroundTime / processes.size()));
    }
}
