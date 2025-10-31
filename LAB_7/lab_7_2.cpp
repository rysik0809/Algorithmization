#include <iostream>
#include <ctime>
#include <random>

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
    ~LinkedList(){ clear(); }

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

class Graph{
    int numVertices;
    LinkedList* adjLists;
public:
    Graph(int V);
    void addEdge(int src, int dest);
    void printGraph();
    ~Graph();

    int getNumVertices() const { return numVertices; }
    Node* getAdjListHead(int vertex) const { return adjLists[vertex].getHead(); }
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
void DFS(const Graph& graph, int* visited, int s){
    visited[s] = 1;
    cout << s << " ";
    
    Node* current = graph.getAdjListHead(s);
    while (current != nullptr) {
        int neighbor = current->data;
        if (visited[neighbor] == 0) {
            DFS(graph, visited, neighbor);
        }
        current = current->next;
    }
}
void runDFS(const Graph& graph, int startVertex) {
    int numVertices = graph.getNumVertices();
    
    if (startVertex < 0 || startVertex >= numVertices) {
        cout << "Ошибка: начальная вершина " << startVertex << " не существует!" << endl;
        return;
    }
    
    int* visited = new int[numVertices]();
    
    cout << "DFS обход начиная с вершины " << startVertex << ": ";
    DFS(graph, visited, startVertex);
    cout << endl;
    
    delete[] visited;
}

Graph createGraph(int n) {
    Graph graph(n);
    srand(time(0));
    
    cout << "Создание случайного графа с " << n << " вершинами..." << endl;
    
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if (rand() % 2 == 1) {
                graph.addEdge(i, j);
                graph.addEdge(j, i);
            }
        }
    }
    
    return graph;
}

int main(){
    int n;
    cout << "Введите количество вершин в графе: ";
    cin >> n;
    
    if (n <= 0) {
        cout << "Ошибка: количество вершин должно быть положительным!" << endl;
        return 1;
    }
    
    Graph g = createGraph(n);
    
    cout << "\nСтруктура графа:" << endl;
    g.printGraph();
    
    int startVertex;
    cout << "Введите начальную вершину (0-" << n-1 << "): ";
    cin >> startVertex;
    runDFS(g, startVertex);

    return 0;
}