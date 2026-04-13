package guu.ru.biglaba5;

import lombok.Cleanup;
import javax.validation.ConstraintViolation;
import javax.validation.Validation;
import javax.validation.Validator;
import javax.validation.ValidatorFactory;
import java.util.Set;

public class Lab5Start {

    public static void main(String[] args) {

        @Cleanup ValidatorFactory factory = Validation.buildDefaultValidatorFactory();
        Validator validator = factory.getValidator();

        System.out.println("=".repeat(60));
        System.out.println("Создание составной аннотации для валидации плотности населения");
        System.out.println("=".repeat(60));
        System.out.println();

        System.out.println("===============ТЕСТ 1: Корректные данные===============");
        NaselennyjPunktDensity punkt1 = new NaselennyjPunktDensity(
                1_000_000, 500.0, 2000.0
        );
        System.out.println("Объект: " + punkt1);
        validateAndPrint(validator, punkt1);

        System.out.println("\n===============ТЕСТ 2: Некорректная плотность===============");
        NaselennyjPunktDensity punkt2 = new NaselennyjPunktDensity(
                1_000_000, 500.0, 1000.0
        );
        System.out.println("Объект: " + punkt2);
        validateAndPrint(validator, punkt2);

        System.out.println("\n===============ТЕСТ 3: Отрицательное количество человек===============");
        NaselennyjPunktDensity punkt3 = new NaselennyjPunktDensity(
                -100, 500.0, 0.0
        );
        System.out.println("Объект: " + punkt3);
        validateAndPrint(validator, punkt3);

        System.out.println("\n===============ТЕСТ 4: Нулевая площадь===============");
        NaselennyjPunktDensity punkt4 = new NaselennyjPunktDensity(
                1_000_000, 0.0, 2000.0
        );
        System.out.println("Объект: " + punkt4);
        validateAndPrint(validator, punkt4);

        System.out.println("\n===============ТЕСТ 5: Исправленный Токио===============");
        NaselennyjPunktDensity tokyoCorrect = new NaselennyjPunktDensity(
                37_400_000, 2194.0, 37_400_000.0 / 2194.0
        );
        System.out.printf("Объект: %s (плотность = %.2f)%n",
                tokyoCorrect, tokyoCorrect.getPlotnostNaseleniya());
        validateAndPrint(validator, tokyoCorrect);

//        System.out.println("\n" + "=".repeat(60));
//        System.out.println("ДЕМОНСТРАЦИЯ АГРЕГИРОВАНИЯ ОГРАНИЧЕНИЙ");
//        System.out.println("Аннотация @ValidDensity объединяет:");
//        System.out.println("  - Собственную логику проверки формулы");
//        System.out.println("  - Валидацию через отдельный класс DensityValidator");
//        System.out.println("=".repeat(60));
    }

    private static void validateAndPrint(Validator validator, NaselennyjPunktDensity obj) {
        Set<ConstraintViolation<NaselennyjPunktDensity>> violations = validator.validate(obj);

        if (violations.isEmpty()) {
            System.out.println("ВАЛИДАЦИЯ ПРОЙДЕНА УСПЕШНО!");
        } else {
            System.out.println("Найдены нарушения (" + violations.size() + "):");
            for (ConstraintViolation<NaselennyjPunktDensity> v : violations) {
                System.out.println("      → " + v.getPropertyPath() + ": " + v.getMessage());
            }
        }
    }
}