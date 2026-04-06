package guu.ru.biglaba3.component;

import org.springframework.context.event.EventListener;
import org.springframework.stereotype.Service;
import guu.ru.biglaba3.events.AddProductEvent;
import guu.ru.biglaba3.events.RemoveProductEvent;
import guu.ru.biglaba3.model.Product;

import java.util.HashMap;
import java.util.Map;

@Service
public class ProductQuantityCalculator {
    private final Map<String, Integer> quantityMap = new HashMap<>();

    @EventListener // тот кто наблюдает и изменяеться (листенер)
    public void onProductAdded(AddProductEvent event) {
        String productName = event.getProduct().getName();
        quantityMap.put(productName, quantityMap.getOrDefault(productName, 0) + event.getQuantity());
    }

    @EventListener // // тот кто наблюдает и изменяеться (листенер)
    public void onProductRemoved(RemoveProductEvent event) {
        String productName = event.getProduct().getName();
        int currentQuantity = quantityMap.getOrDefault(productName, 0);
        int newQuantity = currentQuantity - event.getQuantity();

        if (newQuantity <= 0) {
            quantityMap.remove(productName);
        } else {
            quantityMap.put(productName, newQuantity);
        }
    }

    public int getQuantity(String productName) {
        return quantityMap.getOrDefault(productName, 0);
    }

    public Map<String, Integer> getAllQuantities() {
        return new HashMap<>(quantityMap);
    }

    @Override
    public String toString() {
        return quantityMap.toString();
        // Вывод: {Яблоко=6, Банан=2, Апельсин=4}
    }
}