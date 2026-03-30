// Biglaba1Application.java
package guu.ru.biglaba1;

import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.SpringBootApplication;
import org.springframework.context.ConfigurableApplicationContext;
import guu.ru.biglaba1.component.AppStart;

///Spring Boot автоматически настраивает все компоненты и запускает приложение.

@SpringBootApplication
/// @Configuration - говорит Spring, что здесь есть конфигурация
/// @EnableAutoConfiguration - включает автоматическую настройку Spring Boot
/// @ComponentScan - сканирует все классы с аннотациями @Component, @Service и др.

public class Biglaba1Application {

    public static void main(String[] args) {
        SpringApplication app = new SpringApplication(Biglaba1Application.class); // Создаем объект SpringApplication для настройки перед запуском
        app.setBanner((environment, sourceClass, out) -> { // setBanner() позволяет изменить приветственное сообщение при запуске
            out.println("\n");
            out.println("КОНВЕРТЕР СИСТЕМ СЧИСЛЕНИЯ v1.0");
            out.println("Преобразование десятичных чисел в:");
            out.println("• Двоичную (binary)");
            out.println("• Восьмеричную (octal)");
            out.println("• Шестнадцатеричную (hex)");
            out.println("\n");
        });

        ConfigurableApplicationContext context = app.run(args);
        /// app.run(args) делает следующее:
        /// 1. Запускает встроенный сервер (если есть веб-компоненты)
        /// 2. Сканирует все классы в пакете guu.ru.biglaba1 и подпакетах
        /// 3. Находит все классы с аннотациями @Component, @Service, @Repository и др.
        /// 4. Создает экземпляры (бины) этих классов
        /// 5. Регистрирует их в Spring контейнере (ApplicationContext)
        /// 6. Внедряет зависимости через @Autowired
        /// Возвращает ConfigurableApplicationContext - это контейнер Spring, который хранит все созданные бины.

        AppStart appStart = context.getBean(AppStart.class); // context.getBean(AppStart.class) получает бин AppStart из контекста
        appStart.start();

        appStart.showConverterInfo(); // Показываем информацию о конвертере
    }
}