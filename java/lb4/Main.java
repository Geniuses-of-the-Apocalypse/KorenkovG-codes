package GUU.RU.Laba4J;
import java.util.Scanner;

public class Main {
    public static void main(String[] args) {
        System.out.println("=== ПРИМЕРЫ РАБОТЫ НАШЕГО СПИСКА ===\n");
        exampleWithNumbers(); // работа с числами

        System.out.println("\n-------------------\n");
        exampleWithStrings(); // работа со строками

        System.out.println("\n-------------------\n");
        interactiveExample(); // интерактивный пример
    }

    private static void exampleWithNumbers() {
        System.out.println("--- ПРИМЕР 1: Работа с числами ---");

        MyList<Integer> numbers = new MyList<>(); //список чисел

        numbers.add(5);
        numbers.add(2);
        numbers.add(8);
        numbers.add(1);
        numbers.add(9);
        numbers.add(1);
        numbers.add(4);
        numbers.add(11);
        numbers.add(100);

        System.out.println("исходный список " + numbers);
        System.out.println("размер списка " + numbers.size());


        System.out.println("элемент с индексом 2 " + numbers.get(2)); // получаем элемент по индексу

        int removed = numbers.remove(1); // удаляем элемент
        System.out.println("удалили элемент с индексом 1 (значение " + removed + ")");
        System.out.println("Список после удаления " + numbers);

        numbers.sort(); // сортируем
        System.out.println("отсортированный список " + numbers);

        System.out.println("поиск числа 8 индекс " + numbers.binarySearch(8)); // ищем элементы бинарным поиском
        System.out.println("поиск числа 10 индекс " + numbers.binarySearch(10));

        System.out.println("Список пуст? " + numbers.isEmpty()); // проверяем, пустой ли список
    }


    private static void exampleWithStrings() {
        System.out.println("--- ПРИМЕР 2: Работа со строками ---");

        String[] fruits = {"banana", "tikva", "orange", "onion", "tomato"};
        MyList<String> strings = new MyList<>(fruits);

        System.out.println("исходный список " + strings);

        strings.sort();
        System.out.println("после сортировки " + strings);

        int index = strings.binarySearch("orange");
        System.out.println("индекс 'orange' " + index);

        // Добавляем новый элемент
        strings.add("mango");
        System.out.println("после добавления 'mango' " + strings);

        // Снова сортируем (так как добавили новый элемент)
        strings.sort();
        System.out.println("после повторной сортировки " + strings);

        // Ищем новый элемент
        System.out.println("поиск 'mango' индекс " + strings.binarySearch("mango"));
    }

    private static void interactiveExample() {
        System.out.println("--- ПРИМЕР 3: Интерактивный ---");
        System.out.println("Введите несколько чисел через пробел (например: 5 2 8 1 9):");

        Scanner scanner = new Scanner(System.in);
        String line = scanner.nextLine();

        MyList<Integer> list = new MyList<>();

        String[] numbers = line.split(" ");

        for (String num : numbers) {
            try {
                int value = Integer.parseInt(num);
                list.add(value);
                System.out.println("  Добавлено: " + value);
            } catch (NumberFormatException e) {
                System.out.println("  Пропущено (не число): " + num);
            }
        }

        System.out.println("\nВаш список: " + list);
        list.sort();
        System.out.println("Отсортированный список: " + list);
        System.out.print("\nВведите число для поиска: ");
        try {
            int searchNum = scanner.nextInt();
            int result = list.binarySearch(searchNum);

            if (result >= 0) {
                System.out.println("Число " + searchNum + " найдено на позиции " + result);
            } else {
                System.out.println("Число " + searchNum + " не найдено");
            }
        } catch (Exception e) {
            System.out.println("Ошибка ввода числа");
        }
        scanner.close();
    }
}

