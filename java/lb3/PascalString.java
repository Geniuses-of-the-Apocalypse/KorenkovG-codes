package GUU.RU.Laba3J;

import java.util.Arrays;

public class PascalString implements Array {
    private byte[] data;     // 0 — длина
    private int maxLength;

    public PascalString(int maxLength) {       // Конструктор
        if (maxLength > 255) {
            throw new IllegalArgumentException("Максимум 255");
        }

        this.maxLength = maxLength;
        data = new byte[maxLength + 1];          // +1 для длины
    }

    public PascalString(String str) {     // Конструктор для создания из строки
        this(str.length());
        set(str);
    }

    private PascalString(byte[] data, int maxLength) {     // Конструктор для внутреннего использования
        this.maxLength = maxLength;
        this.data = Arrays.copyOf(data, maxLength + 1);
    }

    public void set(String str) {           // Установить строку
        if (str.length() > maxLength) {
            throw new IllegalArgumentException("Строка слишком длинная");
        }

        data[0] = (byte) str.length();

        for (int i = 0; i < str.length(); i++) {
            data[i + 1] = (byte) str.charAt(i);
        }
    }

    public int length() {     // Длина
        return data[0] & 0xFF;  // Беззнаковое преобразование
    }

    public String get() {      // Строка
        int len = length();
        StringBuilder sb = new StringBuilder();

        for (int i = 1; i <= len; i++) {
            sb.append((char) data[i]);
        }

        return sb.toString();
    }

    @Override
    public Array add(Array other) {
        if (!(other instanceof PascalString)) {
            throw new IllegalArgumentException("Неверный тип для сложения");
        }

        PascalString psOther = (PascalString) other;

        String thisStr = this.get();         // Получаем обе строки
        String otherStr = psOther.get();

        String resultStr = thisStr + otherStr;         // Конкатенируем

        if (resultStr.length() > 255) {         // Проверяем длину
            throw new IllegalArgumentException("Результат слишком длинный (максимум 255 символов)");
        }

        PascalString result = new PascalString(resultStr.length());     // Создаем новую строку
        result.set(resultStr);

        return result;
    }

    @Override
    public void print() {
        System.out.println("Строка: \"" + get() + "\", длина: " + length());
    }

    @Override
    public String toString() {
        return get();
    }
}
