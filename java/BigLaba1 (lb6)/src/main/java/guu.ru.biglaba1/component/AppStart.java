// component/AppStart.java
package guu.ru.biglaba1.component;

import lombok.extern.log4j.Log4j2;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.beans.factory.annotation.Value;
import org.springframework.stereotype.Service;

import java.util.Scanner;


 /// @Service - регистрирует класс как Spring бин
 /// @Log4j2 - автоматически создает поле log для логирования


@Service
@Log4j2
public class AppStart {

    @Value("${numbers.to.convert:10,20,30,40,50,100,255,512,1000}") //appication
    private int[] defaultNumbers;

    @Value("${interactive.mode:false}") //appication
    private boolean interactiveMode;


    @Autowired
    private NumberConversionService conversionService;


    public void start() { /// log.info() - выводит информационное сообщение в консоль
                          /// \n - символ переноса строки
        log.info("");
        log.info("ПРЕОБРАЗОВАТЕЛЬ СИСТЕМ СЧИСЛЕНИЯ");
        log.info("Преобразование десятичных чисел в различные системы");
        log.info("\n");

        if (interactiveMode) { // Проверяем режим работы
            runInteractiveMode(); // Пользователь вводит числа вручную
        } else {
            runDemoMode(); // Используем предустановленный набор чисел
        }
    }

    private void runDemoMode() {
        log.info(" ДЕМОНСТРАЦИОННЫЙ РЕЖИМ");
        log.info("Преобразование чисел: {}", java.util.Arrays.toString(defaultNumbers));
        log.info("----------------------------------------\n");

        conversionService.convertNumbers(defaultNumbers); // Вызываем сервис для преобразования массива чисел
    }


    private void runInteractiveMode() {
        log.info(" ИНТЕРАКТИВНЫЙ РЕЖИМ");
        log.info("Введите числа для преобразования (через пробел или запятую)");
        log.info("Для выхода введите 'exit'\n");

        Scanner scanner = new Scanner(System.in); // Scanner - класс для чтения ввода с консоли

        while (true) {  // Бесконечный цикл, пока пользователь не введет "exit"
            System.out.print("\nВведите числа: ");
            String input = scanner.nextLine().trim();  // Читаем строку и убираем пробелы по краям

            if (input.equalsIgnoreCase("exit")) {  // Проверяем, хочет ли пользователь выйти
                log.info("До свидания!");
                break;
            }

            try {

                /// РАЗБОР ВВОДА ПОЛЬЗОВАТЕЛЯ
                /// split("[ ,]+") - разбивает строку по пробелам и/или запятым
                /// Например: "10,20,30" -> ["10", "20", "30"]
                /// "10 20 30" -> ["10", "20", "30"]
                /// "10,20 30" -> ["10", "20", "30"]

                String[] numberStrings = input.split("[ ,]+");
                int[] numbers = new int[numberStrings.length];

                for (int i = 0; i < numberStrings.length; i++) {
                    numbers[i] = Integer.parseInt(numberStrings[i]);
                }

                conversionService.convertNumbers(numbers); // Вызываем сервис для преобразования

            } catch (NumberFormatException e) { // Если пользователь ввел не число (например, "abc")
                log.error("Ошибка: введите корректные целые числа");
            }
        }

        scanner.close(); // Закрываем сканер (освобождаем ресурсы)
    }

    public void showConverterInfo() {
        log.info(conversionService.getConverterInfo());
    }
}