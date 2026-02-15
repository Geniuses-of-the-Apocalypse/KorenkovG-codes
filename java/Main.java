//package ru.guu.java;
import java.lang.Math;
import java.util.Scanner;

public class Bankomat {
    private int count10, count50, count100, count500, count1000;
    private String id;
    private int minSum, maxSum;

    public Bankomat(String id, int minSum, int maxSum) {
        this.id = id;
        this.minSum = minSum;
        this.maxSum = maxSum;
    }

    public void loadMoney(int c10, int c50, int c100, int c500, int c1000) {
        count10 += c10;
        count50 += c50;
        count100 += c100;
        count500 += c500;
        count1000 += c1000;
    }

    public boolean getMoney(int sum) {
        if (sum < minSum) { System.out.println("ошибка - минимум " + minSum); return false; }
        if (sum > maxSum) { System.out.println("ошибка - максимум " + maxSum); return false; }
        if (sum > totalMoney()) { System.out.println("ошибка - нет денег"); return false; }
        if (sum % 10 != 0) { System.out.println("ошибка - сумма должна быть кратна 10"); return false; }

        int need = sum;
        int g1000 = Math.min(need / 1000, count1000); need -= g1000 * 1000;
        int g500 = Math.min(need / 500, count500); need -= g500 * 500;
        int g100 = Math.min(need / 100, count100); need -= g100 * 100;
        int g50 = Math.min(need / 50, count50); need -= g50 * 50;
        int g10 = Math.min(need / 10, count10); need -= g10 * 10;

        if (need == 0) {
            count1000 -= g1000; count500 -= g500; count100 -= g100;
            count50 -= g50; count10 -= g10;
            System.out.println("успешно - выдано " + sum);
            return true;
        }
        System.out.println("ошибка - нет подходящих купюр");
        return false;
    }

    private int totalMoney() {
        return count10*10 + count50*50 + count100*100 + count500*500 + count1000*1000;
    }

    public String toString() {
        return "Банкомат " + id + ": " + totalMoney() + " руб";
    }
}
