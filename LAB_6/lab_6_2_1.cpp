#include <fstream>
#include <iostream>
#include <ctime>
#include <random>
#include <list>

using namespace std;

void printMatrix(int** m, int n) {
    cout << "   ";
    for (int i = 0; i < n; i++) {
        cout << i << "   ";
    }
    cout << endl;
    
    for (int i = 0; i < n; i++) {
        cout << i << "| ";
        for (int j = 0; j < n; j++) {
            cout << m[i][j] << "   ";
        }
        cout << endl;
    }
    cout << endl;
}

int** createMatrix(int n) {
    int** m = new int*[n];
    for (int i = 0; i < n; i++) {
        m[i] = new int[n];
        for (int j = 0; j < n; j++) {
            m[i][j] = 0;
        }
    }
    
    for (int i = 0; i < n; i++) {
        for (int j = i; j < n; j++) {
            m[j][i] = m[i][j] = rand() % 2;
        }
    }
    return m;
}

int** copyMatrix(int** source, int n) {
    int** copy = new int*[n];
    for (int i = 0; i < n; i++) {
        copy[i] = new int[n];
        for (int j = 0; j < n; j++) {
            copy[i][j] = source[i][j];
        }
    }
    return copy;
}

void deleteMatrix(int** m, int n) {
    for (int i = 0; i < n; ++i) {
        delete[] m[i];
    }
    delete[] m;
}

int** identifyVertices(int** matrix, int n, int v1, int v2) {
    if (v1 == v2 || v1 >= n || v2 >= n || v1 < 0 || v2 < 0) {
        cout << "Неверные вершины для отождествления!" << endl;
        return nullptr;
    }
    
    int newSize = n - 1;
    int** newMatrix = new int*[newSize];
    for (int i = 0; i < newSize; i++) {
        newMatrix[i] = new int[newSize]();
    }
    
    int oldToNew[n];
    int newIndex = 0;
    for (int i = 0; i < n; i++) {
        if (i != v2) {
            oldToNew[i] = newIndex++;
        }
    }
    
    for (int i = 0; i < n; i++) {
        if (i == v2) continue;
        
        for (int j = 0; j < n; j++) {
            if (j == v2) continue;
            
            int newI = oldToNew[i];
            int newJ = oldToNew[j];
            
            if (i == v1 && j == v1) {
                newMatrix[newI][newJ] = matrix[v1][v1] || matrix[v2][v2];
            }
            else if (i == v1) {
                newMatrix[newI][newJ] = matrix[v1][j] || matrix[v2][j];
            }
            else if (j == v1) {
                newMatrix[newI][newJ] = matrix[i][v1] || matrix[i][v2];
            }
            else {
                newMatrix[newI][newJ] = matrix[i][j];
            }
        }
    }
    
    return newMatrix;
}

int** contractEdge(int** matrix, int n, int v1, int v2) {
    if (v1 == v2 || v1 >= n || v2 >= n || v1 < 0 || v2 < 0) {
        cout << "Неверные вершины для стягивания!" << endl;
        return nullptr;
    }
    
    if (matrix[v1][v2] == 0) {
        cout << "Ребро между вершинами " << v1 << " и " << v2 << " не существует!" << endl;
        return nullptr;
    }
    
    return identifyVertices(matrix, n, v1, v2);
}

int** splitVertex(int** matrix, int n, int v) {
    if (v >= n || v < 0) {
        cout << "Неверная вершина для расщепления!" << endl;
        return nullptr;
    }
    
    int newSize = n + 1;
    int** newMatrix = new int*[newSize];
    for (int i = 0; i < newSize; i++) {
        newMatrix[i] = new int[newSize]();
    }
    
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            newMatrix[i][j] = matrix[i][j];
        }
    }
    
    int newVertex = n;
    
    newMatrix[v][newVertex] = 1;
    newMatrix[newVertex][v] = 1;
    
    for (int i = 0; i < n; i++) {
        if (i != v && matrix[v][i] == 1) {
            newMatrix[newVertex][i] = 1;
            newMatrix[i][newVertex] = 1;
        }
    }
    
    return newMatrix;
}

int main() {
    srand(time(0));
    int n;
    
    cout << "Введите количество вершин в графе: ";
    cin >> n;
    
    int** matrix = createMatrix(n);
    int currentSize = n;
    
    cout << "Исходная матрица смежности:" << endl;
    printMatrix(matrix, currentSize);
    
    int choice;
    bool running = true;
    
    while (running) {
        cout << "\nВыберите операцию:" << endl;
        cout << "1 - отождествление вершин" << endl;
        cout << "2 - стягивание ребра" << endl;
        cout << "3 - расщепление вершины" << endl;
        cout << "4 - показать текущую матрицу" << endl;
        cout << "5 - создать новый граф" << endl;
        cout << "6 - выход" << endl;
        cout << "Ваш выбор: ";
        cin >> choice;
        
        int** resultMatrix = nullptr;
        int newSize = currentSize;
        
        switch (choice) {
            case 1: {
                int v1, v2;
                cout << "Введите номера вершин для отождествления: ";
                cin >> v1 >> v2;
                resultMatrix = identifyVertices(matrix, currentSize, v1, v2);
                newSize = currentSize - 1;
                break;
            }
            case 2: {
                int v1, v2;
                cout << "Введите номера вершин для стягивания ребра: ";
                cin >> v1 >> v2;
                resultMatrix = contractEdge(matrix, currentSize, v1, v2);
                newSize = currentSize - 1;
                break;
            }
            case 3: {
                int v;
                cout << "Введите номер вершины для расщепления: ";
                cin >> v;
                resultMatrix = splitVertex(matrix, currentSize, v);
                newSize = currentSize + 1;
                break;
            }
            case 4: {
                cout << "Текущая матрица смежности:" << endl;
                printMatrix(matrix, currentSize);
                break;
            }
            case 5: {
                deleteMatrix(matrix, currentSize);
                cout << "Введите количество вершин в новом графе: ";
                cin >> n;
                matrix = createMatrix(n);
                currentSize = n;
                cout << "Новая матрица смежности:" << endl;
                printMatrix(matrix, currentSize);
                break;
            }
            case 6: {
                running = false;
                break;
            }
            default:
                cout << "Неверный выбор!" << endl;
        }
        
        if (resultMatrix != nullptr && choice >= 1 && choice <= 3) {
            deleteMatrix(matrix, currentSize);
            matrix = resultMatrix;
            currentSize = newSize;
            cout << "Результат операции:" << endl;
            printMatrix(matrix, currentSize);
        }
    }
    
    deleteMatrix(matrix, currentSize);
    cout << "Программа завершена." << endl;
    
    return 0;
}