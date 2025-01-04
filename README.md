
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