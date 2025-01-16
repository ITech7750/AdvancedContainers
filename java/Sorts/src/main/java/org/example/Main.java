package org.example;

import org.example.sorter.SorterService;

import java.util.ArrayList;
import java.util.List;

public class Main {
    public static void main(String[] args) {
        List<Integer> inputData = new ArrayList<>();
        inputData.add(5);
        inputData.add(2);
        inputData.add(8);
        inputData.add(1);
        inputData.add(3);

        String algorithm = "bubble"; // Выберите алгоритм

        ArrayList<ArrayList<Integer>> steps = SorterService.sortStepByStep(inputData, algorithm);

        System.out.println("Steps during sorting:");
        for (int i = 0; i < steps.size(); i++) {
            System.out.println("Step " + (i + 1) + ": " + steps.get(i));
        }
    }
}
