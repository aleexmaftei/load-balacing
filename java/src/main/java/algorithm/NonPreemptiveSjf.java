package algorithm;

import model.Process;

import java.util.List;

public class NonPreemptiveSjf implements SchedulingAlgorithm {

    @Override
    public void apply(List<Process> processes) {
        boolean[] flags = new boolean[processes.size()];
        int systemTime = 0, finishedProcesses = 0;
        float totalWaitingTime = 0, totalTurnAroundTime = 0;

        while (true) {
            int processIndex = processes.size(), min = Integer.MAX_VALUE;

            // all processes are finished => stop
            if (finishedProcesses == processes.size()) {
                break;
            }

            for (int i = 0; i < processes.size(); i++) {
                Process process = processes.get(i);

                // i'th process arrival time <= system time and flag == false and duration < min => executed first
                if (process.getArrivalTime() <= systemTime && !flags[i] && process.getDuration() < min) {
                    min = process.getDuration();
                    processIndex = i;
                }
            }

            // processIndex == n => no process arrival time < system time, so we just increase the system time
            if (processIndex == processes.size()) {
                systemTime++;
            } else {
                Process process = processes.get(processIndex);
                process.setCompletionTime(systemTime + process.getDuration());
                systemTime += process.getDuration();
                process.setTurnAroundTime(process.getCompletionTime() - process.getArrivalTime());
                process.setWaitingTime(process.getTurnAroundTime() - process.getDuration());
                flags[processIndex] = true;
                finishedProcesses++;
            }
        }

        for (Process process : processes) {
            totalWaitingTime += process.getWaitingTime();
            totalTurnAroundTime += process.getTurnAroundTime();
        }

        System.out.println("\n\n####### Shortest Job First (SJF) - Non-Preemptive #######");
        display(processes, totalWaitingTime, totalTurnAroundTime);
    }
}
