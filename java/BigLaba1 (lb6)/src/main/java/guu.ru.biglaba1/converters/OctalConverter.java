// converters/OctalConverter.java
package guu.ru.biglaba1.converters;

import org.springframework.stereotype.Component;

@Component("octal")
public class OctalConverter implements NumberConverter {

    @Override
    public String convert(int number) {
        return Integer.toOctalString(number);
    }

    @Override
    public String getSystemName() {
        return "Восьмеричная система (Octal)";
    }

    @Override
    public int getBase() {
        return 8;
    } // Восьмеричная система имеет основание 8
}
