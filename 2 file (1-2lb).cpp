#include <iostream>
#include <string>
#include <cmath>
#include <iomanip>

using namespace std;

class Money {
private:
    // Номиналы рублей и копеек
    static const int RUBLE_NOMINALS_COUNT = 9;
    static const int KOPECK_NOMINALS_COUNT = 4;
    
    int rubleNominals[9] = {5000, 1000, 500, 100, 50, 10, 5, 2, 1};
    double kopeckNominals[4] = {0.5, 0.1, 0.05, 0.01};
    
    // Количество купюр/монет каждого номинала
    int rubleCount[9];
    int kopeckCount[4];
    
    // Общая сумма в рублях
    double totalAmount;
    
    // Обновление общей суммы
    void updateTotalAmount() {
        totalAmount = 0;
        
        // Сумма рублей
        for (int i = 0; i < RUBLE_NOMINALS_COUNT; i++) {
            totalAmount += rubleNominals[i] * rubleCount[i];
        }
        
        // Сумма копеек
        for (int i = 0; i < KOPECK_NOMINALS_COUNT; i++) {
            totalAmount += kopeckNominals[i] * kopeckCount[i];
        }
    }
    
    // Нормализация (оптимизация количества купюр/монет)
    void normalize() {
        // Нормализация копеек
        for (int i = 0; i < KOPECK_NOMINALS_COUNT - 1; i++) {
            if (kopeckCount[i] >= 10) {
                int groups = kopeckCount[i] / 10;
                kopeckCount[i] %= 10;
                // Переводим в более крупные номиналы
                if (i > 0) {
                    kopeckCount[i-1] += groups;
                }
            }
        }
        
        // Нормализация рублей
        for (int i = RUBLE_NOMINALS_COUNT - 1; i > 0; i--) {
            if (rubleCount[i] >= 2) {
                int groups = rubleCount[i] / 2;
                rubleCount[i] %= 2;
                // Ищем подходящий номинал для объединения
                for (int j = 0; j < i; j++) {
                    if (rubleNominals[j] == rubleNominals[i] * 2) {
                        rubleCount[j] += groups;
                        break;
                    }
                }
            }
        }
        
        updateTotalAmount();
    }
    
    // Обнуление счетчиков
    void resetCounters() {
        for (int i = 0; i < RUBLE_NOMINALS_COUNT; i++) {
            rubleCount[i] = 0;
        }
        for (int i = 0; i < KOPECK_NOMINALS_COUNT; i++) {
            kopeckCount[i] = 0;
        }
    }

public:
    // Конструктор без аргументов
    Money() : totalAmount(0) {
        resetCounters();
    }
    
    // Конструктор инициализации из double
    Money(double amount) {
        resetCounters();
        setAmount(amount);
    }
    
    // Конструктор копирования
    Money(const Money& other) : totalAmount(other.totalAmount) {
        for (int i = 0; i < RUBLE_NOMINALS_COUNT; i++) {
            rubleCount[i] = other.rubleCount[i];
        }
        for (int i = 0; i < KOPECK_NOMINALS_COUNT; i++) {
            kopeckCount[i] = other.kopeckCount[i];
        }
    }
    
    // Установка суммы
    void setAmount(double amount) {
        resetCounters();
        
        int rubles = static_cast<int>(amount);
        double kopecks = round((amount - rubles) * 100) / 100;
        
        // Распределение рублей по номиналам
        int tempRubles = rubles;
        for (int i = 0; i < RUBLE_NOMINALS_COUNT; i++) {
            rubleCount[i] = tempRubles / rubleNominals[i];
            tempRubles %= rubleNominals[i];
        }
        
        // Распределение копеек по номиналам
        int totalKopecks = static_cast<int>(round(kopecks * 100));
        for (int i = 0; i < KOPECK_NOMINALS_COUNT; i++) {
            int kopeckValue = static_cast<int>(kopeckNominals[i] * 100);
            kopeckCount[i] = totalKopecks / kopeckValue;
            totalKopecks %= kopeckValue;
        }
        
        updateTotalAmount();
        normalize();
    }
    
    // Ввод с клавиатуры
    void read() {
        double amount;
        cout << "Введите сумму: ";
        cin >> amount;
        setAmount(amount);
    }
    
    // Вывод на экран
    void display() const {
        cout << "Сумма: " << fixed << setprecision(2) << totalAmount << " руб." << endl;
        cout << "Состав:" << endl;
        
        cout << "Рубли: ";
        bool hasRubles = false;
        for (int i = 0; i < RUBLE_NOMINALS_COUNT; i++) {
            if (rubleCount[i] > 0) {
                cout << rubleNominals[i] << " руб. x " << rubleCount[i] << "; ";
                hasRubles = true;
            }
        }
        if (!hasRubles) cout << "нет";
        cout << endl;
        
        cout << "Копейки: ";
        bool hasKopecks = false;
        for (int i = 0; i < KOPECK_NOMINALS_COUNT; i++) {
            if (kopeckCount[i] > 0) {
                cout << kopeckNominals[i] << " коп. x " << kopeckCount[i] << "; ";
                hasKopecks = true;
            }
        }
        if (!hasKopecks) cout << "нет";
        cout << endl;
    }
    
    // Получение общей суммы
    double getAmount() const {
        return totalAmount;
    }
    
    // Сложение сумм
    Money add(const Money& other) const {
        Money result;
        result.setAmount(this->totalAmount + other.totalAmount);
        return result;
    }
    
    // Вычитание сумм
    Money subtract(const Money& other) const {
        Money result;
        result.setAmount(this->totalAmount - other.totalAmount);
        return result;
    }
    
    // Деление сумм
    double divide(const Money& other) const {
        if (other.totalAmount == 0) {
            cout << "Ошибка: деление на ноль!" << endl;
            return 0;
        }
        return this->totalAmount / other.totalAmount;
    }
    
    // Деление суммы на дробное число
    Money divideByDouble(double divisor) const {
        if (divisor == 0) {
            cout << "Ошибка: деление на ноль!" << endl;
            return Money();
        }
        Money result;
        result.setAmount(this->totalAmount / divisor);
        return result;
    }
    
    // Умножение на дробное число
    Money multiplyByDouble(double multiplier) const {
        Money result;
        result.setAmount(this->totalAmount * multiplier);
        return result;
    }
    
    // Операции сравнения
    bool isEqual(const Money& other) const {
        return fabs(this->totalAmount - other.totalAmount) < 0.001;
    }
    
    bool isGreater(const Money& other) const {
        return this->totalAmount > other.totalAmount;
    }
    
    bool isLess(const Money& other) const {
        return this->totalAmount < other.totalAmount;
    }
};

int main() {
    cout << "=== ДЕМОНСТРАЦИЯ РАБОТЫ КЛАССА Money ===" << endl;
    
    // Конструктор без аргументов
    Money m1;
    cout << "\n1. Конструктор без аргументов:";
    m1.display();
    
    // Конструктор инициализации
    Money m2(1234.56);
    cout << "\n2. Конструктор инициализации (1234.56):";
    m2.display();
    
    // Конструктор копирования
    Money m3(m2);
    cout << "\n3. Конструктор копирования:";
    m3.display();
    
    // Ввод с клавиатуры
    Money m4;
    cout << "\n4. Ввод с клавиатуры:";
    m4.read();
    m4.display();
    
    // Сложение
    Money m5 = m2.add(m4);
    cout << "\n5. Сложение:";
    cout << "m2 + m4 = ";
    m5.display();
    
    // Вычитание
    Money m6 = m2.subtract(m4);
    cout << "\n6. Вычитание:";
    cout << "m2 - m4 = ";
    m6.display();
    
    // Деление сумм
    double divResult = m2.divide(m4);
    cout << "\n7. Деление сумм:";
    cout << "m2 / m4 = " << divResult << endl;
    
    // Деление на дробное число
    Money m7 = m2.divideByDouble(3.0);
    cout << "\n8. Деление на дробное число:";
    cout << "m2 / 3.0 = ";
    m7.display();
    
    // Умножение на дробное число
    Money m8 = m2.multiplyByDouble(1.5);
    cout << "\n9. Умножение на дробное число:";
    cout << "m2 * 1.5 = ";
    m8.display();
    
    // Сравнение
    cout << "\n10. Сравнение:";
    cout << "m2 == m3: " << (m2.isEqual(m3) ? "да" : "нет") << endl;
    cout << "m2 > m4: " << (m2.isGreater(m4) ? "да" : "нет") << endl;
    cout << "m2 < m4: " << (m2.isLess(m4) ? "да" : "нет") << endl;
    
    // Массив объектов
    cout << "\n11. Массив объектов:";
    Money moneyArray[3];
    moneyArray[0].setAmount(100.50);
    moneyArray[1].setAmount(200.75);
    moneyArray[2].setAmount(300.25);
    
    for (int i = 0; i < 3; i++) {
        cout << "moneyArray[" << i << "]: ";
        moneyArray[i].display();
    }
    
    return 0;
}
-----------------------------------------------------------------------------------------------------------------------
#include <iostream>
#include <string>
#include <cmath>
#include <iomanip>

using namespace std;

class Money {
private:
    // Номиналы рублей и копеек
    static const int RUBLE_NOMINALS_COUNT = 9;
    static const int KOPECK_NOMINALS_COUNT = 4;
    
    int rubleNominals[9] = {5000, 1000, 500, 100, 50, 10, 5, 2, 1};
    double kopeckNominals[4] = {0.5, 0.1, 0.05, 0.01};
    
    // Количество купюр/монет каждого номинала
    int rubleCount[9];
    int kopeckCount[4];
    
    // Общая сумма в рублях
    double totalAmount;
    
    // Обновление общей суммы
    void updateTotalAmount() {
        totalAmount = 0;
        
        // Сумма рублей
        for (int i = 0; i < RUBLE_NOMINALS_COUNT; i++) {
            totalAmount += rubleNominals[i] * rubleCount[i];
        }
        
        // Сумма копеек
        for (int i = 0; i < KOPECK_NOMINALS_COUNT; i++) {
            totalAmount += kopeckNominals[i] * kopeckCount[i];
        }
    }
    
    // Нормализация (оптимизация количества купюр/монет)
    void normalize() {
        // Нормализация копеек
        for (int i = 0; i < KOPECK_NOMINALS_COUNT - 1; i++) {
            if (kopeckCount[i] >= 10) {
                int groups = kopeckCount[i] / 10;
                kopeckCount[i] %= 10;
                // Переводим в более крупные номиналы
                if (i > 0) {
                    kopeckCount[i-1] += groups;
                }
            }
        }
        
        // Нормализация рублей
        for (int i = RUBLE_NOMINALS_COUNT - 1; i > 0; i--) {
            if (rubleCount[i] >= 2) {
                int groups = rubleCount[i] / 2;
                rubleCount[i] %= 2;
                // Ищем подходящий номинал для объединения
                for (int j = 0; j < i; j++) {
                    if (rubleNominals[j] == rubleNominals[i] * 2) {
                        rubleCount[j] += groups;
                        break;
                    }
                }
            }
        }
        
        updateTotalAmount();
    }
    
    // Обнуление счетчиков
    void resetCounters() {
        for (int i = 0; i < RUBLE_NOMINALS_COUNT; i++) {
            rubleCount[i] = 0;
        }
        for (int i = 0; i < KOPECK_NOMINALS_COUNT; i++) {
            kopeckCount[i] = 0;
        }
    }

public:
    // Конструктор без аргументов
    Money() : totalAmount(0) {
        resetCounters();
    }
    
    // Конструктор инициализации из double
    Money(double amount) {
        resetCounters();
        setAmount(amount);
    }
    
    // Конструктор копирования
    Money(const Money& other) : totalAmount(other.totalAmount) {
        for (int i = 0; i < RUBLE_NOMINALS_COUNT; i++) {
            rubleCount[i] = other.rubleCount[i];
        }
        for (int i = 0; i < KOPECK_NOMINALS_COUNT; i++) {
            kopeckCount[i] = other.kopeckCount[i];
        }
    }
    
    // Установка суммы
    void setAmount(double amount) {
        resetCounters();
        
        int rubles = static_cast<int>(amount);
        double kopecks = round((amount - rubles) * 100) / 100;
        
        // Распределение рублей по номиналам
        int tempRubles = rubles;
        for (int i = 0; i < RUBLE_NOMINALS_COUNT; i++) {
            rubleCount[i] = tempRubles / rubleNominals[i];
            tempRubles %= rubleNominals[i];
        }
        
        // Распределение копеек по номиналам
        int totalKopecks = static_cast<int>(round(kopecks * 100));
        for (int i = 0; i < KOPECK_NOMINALS_COUNT; i++) {
            int kopeckValue = static_cast<int>(kopeckNominals[i] * 100);
            kopeckCount[i] = totalKopecks / kopeckValue;
            totalKopecks %= kopeckValue;
        }
        
        updateTotalAmount();
        normalize();
    }
    
    // Получение общей суммы
    double getAmount() const {
        return totalAmount;
    }
    
    // Перегрузка операций
    
    // Сложение
    Money operator+(const Money& other) const {
        Money result;
        result.setAmount(this->totalAmount + other.totalAmount);
        return result;
    }
    
    // Вычитание
    Money operator-(const Money& other) const {
        Money result;
        result.setAmount(this->totalAmount - other.totalAmount);
        return result;
    }
    
    // Деление на Money (возвращает коэффициент)
    double operator/(const Money& other) const {
        if (other.totalAmount == 0) {
            throw runtime_error("Деление на ноль!");
        }
        return this->totalAmount / other.totalAmount;
    }
    
    // Деление на double
    Money operator/(double divisor) const {
        if (divisor == 0) {
            throw runtime_error("Деление на ноль!");
        }
        Money result;
        result.setAmount(this->totalAmount / divisor);
        return result;
    }
    
    // Умножение на double
    Money operator*(double multiplier) const {
        Money result;
        result.setAmount(this->totalAmount * multiplier);
        return result;
    }
    
    // Операции сравнения
    bool operator==(const Money& other) const {
        return fabs(this->totalAmount - other.totalAmount) < 0.001;
    }
    
    bool operator!=(const Money& other) const {
        return !(*this == other);
    }
    
    bool operator>(const Money& other) const {
        return this->totalAmount > other.totalAmount;
    }
    
    bool operator<(const Money& other) const {
        return this->totalAmount < other.totalAmount;
    }
    
    bool operator>=(const Money& other) const {
        return *this > other || *this == other;
    }
    
    bool operator<=(const Money& other) const {
        return *this < other || *this == other;
    }
    
    // Дружественные функции для операций с double слева
    
    // Умножение double на Money
    friend Money operator*(double multiplier, const Money& money) {
        return money * multiplier;
    }
    
    // Деление double на Money
    friend double operator/(double dividend, const Money& money) {
        if (money.totalAmount == 0) {
            throw runtime_error("Деление на ноль!");
        }
        return dividend / money.totalAmount;
    }
    
    // Перегрузка операций ввода/вывода
    friend ostream& operator<<(ostream& os, const Money& money) {
        os << fixed << setprecision(2) << money.totalAmount << " руб.";
        return os;
    }
    
    friend istream& operator>>(istream& is, Money& money) {
        double amount;
        is >> amount;
        money.setAmount(amount);
        return is;
    }
    
    // Метод для детального вывода
    void displayDetails() const {
        cout << "Сумма: " << *this << endl;
        cout << "Состав:" << endl;
        
        cout << "Рубли: ";
        bool hasRubles = false;
        for (int i = 0; i < RUBLE_NOMINALS_COUNT; i++) {
            if (rubleCount[i] > 0) {
                cout << rubleNominals[i] << " руб. x " << rubleCount[i] << "; ";
                hasRubles = true;
            }
        }
        if (!hasRubles) cout << "нет";
        cout << endl;
        
        cout << "Копейки: ";
        bool hasKopecks = false;
        for (int i = 0; i < KOPECK_NOMINALS_COUNT; i++) {
            if (kopeckCount[i] > 0) {
                cout << kopeckNominals[i] << " коп. x " << kopeckCount[i] << "; ";
                hasKopecks = true;
            }
        }
        if (!hasKopecks) cout << "нет";
        cout << endl;
    }
};

int main() {
    cout << "=== ДЕМОНСТРАЦИЯ ПЕРЕГРУЗКИ ОПЕРАЦИЙ ===" << endl;
    
    // Создание объектов
    Money m1(1000.50);
    Money m2(500.75);
    
    cout << "m1 = " << m1 << endl;
    cout << "m2 = " << m2 << endl;
    
    // Детальный вывод
    cout << "\nДетальный состав m1:" << endl;
    m1.displayDetails();
    
    // Перегрузка арифметических операций
    cout << "\n--- АРИФМЕТИЧЕСКИЕ ОПЕРАЦИИ ---" << endl;
    
    Money sum = m1 + m2;
    cout << "m1 + m2 = " << sum << endl;
    
    Money diff = m1 - m2;
    cout << "m1 - m2 = " << diff << endl;
    
    double ratio = m1 / m2;
    cout << "m1 / m2 = " << ratio << endl;
    
    Money divByDouble = m1 / 2.0;
    cout << "m1 / 2.0 = " << divByDouble << endl;
    
    Money mulByDouble = m1 * 1.5;
    cout << "m1 * 1.5 = " << mulByDouble << endl;
    
    Money mulDoubleByMoney = 3.0 * m1;
    cout << "3.0 * m1 = " << mulDoubleByMoney << endl;
    
    // Перегрузка операций сравнения
    cout << "\n--- ОПЕРАЦИИ СРАВНЕНИЯ ---" << endl;
    
    cout << "m1 == m2: " << (m1 == m2 ? "да" : "нет") << endl;
    cout << "m1 != m2: " << (m1 != m2 ? "да" : "нет") << endl;
    cout << "m1 > m2: " << (m1 > m2 ? "да" : "нет") << endl;
    cout << "m1 < m2: " << (m1 < m2 ? "да" : "нет") << endl;
    cout << "m1 >= m2: " << (m1 >= m2 ? "да" : "нет") << endl;
    cout << "m1 <= m2: " << (m1 <= m2 ? "да" : "нет") << endl;
    
    // Перегрузка ввода/вывода
    cout << "\n--- ВВОД/ВЫВОД ---" << endl;
    
    Money m3;
    cout << "Введите сумму для m3: ";
    cin >> m3;
    cout << "m3 = " << m3 << endl;
    
    // Массив объектов
    cout << "\n--- МАССИВ ОБЪЕКТОВ ---" << endl;
    
    Money moneyArray[3] = {Money(100.25), Money(200.50), Money(300.75)};
    for (int i = 0; i < 3; i++) {
        cout << "moneyArray[" << i << "] = " << moneyArray[i] << endl;
    }
    
    // Комбинированные операции
    cout << "\n--- КОМБИНИРОВАННЫЕ ОПЕРАЦИИ ---" << endl;
    
    Money result = (m1 + m2) * 0.5 - Money(100);
    cout << "(m1 + m2) * 0.5 - 100 руб. = " << result << endl;
    
    return 0;
}
