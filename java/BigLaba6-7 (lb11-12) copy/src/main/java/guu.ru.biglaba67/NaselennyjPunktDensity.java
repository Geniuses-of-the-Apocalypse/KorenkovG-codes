package guu.ru.biglaba5;

import lombok.AllArgsConstructor;
import lombok.Data;
import lombok.NoArgsConstructor;
import javax.validation.constraints.DecimalMin;
import javax.validation.constraints.NotNull;
import javax.validation.constraints.Positive;

@Data
@NoArgsConstructor
@AllArgsConstructor
@ValidDensity
public class NaselennyjPunktDensity {

    @NotNull(message = "Количество человек должно быть задано")
    @Positive(message = "Количество человек должно быть положительным числом")
    private Integer kolichestvoChelovek;

    @NotNull(message = "Площадь должна быть задана")
    @DecimalMin(value = "0.01", message = "Площадь должна быть больше 0")
    private Double ploshchad;

    @NotNull(message = "Плотность населения должна быть задана")
    @DecimalMin(value = "0.01", message = "Плотность населения должна быть больше 0")
    private Double plotnostNaseleniya;
}