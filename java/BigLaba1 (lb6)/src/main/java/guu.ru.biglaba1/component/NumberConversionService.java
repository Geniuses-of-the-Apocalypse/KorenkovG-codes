// component/NumberConversionService.java
package guu.ru.biglaba1.component;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.beans.factory.annotation.Value;
import org.springframework.context.ApplicationContext;
import org.springframework.stereotype.Service;
import guu.ru.biglaba1.converters.NumberConverter;

import java.util.HashMap;
import java.util.Map;

 ///@Service - специализированная версия @Component для сервисного слоя

@Service
public class NumberConversionService {

    @Value("${converter.type:hex}") //appication
    private String converterType;

    @Autowired
    private ApplicationContext context;

    private NumberConverter converter;   //инверсия

    public NumberConverter getConverter() {
        if (converter == null) {
            converter = context.getBean(converterType, NumberConverter.class); // получаем бин от инверсии
        }
        return converter;
    }

    public String convertNumber(int number) {
        NumberConverter selectedConverter = getConverter();
        return selectedConverter.convert(number);
    }

    public Map<Integer, String> convertNumbers(int[] numbers) {
        NumberConverter selectedConverter = getConverter();
        Map<Integer, String> results = new HashMap<>();

        for (int number : numbers) { // Цикл for-each: перебираем каждое число из массива
            results.put(number, selectedConverter.convert(number)); // Преобразуем число и сохраняем в Map
        }

        return results;
    }

    public String getConverterInfo() {
        NumberConverter selectedConverter = getConverter();                ///  String.format() - форматирует строку
        return String.format("Используемый конвертер: %s (основание: %d)", ///  %s - вставить строку (название системы)
                selectedConverter.getSystemName(),                         ///  %d - вставить число (основание)
                selectedConverter.getBase());
    }

    public String getConverterType() {
        return converterType;
    }
}