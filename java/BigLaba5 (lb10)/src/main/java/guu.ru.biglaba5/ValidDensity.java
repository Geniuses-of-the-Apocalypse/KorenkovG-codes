package guu.ru.biglaba5;

import javax.validation.Constraint;
import javax.validation.Payload;
import java.lang.annotation.*;

@Target({ElementType.TYPE})
@Retention(RetentionPolicy.RUNTIME)
@Constraint(validatedBy = DensityValidator.class)
public @interface ValidDensity {

    String message() default "Плотность населения не соответствует формуле: Плотность = Количество человек / Площадь";

    Class<?>[] groups() default {};

    Class<? extends Payload>[] payload() default {};
}