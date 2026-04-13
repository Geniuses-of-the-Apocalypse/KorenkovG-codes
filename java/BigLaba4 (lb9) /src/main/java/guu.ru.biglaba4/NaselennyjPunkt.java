package guu.ru.biglaba4;

import lombok.AllArgsConstructor;
import lombok.Data;
import lombok.NoArgsConstructor;
import org.hibernate.validator.constraints.Range;

import javax.validation.constraints.*;


@Data                          // Генерирует геттеры, сеттеры, toString, equals, hashCode
@NoArgsConstructor             // Генерирует конструктор без параметров
@AllArgsConstructor            // Генерирует конструктор со всеми параметрами
public class NaselennyjPunkt {

    @NotNull(message = "Код населённого пункта должен быть задан")
    @Size(min = 5, max = 10, message = "Код населённого пункта должен быть от 5 до 10 символов")
    @Pattern(regexp = "^[A-Z0-9]{5,10}$",
            message = "Код должен состоять только из заглавных латинских букв и цифр")
    private String kod;

    @NotNull(message = "Название населённого пункта должно быть задано")
    @Size(min = 2, max = 50, message = "Название должно быть от 2 до 50 символов")
    @Pattern(regexp = "^[А-Яа-яЁё\\s-]{2,50}$",
            message = "Название должно содержать только русские буквы, пробелы и дефисы")
    private String nazvanie;

    @NotNull(message = "Тип населённого пункта должен быть задан")
    @Pattern(regexp = "^(город|село|деревня|посёлок|ПГТ)$",
            message = "Тип должен быть: город, село, деревня, посёлок или ПГТ")
    private String tip;

    @Range(min = 1, max = 20000000, message = "Численность населения должна быть от 1 до 20 000 000")
    private Integer naselenie;

    @NotNull(message = "Регион должен быть задан")
    @Pattern(regexp = "^[А-Яа-яЁё\\s-]{3,40}$",
            message = "Регион должен содержать только русские буквы, пробелы и дефисы (3-40 символов)")
    private String region;

    @Pattern(regexp = "^\\d{6}$",
            message = "Почтовый индекс должен состоять из 6 цифр")
    private String postIndex;

    @DecimalMin(value = "0.0", inclusive = false, message = "Площадь должна быть больше 0")
    @DecimalMax(value = "1000000.0", message = "Площадь не должна превышать 1 000 000 кв.км")
    private Double ploshchad;
}