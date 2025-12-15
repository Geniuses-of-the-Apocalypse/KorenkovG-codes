#include <iostream>
#include <string>

using namespace std;

class Triad {
protected:
    int f;  // first - первое 
    int s;  // second - второе 
    int t;  // third - третье ч

public:
    Triad();
    Triad(int f, int s, int t);
    ~Triad();

    int getF() const;
    int getS() const;
    int getT() const;

    void setF(int f);
    void setS(int s);
    void setT(int t);

    void incF();
    void incS();
    void incT();

    string toString() const;

    void print() const;
    
    void input();

    friend ostream& operator<<(ostream& os, const Triad& triad); // операторы ввода-вывода
    friend istream& operator>>(istream& is, Triad& triad);
};

// -------------------------------методы класса Triad--------------------------------
Triad::Triad() : f(0), s(0), t(0) {}

Triad::Triad(int f, int s, int t) {
    setF(f);
    setS(s);
    setT(t);
}

Triad::~Triad() {}

int Triad::getF() const { return f; }
int Triad::getS() const { return s; }
int Triad::getT() const { return t; }

void Triad::setF(int v) {
    if (v < 0) {
        cout << "Ошибка: первое число не может быть отрицательным" << endl;
        exit(1);
    }
    f = v;
}

void Triad::setS(int v) {
    if (v < 0) {
        cout << "Ошибка: второе число не может быть отрицательным" << endl;
        exit(1);
    }
    s = v;
}

void Triad::setT(int v) {
    if (v < 0) {
        cout << "Ошибка: третье число не может быть отрицательным" << endl;
        exit(1);
    }
    t = v;
}

void Triad::incF() { f++; }
void Triad::incS() { s++; }
void Triad::incT() { t++; }

string Triad::toString() const {
    return "(" + to_string(f) + ", " + to_string(s) + ", " + to_string(t) + ")";
}

void Triad::print() const {
    cout << toString() << endl;
}

void Triad::input() {
    cout << "Введите три числа (через пробел): ";
    cin >> *this;  // Используем оператор ввода
}

// Оператор вывода для Triad
ostream& operator<<(ostream& os, const Triad& triad) {
    os << "(" << triad.f << ", " << triad.s << ", " << triad.t << ")";
    return os;
}

// Оператор ввода для Triad
istream& operator>>(istream& is, Triad& triad) {
    int a, b, c;
    is >> a >> b >> c;
    triad.setF(a);
    triad.setS(b);
    triad.setT(c);
    return is;
}

//-------------------------- класс Date -----------------------
class Date : public Triad {
private:
    bool isLeap(int y) const;  // вспомогательные методы
    int daysInM(int m, int y) const;
    void normalize();

public:
    Date();
    Date(int y, int m, int d);

    void setDate(int y, int m, int d);
    void setY(int y);
    void setM(int m);
    void setD(int d);

    void incF();
    void incS();
    void incT();

    void addDays(int n);

    string toString() const;
    void print() const;
    
    void input();

    int getY() const;
    int getM() const;
    int getD() const;

    // Операторы ввода-вывода
    friend ostream& operator<<(ostream& os, const Date& date);
    friend istream& operator>>(istream& is, Date& date);
};

bool Date::isLeap(int y) const { // проверка на високосный год
    return (y % 4 == 0 && y % 100 != 0) || (y % 400 == 0);
}

int Date::daysInM(int m, int y) const { // количество дней в месяце
    switch (m) {
        case 1: case 3: case 5: case 7: case 8: case 10: case 12:
            return 31;
        case 4: case 6: case 9: case 11:
            return 30;
        case 2:
            return isLeap(y) ? 29 : 28;
        default:
            return 0;
    }
}

void Date::normalize() { // нормализация даты
    while (t > daysInM(s, f)) {
        t -= daysInM(s, f);
        s++;
        if (s > 12) {
            s = 1;
            f++;
        }
    }
    
    while (t < 1) {
        s--;
        if (s < 1) {
            s = 12;
            f--;
        }
        t += daysInM(s, f);
    }
}

Date::Date() : Triad() {}

Date::Date(int y, int m, int d) {
    setDate(y, m, d);
}

void Date::setDate(int y, int m, int d) {
    if (y < 0) {
        cout << "Ошибка: год не может быть отрицательным" << endl;
        exit(1);
    }
    if (m < 1 || m > 12) {
        cout << "Ошибка: месяц должен быть от 1 до 12" << endl;
        exit(1);
    }
    if (d < 1 || d > daysInM(m, y)) {
        cout << "Ошибка: неверное количество дней" << endl;
        exit(1);
    }
    
    f = y;
    s = m;
    t = d;
}

void Date::setY(int y) {
    setDate(y, s, t);
}

void Date::setM(int m) {
    setDate(f, m, t);
}

void Date::setD(int d) {
    setDate(f, s, d);
}

// -----------------------переопределенные методы увеличения---------------------------
void Date::incF() {
    f++;
}

void Date::incS() {
    s++;
    if (s > 12) {
        s = 1;
        f++;
    }
    if (t > daysInM(s, f)) {
        t = daysInM(s, f);
    }
}

void Date::incT() {
    t++;
    if (t > daysInM(s, f)) {
        t = 1;
        incS();
    }
}

void Date::addDays(int n) { // добавление дней
    if (n < 0) {
        cout << "Ошибка: количество дней не может быть отрицательным" << endl;
        exit(1);
    }
    
    t += n;
    normalize();
}

string Date::toString() const {
    return to_string(t) + "." + to_string(s) + "." + to_string(f);
}

void Date::print() const {
    cout << *this << endl;  // Используем оператор вывода
}

void Date::input() {
    cout << "Введите дату (год месяц день через пробел): ";
    cin >> *this;  // Используем оператор ввода
}

int Date::getY() const { return f; }
int Date::getM() const { return s; }
int Date::getD() const { return t; }

// Оператор вывода для Date
ostream& operator<<(ostream& os, const Date& date) {
    os << "Дата: " << date.t << "." << date.s << "." << date.f;
    return os;
}

// Оператор ввода для Date
istream& operator>>(istream& is, Date& date) {
    int y, m, d;
    is >> y >> m >> d;
    date.setDate(y, m, d);
    return is;
}

void demoSub(Triad& t) {
    cout << "Принцип подстановки: " << t.toString() << endl;
}

void showMenu() { // меню
    cout << "\n=== МЕНЮ ===" << endl;
    cout << "1. Создать Triad" << endl;
    cout << "2. Создать Date" << endl;
    cout << "3. Показать все объекты" << endl;
    cout << "4. Демонстрация методов Triad" << endl;
    cout << "5. Демонстрация методов Date" << endl;
    cout << "6. Принцип подстановки" << endl;
    cout << "7. Выход" << endl;
    cout << "Выберите действие: ";
}

int main() {
    Triad* triadObj = nullptr;
    Date* dateObj = nullptr;
    int choice;
    
    do {
        showMenu();
        cin >> choice;
        
        switch(choice) {
            case 1: {
                if (triadObj != nullptr) {
                    delete triadObj;
                }
                triadObj = new Triad();
                cout << "Введите данные для Triad:" << endl;
                triadObj->input();
                cout << "Triad создан: " << *triadObj << endl;  // используем оператор вывода
                break;
            }
            
            case 2: {
                if (dateObj != nullptr) {
                    delete dateObj;
                }
                dateObj = new Date();
                cout << "Введите данные для Date:" << endl;
                dateObj->input();
                cout << "Date создана: " << *dateObj << endl;  // используем оператор вывода
                break;
            }
            
            case 3: {
                cout << "\n--- Все объекты ---" << endl;
                if (triadObj != nullptr) {
                    cout << "Triad: " << *triadObj << endl;  // используем оператор вывода
                } else {
                    cout << "Triad: не создан" << endl;
                }
                
                if (dateObj != nullptr) {
                    cout << "Date: " << *dateObj << endl;  // используем оператор вывода
                } else {
                    cout << "Date: не создана" << endl;
                }
                break;
            }
            
            case 4: {
                if (triadObj != nullptr) {
                    cout << "\n--- Демонстрация Triad ---" << endl;
                    cout << "Текущий объект: " << *triadObj << endl;  // используем оператор вывода
                    
                    cout << "Увеличиваем все поля на 1..." << endl;
                    triadObj->incF();
                    triadObj->incS();
                    triadObj->incT();
                    cout << "После увеличения: " << *triadObj << endl;  // используем оператор вывода
                    
                    cout << "Хотите изменить значения? (1-да, 0-нет): ";
                    int change;
                    cin >> change;
                    if (change == 1) {
                        cout << "Введите новые значения для Triad: ";
                        cin >> *triadObj;  // используем оператор ввода
                        cout << "После изменения: " << *triadObj << endl;  // ииспользуем оператор вывода
                    }
                } else {
                    cout << "Сначала создайте Triad!" << endl;
                }
                break;
            }
            
            case 5: {
                if (dateObj != nullptr) {
                    cout << "\n--- Демонстрация Date ---" << endl;
                    cout << "Текущая дата: " << *dateObj << endl;  // используем оператор вывода
                    
                    cout << "1. Увеличить год" << endl;
                    cout << "2. Увеличить месяц" << endl;
                    cout << "3. Увеличить день" << endl;
                    cout << "4. Добавить дни" << endl;
                    cout << "Выберите действие: ";
                    int dateChoice;
                    cin >> dateChoice;
                    
                    switch(dateChoice) {
                        case 1:
                            dateObj->incF();
                            cout << "После увеличения года: " << *dateObj << endl;  // используем оператор вывода
                            break;
                        case 2:
                            dateObj->incS();
                            cout << "После увеличения месяца: " << *dateObj << endl;  // используем оператор вывода
                            break;
                        case 3:
                            dateObj->incT();
                            cout << "После увеличения дня: " << *dateObj << endl;  // используем оператор вывода
                            break;
                        case 4:
                            cout << "Введите количество дней для добавления: ";
                            int days;
                            cin >> days;
                            dateObj->addDays(days);
                            cout << "После добавления " << days << " дней: " << *dateObj << endl;  // используем оператор вывода
                            break;
                        default:
                            cout << "Неверный выбор!" << endl;
                    }
                } else {
                    cout << "Сначала создайте Date!" << endl;
                }
                break;
            }
            
            case 6: {
                cout << "\n--- Принцип подстановки ---" << endl;
                if (triadObj != nullptr) {
                    cout << "Через указатель на Triad: ";
                    demoSub(*triadObj);
                }
                if (dateObj != nullptr) {
                    cout << "Через указатель на Triad (объект Date): ";
                    Triad* p = dateObj;
                    demoSub(*p);
                }
                break;
            }
            
            case 7:
                cout << "Выход из программы..." << endl;
                break;
                
            default:
                cout << "Неверный выбор!" << endl;
        }
        
    } while (choice != 7);
    
    if (triadObj != nullptr) delete triadObj;
    if (dateObj != nullptr) delete dateObj;
    
    return 0;
}
