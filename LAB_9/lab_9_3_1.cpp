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
    if (v != nullptr) {
        delete[] v;
    }
}

void DFSD(int** G, int numG, int* visited, int* distance, int current, int currentDistance) {
    visited[current] = 1;  
    distance[current] = currentDistance;  
    cout << current << " "; 
    for(int i = 0; i < numG; i++){
        if(G[current][i] == 1 && visited[i] == 0){
            DFSD(G, numG, visited, distance, i, currentDistance + 1);
        }
    }
}

void DFSDistance(int** G, int numG, int startVertex) {
    int* visited = new int[numG];
    int* distance = new int[numG];
    
    for(int i = 0; i < numG; i++){
        visited[i] = 0;      
        distance[i] = -1;    
    }
    
    DFSD(G, numG, visited, distance, startVertex, 0);
    cout << endl;
    
    cout << "Расстояния от вершины " << startVertex << " до:" << endl;
    for(int i = 0; i < numG; i++){
        if(distance[i] != -1) {
            cout << "Вершина " << i << ": " << distance[i] << endl;
        } else {
            cout << "Вершина " << i << ": недостижима" << endl;
        }
    }
    
    delete[] visited;
    delete[] distance;
}

int main(){
    srand(time(0));
    int numG, current = 0;
    
    cout << "Введите количество вершин в графе: ";
    cin >> numG;
    
    if (numG <= 0) {
        cout << "Ошибка: количество вершин должно быть положительным!" << endl;
        return 1;
    }

    int** G = createMatrix(numG);
    printMatrix(G, numG);

    cout << "Введите начальную вершину обхода: ";
    cin >> current;
    
    if (current < 0 || current >= numG) {
        cout << "Ошибка: неверный номер вершины!" << endl;
        deleteM(G, numG, nullptr);
        return 1;
    }
    
    DFSDistance(G, numG, current);
    
    deleteM(G, numG, nullptr);
    return 0;
}