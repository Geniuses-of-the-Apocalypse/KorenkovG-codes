#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
using namespace std;

template<typename T>
class BTree {
    static const int DEFAULT_ORDER = 3;
    
    struct Node {
        T* keys;
        Node** children;
        Node* next;
        int key_count;
        bool is_leaf;
        int capacity;

        Node(bool leaf = false, int order = DEFAULT_ORDER) 
        : next(nullptr), key_count(0), is_leaf(leaf), capacity(order * 2 - 1) {
        keys = new T[capacity];
        children = new Node*[capacity + 1];
        for (int i = 0; i <= capacity; ++i) children[i] = nullptr;
    }
        
        ~Node() {
        delete[] keys;
        if (!is_leaf) {
        for (int i = 0; i <= key_count; ++i) 
            if (children[i]) delete children[i];
        }
        delete[] children;
    }
        
        int findKeyIndex(T vrem) {
            int idx = 0;
            while (idx < key_count && keys[idx] < vrem) ++idx;
            return idx;
        }
        
        void insertKey(int idx, T vrem) {
            for (int i = key_count; i > idx; --i) keys[i] = keys[i - 1];
            keys[idx] = vrem;
            key_count++;
        }
        
        void removeKey(int idx) {
            for (int i = idx; i < key_count - 1; ++i) keys[i] = keys[i + 1];
            key_count--;
        }
        
        bool isFull() { return key_count == capacity; }
    };

    Node* root;
    int order;

    // Основные вспомогательные методы
    void splitChild(Node* parent, int idx, Node* child) {
    Node* new_child = new Node(child->is_leaf, order);
    int split_pos = order - 1;  // Фиксированная позиция разделения
    T middle_key = child->keys[split_pos];
    
    if (child->is_leaf) {
        // Для листового узла копируем ключи включая средний
        for (int i = 0; i < order; ++i) 
            new_child->keys[i] = child->keys[i + split_pos];
        
        new_child->key_count = order;
        child->key_count = order - 1;
        
        // Обновляем связи между листьями
        new_child->next = child->next;
        child->next = new_child;
        
        // Для B+ дерева средний ключ дублируется в родителе
        // и остается в новом листе
    } else {
        // Для внутреннего узла
        for (int i = 0; i < order - 1; ++i) 
            new_child->keys[i] = child->keys[i + split_pos + 1];
        
        for (int i = 0; i < order; ++i) 
            new_child->children[i] = child->children[i + split_pos + 1];
        
        new_child->key_count = order - 1;
        child->key_count = order - 1;
    }
    
    // Вставляем ключ в родителя
    for (int i = parent->key_count; i > idx; --i) 
        parent->keys[i] = parent->keys[i - 1];
    for (int i = parent->key_count + 1; i > idx + 1; --i) 
        parent->children[i] = parent->children[i - 1];
    
    parent->keys[idx] = middle_key;
    parent->children[idx + 1] = new_child;
    parent->key_count++;
}
    
    void insertNonFull(Node* node, T vrem) {
        int idx = node->findKeyIndex(vrem);
        if (node->is_leaf) {
            node->insertKey(idx, vrem);
        } else {
            Node* child = node->children[idx];
            if (child->isFull()) {
                splitChild(node, idx, child);
                if (vrem > node->keys[idx]) idx++;
            }
            insertNonFull(node->children[idx], vrem);
        }
    }
    
    bool searchR(Node* node, T vrem) {
        if (!node) return false;
        int idx = node->findKeyIndex(vrem);
        if (idx < node->key_count && node->keys[idx] == vrem) return true;
        if (node->is_leaf) return false;
        return searchR(node->children[idx], vrem);
    }
    
    void clearR(Node* node) {
        if (node) {
            if (!node->is_leaf) {
                for (int i = 0; i <= node->key_count; ++i) clearR(node->children[i]);
            }
            delete node;
        }
    }
    
    void toStringR(Node* node, stringstream& ss, int level) {
        if (node) {
            for (int i = 0; i < level; ++i) ss << "  ";
            ss << "[";
            for (int i = 0; i < node->key_count; ++i) {
                ss << node->keys[i];
                if (i < node->key_count - 1) ss << ", ";
            }
            ss << "]";
            if (node->is_leaf && node->next) ss << " -> ";
            ss << "\n";
            
            if (!node->is_leaf) {
                for (int i = 0; i <= node->key_count; ++i) 
                    toStringR(node->children[i], ss, level + 1);
            }
        }
    }

public:
    BTree(int tree_order = DEFAULT_ORDER) : root(nullptr), order(tree_order) {}
    ~BTree() { clear(); }
    
    // Основные операции
    bool search(T vrem) { return searchR(root, vrem); }
    
    void insert(T vrem) {
        if (!root) {
            root = new Node(true, order);
            root->insertKey(0, vrem);
            return;
        }
        
        if (root->isFull()) {
            Node* new_root = new Node(false, order);
            new_root->children[0] = root;
            splitChild(new_root, 0, root);
            int idx = (vrem > new_root->keys[0]) ? 1 : 0;
            insertNonFull(new_root->children[idx], vrem);
            root = new_root;
        } else {
            insertNonFull(root, vrem);
        }
    }
    
    void remove(T vrem) {
        // Упрощенная версия - очистка и перестройка
        // В реальной реализации нужно добавить полную логику удаления
        cout << "Удаление " << vrem << " (упрощенная реализация)\n";
    }
    
    void clear() { clearR(root); root = nullptr; }
    
    // Вывод
    string toString() {
        stringstream ss;
        toStringR(root, ss, 0);
        return ss.str();
    }
    
    void print() {
        cout << "B+ Дерево:\n" << toString() << "====================\n";
    }
    
    bool empty() { return root == nullptr; }
    
    // Сериализация (упрощенная)
    void serialize(ostream& os) {
        os << "BTree serialization placeholder\n";
    }
    
    void deserialize(istream& is) {
        clear();
        cout << "Deserialization placeholder\n";
    }
    
    friend ostream& operator<<(ostream& os, BTree& tree) {
        os << tree.toString();
        return os;
    }
};

// Демонстрация работы
int main() {
    BTree<int> tree;
    
    cout << "=== Демонстрация B+ дерева ===\n\n";
    
    // Тестирование вставки
    cout << "1. Вставка элементов: ";
    int elements[] = {50, 30, 70, 20, 40, 60, 80, 10, 25, 35};
    for (int elem : elements) {
        cout << elem << " ";
        tree.insert(elem);
    }
    cout << "\n\nДерево после вставки:\n";
    tree.print();
    
    // Тестирование поиска
    cout << "2. Поиск элементов:\n";
    cout << "Поиск 30: " << (tree.search(30) ? "найден" : "не найден") << "\n";
    cout << "Поиск 55: " << (tree.search(55) ? "найден" : "не найден") << "\n";
    cout << "Поиск 25: " << (tree.search(25) ? "найден" : "не найден") << "\n";
    
    // Тестирование удаления
    cout << "\n3. Удаление элементов:\n";
    tree.remove(30);
    tree.remove(60);
    cout << "Дерево после удаления:\n";
    tree.print();
    
    // Тестирование с строками
    cout << "4. Тест со строками:\n";
    BTree<string> stringTree;
    stringTree.insert("apple");
    stringTree.insert("banana");
    stringTree.insert("cherry");
    stringTree.insert("date");
    cout << stringTree;
    
    cout << "Поиск 'banana': " << (stringTree.search("banana") ? "найден" : "не найден") << "\n";
    
    // Очистка
    cout << "5. Очистка дерева:\n";
    tree.clear();
    cout << "Дерево пустое: " << tree.empty() << "\n";
    
    return 0;
}
