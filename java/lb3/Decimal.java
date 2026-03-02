package GUU.RU.Laba3J;

import java.util.Arrays;

public class Decimal implements Array {
    private byte[] digits;   // 100 цифр (0–9)
    private int sign;        // 1 — плюс, -1 — минус

    public Decimal(String number) {
        digits = new byte[100];

        if (number.startsWith("-")) {  // Определяем знак
            sign = -1;
            number = number.substring(1);
        } else {
            sign = 1;
        }

        int len = number.length();      // Записываем цифры (младший разряд — в нулевой элемент)
        if (len > 100) {
            throw new IllegalArgumentException("Число слишком большое");
        }

        for (int i = 0; i < len; i++) {
            char c = number.charAt(len - 1 - i);
            if (!Character.isDigit(c)) {
                throw new IllegalArgumentException("Неверный формат числа");
            }
            digits[i] = (byte) (c - '0');
        }
    }

    private Decimal(byte[] digits, int sign) {     // Конструктор для внутреннего использования
        this.digits = Arrays.copyOf(digits, 100);
        this.sign = sign;
    }

    @Override               // Сложение через интерфейс Array
    public Array add(Array other) {
        if (!(other instanceof Decimal)) {
            throw new IllegalArgumentException("Неверный тип для сложения");
        }

        Decimal dOther = (Decimal) other;

        if (this.sign == dOther.sign) {               // Если знаки одинаковые - складываем
            return addSameSign(dOther);
        }
        else {
            return addDifferentSign(dOther);         // Если знаки разные - вычитаем
        }
    }

    private Decimal addSameSign(Decimal other) {
        byte[] result = new byte[100];
        int carry = 0;

        for (int i = 0; i < 100; i++) {
            int sum = this.digits[i] + other.digits[i] + carry;         // Поэлементное сложение
            result[i] = (byte) (sum % 10);
            carry = sum / 10;
        }

        if (carry > 0) {
            throw new ArithmeticException("Переполнение");
        }

        return new Decimal(result, this.sign);
    }

    private Decimal addDifferentSign(Decimal other) {
        int comparison = compareAbsolute(other);         // Сравниваем числа по модулю

        if (comparison == 0) {         // Если равны по модулю - результат 0
            return new Decimal("0");
        }

        Decimal larger, smaller;         // Определяем, какое число больше по модулю
        int resultSign;

        if (comparison > 0) {
            larger = this;
            smaller = other;
            resultSign = this.sign;
        } else {
            larger = other;
            smaller = this;
            resultSign = other.sign;
        }

        byte[] result = new byte[100];   // Вычитаем меньшее из большего
        int borrow = 0;

        for (int i = 0; i < 100; i++) {
            int diff = larger.digits[i] - smaller.digits[i] - borrow;
            if (diff < 0) {
                diff += 10;
                borrow = 1;
            } else {
                borrow = 0;
            }
            result[i] = (byte) diff;
        }

        return new Decimal(result, resultSign);
    }

    private int compareAbsolute(Decimal other) {      // Сравнение по модулю
        for (int i = 99; i >= 0; i--) {
            if (this.digits[i] != other.digits[i]) {
                return this.digits[i] - other.digits[i];
            }
        }
        return 0;
    }

    @Override
    public void print() {
        System.out.println(this);
    }

    @Override
    public String toString() {
        StringBuilder sb = new StringBuilder();

        if (sign == -1) {
            sb.append("-");
        }

        boolean leadingZero = true;
        for (int i = 99; i >= 0; i--) {
            if (digits[i] != 0) {
                leadingZero = false;
            }
            if (!leadingZero) {
                sb.append(digits[i]);
            }
        }
        return sb.length() == 0 || sb.toString().equals("-") ? "0" : sb.toString();
    }
}
