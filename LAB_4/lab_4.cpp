#include <iostream>
#include <limits>
#include <cmath>

using namespace std;
struct TreeNode {
    int data;
    TreeNode* left;
    TreeNode* right;
    
    TreeNode(int val) : data(val), left(nullptr), right(nullptr) {}
};

struct Tree {
    TreeNode* root;
    bool allowDuplicates;
    int size;
    
    Tree() : root(nullptr), allowDuplicates(false), size(0) {}
};

TreeNode* insertWithoutDuplicates(TreeNode* root, int value, int& size) {
    if (root == nullptr) {
        size++;
        return new TreeNode(value);
    }
    
    if (value < root->data) {
        root->left = insertWithoutDuplicates(root->left, value, size);
    } else if (value > root->data) {
        root->right = insertWithoutDuplicates(root->right, value, size);
    }
    
    return root;
}

TreeNode* insertWithDuplicates(TreeNode* root, int value, int& size) {
    if (root == nullptr) {
        size++;
        return new TreeNode(value);
    }
    
    if (value <= root->data) {
        root->left = insertWithDuplicates(root->left, value, size);
    } else {
        root->right = insertWithDuplicates(root->right, value, size);
    }
    
    return root;
}
void waitForEnter() {
    cout << "\nНажмите Enter для продолжения...";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin.get();
}


bool search(TreeNode* root, int target) {
    if (root == nullptr) {
        return false;
    }
    
    if (root->data == target) {
        return true;
    } else if (target < root->data) {
        return search(root->left, target);
    } else {
        return search(root->right, target);
    }
}

int countOccurrences(TreeNode* root, int target) {
    if (root == nullptr) {
        return 0;
    }
    
    int count = 0;
    if (root->data == target) {
        count = 1;
    }
    return count + countOccurrences(root->left, target) + countOccurrences(root->right, target);
}

int getHeight(TreeNode* root) {
    if (root == nullptr) {
        return 0;
    }
    
    int leftHeight = getHeight(root->left);
    int rightHeight = getHeight(root->right);
    
    return 1 + max(leftHeight, rightHeight);
}

Tree* createTreeFromUserInput() {
    Tree* tree = new Tree();
    int value;
    char choice;
    
    cout << "=== ЗАПОЛНЕНИЕ ДЕРЕВА ===\n";
    
    cout << "Разрешить дубликаты в дереве? (y/n): ";
    cin >> choice;
    tree->allowDuplicates = (choice == 'y' || choice == 'Y');
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    
    cout << "Введите значения для добавления в дерево.\n";
    
    do {
        cout << "Введите значение: ";
        cin >> value;
        
        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Ошибка! Пожалуйста, введите целое число.\n";
            continue;
        }
        
        if (tree->allowDuplicates) {
            tree->root = insertWithDuplicates(tree->root, value, tree->size);
            cout << "Значение " << value << " добавлено в дерево.\n";
        } else {
            if (search(tree->root, value)) {
                cout << "Значение " << value << " уже существует в дереве. Дубликаты не разрешены.\n";
            } else {
                tree->root = insertWithoutDuplicates(tree->root, value, tree->size);
                cout << "Значение " << value << " добавлено в дерево.\n";
            }
        }
        
        cout << "Добавить еще одно значение? (y/n): ";
        cin >> choice;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        
    } while (choice == 'y' || choice == 'Y');
    
    return tree;
}

void inOrderTraversal(TreeNode* root) {
    if (root != nullptr) {
        inOrderTraversal(root->left);
        cout << root->data << " ";
        inOrderTraversal(root->right);
    }
}

void deleteTree(TreeNode* root) {
    if (root != nullptr) {
        deleteTree(root->left);
        deleteTree(root->right);
        delete root;
    }
}

void addValueToTree(Tree* tree) {
    if (tree == nullptr) {
        cout << "Дерево не создано!\n";
        waitForEnter();
        return;
    }
    
    int value;
    cout << "Введите значение для добавления: ";
    cin >> value;
    
    if (cin.fail()) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Ошибка! Пожалуйста, введите целое число.\n";
        waitForEnter();
        return;
    }
    
    if (tree->allowDuplicates) {
        tree->root = insertWithDuplicates(tree->root, value, tree->size);
        cout << "Значение " << value << " добавлено в дерево.\n";
    } else {
        if (search(tree->root, value)) {
            cout << "Значение " << value << " уже существует в дереве. Дубликаты не разрешены.\n";
        } else {
            tree->root = insertWithoutDuplicates(tree->root, value, tree->size);
            cout << "Значение " << value << " добавлено в дерево.\n";
        }
    }
    
    waitForEnter();
}

void analyzeSearchComplexity(Tree* tree) {
    if (tree == nullptr || tree->root == nullptr) {
        cout << "Дерево пустое! Сначала создайте дерево.\n";
        waitForEnter();
        return;
    }
    
    cout << "\n=== АНАЛИЗ СЛОЖНОСТИ ПОИСКА ===\n";
    
    int height = getHeight(tree->root);
    int n = tree->size;
    cout << "Характеристики дерева:\n";
    cout << " - Количество элементов: " << n << "\n";
    cout << " - Высота дерева: " << height << "\n";
    
    cout << "\nОжидаемая сложность поиска: ";
    
    if (height <= log2(n) + 2) {
        int operations = ceil(log2(n));
        cout << "O(log n) = O(log " << n << ") = " << operations << " операций\n";
    } else {
        cout << "O(n) = O(" << n << ") = " << n << " операций\n";
    }
    
    waitForEnter();
}

int main() {
    Tree* tree = nullptr;
    int choice;
    
    cout << "=== ПРОГРАММА ПОИСКА В ДЕРЕВЕ ===\n";
    
    do {
        cout << "\nМеню:\n";
        cout << "1. Создать новое дерево\n";
        cout << "2. Поиск значения в дереве\n";
        cout << "3. Показать дерево (в порядке возрастания)\n";
        cout << "4. Добавить значение в дерево\n";
        cout << "5. Информация о дереве\n";
        cout << "6. Анализ сложности поиска\n";
        cout << "7. Выход\n";
        cout << "Выберите действие: ";
        cin >> choice;
        
        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Ошибка! Пожалуйста, введите число от 1 до 7.\n";
            waitForEnter();
            continue;
        }
        
        switch (choice) {
            case 1: {
                if (tree != nullptr) {
                    deleteTree(tree->root);
                    delete tree;
                }
                tree = createTreeFromUserInput();
                break;
            }
            
            case 2: {
                if (tree == nullptr || tree->root == nullptr) {
                    cout << "Дерево пустое! Сначала создайте дерево.\n";
                } else {
                    int key;
                    cout << "Введите значение для поиска: ";
                    cin >> key;
                    
                    if (cin.fail()) {
                        cin.clear();
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        cout << "Ошибка! Пожалуйста, введите целое число.\n";
                    } else {
                        if (search(tree->root, key)) {
                            if (tree->allowDuplicates) {
                                int count = countOccurrences(tree->root, key);
                                cout << "✓ Значение " << key << " найдено в дереве " << count << " раз(а).\n";
                            } else {
                                cout << "✓ Значение " << key << " найдено в дереве.\n";
                            }
                        } else {
                            cout << "✗ Значение " << key << " не найдено в дереве.\n";
                        }
                    }
                }
                waitForEnter();
                break;
            }
            
            case 3: {
                if (tree == nullptr || tree->root == nullptr) {
                    cout << "Дерево пустое!\n";
                } else {
                    cout << "Элементы дерева (в порядке возрастания): ";
                    inOrderTraversal(tree->root);
                    cout << endl;
                }
                waitForEnter();
                break;
            }
            
            case 4: {
                addValueToTree(tree);
                break;
            }
            
            case 5: {
                if (tree == nullptr) {
                    cout << "Дерево не создано!\n";
                } else {
                    cout << "Информация о дереве:\n";
                    cout << " - Разрешены дубликаты: " << (tree->allowDuplicates ? "Да" : "Нет") << "\n";
                    cout << " - Количество элементов: " << tree->size << "\n";
                    if (tree->root != nullptr) {
                        cout << " - Высота дерева: " << getHeight(tree->root) << "\n";
                    } else {
                        cout << " - Дерево пустое\n";
                    }
                }
                waitForEnter();
                break;
            }
            
            case 6: {
                analyzeSearchComplexity(tree);
                break;
            }
            
            case 7: {
                cout << "Выход из программы...\n";
                break;
            }
            
            default: {
                cout << "Неверный выбор! Пожалуйста, выберите от 1 до 7.\n";
                waitForEnter();
                break;
            }
        }
        
    } while (choice != 7);
    
    if (tree != nullptr) {
        deleteTree(tree->root);
        delete tree;
    }
    
    return 0;
}