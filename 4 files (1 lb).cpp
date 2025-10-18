#include <iostream>
#include <string>

using namespace std;

// Структура для представления времени
struct Time {
    int hour;
    int minute;
    int second;
    
    Time(int h = 0, int m = 0, int s = 0) : hour(h), minute(m), second(s) {}
};

// 1. Пустой класс для исключения
class EmptyTimeException {};

// 2. Независимый класс с полями-параметрами функции
class TimeExceptionWithFields {
public:
    Time start;
    Time end;
    string message;
    
    TimeExceptionWithFields(const Time& s, const Time& e, const string& msg) 
        : start(s), end(e), message(msg) {}
};

// 3. Наследник от базового исключения с полями
class BaseTimeException {
protected:
    string message;
public:
    BaseTimeException(const string& msg) : message(msg) {}
    virtual const string& what() const { return message; }
    virtual ~BaseTimeException() {}
};

class TimeExceptionStd : public BaseTimeException {
public:
    Time start;
    Time end;
    
    TimeExceptionStd(const Time& s, const Time& e, const string& msg) 
        : BaseTimeException(msg), start(s), end(e) {}
};

// Вспомогательные функции
bool isValidTime(const Time& time) {
    if (time.hour < 0 || time.hour > 23) return false;
    if (time.minute < 0 || time.minute > 59) return false;
    if (time.second < 0 || time.second > 59) return false;
    return true;
}

// Функция для преобразования времени в секунды
int timeToSeconds(const Time& time) {
    return time.hour * 3600 + time.minute * 60 + time.second;
}

// Функция для преобразования числа в строку
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

// ВАРИАНТ 1: Без спецификации исключений
int callDuration1(const Time& start, const Time& end) {
    // Проверка валидности времени
    if (!isValidTime(start)) {
        throw string("Время начала разговора невалидно");
    }
    if (!isValidTime(end)) {
        throw string("Время окончания разговора невалидно");
    }
    
    int startSeconds = timeToSeconds(start);
    int endSeconds = timeToSeconds(end);
    
    // Если время окончания меньше времени начала, считаем что разговор перешел через полночь
    if (endSeconds < startSeconds) {
        endSeconds += 24 * 3600; // Добавляем сутки
    }
    
    int durationSeconds = endSeconds - startSeconds;
    
    // Переводим секунды в минуты, неполная минута считается за полную
    int durationMinutes = durationSeconds / 60;
    if (durationSeconds % 60 != 0) {
        durationMinutes++; // Неполная минута считается за полную
    }
    
    return durationMinutes;
}

// ВАРИАНТ 2: Со спецификацией throw()
int callDuration2(const Time& start, const Time& end) throw() {
    if (!isValidTime(start)) {
        throw EmptyTimeException();
    }
    if (!isValidTime(end)) {
        throw EmptyTimeException();
    }
    
    int startSeconds = timeToSeconds(start);
    int endSeconds = timeToSeconds(end);
    
    if (endSeconds < startSeconds) {
        endSeconds += 24 * 3600;
    }
    
    int durationSeconds = endSeconds - startSeconds;
    int durationMinutes = durationSeconds / 60;
    if (durationSeconds % 60 != 0) {
        durationMinutes++;
    }
    
    return durationMinutes;
}

// ВАРИАНТ 3: С конкретной спецификацией
int callDuration3(const Time& start, const Time& end) throw(const char*) {
    if (!isValidTime(start)) {
        throw "Время начала разговора невалидно";
    }
    if (!isValidTime(end)) {
        throw "Время окончания разговора невалидно";
    }
    
    int startSeconds = timeToSeconds(start);
    int endSeconds = timeToSeconds(end);
    
    if (endSeconds < startSeconds) {
        endSeconds += 24 * 3600;
    }
    
    int durationSeconds = endSeconds - startSeconds;
    int durationMinutes = durationSeconds / 60;
    if (durationSeconds % 60 != 0) {
        durationMinutes++;
    }
    
    return durationMinutes;
}

// ВАРИАНТ 4: Спецификация с собственным реализованным исключением
int callDuration4(const Time& start, const Time& end) throw(TimeExceptionStd) {
    if (!isValidTime(start)) {
        throw TimeExceptionStd(start, end, 
                             "Время начала разговора невалидно: " + 
                             intToString(start.hour) + ":" + 
                             intToString(start.minute) + ":" + 
                             intToString(start.second));
    }
    if (!isValidTime(end)) {
        throw TimeExceptionStd(start, end,
                             "Время окончания разговора невалидно: " + 
                             intToString(end.hour) + ":" + 
                             intToString(end.minute) + ":" + 
                             intToString(end.second));
    }
    
    int startSeconds = timeToSeconds(start);
    int endSeconds = timeToSeconds(end);
    
    if (endSeconds < startSeconds) {
        endSeconds += 24 * 3600;
    }
    
    int durationSeconds = endSeconds - startSeconds;
    int durationMinutes = durationSeconds / 60;
    if (durationSeconds % 60 != 0) {
        durationMinutes++;
    }
    
    return durationMinutes;
}

// Демонстрация работы всех вариантов
int main() {
    cout << "=== ВАРИАНТ 13: Вычисление продолжительности телефонного разговора в минутах ===" << endl;
    cout << "=== Демонстрация четырех вариантов обработки исключений ===" << endl;
    
    // Тестовые данные
    Time validStart1(10, 30, 15);
    Time validEnd1(10, 45, 30);
    Time validStart2(23, 55, 0);
    Time validEnd2(0, 5, 0);    // Разговор через полночь
    Time invalidTime1(25, 30, 0);  // Невалидное время (часы > 23)
    Time invalidTime2(10, 70, 0);  // Невалидное время (минуты > 59)
    Time invalidTime3(10, 30, 70); // Невалидное время (секунды > 59)
    
    cout << "\nТестовые времена:" << endl;
    cout << "Валидное начало 1: " << validStart1.hour << ":" << validStart1.minute << ":" << validStart1.second << endl;
    cout << "Валидное окончание 1: " << validEnd1.hour << ":" << validEnd1.minute << ":" << validEnd1.second << endl;
    cout << "Валидное начало 2: " << validStart2.hour << ":" << validStart2.minute << ":" << validStart2.second << endl;
    cout << "Валидное окончание 2: " << validEnd2.hour << ":" << validEnd2.minute << ":" << validEnd2.second << endl;
    cout << "Невалидное время 1: " << invalidTime1.hour << ":" << invalidTime1.minute << ":" << invalidTime1.second << endl;
    cout << "Невалидное время 2: " << invalidTime2.hour << ":" << invalidTime2.minute << ":" << invalidTime2.second << endl;
    
    // ТЕСТ 1: Без спецификации исключений
    cout << "\n--- ТЕСТ 1: Без спецификации исключений ---" << endl;
    try {
        cout << "Попытка вычисления с валидными временами..." << endl;
        int duration1 = callDuration1(validStart1, validEnd1);
        cout << "Успех! Продолжительность разговора: " << duration1 << " минут" << endl;
        
        cout << "Попытка вычисления с невалидным временем..." << endl;
        int duration2 = callDuration1(invalidTime1, validEnd1);
        cout << "Эта строка не должна выводиться" << endl;
    }
    catch (const string& e) {
        cout << "Поймано исключение string: " << e << endl;
    }
    catch (...) {
        cout << "Поймано неизвестное исключение" << endl;
    }
    
    // ТЕСТ 2: Со спецификацией throw()
    cout << "\n--- ТЕСТ 2: Со спецификацией throw() ---" << endl;
    try {
        cout << "Попытка вычисления с валидными временами..." << endl;
        int duration1 = callDuration2(validStart1, validEnd1);
        cout << "Успех! Продолжительность разговора: " << duration1 << " минут" << endl;
        
        cout << "Попытка вычисления с невалидным временем..." << endl;
        int duration2 = callDuration2(validStart1, invalidTime2);
        cout << "Эта строка не должна выводиться" << endl;
    }
    catch (const EmptyTimeException&) {
        cout << "Поймано исключение EmptyTimeException" << endl;
    }
    catch (...) {
        cout << "Поймано другое исключение" << endl;
    }
    
    // ТЕСТ 3: С конкретной спецификацией
    cout << "\n--- ТЕСТ 3: С конкретной спецификацией (const char*) ---" << endl;
    try {
        cout << "Попытка вычисления с валидными временами..." << endl;
        int duration1 = callDuration3(validStart1, validEnd1);
        cout << "Успех! Продолжительность разговора: " << duration1 << " минут" << endl;
        
        cout << "Попытка вычисления с невалидными временами..." << endl;
        int duration2 = callDuration3(invalidTime1, invalidTime2);
        cout << "Эта строка не должна выводиться" << endl;
    }
    catch (const char* e) {
        cout << "Поймано исключение const char*: " << e << endl;
    }
    catch (...) {
        cout << "Поймано другое исключение" << endl;
    }
    
    // ТЕСТ 4: С собственным исключением (наследник базового)
    cout << "\n--- ТЕСТ 4: С собственным исключением ---" << endl;
    try {
        cout << "Попытка вычисления с валидными временами..." << endl;
        int duration1 = callDuration4(validStart1, validEnd1);
        cout << "Успех! Продолжительность разговора: " << duration1 << " минут" << endl;
        
        cout << "Попытка вычисления с невалидным временем..." << endl;
        int duration2 = callDuration4(validStart1, invalidTime3);
        cout << "Эта строка не должна выводиться" << endl;
    }
    catch (const TimeExceptionStd& e) {
        cout << "Поймано исключение TimeExceptionStd: " << e.what() << endl;
        cout << "Начало: " << e.start.hour << ":" << e.start.minute << ":" << e.start.second << endl;
        cout << "Окончание: " << e.end.hour << ":" << e.end.minute << ":" << e.end.second << endl;
    }
    catch (...) {
        cout << "Поймано другое исключение" << endl;
    }
    
    // ТЕСТ 5: Демонстрация работы с независимым классом исключения
    cout << "\n--- ТЕСТ 5: Независимый класс исключения ---" << endl;
    try {
        cout << "Проверка валидности времени..." << endl;
        if (!isValidTime(invalidTime1)) {
            throw TimeExceptionWithFields(validStart1, invalidTime1, 
                                        "Обнаружено невалидное время в операции");
        }
    }
    catch (const TimeExceptionWithFields& e) {
        cout << "Поймано исключение TimeExceptionWithFields: " << e.message << endl;
        cout << "Начало: " << e.start.hour << ":" << e.start.minute << ":" << e.start.second << endl;
        cout << "Окончание: " << e.end.hour << ":" << e.end.minute << ":" << e.end.second << endl;
    }
    
    // ТЕСТ 6: Демонстрация корректных вычислений с разными сценариями
    cout << "\n--- ТЕСТ 6: Корректные вычисления ---" << endl;
    
    Time testCases[][2] = {
        {Time(10, 0, 0), Time(10, 15, 0)},     // Ровно 15 минут
        {Time(10, 0, 0), Time(10, 15, 30)},    // 15 минут 30 секунд -> 16 минут
        {Time(10, 0, 0), Time(10, 0, 45)},     // 45 секунд -> 1 минута
        {Time(23, 55, 0), Time(0, 5, 0)},      // Через полночь
        {Time(10, 30, 0), Time(10, 30, 1)}     // 1 секунда -> 1 минута
    };
    
    string descriptions[] = {
        "Ровно 15 минут",
        "15 минут 30 секунд (неполная минута)",
        "45 секунд (неполная минута)", 
        "Через полночь (10 минут)",
        "1 секунда (неполная минута)"
    };
    
    for (int i = 0; i < 5; i++) {
        try {
            int duration = callDuration1(testCases[i][0], testCases[i][1]);
            cout << descriptions[i] << ": " << duration << " минут" << endl;
            cout << "  (" << testCases[i][0].hour << ":" << testCases[i][0].minute << ":" << testCases[i][0].second;
            cout << " -> " << testCases[i][1].hour << ":" << testCases[i][1].minute << ":" << testCases[i][1].second << ")" << endl;
        }
        catch (...) {
            cout << "Ошибка при вычислении для " << descriptions[i] << endl;
        }
    }
    
    // ТЕСТ 7: Демонстрация обработки граничных случаев
    cout << "\n--- ТЕСТ 7: Граничные случаи ---" << endl;
    
    Time edgeCases[][2] = {
        {Time(0, 0, 0), Time(0, 0, 59)},   // 59 секунд -> 1 минута
        {Time(0, 0, 0), Time(0, 1, 0)},    // Ровно 1 минута
        {Time(23, 59, 0), Time(0, 1, 0)},  // Через полночь (2 минуты)
        {Time(0, 0, 0), Time(23, 59, 59)}  // Почти полные сутки
    };
    
    string edgeDescriptions[] = {
        "59 секунд (неполная минута)",
        "Ровно 1 минута",
        "Через полночь 2 минуты", 
        "Почти полные сутки"
    };
    
    for (int i = 0; i < 4; i++) {
        try {
            int duration = callDuration1(edgeCases[i][0], edgeCases[i][1]);
            cout << edgeDescriptions[i] << ": " << duration << " минут" << endl;
        }
        catch (...) {
            cout << "Ошибка при вычислении для " << edgeDescriptions[i] << endl;
        }
    }
    
    cout << "\n=== Программа завершена ===" << endl;
    return 0;
}
