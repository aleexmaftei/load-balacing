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
            for (int i = 0; i < processes.size(); i++) {
                if (processes.get(i).getArrivalTime() > systemTime) {
                    systemTime++;
                    continue;
                }

                if (remainingDuration[i] > 0) {
                    if (remainingDuration[i] > quantumTime) {
                        remainingDuration[i] -= quantumTime;
                        systemTime += quantumTime;
                        for (int j = 0; j < processes.size(); j++) {
                            if (j != i && remainingDuration[j] != 0) {
                                processes.get(j).setWaitingTime(processes.get(j).getWaitingTime() + quantumTime);
                            }
                        }
                    } else {
                        systemTime += remainingDuration[i];
                        processes.get(i).setCompletionTime(systemTime);
                        for( int j = 0; j < processes.size(); j++) {
                            if (j != i && remainingDuration[j] != 0) {
                                processes.get(j)
                                        .setWaitingTime(processes.get(j).getWaitingTime() + remainingDuration[i]);
                            }
                        }
                        remainingDuration[i] = 0;
                    }
                }
            }
            sum = 0;
            for (int k = 0; k < processes.size(); k++) {
                sum += remainingDuration[k];
            }
        } while (sum !=0);

        for (Process process : processes) {
            process.setTurnAroundTime(process.getWaitingTime() + process.getArrivalTime());
            totalWaitingTime += process.getWaitingTime();
            totalTurnAroundTime += process.getTurnAroundTime();
        }

        System.out.println("\n\n####### Round Robin #######");
        display(processes, totalWaitingTime, totalTurnAroundTime, startTime, new Date().getTime());
    }
}
