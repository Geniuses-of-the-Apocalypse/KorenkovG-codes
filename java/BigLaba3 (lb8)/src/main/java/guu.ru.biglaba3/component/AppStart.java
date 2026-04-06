package guu.ru.biglaba3.component;

import lombok.extern.log4j.Log4j2;
import org.springframework.stereotype.Service;
import guu.ru.biglaba3.model.Product;

@Service
@Log4j2
public class AppStart {
    private final ProductManager productManager;
    private final ProductQuantityCalculator quantityCalculator;
    private final ProductPriceCalculator priceCalculator;
    private final TotalPriceCalculator totalPriceCalculator;

    public AppStart(ProductManager productManager, ProductQuantityCalculator quantityCalculator, ProductPriceCalculator priceCalculator, TotalPriceCalculator totalPriceCalculator) {
        this.productManager = productManager;
        this.quantityCalculator = quantityCalculator;
        this.priceCalculator = priceCalculator;
        this.totalPriceCalculator = totalPriceCalculator;
    }

    public void start() {
        Product apple = new Product("Яблоко", 50.0); // товары создаются с авто-генерацией UUID
        Product banana = new Product("Банан", 30.0);
        Product orange = new Product("Апельсин", 70.0);

        Product applePremium = new Product("Яблоко", 120.0); // пример: два товара с одинаковым именем, но разной ценой и разными ID

        log.info("");
        log.info("===Добавляем товары===");
        log.info("Apple ID: {}", apple.getId());
        log.info("Apple Premium ID: {}", applePremium.getId()); // премиум яблоко

        productManager.addProduct(apple, 5);           // Обычные яблоки
        productManager.addProduct(banana, 3);
        productManager.addProduct(apple, 2);           // Ещё обычные
        productManager.addProduct(orange, 4);
        productManager.addProduct(applePremium, 2);

        printStats();

        log.info("\n===Удаляем товары===");
        productManager.removeProduct(apple, 3); // удаляем яблоко обычное
        productManager.removeProduct(banana, 1); // удаляем банан

        printStats();

        log.info("\n===Тест: удаление по несуществующему ID==="); // попытка удалить товар, которого нет
        Product fakeProduct = new Product("Не существует", 999.0);
        productManager.removeProduct(fakeProduct, 5);
        printStats();

        log.info("\n===Тест: удаление ВСЕХ 'Яблоко' по имени==="); //удаление по имени (все "Яблоко", и обычные, и премиум)
        productManager.removeProductsByName("Яблоко", 10); // удалит до 10 штук любых яблок
        printStats();
    }

    private void printStats() {
        log.info("Количество: {}", quantityCalculator);
        log.info("Цена по наименованиям: {}", priceCalculator);
        log.info("Общая цена: {}", totalPriceCalculator);
        log.info("Всего единиц в менеджере: {}", productManager.getTotalCount());
    }
}