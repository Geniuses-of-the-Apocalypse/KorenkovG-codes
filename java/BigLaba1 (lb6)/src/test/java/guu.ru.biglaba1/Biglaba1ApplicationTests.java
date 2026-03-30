// Biglaba1ApplicationTests.java
package guu.ru.biglaba1;

import org.junit.jupiter.api.Test;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.boot.test.context.SpringBootTest;
import org.springframework.context.ApplicationContext;
import guu.ru.biglaba1.component.NumberConversionService;
import guu.ru.biglaba1.converters.NumberConverter;

import static org.junit.jupiter.api.Assertions.*;

@SpringBootTest
class Biglaba1ApplicationTests {

    @Autowired
    private ApplicationContext context;

    @Autowired
    private NumberConversionService conversionService;

    @Test
    void testBinaryConverter() {
        NumberConverter binaryConverter = context.getBean("binary", NumberConverter.class);
        assertEquals("1010", binaryConverter.convert(10));
        assertEquals("11111111", binaryConverter.convert(255));
        assertEquals("1", binaryConverter.convert(1));
    }

    @Test
    void testOctalConverter() {
        NumberConverter octalConverter = context.getBean("octal", NumberConverter.class);
        assertEquals("12", octalConverter.convert(10));
        assertEquals("377", octalConverter.convert(255));
        assertEquals("1", octalConverter.convert(1));
    }

    @Test
    void testHexConverter() {
        NumberConverter hexConverter = context.getBean("hex", NumberConverter.class);
        assertEquals("A", hexConverter.convert(10));
        assertEquals("FF", hexConverter.convert(255));
        assertEquals("1", hexConverter.convert(1));
    }

    @Test
    void testConversionService() {
        assertNotNull(conversionService.getConverter());

        String result = conversionService.convertNumber(255);
        assertNotNull(result);

        int[] numbers = {10, 20, 30};
        var results = conversionService.convertNumbers(numbers);
        assertEquals(3, results.size());
    }

    @Test
    void contextLoads() {
        assertNotNull(context);
    }
}