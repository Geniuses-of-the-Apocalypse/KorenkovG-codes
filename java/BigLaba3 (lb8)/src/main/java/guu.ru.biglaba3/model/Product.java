package guu.ru.biglaba3.model;

import lombok.Getter;
import lombok.ToString;
import java.util.UUID; // для ID

@Getter
@ToString
public class Product {
    private final UUID id;
    private final String name;
    private final double pricePerUnit;

    public Product(UUID id, String name, double pricePerUnit) {     // для тестов, импорта, точного контроля
        this.id = id;
        this.name = name;
        this.pricePerUnit = pricePerUnit;
        validate();
    }

    public Product(String name, double pricePerUnit) { // ID генерируется автоматически
        this(UUID.randomUUID(), name, pricePerUnit);
    }

    private void validate() {
        if (name == null || name.isBlank()) {
            throw new IllegalArgumentException("Название товара не может быть пустым");
        }
        if (pricePerUnit < 0) {
            throw new IllegalArgumentException("Цена не может быть отрицательной: " + pricePerUnit);
        }
    }

    @Override
    public boolean equals(Object o) { // сравниваем товары по ID
        if (this == o) return true;
        if (!(o instanceof Product product)) return false;
        return id.equals(product.id);
    }

    @Override
    public int hashCode() {
        return id.hashCode();
    }
}