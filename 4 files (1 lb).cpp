#include <iostream>
#include <string>
#include <cmath>

using namespace std;

// Структура для представления даты
struct Date {
    int year;
    int month;
    int day;
    
    Date(int y, int m, int d) : year(y), month(m), day(d) {}
};

// Собственные классы исключений вместо стандартных
class InvalidArgument {
private:
    string message;
public:
    InvalidArgument(const string& msg) : message(msg) {}
    const string& what() const { return message; }
};

class RuntimeError {
private:
    string message;
public:
    RuntimeError(const string& msg) : message(msg) {}
    const string& what() const { return message; }
};

// 1. Пустой класс для исключения
class DateExceptionEmpty {};

// 2. Независимый класс с полями-параметрами функции
class DateExceptionWithFields {
public:
    Date date1;
    Date date2;
    string message;
    
    DateExceptionWithFields(const Date& d1, const Date& d2, const string& msg) 
        : date1(d1), date2(d2), message(msg) {}
};

// 3. Наследник от собственного базового исключения с полями
class DateExceptionBase {
protected:
    string message;
public:
    DateExceptionBase(const string& msg) : message(msg) {}
    virtual const string& what() const { return message; }
    virtual ~DateExceptionBase() {}
};

class DateExceptionStd : public DateExceptionBase {
public:
    Date date1;
    Date date2;
    
    DateExceptionStd(const Date& d1, const Date& d2, const string& msg) 
        : DateExceptionBase(msg), date1(d1), date2(d2) {}
};

// Вспомогательные функции
bool isLeapYear(int year) {
    return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}

int daysInMonth(int month, int year) {
    if (month == 2) {
        return isLeapYear(year) ? 29 : 28;
    }
    if (month == 4 || month == 6 || month == 9 || month == 11) {
        return 30;
    }
    return 31;
}

bool isValidDate(const Date& date) {
    if (date.year < 0) return false;
    if (date.month < 1 || date.month > 12) return false;
    if (date.day < 1 || date.day > daysInMonth(date.month, date.year)) return false;
    return true;
}

// Функция для вычисления количества дней от начала эпохи до даты
int daysFromEpoch(const Date& date) {
    int days = date.day;
    
    // Добавляем дни из полных месяцев текущего года
    for (int m = 1; m < date.month; m++) {
        days += daysInMonth(m, date.year);
    }
    
    // Добавляем дни из полных лет
    for (int y = 0; y < date.year; y++) {
        days += isLeapYear(y) ? 366 : 365;
    }
    
    return days;
}

// ВАРИАНТ 1: Без спецификации исключений
int dateDifference1(const Date& date1, const Date& date2) {
    // Проверка валидности дат
    if (!isValidDate(date1)) {
        throw RuntimeError("Первая дата невалидна");
    }
    if (!isValidDate(date2)) {
        throw RuntimeError("Вторая дата невалидна");
    }
    
    int days1 = daysFromEpoch(date1);
    int days2 = daysFromEpoch(date2);
    
    return abs(days2 - days1);
}

// ВАРИАНТ 2: Со спецификацией throw()
int dateDifference2(const Date& date1, const Date& date2) throw() {
    if (!isValidDate(date1)) {
        throw DateExceptionEmpty();
    }
    if (!isValidDate(date2)) {
        throw DateExceptionEmpty();
    }
    
    int days1 = daysFromEpoch(date1);
    int days2 = daysFromEpoch(date2);
    
    return abs(days2 - days1);
}

// ВАРИАНТ 3: С конкретной спецификацией с подходящим исключением
int dateDifference3(const Date& date1, const Date& date2) throw(InvalidArgument) {
    if (!isValidDate(date1)) {
        throw InvalidArgument("Первая дата невалидна: " + 
                              to_string(date1.day) + "." + 
                              to_string(date1.month) + "." + 
                              to_string(date1.year));
    }
    if (!isValidDate(date2)) {
        throw InvalidArgument("Вторая дата невалидна: " + 
                              to_string(date2.day) + "." + 
                              to_string(date2.month) + "." + 
                              to_string(date2.year));
    }
    
    int days1 = daysFromEpoch(date1);
    int days2 = daysFromEpoch(date2);
    
    return abs(days2 - days1);
}

// ВАРИАНТ 4: Спецификация с собственным реализованным исключением
int dateDifference4(const Date& date1, const Date& date2) throw(DateExceptionStd) {
    if (!isValidDate(date1)) {
        throw DateExceptionStd(date1, date2, 
                             "Первая дата невалидна: " + 
                             to_string(date1.day) + "." + 
                             to_string(date1.month) + "." + 
                             to_string(date1.year));
    }
    if (!isValidDate(date2)) {
        throw DateExceptionStd(date1, date2,
                             "Вторая дата невалидна: " + 
                             to_string(date2.day) + "." + 
                             to_string(date2.month) + "." + 
                             to_string(date2.year));
    }
    
    int days1 = daysFromEpoch(date1);
    int days2 = daysFromEpoch(date2);
    
    return abs(days2 - days1);
}

// Функция для преобразования числа в строку (замена std::to_string)
string intToString(int value) {
    if (value == 0) return "0";
    
    string result;
    bool negative = false;
    
    if (value < 0) {
        negative = true;
        value = -value;
    }
    
    while (value > 0) {
        char digit = '0' + (value % 10);
        result = digit + result;
        value /= 10;
    }
    
    if (negative) {
        result = "-" + result;
    }
    
    return result;
}

// Демонстрация работы всех вариантов
int main() {
    cout << "=== Демонстрация работы с исключениями для разности дат ===" << endl;
    
    // Тестовые данные
    Date validDate1(2023, 1, 15);
    Date validDate2(2023, 12, 31);
    Date invalidDate1(2023, 2, 30);  // Невалидная дата
    Date invalidDate2(2023, 13, 1);  // Невалидная дата
    
    // ТЕСТ 1: Без спецификации исключений
    cout << "\n--- ТЕСТ 1: Без спецификации исключений ---" << endl;
    try {
        int diff1 = dateDifference1(validDate1, validDate2);
        cout << "Разница между датами: " << diff1 << " дней" << endl;
        
        // Проверим с невалидной датой
        int diff2 = dateDifference1(invalidDate1, validDate2);
        cout << "Эта строка не должна выводиться" << endl;
    }
    catch (const RuntimeError& e) {
        cout << "Поймано исключение: " << e.what() << endl;
    }
    catch (...) {
        cout << "Поймано неизвестное исключение" << endl;
    }
    
    // ТЕСТ 2: Со спецификацией throw()
    cout << "\n--- ТЕСТ 2: Со спецификацией throw() ---" << endl;
    try {
        int diff1 = dateDifference2(validDate1, validDate2);
        cout << "Разница между датами: " << diff1 << " дней" << endl;
        
        // Проверим с невалидной датой
        int diff2 = dateDifference2(validDate1, invalidDate2);
        cout << "Эта строка не должна выводиться" << endl;
    }
    catch (const DateExceptionEmpty&) {
        cout << "Поймано исключение DateExceptionEmpty" << endl;
    }
    catch (...) {
        cout << "Поймано другое исключение" << endl;
    }
    
    // ТЕСТ 3: С конкретной спецификацией с исключением
    cout << "\n--- ТЕСТ 3: С исключением InvalidArgument ---" << endl;
    try {
        int diff1 = dateDifference3(validDate1, validDate2);
        cout << "Разница между датами: " << diff1 << " дней" << endl;
        
        // Проверим с невалидной датой
        int diff2 = dateDifference3(invalidDate1, invalidDate2);
        cout << "Эта строка не должна выводиться" << endl;
    }
    catch (const InvalidArgument& e) {
        cout << "Поймано исключение InvalidArgument: " << e.what() << endl;
    }
    catch (...) {
        cout << "Поймано другое исключение" << endl;
    }
    
    // ТЕСТ 4: С собственным исключением (наследник базового)
    cout << "\n--- ТЕСТ 4: С собственным исключением ---" << endl;
    try {
        int diff1 = dateDifference4(validDate1, validDate2);
        cout << "Разница между датами: " << diff1 << " дней" << endl;
        
        // Проверим с невалидной датой
        int diff2 = dateDifference4(validDate1, invalidDate1);
        cout << "Эта строка не должна выводиться" << endl;
    }
    catch (const DateExceptionStd& e) {
        cout << "Поймано исключение DateExceptionStd: " << e.what() << endl;
        cout << "Дата1: " << e.date1.day << "." << e.date1.month << "." << e.date1.year << endl;
        cout << "Дата2: " << e.date2.day << "." << e.date2.month << "." << e.date2.year << endl;
    }
    catch (...) {
        cout << "Поймано другое исключение" << endl;
    }
    
    // ТЕСТ 5: Демонстрация работы с независимым классом исключения
    cout << "\n--- ТЕСТ 5: Независимый класс исключения ---" << endl;
    try {
        // Используем функцию без спецификации, но бросаем наш класс
        if (!isValidDate(invalidDate2)) {
            throw DateExceptionWithFields(validDate1, invalidDate2, 
                                        "Обнаружена невалидная дата в операции");
        }
    }
    catch (const DateExceptionWithFields& e) {
        cout << "Поймано исключение DateExceptionWithFields: " << e.message << endl;
        cout << "Дата1: " << e.date1.day << "." << e.date1.month << "." << e.date1.year << endl;
        cout << "Дата2: " << e.date2.day << "." << e.date2.month << "." << e.date2.year << endl;
    }
    
    // ТЕСТ 6: Демонстрация корректных вычислений
    cout << "\n--- ТЕСТ 6: Корректные вычисления ---" << endl;
    Date date1(2023, 1, 1);
    Date date2(2023, 1, 15);
    Date date3(2024, 1, 1);  // Високосный год
    
    try {
        cout << "Разница между 01.01.2023 и 15.01.2023: " 
             << dateDifference1(date1, date2) << " дней" << endl;
        cout << "Разница между 01.01.2023 и 01.01.2024: " 
             << dateDifference1(date1, date3) << " дней" << endl;
             
        // Проверим граничные случаи
        Date date4(2000, 2, 29); // Високосный год
        Date date5(2000, 3, 1);
        cout << "Разница между 29.02.2000 и 01.03.2000: " 
             << dateDifference1(date4, date5) << " дней" << endl;
    }
    catch (const RuntimeError& e) {
        cout << "Ошибка: " << e.what() << endl;
    }
    catch (const InvalidArgument& e) {
        cout << "Ошибка: " << e.what() << endl;
    }
    
    // ТЕСТ 7: Демонстрация всех типов исключений в одном блоке
    cout << "\n--- ТЕСТ 7: Обработка разных исключений в одном блоке ---" << endl;
    
    // Массив тестовых случаев
    struct TestCase {
        Date date1;
        Date date2;
        string description;
    };
    
    TestCase testCases[] = {
        {validDate1, validDate2, "Обе даты валидны"},
        {invalidDate1, validDate2, "Первая дата невалидна"},
        {validDate1, invalidDate2, "Вторая дата невалидна"},
        {invalidDate1, invalidDate2, "Обе даты невалидны"}
    };
    
    for (int i = 0; i < 4; i++) {
        cout << "\nТест " << (i + 1) << ": " << testCases[i].description << endl;
        
        try {
            int diff = dateDifference1(testCases[i].date1, testCases[i].date2);
            cout << "Успех! Разница: " << diff << " дней" << endl;
        }
        catch (const RuntimeError& e) {
            cout << "RuntimeError: " << e.what() << endl;
        }
        catch (const DateExceptionEmpty&) {
            cout << "DateExceptionEmpty поймано" << endl;
        }
        catch (const InvalidArgument& e) {
            cout << "InvalidArgument: " << e.what() << endl;
        }
        catch (const DateExceptionStd& e) {
            cout << "DateExceptionStd: " << e.what() << endl;
        }
        catch (...) {
            cout << "Неизвестное исключение" << endl;
        }
    }
    
    return 0;
}
