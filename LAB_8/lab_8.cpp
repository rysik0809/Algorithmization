#include <iostream>
#include <ctime>
#include <random>
#include <queue>

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

bool isIsolatedVertex(int** G, int numG, int vertex) {
    for(int i = 0; i < numG; i++){
        if(i != vertex && G[vertex][i] == 1) {
            return false;
        }
    }
    return true;
}

void BFS(int** G, int numG, int* visited, int s) {
    queue<int> q;
    int v = 0;
    visited[s] = 1;
    q.push(s);

    while (!q.empty())
    {
        v = q.front();
        q.pop();
        cout<<v << " ";
        for(int i = 0; i < numG; i++){
            if(G[v][i] == 1 && visited[i] == 0){
                q.push(i);
                visited[i] = 1;
            }
        }
    }
}

int main() {
    srand(time(0));
    int numG = 0;
    int n = 0;
    
    cout << "Введите количество вершин в графе: ";
    cin >> numG;
    if (numG <= 0) {
        cout << "Ошибка: количество вершин должно быть положительным!" << endl;
        return 1;
    }
    
    int* visited = new int[numG];
    for(int i = 0; i < numG; i++){
        visited[i] = 0;
    }

    int** G = createMatrix(numG);

    cout << "Матрица смежности графа:" << endl;
    printMatrix(G, numG);

    cout << "Введите начальную вершину обхода: ";
    cin >> n;
    
    if (n < 0 || n >= numG) {
        cout << "Ошибка: вершина должна быть в диапазоне [0, " << numG-1 << "]!" << endl;
        deleteM(G, numG, visited);
        return 1;
    }
    
    // Проверка на изолированную вершину
    if (isIsolatedVertex(G, numG, n)) {
        cout << "ВНИМАНИЕ: Выбранная вершина " << n << " является изолированной!" << endl;
        cout << "Обход начнется только с этой вершины и завершится сразу." << endl;
        cout << "Продолжить? (y/n): ";
        char choice;
        cin >> choice;
        if (choice == 'n' || choice == 'N') {
            cout << "Обход отменен." << endl;
            deleteM(G, numG, visited);
            return 0;
        }
    }
    
    cout << "Порядок обхода графа в ширину (матрица смежности): ";
    BFS(G, numG, visited, n);
    cout << endl;
    
    deleteM(G, numG, visited);
    
    return 0;
}