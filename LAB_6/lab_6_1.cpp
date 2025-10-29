#include <fstream>
#include <iostream>
#include <ctime>
#include <random>
#include <list>

using namespace std;

// Список смежности
class Graph
{
    int numVertices;
    list<int> *adjLists;

public:
    Graph(int V);
    void addEdge(int src, int dest);
    void printGraph();
    ~Graph();
};
Graph::Graph(int vertices)
{
    numVertices = vertices;
    adjLists = new list<int>[vertices];
}
Graph::~Graph()
{
    delete[] adjLists;
}
void Graph::addEdge(int src, int dest)
{
    adjLists[src].push_front(dest);
}
void Graph::printGraph()
{
    for (int i = 0; i < numVertices; i++)
    {
        cout << "Вершина " << i << ":";
        for (auto it = adjLists[i].begin(); it != adjLists[i].end(); ++it)
        {
            cout << " -> " << *it;
        }
        cout << endl;
    }
    cout << endl;
}

// Матрица смежности
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

// Функция для преобразования матрицы смежности в список смежности
Graph matrixToList(int** matrix, int n) {
    Graph graph(n);
    
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (matrix[i][j] == 1) {
                graph.addEdge(i, j);
            }
        }
    }
    
    return graph;
}

int main(){
    srand(time(0));
    int N1 = 0;
    int N2 = 0;
    
    cout << "Введите кол-во вершин в матрице M1: " << endl;
    cin >> N1;
    cout << "Введите кол-во вершин в матрице M2: " << endl;
    cin >> N2;
    
    int** M1 = createMatrix(N1);
    int** M2 = createMatrix(N2);
    
    cout << "Матрица смежности M1:" << endl;
    printMatrix(M1, N1);
    cout << "Матрица смежности M2:" << endl;
    printMatrix(M2, N2);

    Graph graph1 = matrixToList(M1, N1);
    Graph graph2 = matrixToList(M2, N2);
    
    cout << "Список смежности для M1:" << endl;
    graph1.printGraph();
    
    cout << "Список смежности для M2:" << endl;
    graph2.printGraph();

    deleteMatrix(M1, N1);
    deleteMatrix(M2, N2);
    
    return 0;
}