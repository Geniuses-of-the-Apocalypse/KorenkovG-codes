// converters/BinaryConverter.java
package guu.ru.biglaba1.converters;

import org.springframework.stereotype.Component;

@Component("binary")
public class BinaryConverter implements NumberConverter {

    @Override
    public String convert(int number) {
        return Integer.toBinaryString(number);
    }

    @Override
    public String getSystemName() {
        return "Двоичная система (Binary)";
    }

    @Override
    public int getBase() {
        return 2;
    } // Двоичная система имеет основание 2
}
