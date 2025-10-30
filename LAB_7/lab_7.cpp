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
            m[i][j] = m[j][i] = (i == j ? 0 : rand() % 2);
        }
    }
    return m;
}
void deleteM(int** m, int n, int* v) {
    for (int i = 0; i < n; ++i) {
        delete[] m[i];
    }
    delete[] m;
    delete[] v;
}
void DFS(int** G, int numG, int* visited, int s){
    visited[s] = 1;
    cout<<s;
    for(int i = 0; i < numG; i++){
        if(G[s][i] == 1 && visited[i] == 0){
            DFS(G, numG, visited, i);
        }
    }
}

int main(){
    srand(time(0));
    int numG, current = 0;
    
    cout << "Введите кол-во вершин в матрице: ";
    cin >> numG;
    
    int* visited = new int[numG];

    for(int i = 0; i < numG; i++){
        visited[i] = 0;
    }

    int** G = createMatrix(numG);
    printMatrix(G, numG);

    cout << "Вершина с которой начинать обход: ";
    cin >> current;
    cout << "Результат: ";
    DFS(G, numG, visited, current);
    cout << endl;
    deleteM(G, numG, visited);
    return 0;
}