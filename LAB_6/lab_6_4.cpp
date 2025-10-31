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

int** cartesianProduct(int** G1, int n1, int** G2, int n2) {
    int n = n1 * n2;
    int** result = new int*[n];
    for (int i = 0; i < n; i++) {
        result[i] = new int[n];
        for (int j = 0; j < n; j++) {
            result[i][j] = 0;
        }
    }
    for (int i = 0; i < n1; i++) {
        for (int j = 0; j < n2; j++) {
            for (int k = 0; k < n1; k++) {
                for (int l = 0; l < n2; l++) {
                    int vertex1 = i * n2 + j;
                    int vertex2 = k * n2 + l;
                    if ((i == k && G2[j][l] == 1) || (j == l && G1[i][k] == 1)) {
                        result[vertex1][vertex2] = 1;
                    }
                }
            }
        }
    }
    
    return result;
}

int main(){
    srand(time(0));
    int n1, n2;
    
    cout << "Введите количество вершин в графе G1: ";
    cin >> n1;
    cout << "Введите количество вершин в графе G2: ";
    cin >> n2;
    
    int** G1 = createMatrix(n1);
    int** G2 = createMatrix(n2);
    
    cout << "Матрица смежности G1 (" << n1 << " вершин):" << endl;
    printMatrix(G1, n1);
    
    cout << "Матрица смежности G2 (" << n2 << " вершин):" << endl;
    printMatrix(G2, n2);
    
    int** product = cartesianProduct(G1, n1, G2, n2);
    int productSize = n1 * n2;
    
    cout << "Декартово произведение G1 X G2 (" << productSize << " вершин):" << endl;
    printMatrix(product, productSize);
    
    cout << "Соответствие вершин:" << endl;
    cout << "Вершина G1 X G2 = (вершина G1, вершина G2)" << endl;
    for (int i = 0; i < n1; i++) {
        for (int j = 0; j < n2; j++) {
            int vertex = i * n2 + j;
            cout << "Вершина " << vertex << " = (" << i << ", " << j << ")" << endl;
        }
    }
    cout << endl;
    
    deleteMatrix(G1, n1);
    deleteMatrix(G2, n2);
    deleteMatrix(product, productSize);
    return 0;
}