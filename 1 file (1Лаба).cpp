#include <iostream>
#include <cmath>
using namespace std;

struct Para {
    double first;   // катет a
    double second;  // катет b

    void init(double f, double s);
    void read();
    void display();
    double hypotenuse();
};

// Реализация методов вне класса
void Para::init(double f, double s) {
    if (f > 0 && s > 0) {
        first = f;
        second = s;
    } else {
        cout << "Ошибка: катеты должны быть положительными!" << endl;
        exit(1);
    }
}

void Para::read() {
    cout << "Введите катет a: ";
    cin >> first;
    cout << "Введите катет b: ";
    cin >> second;
    if (first <= 0 || second <= 0) {
        cout << "Ошибка: катеты должны быть положительными!" << endl;
        exit(1);
    }
}

void Para::display() {
    cout << "Катет a: " << first << endl;
    cout << "Катет b: " << second << endl;
}

double Para::hypotenuse() {
    return sqrt(first * first + second * second);
}

Para make_para(double a, double b) {
    if (a <= 0 || b <= 0) {
        cout << "Ошибка: катеты должны быть положительными!" << endl;
        exit(1);
    }
    Para p;
    p.init(a, b);
    return p;
}

int main() {
    // Демонстрация различных способов создания объектов
    Para p1;
    p1.init(3.0, 4.0);
    cout << "Прямоугольный треугольник 1:" << endl;
    p1.display();
    cout << "Гипотенуза: " << p1.hypotenuse() << endl << endl;

    Para p2;
    p2.read();
    cout << "Прямоугольный треугольник 2:" << endl;
    p2.display();
    cout << "Гипотенуза: " << p2.hypotenuse() << endl << endl;

    return 0;
}
