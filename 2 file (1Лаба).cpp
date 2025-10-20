#include <iostream>
#include <cmath>
#include <string>

using namespace std;

class Money {
private:
    // Хранение количества купюр каждого номинала
    int rub[9] = {0}; // Номиналы рублей: 1, 2, 5, 10, 50, 100, 500, 1000, 5000
    int kop[4] = {0}; // Номиналы копеек: 0.01, 0.05, 0.1, 0.5
    
    // Статические массивы номиналов (общие для всех объектов)
    static const int rubNom[9];
    static const double kopNom[4];
    
    // Вспомогательные методы для конвертации
    double toDouble() const;     // Преобразование в число
    void fromDouble(double amount); // Преобразование из числа

public:
    // Конструкторы (требуются по заданию)
    Money();                    // Конструктор без аргументов
    Money(double amount);       // Конструктор инициализации из числа
    Money(const Money& other);  // Конструктор копирования
    
    // Арифметические операции
    Money add(const Money& other) const;      // Сложение сумм
    Money sub(const Money& other) const;      // Вычитание сумм
    double div(const Money& other) const;     // Деление сумм
    Money divByDouble(double divisor) const;  // Деление на дробное число
    Money mulByDouble(double multiplier) const; // Умножение на дробное число
    
    // Операции сравнения
    bool equal(const Money& other) const;   // Равенство
    bool greater(const Money& other) const; // Больше
    bool less(const Money& other) const;    // Меньше
    
    // Методы вывода
    void display() const;       // Вывод на экран
    string toString() const;    // Преобразование в строку
};

// Инициализация статических массивов номиналов
const int Money::rubNom[9] = {1, 2, 5, 10, 50, 100, 500, 1000, 5000};
const double Money::kopNom[4] = {0.01, 0.05, 0.1, 0.5};

// Реализация методов ВНЕ класса

// Конструктор без аргументов - инициализирует нулями
Money::Money() {
    for (int i = 0; i < 9; i++) rub[i] = 0;
    for (int i = 0; i < 4; i++) kop[i] = 0;
}

// Конструктор инициализации из double
Money::Money(double amount) {
    fromDouble(amount);
}

// Конструктор копирования - копирует все номиналы
Money::Money(const Money& other) {
    for (int i = 0; i < 9; i++) rub[i] = other.rub[i];
    for (int i = 0; i < 4; i++) kop[i] = other.kop[i];
}

// Преобразование внутреннего представления в double
double Money::toDouble() const {
    double total = 0;
    
    // Суммируем рубли по номиналам
    for (int i = 0; i < 9; i++) {
        total += rub[i] * rubNom[i];
    }
    
    // Суммируем копейки по номиналам
    for (int i = 0; i < 4; i++) {
        total += kop[i] * kopNom[i];
    }
    
    return total;
}

// Преобразование double во внутреннее представление (по номиналам)
void Money::fromDouble(double amount) {
    // Обнуляем текущие значения
    for (int i = 0; i < 9; i++) rub[i] = 0;
    for (int i = 0; i < 4; i++) kop[i] = 0;
    
    // Разделяем на рубли и копейки
    long rubPart = static_cast<long>(amount);
    double kopPart = amount - rubPart;
    
    // Распределяем рубли по номиналам (от большего к меньшему)
    for (int i = 8; i >= 0; i--) {
        if (rubPart >= rubNom[i]) {
            rub[i] = rubPart / rubNom[i];
            rubPart %= rubNom[i];
        }
    }
    
    // Распределяем копейки по номиналам (от большего к меньшему)
    kopPart = round(kopPart * 100) / 100; // Округляем до 2 знаков
    for (int i = 3; i >= 0; i--) {
        if (kopPart >= kopNom[i] - 1e-10) { // Учитываем погрешность double
            kop[i] = static_cast<int>(kopPart / kopNom[i]);
            kopPart -= kop[i] * kopNom[i];
            kopPart = round(kopPart * 100) / 100; // Корректируем остаток
        }
    }
}

// Сложение двух денежных сумм
Money Money::add(const Money& other) const {
    return Money(this->toDouble() + other.toDouble());
}

// Вычитание денежных сумм
Money Money::sub(const Money& other) const {
    return Money(this->toDouble() - other.toDouble());
}

// Деление одной суммы на другую (возвращает коэффициент)
double Money::div(const Money& other) const {
    return this->toDouble() / other.toDouble();
}

// Деление суммы на дробное число
Money Money::divByDouble(double divisor) const {
    return Money(this->toDouble() / divisor);
}

// Умножение суммы на дробное число
Money Money::mulByDouble(double multiplier) const {
    return Money(this->toDouble() * multiplier);
}

// Проверка на равенство сумм (с учетом погрешности double)
bool Money::equal(const Money& other) const {
    return abs(this->toDouble() - other.toDouble()) < 1e-10;
}

// Проверка, что текущая сумма больше другой
bool Money::greater(const Money& other) const {
    return this->toDouble() > other.toDouble();
}

// Проверка, что текущая сумма меньше другой
bool Money::less(const Money& other) const {
    return this->toDouble() < other.toDouble();
}

// Вывод суммы на экран
void Money::display() const {
    cout << toString();
}

// Преобразование суммы в строку (формат: "рубли,копейки")
string Money::toString() const {
    double total = toDouble();
    long rubles = static_cast<long>(total);
    int kops = static_cast<int>((total - rubles) * 100 + 0.5); // Округляем копейки
    
    // Форматируем вывод: добавляем ведущий ноль для копеек
    string result = to_string(rubles) + ",";
    if (kops < 10) result += "0";
    result += to_string(kops);
    return result;
}

int main() {
    cout << "=== Лабораторная работа №1 ===" << endl;
    
    // Демонстрация работы конструкторов
    cout << "1. Тестирование конструкторов:" << endl;
    Money m1;                    // Конструктор без аргументов
    Money m2(150.75);           // Конструктор инициализации
    Money m3(m2);               // Конструктор копирования
    
    cout << "m1 (по умолчанию): " << m1.toString() << endl;
    cout << "m2 (150.75): " << m2.toString() << endl;
    cout << "m3 (копия m2): " << m3.toString() << endl;
    
    // Демонстрация арифметических операций
    cout << "\n2. Арифметические операции:" << endl;
    Money sum = m2.add(m3);
    cout << "m2 + m3: " << sum.toString() << endl;
    
    Money diff = m2.sub(m1);
    cout << "m2 - m1: " << diff.toString() << endl;
    
    double divVal = m2.div(m3);
    cout << "m2 / m3: " << divVal << endl;
    
    Money divDouble = m2.divByDouble(3);
    cout << "m2 / 3: " << divDouble.toString() << endl;
    
    Money mulDouble = m2.mulByDouble(2);
    cout << "m2 * 2: " << mulDouble.toString() << endl;
    
    // Демонстрация операций сравнения
    cout << "\n3. Операции сравнения:" << endl;
    cout << "m2 == m3: " << m2.equal(m3) << endl;
    cout << "m2 > m1: " << m2.greater(m1) << endl;
    cout << "m2 < m3: " << m2.less(m3) << endl;
    
    // Демонстрация работы с массивами объектов
    cout << "\n4. Массив объектов:" << endl;
    Money arr[3] = { Money(50.25), Money(100.50), Money(200.75) };
    for (int i = 0; i < 3; i++) {
        cout << "arr[" << i << "]: " << arr[i].toString() << endl;
    }
    
    // Дополнительные тесты для проверки точности
    cout << "\n5. Дополнительные тесты точности:" << endl;
    Money test1(10.10);
    Money test2(5.05);
    Money test3 = test1.add(test2);
    cout << "10.10 + 5.05 = " << test3.toString() << endl;
    
    Money test4 = test1.sub(test2);
    cout << "10.10 - 5.05 = " << test4.toString() << endl;

    return 0;
}
