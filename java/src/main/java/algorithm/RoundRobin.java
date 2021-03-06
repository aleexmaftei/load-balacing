package algorithm;

import model.Process;

import java.util.Comparator;
import java.util.Date;
import java.util.List;

public class RoundRobin implements SchedulingAlgorithm {

    @Override
    public void apply(List<Process> givenProcesses) {
        double startTime = new Date().getTime();

        float totalWaitingTime = 0, totalTurnAroundTime = 0;
        int systemTime = 0, sum, quantumTime = 2;
        int[] remainingDuration = new int[givenProcesses.size()];

        List<Process> processes = givenProcesses.stream()
                .sorted(Comparator.comparingInt(Process::getArrivalTime))
                .toList();

        for (int i = 0; i < processes.size(); i++) {
            remainingDuration[i] = processes.get(i).getDuration();
        }

        do {
            boolean found = false;
            for (int i = 0; i < processes.size(); i++) {
                if (processes.get(i).getArrivalTime() > systemTime) {
                    continue;
                }
                found = true;

                if (remainingDuration[i] > 0) {
                    if (remainingDuration[i] > quantumTime) {
                        remainingDuration[i] -= quantumTime;
                        systemTime += quantumTime;
                    } else {
                        systemTime += remainingDuration[i];
                        processes.get(i).setCompletionTime(systemTime);
                        remainingDuration[i] = 0;
                    }
                }
            }

            if (!found) {
                systemTime++;
            }

            sum = 0;
            for (int k = 0; k < processes.size(); k++) {
                sum += remainingDuration[k];
            }
        } while (sum != 0);

        for (Process process : processes) {
            process.setWaitingTime(process.getCompletionTime() - process.getDuration() - process.getArrivalTime());
            process.setTurnAroundTime(process.getCompletionTime() - process.getArrivalTime());
            totalWaitingTime += process.getWaitingTime();
            totalTurnAroundTime += process.getTurnAroundTime();
        }

        System.out.println("\n\n####### Round Robin #######");
        display(processes, totalWaitingTime, totalTurnAroundTime, startTime, new Date().getTime());
    }
}
