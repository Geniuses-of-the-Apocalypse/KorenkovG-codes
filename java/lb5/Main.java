package GUU.RU.Laba5J;
import java.util.List;

/**
 * Главный класс программы для поиска незакрытых HTML-тегов
 */
public class Main {

    public static void main(String[] args) {
        HTMLInputHandler input = new HTMLInputHandler();
        HTMLTagAnalyzer analyzer = new HTMLTagAnalyzer();

        while (true) {
            int choice = input.showMenu();

            List<String> htmlLines = null;

            switch (choice) {
                case 1:
                    htmlLines = input.inputFromKeyboard();
                    break;
                case 2:
                    htmlLines = input.loadFromFile();
                    if (htmlLines == null) {
                        continue;
                    }
                    break;
                case 3:
                    input.close();
                    return;
                default:
                    System.out.println("неверный выбор");
                    continue;
            }

            if (htmlLines == null || htmlLines.isEmpty()) {
                System.out.println("\n нет данных для анализа");
                continue;
            }

            List<TagInfo> unclosedTags = analyzer.findUnclosedTags(htmlLines); // поиск незакрытых тегов

            System.out.println("\n" + "=".repeat(60));             // вывод результатов
            if (unclosedTags.isEmpty()) {
                System.out.println(" все теги закрыты правильно");
            } else {
                System.out.println(" найдено незакрытых тегов: " + unclosedTags.size());
                System.out.println("\n список");
                for (int i = 0; i < unclosedTags.size(); i++) {
                    System.out.println((i + 1) + ". " + unclosedTags.get(i));
                }
            }
            System.out.println("=".repeat(60));

            if (!input.askContinue()) {
                System.out.println("\n до свидания");
                break;
            }
        }
        input.close();
    }
}

