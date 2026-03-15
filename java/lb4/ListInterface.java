package GUU.RU.Laba4J;

public interface ListInterface<T extends Comparable<T>> {
    void add(T element);
    T get(int index);            // получение элемента по индексу
    T remove(int index);        // удалить элемент по индексу
    int size();                 // кол-во элементов
    boolean isEmpty();          // пусто ли список
    void sort();                //отсортировка списка
    int binarySearch(T element); // бинарный поиск
    String toString();          // в строку перевод
}
