package guu.ru.biglaba5;

import javax.validation.ConstraintValidator;
import javax.validation.ConstraintValidatorContext;

public class DensityValidator implements ConstraintValidator<ValidDensity, NaselennyjPunktDensity> {

    private static final double EPSILON = 0.0001;

    @Override
    public boolean isValid(NaselennyjPunktDensity obj, ConstraintValidatorContext context) {

        if (obj == null) {
            return true;
        }

        Integer kolichestvo = obj.getKolichestvoChelovek();
        Double ploshchad = obj.getPloshchad();
        Double plotnost = obj.getPlotnostNaseleniya();

        if (kolichestvo == null || ploshchad == null || plotnost == null) {
            return true;
        }

        if (ploshchad <= 0) {
            return true;
        }

        double expectedDensity = kolichestvo / ploshchad;
        boolean isValid = Math.abs(plotnost - expectedDensity) < EPSILON;

        if (!isValid) {
            context.disableDefaultConstraintViolation();
            context.buildConstraintViolationWithTemplate(
                    String.format("Плотность населения %.2f не соответствует формуле. " +
                                    "Ожидается: %d / %.2f = %.2f",
                            plotnost, kolichestvo, ploshchad, expectedDensity)
            ).addConstraintViolation();
        }

        return isValid;
    }
}