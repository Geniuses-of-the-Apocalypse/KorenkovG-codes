package GUU.RU.Laba2J;
import java.lang.Math;
import java.util.Scanner;

public class Real extends Number {

    public Real() {super(0.0);}     // Конструкторы

    public Real(double num) {super(num);}

    public Real(Real other) {super(other.getNum());}

    public Real coren(int n) {      // Корень произвольной степени
        if (n <= 0) {
            System.out.println("Степень должна быть > 0");
            return new Real(0);
        }
        double num = this.getNum(); // Геттер

        if (num < 0 && n % 2 == 0) {   // Проверка
            System.out.println("Нельзя извлечь корень четной степени из отрицательного числа");
            return new Real(0);
        }

        if (num < 0 && n % 2 == 1) { // Обработка отрицательных через Math
            return new Real(-Math.pow(-num, 1.0/n));
        }
        return new Real(Math.pow(num, 1.0/n));
    }

    public Real power(int n) {          // Возведение в целочисленную степень
        double num = this.getNum();

        if (num == 0 && n < 0) {     // Проверка
            System.out.println("Нельзя возвести 0 в отрицательную степень");
            return new Real(0);
        }

        double result = 1;
        for (int i = 0; i < Math.abs(n); i++) {
            result *= num;
        }

        if (n < 0) result = 1.0/result;
        return new Real(result);
    }

    public Real power(double n) {    // Возведение в вещественную степень
        double num = this.getNum();

        if (num < 0) {                    // Проверка
            System.out.println("Нельзя возвести отрицательное число в вещественную степень");
            return new Real(0);
        }
        return new Real(Math.pow(num, n));
    }
}
