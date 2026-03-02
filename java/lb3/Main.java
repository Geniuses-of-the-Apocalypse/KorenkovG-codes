package GUU.RU.Laba3J;

public class Main {
    public static void main(String[] args) {
        System.out.println("=== Decimal ===");

        // Твои примеры
        Decimal d1 = new Decimal("123456789");
        Decimal d2 = new Decimal("-98765");

        System.out.println("d1 = " + d1);
        System.out.println("d2 = " + d2);
        System.out.println("d1 + d2 = " + d1.add(d2));

        System.out.println("\n=== PascalString ===");

        // Твой пример
        PascalString s1 = new PascalString(50);
        s1.set("Darova novaya stroka");

        System.out.println("Строка = " + s1);
        System.out.println("Длина = " + s1.length());

        // Добавил второй пример для демонстрации сложения
        PascalString s2 = new PascalString(50);
        s2.set(" + ewe odna stroka");

        System.out.println("\nСложение:");
        System.out.println(s1 + " + " + s2 + " = " + s1.add(s2));
    }
}
