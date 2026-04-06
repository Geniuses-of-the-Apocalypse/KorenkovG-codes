package guu.ru.biglaba3.events;

import org.springframework.context.ApplicationEvent;
import guu.ru.biglaba3.model.Product;

public class AddProductEvent extends ApplicationEvent {
    private Product product;
    private int quantity;

    public AddProductEvent(Object source, Product product, int quantity) {
        super(source);
        this.product = product;
        this.quantity = quantity;
    }

    public Product getProduct() {
        return product;
    }

    public int getQuantity() {
        return quantity;
    }
}