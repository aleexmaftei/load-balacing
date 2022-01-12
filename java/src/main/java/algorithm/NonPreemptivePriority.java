package algorithm;

import model.Process;

import java.util.*;

public class NonPreemptivePriority implements SchedulingAlgorithm {

    @Override
    public void apply(List<Process> processes) {
        boolean[] flags = new boolean[processes.size()];
        float totalWaitingTime = 0, totalTurnAroundTime = 0;
        List<Process> result = new LinkedList<>();
        int systemTime = 0, finishedProcesses = 0;

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

            if (process == null) {
                // there is no process to be executed at the current time => only increase the system time
                systemTime++;
                continue;
            } else {
                // mark the process as finished
                flags[processes.indexOf(process)] = true;
                finishedProcesses++;
            }

            systemTime += process.getDuration();
            process.setCompletionTime(systemTime);
            process.setTurnAroundTime(process.getCompletionTime() - process.getArrivalTime());
            process.setWaitingTime(process.getTurnAroundTime() - process.getDuration());

            totalTurnAroundTime += process.getTurnAroundTime();
            totalWaitingTime += process.getWaitingTime();

            result.add(process);
        }

        System.out.println("\n\n####### Priority Scheduling - Non-Preemptive #######");
        display(result, totalWaitingTime, totalTurnAroundTime);
    }

}
