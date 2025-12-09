#include <iostream>
#include <ctime>
#include <vector>
#include <queue>
#include <limits>
#include <iomanip>
#include <algorithm>

using namespace std;

const int INF = numeric_limits<int>::max();

vector<vector<int>> createWeightedDirectedGraph(int n, int maxWeight = 15) {
    vector<vector<int>> graph(n, vector<int>(n, 0));
    
    for (int i = 0; i < n; i++) {
        int j = (i + 1) % n; 
        int weight = 1 + rand() % maxWeight;
        graph[i][j] = weight;
    }
    
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (i != j && rand() % 3 == 1) {
                int weight = 1 + rand() % maxWeight;
                graph[i][j] = weight;
            }
        }
    }
    
    return graph;
}

void printAdjacencyMatrix(const vector<vector<int>>& graph) {
    int n = graph.size();
    cout << "Матрица смежности ориентированного графа:" << endl;
    cout << "   ";
    for (int i = 0; i < n; i++) {
        cout << setw(3) << i;
    }
    cout << endl;
    
    for (int i = 0; i < n; i++) {
        cout << setw(2) << i << ":";
        for (int j = 0; j < n; j++) {
            if (graph[i][j] == 0 && i != j) {
                cout << setw(3) << "-";
            } else {
                cout << setw(3) << graph[i][j];
            }
        }
        cout << endl;
    }
    cout << endl;
}

vector<vector<int>> floydWarshall(const vector<vector<int>>& graph) {
    int n = graph.size();
    vector<vector<int>> dist(n, vector<int>(n, INF));
    
    for (int i = 0; i < n; i++) {
        dist[i][i] = 0;
        for (int j = 0; j < n; j++) {
            if (graph[i][j] > 0) {
                dist[i][j] = graph[i][j];
            }
        }
    }
    
    for (int k = 0; k < n; k++) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (dist[i][k] != INF && dist[k][j] != INF) {
                    if (dist[i][j] > dist[i][k] + dist[k][j]) {
                        dist[i][j] = dist[i][k] + dist[k][j];
                    }
                }
            }
        }
    }
    
    return dist;
}

void printShortestDistances(const vector<vector<int>>& dist) {
    int n = dist.size();
    
    cout << "== Задача 2: Поиск расстояний с использованием BFS/очереди ==" << endl;
    cout << "Матрица кратчайших расстояний (-1 означает недостижимость):" << endl << endl;
    
    cout << "|    |";
    for (int j = 0; j < n; j++) {
        cout << setw(3) << j << " |";
    }
    cout << endl;
    
    cout << "|";
    for (int j = 0; j <= n; j++) {
        cout << "----|";
    }
    cout << endl;
    
    for (int i = 0; i < n; i++) {
        cout << "| " << setw(2) << i << " |";
        for (int j = 0; j < n; j++) {
            if (dist[i][j] == INF) {
                cout << setw(3) << -1 << " |";
            } else {
                cout << setw(3) << dist[i][j] << " |";
            }
        }
        cout << endl;
    }
    cout << endl;
}

void calculateGraphProperties(const vector<vector<int>>& dist) {
    int n = dist.size();
    vector<int> eccentricity(n, 0);
    
    for (int i = 0; i < n; i++) {
        int maxDist = 0;
        bool hasUnreachable = false;
        for (int j = 0; j < n; j++) {
            if (i != j) {
                if (dist[i][j] == INF) {
                    hasUnreachable = true;
                } else if (dist[i][j] > maxDist) {
                    maxDist = dist[i][j];
                }
            }
        }
        
        if (hasUnreachable) {
            eccentricity[i] = INF;
        } else {
            eccentricity[i] = maxDist;
        }
    }
    
    int radius = INF;
    int diameter = 0;
    
    for (int i = 0; i < n; i++) {
        if (eccentricity[i] != INF) {
            if (eccentricity[i] < radius) {
                radius = eccentricity[i];
            }
            if (eccentricity[i] > diameter) {
                diameter = eccentricity[i];
            }
        }
    }
    
    if (radius == INF) {
        radius = -1;
    }
    if (diameter == 0) {
        diameter = -1;
    }
    
    vector<int> centralVertices;
    for (int i = 0; i < n; i++) {
        if (eccentricity[i] == radius) {
            centralVertices.push_back(i);
        }
    }
    
    vector<int> peripheralVertices;
    for (int i = 0; i < n; i++) {
        if (eccentricity[i] == diameter) {
            peripheralVertices.push_back(i);
        }
    }
    
    cout << "== Дополнительная информация ==" << endl;
    cout << "Эксцентриситеты вершин:" << endl;
    for (int i = 0; i < n; i++) {
        if (eccentricity[i] == INF) {
            cout << "Вершина " << i << ": недостижимы некоторые вершины (∞)" << endl;
        } else {
            cout << "Вершина " << i << ": " << eccentricity[i] << endl;
        }
    }
    cout << endl;
    
    if (radius == -1 || diameter == -1) {
        cout << "Граф не является сильно связным. Радиус и диаметр не определены." << endl;
    } else {
        cout << "Радиус графа: " << radius << endl;
        cout << "Диаметр графа: " << diameter << endl;
    }
    
    if (!centralVertices.empty()) {
        cout << "Центральные вершины: ";
        for (size_t i = 0; i < centralVertices.size(); i++) {
            cout << centralVertices[i];
            if (i < centralVertices.size() - 1) {
                cout << " ";
            }
        }
        cout << endl;
    }
    
    if (!peripheralVertices.empty()) {
        cout << "Периферийные вершины: ";
        for (size_t i = 0; i < peripheralVertices.size(); i++) {
            cout << peripheralVertices[i];
            if (i < peripheralVertices.size() - 1) {
                cout << " ";
            }
        }
        cout << endl << endl;
    }
}

int main() {
    srand(time(0));
    int n;
    
    cout << "АНАЛИЗ ОРИЕНТИРОВАННОГО ВЗВЕШЕННОГО ГРАФА" << endl;
    cout << "=========================================" << endl;
    cout << "Введите количество вершин в графе: ";
    cin >> n;
    
    if (n <= 0) {
        cout << "Ошибка: количество вершин должно быть положительным!" << endl;
        return 1;
    }
    
    cout << "\nСоздание ориентированного взвешенного графа из " << n << " вершин..." << endl;
    auto graph = createWeightedDirectedGraph(n, 15);
    
    cout << "\n";
    printAdjacencyMatrix(graph);
    
    auto distMatrix = floydWarshall(graph);
    
    printShortestDistances(distMatrix);
    
    calculateGraphProperties(distMatrix);
    
    cout << "\n=========================================" << endl;
    cout << "Анализ графа завершен!" << endl;
    
    return 0;
}