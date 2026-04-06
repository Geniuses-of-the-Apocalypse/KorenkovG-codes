package guu.ru.biglaba3.component;

import lombok.extern.log4j.Log4j2;
import org.springframework.context.ApplicationEventPublisher;
import org.springframework.context.ApplicationEventPublisherAware;
import org.springframework.stereotype.Service;
import guu.ru.biglaba3.events.AddProductEvent;
import guu.ru.biglaba3.events.RemoveProductEvent;
import guu.ru.biglaba3.model.Product;

import java.util.List;
import java.util.concurrent.CopyOnWriteArrayList;

@Service
@Log4j2
public class ProductManager implements ApplicationEventPublisherAware {  // тот кто публикует информацию
    private ApplicationEventPublisher applicationEventPublisher;
    private final List<Product> products = new CopyOnWriteArrayList<>();

    @Override
    public void setApplicationEventPublisher(ApplicationEventPublisher applicationEventPublisher) { // тот кто публикует информацию
        this.applicationEventPublisher = applicationEventPublisher;
    }

    public void addProduct(Product product, int quantity) {
        validateQuantity(quantity);
        if (product == null) throw new IllegalArgumentException("Product cannot be null");

        for (int i = 0; i < quantity; i++) {
            products.add(product);
        }
        applicationEventPublisher.publishEvent(new AddProductEvent(this, product, quantity));
        log.debug("Добавлено {} шт. [ID:{}, Name:'{}', Price:{}]",
                quantity, product.getId(), product.getName(), product.getPricePerUnit());
    }

    public void removeProduct(Product product, int quantity) { // метод удаление по ID
        validateQuantity(quantity);
        if (product == null) throw new IllegalArgumentException("Product cannot be null");

        int removed = 0;
        for (int i = products.size() - 1; i >= 0 && removed < quantity; i--) { // удаление по ID
            if (products.get(i).getId().equals(product.getId())) {
                products.remove(i);
                removed++;
            }
        }
        if (removed > 0) {
            applicationEventPublisher.publishEvent(new RemoveProductEvent(this, product, removed));
            log.debug("Удалено {} шт. [ID:{}, Name:'{}']", removed, product.getId(), product.getName());
        } else {
            log.warn("Не удалось удалить [ID:{}]: товар не найден или количество превышает доступное",
                    product.getId());
        }
    }

    public int removeProductsByName(String productName, int quantity) { // метод для удаления по имени
        validateQuantity(quantity);
        int removed = 0;
        for (int i = products.size() - 1; i >= 0 && removed < quantity; i--) {
            if (products.get(i).getName().equals(productName)) {
                Product removedProduct = products.get(i);
                products.remove(i);
                removed++;
                // Публикуем событие для каждого удалённого экземпляра
                applicationEventPublisher.publishEvent(
                        new RemoveProductEvent(this, removedProduct, 1)
                );
            }
        }
        log.debug("️Удалено {} шт. по имени '{}'", removed, productName);
        return removed;
    }

    private void validateQuantity(int quantity) {
        if (quantity <= 0) {
            throw new IllegalArgumentException("Количество должно быть положительным: " + quantity);
        }
    }

    public List<Product> getAllProducts() {
        return List.copyOf(products);
    }

    public int getTotalCount() {
        return products.size();
    }

    @Override
    public String toString() {
        return String.format("ProductManager{totalItems=%d, uniqueProducts=%d}", products.size(), products.stream().map(Product::getId).distinct().count());
    }
}