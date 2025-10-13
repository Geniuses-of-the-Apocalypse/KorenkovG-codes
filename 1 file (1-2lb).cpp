#include <iostream>
#include <cmath>
using namespace std;

struct Para {
    double first;   // катет a
    double second;  // катет b

    void init(double f, double s) {
        if (f > 0 && s > 0) {
            first = f;
            second = s;
        } else {
            cout << "Ошибка: катеты должны быть положительными!" << endl;
            exit(1);
        }
    }

    void read() {
        cout << "Введите катет a: ";
        cin >> first;
        cout << "Введите катет b: ";
        cin >> second;
        if (first <= 0 || second <= 0) {
            cout << "Ошибка: катеты должны быть положительными!" << endl;
            exit(1);
        }
    }

    void display() {
        cout << "Катет a: " << first << endl;
        cout << "Катет b: " << second << endl;
    }

    double hypotenuse() {
        return sqrt(first * first + second * second);
    }
};

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

    Para p3 = make_para(5.0, 12.0);
    cout << "Прямоугольный треугольник 3:" << endl;
    p3.display();
    cout << "Гипотенуза: " << p3.hypotenuse() << endl << endl;

    // Массив объектов
    Para triangles[2];
    cout << "Введите данные для массива треугольников:" << endl;
    for (int i = 0; i < 2; i++) {
        cout << "Треугольник " << i + 1 << ":" << endl;
        triangles[i].read();
    }

    cout << "Результаты для массива:" << endl;
    for (int i = 0; i < 2; i++) {
        cout << "Треугольник " << i + 1 << ":" << endl;
        triangles[i].display();
        cout << "Гипотенуза: " << triangles[i].hypotenuse() << endl << endl;
    }

    return 0;
}
-----------------------------------------------------------------------------------------------------------------------
#include <iostream>
#include <cmath>
using namespace std;

struct Point {
    double x;
    double y;
};

// Внешние функции для работы со структурой Point
void init(Point& p, double x_val, double y_val) {
    p.x = x_val;
    p.y = y_val;
}

void read(Point& p) {
    cout << "Введите координату x: ";
    cin >> p.x;
    cout << "Введите координату y: ";
    cin >> p.y;
}

void display(const Point& p) {
    cout << "(" << p.x << ", " << p.y << ")" << endl;
}

string toString(const Point& p) {
    return "(" + to_string(p.x) + ", " + to_string(p.y) + ")";
}

void moveX(Point& p, double dx) {
    p.x += dx;
}

void moveY(Point& p, double dy) {
    p.y += dy;
}

double distanceToOrigin(const Point& p) {
    return sqrt(p.x * p.x + p.y * p.y);
}

double distanceBetween(const Point& p1, const Point& p2) {
    return sqrt(pow(p2.x - p1.x, 2) + pow(p2.y - p1.y, 2));
}

void toPolar(const Point& p, double& r, double& theta) {
    r = distanceToOrigin(p);
    theta = atan2(p.y, p.x);
}

bool isEqual(const Point& p1, const Point& p2) {
    return (p1.x == p2.x) && (p1.y == p2.y);
}

bool isNotEqual(const Point& p1, const Point& p2) {
    return !isEqual(p1, p2);
}

// Демонстрация работы со структурой
void demoStruct() {
    cout << "=== РЕАЛИЗАЦИЯ СТРУКТУРОЙ ===" << endl;
    
    Point p1, p2;
    init(p1, 3.0, 4.0);
    read(p2);
    
    cout << "Точка 1: ";
    display(p1);
    cout << "Точка 2: ";
    display(p2);
    
    cout << "Расстояние от p1 до начала координат: " << distanceToOrigin(p1) << endl;
    cout << "Расстояние между точками: " << distanceBetween(p1, p2) << endl;
    
    double r, theta;
    toPolar(p1, r, theta);
    cout << "Полярные координаты p1: r=" << r << ", θ=" << theta << endl;
    
    cout << "Точки равны: " << isEqual(p1, p2) << endl;
    cout << "Точки не равны: " << isNotEqual(p1, p2) << endl;
}
