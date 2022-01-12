package algorithm;

import model.Process;

import java.util.Comparator;
import java.util.List;

public class Fcfs implements SchedulingAlgorithm {

    @Override
    public void apply(List<Process> givenProcesses) {
        float totalWaitingTime = 0, totalTurnAroundTime = 0;
        List<Process> processes = givenProcesses.stream()
                .sorted(Comparator.comparingInt(Process::getArrivalTime))
                .toList();

        // find completion times
        for (Process process : processes) {
            int index = processes.indexOf(process);
            if (index == 0) {
                process.setCompletionTime(process.getArrivalTime() + process.getDuration());
            } else {
                if (process.getArrivalTime() > processes.get(index - 1).getCompletionTime()) {
                    process.setCompletionTime(process.getArrivalTime() + process.getDuration());
                } else {
                    process.setCompletionTime(processes.get(index - 1).getCompletionTime() + process.getDuration());
                }
            }

            process.setTurnAroundTime(process.getCompletionTime() - process.getArrivalTime());
            process.setWaitingTime(process.getTurnAroundTime() - process.getDuration());
            totalWaitingTime += process.getWaitingTime();
            totalTurnAroundTime += process.getTurnAroundTime();
        }

        System.out.println("\n\n####### First Come First Serve (FCFS) #######");
        display(processes, totalWaitingTime, totalTurnAroundTime);
    }
}
