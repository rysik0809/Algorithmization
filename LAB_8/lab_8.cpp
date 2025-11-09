#include <iostream>
#include <ctime>
#include <random>
#include <queue>

using namespace std;

class Node{
public:
    int data;
    Node* next;

    Node(int value):data(value),next(nullptr){}
};

class LinkedList{
private:
    Node* head;

public:
    LinkedList():head(nullptr){}
    ~LinkedList(){
        clear(); 
    }

    void push_front(int value) {
        Node* newNode = new Node(value);
        newNode->next = head;
        head = newNode;
    }
    Node* getHead() const{
        return head;
    }
    void clear() {
        Node* current = head;
        while (current != nullptr) {
            Node* next = current->next;
            delete current;
            current = next;
        }
        head = nullptr;
    }
    bool empty() const {
        return head == nullptr;
    }
};

//Список смежности
class Graph{
    int numVertices;
    LinkedList* adjLists;
public:
    Graph(int V);
    void addEdge(int src, int dest);
    void printGraph();
    ~Graph();

    int getNumVertices() { return numVertices; }
    Node* getAdjListHead(int vertex){
        return adjLists[vertex].getHead(); 
    }
};
Graph::Graph(int vertices){
    numVertices = vertices;
    adjLists = new LinkedList[vertices];
}
Graph::~Graph(){
    delete[] adjLists;
}
void Graph::addEdge(int src, int dest){
    adjLists[src].push_front(dest);
}
void Graph::printGraph()
{
    for (int i = 0; i < numVertices; i++)
    {
        cout << "Вершина " << i << ":";
        
        Node* current = adjLists[i].getHead();
        while (current != nullptr)
        {
            cout << " -> " << current->data;
            current = current->next;
        }
        cout << endl;
    }
    cout << endl;
}

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

void BFS_AdjList(Graph& G, int v, bool* NUM, int size_G) {
    queue<int> Q;
    Q.push(v);
    NUM[v] = true;
    
    while (!Q.empty()) {
        v = Q.front();
        Q.pop();
        cout << v << " ";
        
        Node* current = G.getAdjListHead(v);
        
        while (current != nullptr) {
            int neighbor = current->data;
            if (!NUM[neighbor]) {
                Q.push(neighbor);
                NUM[neighbor] = true;
            }
            current = current->next;
        }
    }
}

void POH_AdjList(Graph& G, int size_G) {
    bool* NUM = new bool[size_G];
    for (int i = 0; i < size_G; i++) {
        NUM[i] = false;
    }
    
    for (int v = 0; v < size_G; v++) {
        if (!NUM[v]) {
            BFS_AdjList(G, v, NUM, size_G);
        }
    }
    
    cout << endl;
    delete[] NUM;
}

//Матрица смежности
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
void deleteM(int** m, int n, int* v, int* v2) {
    for (int i = 0; i < n; ++i) {
        delete[] m[i];
    }
    delete[] m;
    delete[] v;
    delete[] v2;
}

void BFS(int** G, int v, bool* NUM, int size_G) {
    queue<int> Q;
    Q.push(v);
    NUM[v] = true;
    
    while (!Q.empty()) {
        v = Q.front();
        Q.pop();
        cout << v << " ";
        
        for (int i = 0; i < size_G; i++) {
            if (G[v][i] == 1 && !NUM[i]) {
                Q.push(i);  
                NUM[i] = true;
            }
        }
    }
}
void POH(int** G, int size_G) {
    bool* NUM = new bool[size_G];
    for (int i = 0; i < size_G; i++) {
        NUM[i] = false;
    }
    
    for (int v = 0; v < size_G; v++) {
        if (!NUM[v]) {
            BFS(G, v, NUM, size_G);
        }
    }
    
    cout << endl;
    delete[] NUM;
}

int main() {
    srand(time(0));
    int n = 0;
    
    cout << "Введите количество вершин в графе: ";
    cin >> n;
    if (n <= 0) {
        cout << "Ошибка: количество вершин должно быть положительным!" << endl;
        return 1;
    }

    int** M = createMatrix(n);

    cout << "Матрица смежности графа:" << endl;
    printMatrix(M, n);
    cout << "Порядок обхода графа в ширину (матрица смежности): ";
    POH(M, n);

    Graph g = matrixToList(M, n);
    cout << "\nСтруктура графа (список смежности):" << endl;
    g.printGraph();
    
    cout << "Порядок обхода графа в ширину (список смежности): ";
    POH_AdjList(g, n);
    
    deleteM(M, n, nullptr, nullptr);
    
    return 0;
}