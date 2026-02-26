package GUU.RU.Laba2J;
import java.lang.Math;
import java.util.Scanner;

public class Number {
    private double num;

    public Number() {              //Конструкторы
        this.num = 0.0;
    }

    public Number(double num) {
        this.num = num;
    }

    public Number(Number other) {
        this.num = other.num;
    }

    public double getNum() {                 // Геттер
        return num;
    }

    public void setNum(double num) {            // Сеттер
        this.num = num;
    }

    public Number multiply(Number other) {           //Умнож
        return new Number(this.num * other.num);
    }

    public Number subtract(Number other) {         //Вычет
        return new Number(this.num - other.num);
    }

    public void print() {
        System.out.println("Number: " + num);
    }
}
