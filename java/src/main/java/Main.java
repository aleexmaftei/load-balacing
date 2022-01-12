import algorithm.*;
import model.Process;

import java.io.File;
import java.io.FileNotFoundException;
import java.util.ArrayList;
import java.util.List;
import java.util.Scanner;

public class Main {
    public static void main(String[] args) throws FileNotFoundException {
        Scanner sc = new Scanner(new File("src/main/resources/processes.txt"));
        int numberOfProcesses = sc.nextInt();
        List<Process> processes = new ArrayList<>();

        for (int i = 0; i < numberOfProcesses; i++) {
            Process process = new Process();
            process.setName(sc.next());
            process.setArrivalTime(sc.nextInt());
            process.setDuration(sc.nextInt());
            process.setPriority(sc.nextInt());

            processes.add(process);
        }
        sc.close();

        List<SchedulingAlgorithm> algorithms =
                List.of(new Fcfs(), new NonPreemptivePriority(), new NonPreemptiveSjf(), new PreemptiveSjf());

        for (SchedulingAlgorithm algorithm : algorithms) {
            algorithm.apply(deepCopy(processes));
        }
    }

    private static List<Process> deepCopy(List<Process> processes) {
        List<Process> processesCopy = new ArrayList<>();

        for (var process : processes) {
            Process processCopy = new Process();
            processCopy.setName(process.getName());
            processCopy.setArrivalTime(process.getArrivalTime());
            processCopy.setDuration(process.getDuration());
            processCopy.setPriority(process.getPriority());

            processesCopy.add(processCopy);
        }

        return processesCopy;
    }
}