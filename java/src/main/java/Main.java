import algorithm.*;
import model.Process;

import java.io.*;
import java.nio.charset.StandardCharsets;
import java.util.ArrayList;
import java.util.List;

public class Main {
    public static void main(String[] args) throws IOException {
        String fileName = "src/main/resources/data_1000.txt";//"src/main/resources/processes.txt";
        int numberOfProcesses;
        List<Process> processes = new ArrayList<>();

        try(BufferedReader br = new BufferedReader(
                new InputStreamReader(new FileInputStream(fileName), StandardCharsets.UTF_8))) {
            numberOfProcesses = Integer.parseInt(br.readLine());
            for (int i = 0; i < numberOfProcesses; i++) {
                String[] split = br.readLine().split(",");
                Process process = new Process();
                process.setName(split[0]);
                process.setDuration(Integer.parseInt(split[1]));
                process.setArrivalTime(Integer.parseInt(split[2]));
                process.setPriority(Integer.parseInt(split[3]));

                processes.add(process);
            }
        }

        List<SchedulingAlgorithm> algorithms = List.of(new Fcfs(), new NonPreemptivePriority(), new NonPreemptiveSjf(),
                new PreemptivePriority(), new PreemptiveSjf(), new RoundRobin());

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