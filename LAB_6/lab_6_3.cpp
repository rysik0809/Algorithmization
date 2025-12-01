#include <iostream>
#include <ctime>
#include <random>
#include <algorithm>

using namespace std;

int printMatrix(int** m, int n) {
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
    return 0;
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
            if (i == j) {
                m[i][j] = 0;
            } else {
                m[i][j] = m[j][i] = rand() % 2;
            }
        }
    }
    return m;
}

int** resizeMatrix(int** original, int oldSize, int newSize) {
    int** newMatrix = new int*[newSize];
    for (int i = 0; i < newSize; i++) {
        newMatrix[i] = new int[newSize];
        for (int j = 0; j < newSize; j++) {
            if (i < oldSize && j < oldSize) {
                newMatrix[i][j] = original[i][j];
            } else {
                newMatrix[i][j] = 0;
            }
        }
    }
    return newMatrix;
}

void deleteMatrix(int** m, int n) {
    for (int i = 0; i < n; ++i) {
        delete[] m[i];
    }
    delete[] m;
}

int** unionGraphs(int** G1, int** G2, int n) {
    int** result = new int*[n];
    for (int i = 0; i < n; i++) {
        result[i] = new int[n];
        for (int j = 0; j < n; j++) {
            result[i][j] = (G1[i][j] == 1 || G2[i][j] == 1) ? 1 : 0;
        }
    }
    return result;
}

int** intersectionGraphs(int** G1, int** G2, int n) {
    int** result = new int*[n];
    for (int i = 0; i < n; i++) {
        result[i] = new int[n];
        for (int j = 0; j < n; j++) {
            result[i][j] = (G1[i][j] == 1 && G2[i][j] == 1) ? 1 : 0;
        }
    }
    return result;
}

int** ringSumGraphs(int** G1, int** G2, int n) {
    int** result = new int*[n];
    for (int i = 0; i < n; i++) {
        result[i] = new int[n];
        for (int j = 0; j < n; j++) {
            result[i][j] = (G1[i][j] != G2[i][j]) ? 1 : 0;
        }
    }
    return result;
}

int main() {
    srand(time(0));
    int n1, n2;
    
    cout << "Введите количество вершин в графе G1: ";
    cin >> n1;
    
    cout << "Введите количество вершин в графе G2: ";
    cin >> n2;
    
    int** G1 = createMatrix(n1);
    int** G2 = createMatrix(n2);
    
    cout << "\nМатрица смежности G1 (" << n1 << "x" << n1 << "):" << endl;
    printMatrix(G1, n1);
    
    cout << "Матрица смежности G2 (" << n2 << "x" << n2 << "):" << endl;
    printMatrix(G2, n2);
    
    if (n1 != n2) {
        cout << "Внимание: Графы имеют разные размеры (" << n1 << " и " << n2 << ")." << endl;
        cout << "Хотите привести матрицы к одному размеру для выполнения операций? (y/n): ";
        char choice;
        cin >> choice;
        
        if (choice == 'y' || choice == 'Y') {
            int newSize = max(n1, n2);
            
            if (n1 < newSize) {
                int** temp = resizeMatrix(G1, n1, newSize);
                deleteMatrix(G1, n1);
                G1 = temp;
                n1 = newSize;
            }
            
            if (n2 < newSize) {
                int** temp = resizeMatrix(G2, n2, newSize);
                deleteMatrix(G2, n2);
                G2 = temp;
                n2 = newSize;
            }
            
            cout << "\nМатрицы приведены к размеру " << newSize << "x" << newSize << ":" << endl;
            cout << "Матрица смежности G1:" << endl;
            printMatrix(G1, newSize);
            
            cout << "Матрица смежности G2:" << endl;
            printMatrix(G2, newSize);
        } else {
            cout << "\nОперации над графами не выполнялись." << endl;
            cout << "Операции (объединение, пересечение, кольцевая сумма)" << endl;
            cout << "могут быть выполнены только для графов одинакового размера." << endl;
            
            deleteMatrix(G1, n1);
            deleteMatrix(G2, n2);
            return 0;
        }
    }
    
    int n = n1;
    
    cout << "\nРезультаты операций над графами:" << endl;
    
    int** unionResult = unionGraphs(G1, G2, n);
    cout << "Объединение G1 ∪ G2:" << endl;
    printMatrix(unionResult, n);
    
    int** intersectionResult = intersectionGraphs(G1, G2, n);
    cout << "Пересечение G1 ∩ G2:" << endl;
    printMatrix(intersectionResult, n);
    
    int** ringSumResult = ringSumGraphs(G1, G2, n);
    cout << "Кольцевая сумма G1 ⊕ G2:" << endl;
    printMatrix(ringSumResult, n);
    
    deleteMatrix(G1, n);
    deleteMatrix(G2, n);
    deleteMatrix(unionResult, n);
    deleteMatrix(intersectionResult, n);
    deleteMatrix(ringSumResult, n);
    
    cout << "Программа завершена." << endl;
    
    return 0;
}