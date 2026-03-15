package GUU.RU.Laba5J;

import java.util.*;
import java.nio.file.*;
import java.io.*;

/**
 * Класс для обработки ввода HTML (клавиатура или файл)
 */
public class HTMLInputHandler {

    private Scanner scanner;

    public HTMLInputHandler() {
        this.scanner = new Scanner(System.in);
    }

    public List<String> inputFromKeyboard() {   // ввод с клавиатуры
        List<String> lines = new ArrayList<>();

        System.out.println("\n ВВОД HTML С КЛАВИАТУРЫ");

        System.out.println("(Вводите строки. Пустая строка - конец ввода)");
        System.out.println("-".repeat(50));

        int lineCount = 1;
        while (true) {
            System.out.printf("%2d: ", lineCount);
            String line = scanner.nextLine();

            if (line.trim().isEmpty()) {
                break;
            }

            lines.add(line);
            lineCount++;
        }

        return lines;
    }

    public List<String> loadFromFile() {           // вводим фалом
        System.out.print("\n Введите путь к файлу: ");
        String filePath = scanner.nextLine().trim();

        try {
            Path path = Paths.get(filePath);

            if (!Files.exists(path)) {
                System.out.println(" файл не найден");
                return null;
            }

            if (Files.isDirectory(path)) {
                System.out.println("это папка, а не файл");
                return null;
            }

            List<String> lines = Files.readAllLines(path);
            System.out.printf(" загружено %d строк%n", lines.size());
            return lines;

        } catch (IOException e) {
            System.out.println(" ошибка чтения " + e.getMessage());
            return null;
        }
    }

    public int showMenu() {
        System.out.println("\n" + "=".repeat(60));
        System.out.println(" ПОИСК НЕЗАКРЫТЫХ ТЕГОВ");
        System.out.println("=".repeat(60));
        System.out.println("1. ввести с клавиатуры");
        System.out.println("2. загрузить из файла");
        System.out.println("3. выход");
        System.out.print("\nвыберите действие: ");

        try {
            return Integer.parseInt(scanner.nextLine().trim());
        } catch (NumberFormatException e) {
            return -1;
        }
    }

    public boolean askContinue() {
        System.out.print("\nпроверить еще? (да/нет): ");
        String answer = scanner.nextLine().trim().toLowerCase();
        return answer.equals("да") || answer.equals("yes") || answer.equals("y");
    }


    public void close() {
        scanner.close();
    }
}
