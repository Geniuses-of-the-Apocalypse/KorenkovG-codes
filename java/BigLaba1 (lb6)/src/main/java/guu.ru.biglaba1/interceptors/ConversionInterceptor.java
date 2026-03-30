// interceptors/ConversionInterceptor.java
package guu.ru.biglaba1.interceptors;

import lombok.extern.log4j.Log4j2;
import org.aspectj.lang.JoinPoint;
import org.aspectj.lang.ProceedingJoinPoint;
import org.aspectj.lang.annotation.*;
import org.springframework.stereotype.Component;
import guu.ru.biglaba1.component.NumberConversionService;

import java.util.Arrays;
import java.util.Map;

 ///АОП (Aspect-Oriented Programming) - аспектно-ориентированное программирование
 ///Позволяет добавлять поведение (логирование, замер времени) к существующим методам без изменения их кода.
 ///@Component - регистрирует как Spring бин
 ///@Aspect - указывает, что этот класс является аспектом (содержит перехватывающую логику)
 ///@Log4j2 - создает поле log для логирования


@Component
@Aspect
@Log4j2
public class ConversionInterceptor {

     ///@Pointcut - аннотация, которая определяет шаблон для методов

    @Pointcut("execution(* guu.ru.biglaba1.component.NumberConversionService.convert*(..))")
    public void conversionMethods() {}

    @Pointcut("execution(* guu.ru.biglaba1.component.NumberConversionService.convertNumber(..))")
    public void singleConversion() {}

    @Pointcut("execution(* guu.ru.biglaba1.component.NumberConversionService.convertNumbers(..))")
    public void batchConversion() {}

     ///@Before - выполняется ДО того, как будет вызван целевой метод

    @Before("conversionMethods()")
    public void logBeforeConversion(JoinPoint joinPoint) {          // Получаем сервис, на котором вызывается метод
        NumberConversionService service = (NumberConversionService) joinPoint.getTarget();
        String converterInfo = service.getConverterInfo();
        String methodName = joinPoint.getSignature().getName(); // Получаем имя метода

        log.info("========================================"); // Логируем начало операции
        log.info(" НАЧАЛО ПРЕОБРАЗОВАНИЯ");
        log.info("Метод: {}", methodName);
        log.info("{}", converterInfo);

        Object[] args = joinPoint.getArgs(); // Получаем аргументы метода
        if (args.length > 0) {
            log.info("Входные данные: {}", Arrays.toString(args));
        }
    }

     ///@AfterReturning - выполняется ПОСЛЕ успешного выполнения метода

    @AfterReturning(pointcut = "singleConversion()", returning = "result")
    public void logAfterSingleConversion(JoinPoint joinPoint, Object result) {
        NumberConversionService service = (NumberConversionService) joinPoint.getTarget();
        int number = (int) joinPoint.getArgs()[0]; // Получаем аргумент метода (число для преобразования)

        log.info("✓ Результат преобразования:"); // Логируем результат
        log.info("  10-ичная система: {}", number);
        log.info("  {}: {}", service.getConverter().getSystemName(), result);
        log.info("========================================");
    }


     /// @AfterReturning - выполняется ПОСЛЕ успешного выполнения метода

    @AfterReturning(pointcut = "batchConversion()", returning = "result")
    public void logAfterBatchConversion(JoinPoint joinPoint, Object result) {
        NumberConversionService service = (NumberConversionService) joinPoint.getTarget(); // Приводим результат к типу Map
        Map<Integer, String> conversionResults = (Map<Integer, String>) result;

        log.info("✓ РЕЗУЛЬТАТЫ ПАКЕТНОГО ПРЕОБРАЗОВАНИЯ:"); // Логируем результаты
        log.info("Количество преобразованных чисел: {}", conversionResults.size());
        log.info("----------------------------------------");

        conversionResults.forEach((decimal, converted) -> // Перебираем все записи в Map и выводим их
                log.info("  {} -> {}", decimal, converted)
        );

        log.info("========================================");
    }


     /// @Around - выполняется ВОКРУГ метода (и до, и после)

    @Around("conversionMethods()")
    public Object measureExecutionTime(ProceedingJoinPoint joinPoint) throws Throwable {
        long startTime = System.nanoTime(); // Запоминаем время ДО выполнения

        // наносекунды (1/1_000_000_000 секунды)

        Object result = joinPoint.proceed(); // ВЫПОЛНЯЕМ ЦЕЛЕВОЙ МЕТОД!

        long endTime = System.nanoTime();  // Вычисляем разницу
        long durationMs = (endTime - startTime) / 1_000_000; // миллисекунды
        long durationNs = (endTime - startTime);             // наносекунды

        log.info("⏱ Время выполнения: {} мс ({} нс)", durationMs, durationNs); // Логируем время выполнения

        return result; // Возвращаем результат (обязательно!)
    }

     ///@AfterThrowing - выполняется, если метод выбросил исключение


    @AfterThrowing(pointcut = "conversionMethods()", throwing = "exception")
    public void logConversionError(JoinPoint joinPoint, Exception exception) {
        log.error(" ОШИБКА при преобразовании в методе {}: {}",
                joinPoint.getSignature().getName(),
                exception.getMessage());
    }
}