package ui;

import nativelib.NativeGistogram;
import org.knowm.xchart.CategoryChart;
import org.knowm.xchart.CategoryChartBuilder;
import org.knowm.xchart.SwingWrapper;

import java.util.ArrayList;
import java.util.List;
import java.util.Map;
import java.util.stream.Collectors;

public class GistogramExample {
    public static void main(String[] args) {
        NativeGistogram gistogram = new NativeGistogram();

        // Добавление данных
        gistogram.addData(10);
        gistogram.addData(20);
        gistogram.addData(10);
        gistogram.addData(30);
        gistogram.addData(20);
        gistogram.addData(10);

        // Получение наиболее часто встречающегося значения
        int mostFrequent = gistogram.getMostFrequent();
        System.out.println("Most Frequent Value: " + mostFrequent);

        // Подсчет значений в диапазоне
        int countInRange = gistogram.countInRange(10, 20);
        System.out.println("Count in Range [10, 20]: " + countInRange);

        // Данные для построения гистограммы
        List<Integer> data = List.of(10, 20, 10, 30, 20, 10); // Примерные данные (могут быть получены через JNI)

        // Построение графика
        createHistogram(data);
    }

    private static void createHistogram(List<Integer> data) {
        // Подсчет частот
        Map<Integer, Long> frequencyMap = data.stream()
                .collect(Collectors.groupingBy(e -> e, Collectors.counting()));

        // Преобразование ключей и значений в списки
        List<Integer> keys = new ArrayList<>(frequencyMap.keySet());
        List<Long> values = new ArrayList<>(frequencyMap.values());

        // Создание графика
        CategoryChart chart = new CategoryChartBuilder()
                .width(800)
                .height(600)
                .title("Gistogram Example")
                .xAxisTitle("Values")
                .yAxisTitle("Frequency")
                .build();

        // Добавление данных
        chart.addSeries("Frequency", keys, values);

        // Отображение графика
        new SwingWrapper<>(chart).displayChart();
    }
}
