package guu.ru.biglaba3.component;

import org.springframework.context.event.EventListener;
import org.springframework.stereotype.Service;
import guu.ru.biglaba3.events.AddProductEvent;
import guu.ru.biglaba3.events.RemoveProductEvent;
import guu.ru.biglaba3.model.Product;

import java.util.HashMap;
import java.util.Map;

@Service
public class ProductPriceCalculator {
    private final Map<String, Double> totalPriceMap = new HashMap<>();

    @EventListener
    public void onProductAdded(AddProductEvent event) {
        Product product = event.getProduct();
        String productName = product.getName();
        double addedValue = product.getPricePerUnit() * event.getQuantity();

        totalPriceMap.put(productName,
                totalPriceMap.getOrDefault(productName, 0.0) + addedValue);
    }

    @EventListener
    public void onProductRemoved(RemoveProductEvent event) {
        Product product = event.getProduct();
        String productName = product.getName();
        double removedValue = product.getPricePerUnit() * event.getQuantity();

        double currentPrice = totalPriceMap.getOrDefault(productName, 0.0);
        double newPrice = currentPrice - removedValue;

        if (newPrice <= 0.01) {
            totalPriceMap.remove(productName);
        } else {
            totalPriceMap.put(productName, newPrice);
        }
    }

    public double getTotalPrice(String productName) {
        return totalPriceMap.getOrDefault(productName, 0.0);
    }

    public Map<String, Double> getAllPrices() {
        return new HashMap<>(totalPriceMap);
    }

    @Override
    public String toString() {
        return totalPriceMap.toString();
    }
}