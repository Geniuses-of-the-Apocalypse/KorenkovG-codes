package GUU.RU.Laba2J;

public class Main {
    public static void main(String[] args) {
        System.out.println("-------------Работа классов---------\n");

        System.out.println("\n---Number---");
        GUU.RU.Laba2J.Number num1 = new GUU.RU.Laba2J.Number(10);
        GUU.RU.Laba2J.Number num2 = new Number(3);

        System.out.println("10 * 3 = " + num1.multiply(num2).getNum());
        System.out.println("10 - 3 = " + num1.subtract(num2).getNum());

        System.out.println("\n-----Real (Корни и Степени)-----");
        Real real1 = new Real(27);
        Real real2 = new Real(16);
        Real real3 = new Real(-8);

        System.out.println("Корень со степенью 3 из 27 = " + real1.coren(3).getNum());
        System.out.println("Корень со степенью 4 из 16 = " + real2.coren(4).getNum());
        System.out.println("Корень со степенью 3 из -8 = " + real3.coren(3).getNum());

        System.out.println(" ");

        System.out.println("2^3 = " + new Real(2).power(3).getNum());
        System.out.println("4^(-2) = " + new Real(4).power(-2).getNum());
        System.out.println("9^0.5 = " + new Real(9).power(0.5).getNum());

        System.out.println("\n--- Наследование ---");
        System.out.println("27 * 16 = " + real1.multiply(real2).getNum());
        System.out.println("27 - 16 = " + real1.subtract(real2).getNum());

        System.out.println("\n--- Ошибки ---");
        System.out.println("Корень 2 из -4:");
        new Real(-4).coren(2);

        System.out.println("\n0 в степени -2:");
        new Real(0).power(-2);
    }
}
