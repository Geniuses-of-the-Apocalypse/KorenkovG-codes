package guu.ru.biglaba2.service;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.beans.factory.annotation.Qualifier;
import org.springframework.beans.factory.annotation.Value;
import org.springframework.context.ApplicationContext;
import org.springframework.stereotype.Service;

import java.util.Arrays;
import java.util.List;
import java.util.Set;

@Service
public class WindowBean {

    @Value("${windowDecoratorList:}")
    private String useDecorators;

    private IWindow window;

    private static final Set<String> VALID_DECORATORS = Set.of("menu", "status", "sidebar");

    @Autowired
    public void buildWindow(
            @Qualifier("simpleWindow") IWindow baseWindow,
            ApplicationContext context) {

        // Начинаем с базового окна
        this.window = baseWindow;

        if (useDecorators == null || useDecorators.isBlank()) {
            return;
        }

        List<String> decoratorNames = Arrays.stream(useDecorators.split(","))
                .map(String::trim)
                .filter(name -> !name.isEmpty())
                .toList();

        // Валидация имён декораторов
        for (String name : decoratorNames) {
            if (!VALID_DECORATORS.contains(name)) {
                throw new IllegalArgumentException("Unknown decorator: " + name);
            }
        }

        // Последовательно оборачиваем окно
        for (String decoratorName : decoratorNames) {
            // Явное приведение типа к IWindow
            this.window = (IWindow) context.getBean(decoratorName, this.window);
        }
    }

    public String drawWindow() {
        return window.draw();
    }
}