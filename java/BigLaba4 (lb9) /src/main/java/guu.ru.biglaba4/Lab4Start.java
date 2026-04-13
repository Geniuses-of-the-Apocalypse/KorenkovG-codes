package guu.ru.biglaba4;

import lombok.Cleanup;
import javax.validation.ConstraintViolation;
import javax.validation.Validation;
import javax.validation.Validator;
import javax.validation.ValidatorFactory;
import java.util.Set;
import java.util.stream.Collectors;

public class Lab4Start {

    public static void main(String[] args) {

        @Cleanup ValidatorFactory factory = Validation.buildDefaultValidatorFactory(); // @Cleanup автоматически закроет factory в конце блока
        Validator validator = factory.getValidator();

        System.out.println("==========ВАЛИДАЦИЯ ЧЕРЕЗ АННОТАЦИИ (NaselennyjPunkt)==========\n"); // с ошибками

        NaselennyjPunkt punkt = new NaselennyjPunkt();
        punkt.setKod("32");
        punkt.setNazvanie("Moscow");
        punkt.setTip("Мегаполис");
        punkt.setNaselenie(-10000);
        punkt.setRegion("Москва и область");
        punkt.setPostIndex("32322");
        punkt.setPloshchad(0.7);

        System.out.println("Проверяемый объект:");
        System.out.println("  " + punkt);  // toString() от Lombok @Data
        System.out.println();

        Set<ConstraintViolation<NaselennyjPunkt>> violations1 = validator.validate(punkt);

        if (violations1.isEmpty()) {
            System.out.println("ОШИБОК НЕ НАЙДЕНО");
        } else {
            System.out.println("Найдены нарушения (" + violations1.size() + "):");
            violations1.forEach(v ->
                    System.out.println("  → " + v.getPropertyPath() + ": '" + v.getInvalidValue() + "' - " + v.getMessage())
            );
        }

        System.out.println("\n==========КОРРЕКТНЫЙ ОБЪЕКТ==========\n");

        // Используем @AllArgsConstructor от Lombok
        NaselennyjPunkt punktCorrect = new NaselennyjPunkt(
                "MOSKVA23", "Москва", "город", 12500000, "Московская область", "101000", 2511.0
        );

        Set<ConstraintViolation<NaselennyjPunkt>> violations2 = validator.validate(punktCorrect);

        if (violations2.isEmpty()) {
            System.out.println("Корректный объект прошел валидацию!");
            System.out.println("  " + punktCorrect);
        } else {
            System.out.println("Найдены нарушения:");
            violations2.forEach(v -> System.out.println("  → " + v.getMessage()));
        }

        System.out.println("\n==========ВАЛИДАЦИЯ ЧЕРЕЗ XML (PureNaselennyjPunkt)==========\n"); // с ошибками

        PureNaselennyjPunkt purePunkt = new PureNaselennyjPunkt(
                "D23CBE", "Гагарино", "деревня", 5000000, "Смоленская область", "19102300000", 100.0
        );

        System.out.println("Проверяемый объект:");
        System.out.println("  " + purePunkt);
        System.out.println();

        Set<ConstraintViolation<PureNaselennyjPunkt>> violations3 = validator.validate(purePunkt);

        if (violations3.isEmpty()) {
            System.out.println("Валидация XML пройдена");
        } else {
            System.out.println("Найдены нарушения валидации (через XML):");
            violations3.forEach(v ->
                    System.out.println("  → " + v.getPropertyPath() + ": '" + v.getInvalidValue() + "' - " + v.getMessage())
            );
        }
    }
}