// converters/HexConverter.java
package guu.ru.biglaba1.converters;

import org.springframework.stereotype.Component;

@Component("hex")
public class HexConverter implements NumberConverter {

    @Override
    public String convert(int number) {
        return Integer.toHexString(number).toUpperCase();
    }

    @Override
    public String getSystemName() {
        return "Шестнадцатеричная система (Hexadecimal)";
    }

    @Override
    public int getBase() {
        return 16;
    } // Шестнадцатеричная система имеет основание 16
}