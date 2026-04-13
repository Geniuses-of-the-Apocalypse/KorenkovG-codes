package guu.ru.biglaba4;

import lombok.AllArgsConstructor;
import lombok.Data;
import lombok.NoArgsConstructor;

@Data                          // генерирует геттеры, сеттеры, toString, equals, hashCode
@NoArgsConstructor             // генерирует конструктор без параметров
@AllArgsConstructor            // генерирует конструктор со всеми параметрами
public class PureNaselennyjPunkt {

    private String kod;
    private String nazvanie;
    private String tip;
    private Integer naselenie;
    private String region;
    private String postIndex;
    private Double ploshchad;
}