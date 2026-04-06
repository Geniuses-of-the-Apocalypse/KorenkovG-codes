package guu.ru.biglaba3.component;

import org.springframework.context.event.EventListener;
import org.springframework.stereotype.Service;
import guu.ru.biglaba3.events.AddProductEvent;
import guu.ru.biglaba3.events.RemoveProductEvent;
import guu.ru.biglaba3.model.Product;

@Service
public class TotalPriceCalculator {
    private double totalPrice = 0.0;

    @EventListener // тот кто наблюдает и изменяеться (листенер)
    public void onProductAdded(AddProductEvent event) {
        Product product = event.getProduct();
        totalPrice += product.getPricePerUnit() * event.getQuantity();
    }

    @EventListener // тот кто наблюдает и изменяеться (листенер)
    public void onProductRemoved(RemoveProductEvent event) {
        Product product = event.getProduct();
        totalPrice -= product.getPricePerUnit() * event.getQuantity();

        if (totalPrice < 0.01) {
            totalPrice = 0.0;
        }
    }

    public double getTotalPrice() {
        return totalPrice;
    }

    @Override
    public String toString() {
        return String.format("%.2f", totalPrice);
        // Вывод: 690.00
    }
}