
# Информатика (организация и поиск данных) (3 семестр)
## Лабораторная работа №1

### Описание проекта

В данном проекте реализованы и протестированы различные типы указателей:
- **Smart Pointer** [SmrtPtr.h](pointer/SmrtPtr.h)
- **Unique Pointer** [UnqPtr.h](pointer/UnqPtr.h)
- **Shared Pointer** [ShrdPtr.h](pointer/ShrdPtr.h)
для работы с динамической памятью в C++. 
- Также реализованы контейнеры последовательностей, контейнер, который реализует динамический массив и связный список :
- **Sequence** [Sequence.h](collectionunqptr/sequence/Sequence.h)
- **MutableSequence** [MutableSequence.h](collectionunqptr/sequence/MutableSequence.h)
- **LinkedList** [LinkedListUP.h](collectionunqptr/linkedlist/LinkedListUP.h)
- **DynamicArray** [DynamicArray.h](collectionunqptr/dinamicarray/DynamicArray.h)

### Клонирование репозитория:

```bash
git clone git@github.com:ITech7750/AdvancedContainers.git
```

### Тестирование

Для тестирования производительности указателей был реализован скрипт, который заполняет последовательность с использованием указателей определенного типа и измеряет время выполнения операции. Результаты записываются в файл CSV для последующего анализа. На основе данных из этого файла построен график с использованием Python, который сравнивает время выполнения для каждого типа указателя.

### Построение графиков

Для анализа данных используется Python-скрипт, который строит графики на основе результатов тестов, записанных в CSV файл `load_test_results.csv`.

#### Как запустить:

1. После завершения тестов, убедитесь, что файл `load_test_results.csv` создан.
2. Установите необходимые библиотеки для Python:

```bash
pip install pandas matplotlib
```

3. Запустите Python-скрипт для построения графиков:

```bash
python plot.py
```

Этот скрипт построит графики, на которых сравнивается время выполнения операций для различных типов указателей при разном количестве элементов.

---

## Лабораторная работа №2

Реализованы следующие алгоритмы сортировки:
- **Quick Sort** [QuickSorter.h](sort/impl/QuickSorter.h)
- **Merge Sort** [MergeSorter.h](sort/impl/MergeSorter.h)
- **Bubble Sort** [BubbleSorter.h](sort/impl/BubbleSorter.h)
- **Insertion Sort** [InsertionSorter.h](sort/impl/InsertionSorter.h)
- **Heap Sort** [HeapSorter.h](sort/impl/HeapSorter.h)

При помощи них можно сортировать элементы последовательностей на кастомных указателях, например:
- **MutableArraySequenceUnqPtr.h** [MutableArraySequenceUnqPtr.h](collectionunqptr/sequence/arraysequence/MutableArraySequenceUnqPtr.h)
- **MutableListSequenceUnqPtr.h** [MutableListSequenceUnqPtr.h](collectionunqptr/sequence/linkedlistsequence/MutableListSequenceUnqPtr.h)

Для выбора и управления сортировками реализован сервис сортировок, например:
- **SorterServiceArray.h** [SorterServiceArray.h](sort/SorterServiceArray.h)

Также добавлена возможность работать с этими контейнерами на Java при помощи JNI.

### Простой пример кода для работы с сортировками на Java:

1. Подключим библиотеку:

```java
package org.example.sorter;

import org.example.model.Person;

import java.util.List;

public class SorterService {
    static {
        System.out.println("Loading library...");
        System.load("/home/itech/Desktop/University/AdvancedContainers/cmake-build-debug/libSorterService.so");
        System.out.println("Library loaded successfully.");
    }

    public native static void sortByAge(String fileName, boolean isJson, String algorithm);
    public native static void sortByName(String fileName, boolean isJson, String algorithm);
    public native static double sortByAgeAndGetTime(String fileName, boolean isJson, String algorithm);
    public native static List<Person> getSortedByAge(String fileName, boolean isJson, String algorithm);
}
```

2. Создадим тестовый класс по аналогии с [Person.h](test/testClasses/Person.h):

```java
package org.example.model;

public class Person {
    private String firstName;
    private String lastName;
    private int age;
    private String address;
    private double height;
    private double weight;
    private int yearOfBirth;
    private String phoneNumber;
    private String email;
    private String jobTitle;

    public Person(String firstName, String lastName, int age, String address, double height, double weight,
                  int yearOfBirth, String phoneNumber, String email, String jobTitle) {
        this.firstName = firstName;
        this.lastName = lastName;
        this.age = age;
        this.address = address;
        this.height = height;
        this.weight = weight;
        this.yearOfBirth = yearOfBirth;
        this.phoneNumber = phoneNumber;
        this.email = email;
        this.jobTitle = jobTitle;
    }

    @Override
    public String toString() {
        return firstName + " " + lastName + ", Age: " + age + ", Address: " + address;
    }
}
```

3. Проверим работоспособность библиотеки:

```java
package org.example;

import org.example.sorter.SorterService;
import org.example.model.Person;

import java.util.List;

public class Main {
    public static void main(String[] args) {
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
            System.out.println("Sorting by name completed.");
        } catch (Exception e) {
            System.err.println("An error occurred: " + e.getMessage());
        }
    }
}

```
Весь функционал для работы с кастомными контенерами покрыт тестами в парадигме AAA.


## Лабораторная работа №3
### Описание проекта

В третьей лабораторной работе реализована система для обработки и анализа данных с использованием пар ключ-значение, хэш-таблиц, словарей и построения гистограмм. Проект включает следующие основные компоненты:

1. [Pair.h](gistogram/model/dictionary/Pair.h)

Класс Pair предназначен для хранения пар ключ-значение:

Конструктор: инициализирует ключ и значение.
Методы: getKey, getValue для доступа к ключу и значению; copy создает новую пару с тем же ключом, но другим значением; equal и оператор == проверяют равенство пар.

2. [HashMap.h](gistogram/model/dictionary/HashMap.h)

HashMap представляет собой хэш-таблицу для хранения данных в виде пар ключ-значение:

Метод hashCode: вычисляет хэш-код ключа.
Основные методы: insert добавляет новые пары, get и operator[] извлекают значение по ключу, contains проверяет наличие ключа, getKeys возвращает все ключи.

3. [Dictionary.h](gistogram/model/dictionary/Dictionary.h)

Dictionary базируется на HashMap и предназначен для работы с коллекцией значений:

Метод add: добавляет пару ключ-значение.
Метод addStatistic: рассчитывает и добавляет статистические данные с использованием предиката.
Методы getData и getStatistic: предоставляют доступ к данным и статистике.

4. [GistogramScope.h](gistogram/dsl/GistogramScope.h) и [Gistogram.h](gistogram/model/Gistogram.h)

GistogramScope является основным классом для конфигурирования и построения гистограмм. Он предоставляет методы для добавления данных, настройки параметров и включения вычисления статистики.

Gistogram представляет собой структуру данных для хранения и анализа пар ключ-значение, соответствующих параметрам и данным гистограммы.

Метод addData: добавляет данные для анализа.

Метод parameter: определяет параметры с использованием предикатов.

Метод enableStatistic: включает расчет статистики.

Метод buildGistogram: создает и возвращает гистограмму.

В данном проекте реализован специализированный "dsl" для создания и анализа гистограмм на основе шаблонных классов GistogramScope и Gistogram. Этот DSL предоставляет пользователям удобные средства для работы с гистограммами, позволяя конфигурировать параметры, добавлять данные и вычислять статистику.

Далее все это будем использовать в ЛР4.

## Лабораторная работа №4

### Описание

В этой лабораторной работе был реализован API для работы с логистическими данными [Gistogram](Gistogram). Использовалась моя библиотека написанная на C++, которая предоставляет функции для создания и анализа графов, а также нахождения кратчайших путей между вершинами . Для связи C++ и Kotlin использовался JNI [nativelib.cpp](jni/nativelib.cpp).

### Что было реализовано:

1. Библиотека на C++:

2. Генерация графов с логистическими данными (города и дороги).

3. Чтение графов из файла.

4. Нахождение кратчайшего пути (по времени и по вершинам).

5. Работа как с направленными, так и с ненаправленными графами.

### API на Kotlin:

REST API с использованием Spring Boot для управления логистическими данными.

1. CRUD операции для городов и дорог.

2. Вызов функций из C++ библиотеки через JNI.

Синхронизация C++ и Kotlin:

1. Использование JNI для вызова методов библиотеки.

2. Форматы данных: JSON и текстовые файлы.

Использование PostgreSQL:

1. Хранение данных о городах и дорогах.

2. Использование Spring Data JPA для работы с базой данных.

### Описание API

1. POST /api/logistics/logistic

Создание логистических данных.

Пример запроса:
```bash
curl -X POST "http://localhost:8080/api/logistics/logistic" \
-d "resultFilePath=/tmp/logistics_result.txt" \
-d "cityAmount=10" \
-d "roadAmount=20" \
-d "cargo=100"
```

2. POST /api/logistics/logistic/from-file


Создание логистических данных из файла.

Пример запроса:

```bash
curl -X POST "http://localhost:8080/api/logistics/logistic/from-file" \
-F "dataFilePath=@logistics_input.txt" \
-F "resultFilePath=/tmp/logistics_result.txt" \
-F "startCity=CityA" \
-F "endCity=CityB" \
-F "cargo=200"
```
Формат файла logistics_input.txt:

{Road1;15.5;100;CityA;CityB}
{Road2;10.2;80;CityB;CityC}
{Road3;5.5;60;CityA;CityC}
{Road4;12.8;90;CityC;CityD}
{Road5;7.3;70;CityD;CityE}

3. GET /api/logistics/greeting

Возвращает приветственное сообщение.

Пример запроса:

```bash
curl -X GET "http://localhost:8080/api/logistics/greeting"
```

4. CRUD операции для городов и дорог

```bash
Пример запроса на добавление города:

curl -X POST "http://localhost:8080/api/logistics/city" \
-H "Content-Type: application/json" \
-d '{"name": "CityA", "cargoToDrop": 50, "x": 10.0, "y": 20.0}'
```

Сохранение информации о городе.

POST /api/logistics/city
```bash
curl -X POST http://localhost:8080/api/logistics/city \
-H "Content-Type: application/json" \
-d '{
"name": "CityA",
"cargoToDrop": 50,
"x": 1.5,
"y": 3.2
}'
```
пример ответа:
```
{
"id": 1,
"name": "CityA",
"cargoToDrop": 50,
"x": 1.5,
"y": 3.2
}
```

POST /api/logistics/road
Сохранение информации о дороге.
```bash
curl -X POST http://localhost:8080/api/logistics/road \
-H "Content-Type: application/json" \
-d '{
"name": "Road1",
"length": "15.5",
"maxSpeed": "100",
"start": {
"id": 1
},
"end": {
"id": 2
}
}'
```
Пример ответа:
```bash
{
"id": 1,
"name": "Road1",
"length": "15.5",
"maxSpeed": "100",
"start": {
"id": 1,
"name": "CityA",
"cargoToDrop": 50,
"x": 1.5,
"y": 3.2
},
"end": {
"id": 2,
"name": "CityB",
"cargoToDrop": 30,
"x": 2.5,
"y": 4.1
}
}
```

Технологии:

C++: Для работы с графами и реализации алгоритмов.

Kotlin: Реализация REST API с использованием Spring Boot. 

JNI: Для интеграции функций C++ с Kotlin.

PostgreSQL: Для хранения данных о городах и дорогах.

Spring Data JPA: Для работы с базой данных.

