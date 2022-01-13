package algorithm;

import model.Process;

import java.util.Date;
import java.util.List;

public class PreemptivePriority implements SchedulingAlgorithm {
    @Override
    public void apply(List<Process> processes) {
        double startTime = new Date().getTime();

        int[] durationsCopy = new int[processes.size()];
        boolean[] flags = new boolean[processes.size()];
        float totalWaitingTime = 0, totalTurnAroundTime = 0;
        int systemTime = 0, finishedProcesses = 0;

        for (int i = 0; i < processes.size(); i++) {
            durationsCopy[i] = processes.get(i).getDuration();
        }

        // iterate until there is no process to be completed
        while (finishedProcesses < processes.size()) {
            Process process = null;
            int priority = Integer.MAX_VALUE;

            // arrival time <= system time and highest priority => executed next
            for (Process currentProcess : processes) {
                if (currentProcess.getArrivalTime() <= systemTime
                        && !flags[processes.indexOf(currentProcess)] && currentProcess.getPriority() < priority) {
                    priority = currentProcess.getPriority();
                    process = currentProcess;
                }
            }

            systemTime++;

            if (process != null) {
                process.setDuration(process.getDuration() - 1);

                // mark the process as finished
                if (process.getDuration() == 0) {
                    flags[processes.indexOf(process)] = true;
                    finishedProcesses++;
                    process.setCompletionTime(systemTime);
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

        System.out.println("\n\n####### Priority Scheduling - Preemptive #######");
        display(processes, totalWaitingTime, totalTurnAroundTime, startTime, new Date().getTime());
    }
}
