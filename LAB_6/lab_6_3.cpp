#include <iostream>
#include <ctime>
#include <random>

using namespace std;

int printMatrix(int** m, int n){
    cout << "   ";
    for(int i = 0; i < n; i++){
        cout << i << "   ";
    }
    cout << endl;
    
    for(int i = 0; i < n; i++){
        cout << i << "| ";
        for(int j = 0; j < n; j++){
            cout << m[i][j] << "   ";
        }
        cout << endl;
    }
    cout << endl;
    return 0;
}
int** createMatrix(int n){
    int** m = new int*[n];
    for (int i = 0; i < n; i++) {
        m[i] = new int[n];
    }
    for(int i = 0; i < n; i++){
        for(int j = i; j < n; j++){
            m[j][i] = m[i][j] = rand() % 2;
        }
    }
    return m;
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
    int n;
    
    cout << "Введите количество вершин в графах: ";
    cin >> n;
    
    int** G1 = createMatrix(n);
    int** G2 = createMatrix(n);
    
    cout << "Матрица смежности G1:" << endl;
    printMatrix(G1, n);
    
    cout << "Матрица смежности G2:" << endl;
    printMatrix(G2, n);
    
    int** unionResult = unionGraphs(G1, G2, n);
    int** intersectionResult = intersectionGraphs(G1, G2, n);
    int** ringSumResult = ringSumGraphs(G1, G2, n);
    
    cout << "Объединение G1 ∪ G2:" << endl;
    printMatrix(unionResult, n);
    
    cout << "Пересечение G1 ∩ G2:" << endl;
    printMatrix(intersectionResult, n);
    
    cout << "Кольцевая сумма G1 ⊕ G2:" << endl;
    printMatrix(ringSumResult, n);
    
    deleteMatrix(G1, n);
    deleteMatrix(G2, n);
    deleteMatrix(unionResult, n);
    deleteMatrix(intersectionResult, n);
    deleteMatrix(ringSumResult, n);
    
    return 0;
}