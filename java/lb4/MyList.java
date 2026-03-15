package GUU.RU.Laba4J;
import java.util.Arrays;

public class MyList<T extends Comparable<T>> implements ListInterface<T> {

    private Object[] elements;                                    // массив
    private int size;
    private static final int DEFAULT_CAPACITY = 10;              // начальный размер

    public MyList() {
        elements = new Object[DEFAULT_CAPACITY];       // создаем массив на 10 ячеек
        size = 0;                                     // пока элементов нет
    }

    public MyList(int capacity) {  // проверка
        if (capacity < 0) {
            throw new IllegalArgumentException("Размер не может быть отрицательным");
        }
        elements = new Object[capacity];
        size = 0;
    }

    public MyList(T[] array) {
        elements = Arrays.copyOf(array, array.length);         // копируем массив
        size = array.length;
    }

    @Override                                     // добавление в конец списка
    public void add(T element) {
        if (size == elements.length) {             // проверяем, хватает ли места в массиве
            int newCapacity = elements.length * 2;   // уеличиваем размер
            elements = Arrays.copyOf(elements, newCapacity);
        }
        elements[size] = element;
        size++;
    }

    @Override                              // поиск элемента
    //@SuppressWarnings("unchecked")
    public T get(int index) {
        if (index < 0 || index >= size) {
            throw new IndexOutOfBoundsException("Индекс " + index + " вне границ");
        }
        return (T) elements[index];
    }

    @Override                            // удаление элемента
    //@SuppressWarnings("unchecked")
    public T remove(int index) {
        if (index < 0 || index >= size) {
            throw new IndexOutOfBoundsException("Индекс " + index + " вне границ");
        }

        T removedElement = (T) elements[index];

        for (int i = index; i < size - 1; i++) {      // сдвигаем все элементы после удаления
            elements[i] = elements[i + 1];
        }

        elements[size - 1] = null;
        size--;

        return removedElement;
    }

    @Override                        // размер
    public int size() {
        return size;
    }

    @Override                       // пуст ли
    public boolean isEmpty() {
        return size == 0;
    }

    @Override                       // пузырьковая сортировка
    public void sort() {
        for (int i = 0; i < size - 1; i++) {
            for (int j = 0; j < size - i - 1; j++) {
                T current = (T) elements[j];
                T next = (T) elements[j + 1];

                if (current.compareTo(next) > 0) {
                    elements[j] = next;
                    elements[j + 1] = current;
                }
            }
        }
    }

    @Override                                 // бинарный поиск в отсортированном списке
    public int binarySearch(T element) {
        int left = 0;           // левая граница(начало)
        int right = size - 1;   // правая граница(конец)

        while (left <= right) {
            int middle = left + (right - left) / 2;  // находим середину (без риска переполнения)

            int comparison = element.compareTo((T) elements[middle]);

            if (comparison == 0) {
                return middle;
            } else if (comparison < 0) {
                right = middle - 1;
            } else {
                left = middle + 1;
            }
        }

        return -1;  // ничего не нашли
    }

    @Override                                                         // превращение в красивую строку
    public String toString() {
        // Если список пустой
        if (size == 0) {
            return "[]";
        }

        StringBuilder sb = new StringBuilder();
        sb.append("[");

        for (int i = 0; i < size; i++) {
            sb.append(elements[i]);           // добавляем элемент

            if (i < size - 1) {               //добавляем запятую и пробел
                sb.append(", ");
            }
        }
        sb.append("]");

        return sb.toString();  // Превращаем StringBuilder в строку
    }
}
