package guu.ru.biglaba2;

import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.SpringBootApplication;
import org.springframework.context.ConfigurableApplicationContext;
import guu.ru.biglaba2.component.AppStart;

@SpringBootApplication
public class BigLaba2Application {

    public static void main(String[] args) {
        ConfigurableApplicationContext context =
                SpringApplication.run(BigLaba2Application.class, args);

        AppStart appStart = context.getBean(AppStart.class);
        appStart.start();

        // context.close(); // опционально
    }
}