#include <iostream>
#include <ctime>
#include <random>
#include <queue>
#include <limits.h>

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
            if (m[i][j] == INT_MAX) {
                cout << "∞   ";
            } else {
                cout << m[i][j] << "   ";
            }
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
    }

    for (int i = 0; i < n; i++) {
        for (int j = i; j < n; j++) {
            if (i == j) {
                m[i][j] = 0; 
            } else {
                bool hasEdge = (rand() % 100) < 70;
                if (hasEdge) {
                    m[i][j] = m[j][i] = rand() % 11;
                } else {
                    m[i][j] = m[j][i] = 0;
                }
            }
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

void BFSD(int** G, int numG, int** GD, int start) {
    int* dist = new int[numG];
    bool* visited = new bool[numG];

    for (int i = 0; i < numG; i++) {
        dist[i] = INT_MAX;
        visited[i] = false;
    }

    dist[start] = 0;

    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    pq.push(make_pair(0, start));

    while (!pq.empty()) {
        int u = pq.top().second;
        pq.pop();

        if (visited[u]) continue;
        visited[u] = true;

        for (int v = 0; v < numG; v++) {
            if (G[u][v] > 0) {
                if (!visited[v] && dist[u] != INT_MAX) {
                    int newDist = dist[u] + G[u][v];
                    if (newDist < dist[v]) {
                        dist[v] = newDist;
                        pq.push(make_pair(dist[v], v));
                    }
                }
            }
        }
    }

    // Записываем результаты в матрицу расстояний
    for (int i = 0; i < numG; i++) {
        GD[start][i] = (dist[i] == INT_MAX ? -1 : dist[i]);
    }

    delete[] dist;
    delete[] visited;
}

// Функция для вычисления эксцентриситетов
int* calculateEccentricities(int** GD, int n) {
    int* ecc = new int[n];
    for (int i = 0; i < n; i++) {
        ecc[i] = 0;
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (GD[i][j] > ecc[i] && GD[i][j] != -1) {
                ecc[i] = GD[i][j];
            }
        }
    }

    return ecc;
}

int main() {
    srand(time(0)); 

    int numG = 0;

    cout << "Введите количество вершин в графе: ";
    cin >> numG;

    if (numG <= 0) {
        cout << "Количество вершин должно быть положительным числом!" << endl;
        return 1;
    }

    cout << "\n=== Задача 1: Генерация матрицы смежности ===" << endl;
    int** G = createMatrix(numG);
    
    cout << "Матрица смежности графа (0 означает отсутствие ребра):" << endl;
    printMatrix(G, numG);

    cout << "\n=== Задача 2: Поиск расстояний с использованием BFS/очереди ===" << endl;
    
    int** GD = new int*[numG];
    for (int i = 0; i < numG; i++) {
        GD[i] = new int[numG];
        for (int j = 0; j < numG; j++) {
            GD[i][j] = -1; 
        }
    }

    for (int i = 0; i < numG; i++) {
        BFSD(G, numG, GD, i);
    }

    cout << "Матрица кратчайших расстояний (-1 означает недостижимость):" << endl;
    printMatrix(GD, numG);

    cout << "\n=== Дополнительная информация ===" << endl;
    int* ecc = calculateEccentricities(GD, numG);
    
    cout << "Эксцентриситеты вершин:" << endl;
    for (int i = 0; i < numG; i++) {
        cout << "Вершина " << i << ": " << ecc[i] << endl;
    }

    int radius = INT_MAX;
    int diameter = 0;
    for (int i = 0; i < numG; i++) {
        if (ecc[i] < radius) radius = ecc[i];
        if (ecc[i] > diameter) diameter = ecc[i];
    }

    cout << "\nРадиус графа: " << radius << endl;
    cout << "Диаметр графа: " << diameter << endl;

    cout << "Центральные вершины: ";
    for (int i = 0; i < numG; i++) {
        if (ecc[i] == radius) {
            cout << i << " ";
        }
    }
    cout << endl;

    cout << "Периферийные вершины: ";
    for (int i = 0; i < numG; i++) {
        if (ecc[i] == diameter) {
            cout << i << " ";
        }
    }
    cout << endl;

    deleteMatrix(G, numG);
    deleteMatrix(GD, numG);
    delete[] ecc;

    return 0;
}