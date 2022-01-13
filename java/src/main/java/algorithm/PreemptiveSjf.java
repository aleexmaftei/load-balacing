package algorithm;

import model.Process;

import java.util.Date;
import java.util.List;

public class PreemptiveSjf implements SchedulingAlgorithm {

    @Override
    public void apply(List<Process> processes) {
        double startTime = new Date().getTime();

        boolean[] flags = new boolean[processes.size()];
        int[] durationsCopy = new int[processes.size()];
        int systemTime = 0, completedProcesses = 0;
        float totalWaitingTime = 0, totalTurnAroundTime = 0;

        for (int i = 0; i < processes.size(); i++) {
            durationsCopy[i] = processes.get(i).getDuration();
        }

        while (true) {
            int min = Integer.MAX_VALUE, processIndex = processes.size();

            // all processes are finished => stop
            if (completedProcesses == processes.size()) {
                break;
            }

            for (int i = 0; i < processes.size(); i++) {
                Process process = processes.get(i);

                if (process.getArrivalTime() <= systemTime && !flags[i] && process.getDuration() < min) {
                    processIndex = i;
                    min = process.getDuration();
                }
            }

            // processIndex == n => no process arrival time < system time, so we just increase the system time
            if (processIndex == processes.size()) {
                systemTime++;
            } else {
                Process process = processes.get(processIndex);
                process.setDuration(process.getDuration() - 1);
                systemTime++;
                if (process.getDuration() == 0) {
                    process.setCompletionTime(systemTime);
                    flags[processIndex] = true;
                    completedProcesses++;
                }
            }
        }

        for (Process process : processes) {
            process.setTurnAroundTime(process.getCompletionTime() - process.getArrivalTime());
            process.setWaitingTime(process.getTurnAroundTime() - durationsCopy[processes.indexOf(process)]);
            process.setDuration(durationsCopy[processes.indexOf(process)]);
            totalWaitingTime += process.getWaitingTime();
            totalTurnAroundTime += process.getTurnAroundTime();
        }

        System.out.println("\n\n####### Shortest Job First (SJF) - Preemptive #######");
        display(processes, totalWaitingTime, totalTurnAroundTime, startTime, new Date().getTime());
    }
}
