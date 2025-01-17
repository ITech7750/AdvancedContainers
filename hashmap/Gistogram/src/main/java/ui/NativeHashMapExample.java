package ui;

import nativelib.NativeHashMap;

import java.util.List;

public class NativeHashMapExample {

    public static void main(String[] args) {
        // Создаем экземпляр NativeHashMap
        NativeHashMap nativeHashMap = new NativeHashMap();

        System.out.println("Добавляем элементы в NativeHashMap...");
        nativeHashMap.put("key1", "value1");
        nativeHashMap.put("key2", "value2");
        nativeHashMap.put("key3", "value3");

        System.out.println("Размер хэш-таблицы: " + nativeHashMap.size());

        System.out.println("Значение для key1: " + nativeHashMap.get("key1"));

        System.out.println("Содержит key2? " + nativeHashMap.containsKey("key2"));
        System.out.println("Содержит key4? " + nativeHashMap.containsKey("key4"));

        List<String> keys = nativeHashMap.getKeys();
        System.out.println("Ключи в NativeHashMap: " + keys);

        List<String> values = nativeHashMap.getValues();
        System.out.println("Значения в NativeHashMap: " + values);

        System.out.println("Удаляем key2...");
        nativeHashMap.remove("key2");

        System.out.println("Размер после удаления: " + nativeHashMap.size());

        System.out.println("Пуста ли таблица? " + nativeHashMap.isEmpty());

        System.out.println("Очищаем таблицу...");
        nativeHashMap.clear();
        System.out.println("Размер после очистки: " + nativeHashMap.size());
        System.out.println("Пуста ли таблица? " + nativeHashMap.isEmpty());
    }
}
