package org.example.perfomance;


import org.example.sorter.SorterService;
import org.example.model.Person;

import org.knowm.xchart.CategoryChart;
import org.knowm.xchart.CategoryChartBuilder;
import org.knowm.xchart.SwingWrapper;

import java.util.*;

public class SortPerformanceTest {

    public static void main(String[] args) {
        SortPerformanceTester tester = new SortPerformanceTester();
        tester.runTestsAndPlotResults();
        tester.testAdditionalSorterFunctions();
    }
}

class SortPerformanceTester {

    private final List<String> filePaths = Arrays.asList(
            "data_10.txt",
            "data_100.txt",
            "data_1000.txt",
            "data_10000.txt"
    );

    private final List<String> algorithms = Arrays.asList("quick", "merge", "bubble", "insertion", "heap");

    public void runTestsAndPlotResults() {
        Map<String, List<Double>> results = new HashMap<>();

        for (String algorithm : algorithms) {
            System.out.println("Testing algorithm: " + algorithm);
            List<Double> times = new ArrayList<>();
            for (String filePath : filePaths) {
                System.out.println("File: " + filePath);
                try {
                    long startTime = System.currentTimeMillis();

                    double timeTaken = SorterService.sortByAgeAndGetTime(filePath, false, algorithm);

                    long endTime = System.currentTimeMillis();

                    times.add(timeTaken);
                    System.out.printf("Time taken: %.2f ms (Measured by service), Actual elapsed time: %d ms\n", timeTaken, (endTime - startTime));
                } catch (Exception e) {
                    System.err.println("Error while testing " + algorithm + " on file " + filePath + ": " + e.getMessage());
                    times.add(Double.NaN);
                }
            }
            results.put(algorithm, times);
            System.out.println();
        }

        plotResults(results);
    }

    public void testAdditionalSorterFunctions() {
        try {
            double timeTaken = SorterService.sortByAgeAndGetTime("data.json", true, "quick");
            System.out.println("Sorting by age took: " + timeTaken + " ms.");

            List<Person> sortedPersons = SorterService.getSortedByAge("data.json", true, "merge");
            System.out.println("Sorted persons:");
            for (Person person : sortedPersons) {
                System.out.println(person);
            }

            SorterService.sortByName("data.txt", false, "heap");
            System.out.println("Sorting by name completed.");

            SorterService.sortByAge("data.txt", false, "bubble");
            System.out.println("Sorting by age completed.");
        } catch (Exception e) {
            System.err.println("An error occurred: " + e.getMessage());
        }
    }

    private void plotResults(Map<String, List<Double>> results) {
        CategoryChart chart = new CategoryChartBuilder()
                .title("Sorting Performance")
                .xAxisTitle("File Size")
                .yAxisTitle("Time (ms)")
                .build();

        List<String> fileSizes = Arrays.asList("10", "100", "1000", "10000");

        for (Map.Entry<String, List<Double>> entry : results.entrySet()) {
            chart.addSeries(entry.getKey(), fileSizes, entry.getValue());
        }

        new SwingWrapper<>(chart).displayChart();
    }
}
