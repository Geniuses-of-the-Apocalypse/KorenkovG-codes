//package ru.guu.java;
import java.util.Scanner;

public class Main {
    public static void main(String[] args) {
        Bankomat atm = new Bankomat("AbA01", 100, 50000);

        atm.loadMoney(10, 10, 10, 10, 10);
        System.out.println(atm);

        atm.getMoney(500);
        System.out.println(atm);

        atm.getMoney(50);
        atm.getMoney(123);
        atm.getMoney(4500);
        System.out.println(atm);
    }
}
