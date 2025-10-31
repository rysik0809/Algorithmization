#include <iostream>
#include <ctime>
#include <random>

using namespace std;

class Node {
public:
    int data;
    Node* next;

    Node(int value) : data(value), next(nullptr) {}
};

class LinkedList {
private:
    Node* head;

public:
    LinkedList() : head(nullptr) {}
    ~LinkedList() { clear(); }

    void push_front(int value) {
        Node* newNode = new Node(value);
        newNode->next = head;
        head = newNode;
    }
    Node* getHead() const {
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
    bool contains(int value) const {
        Node* current = head;
        while (current != nullptr) {
            if (current->data == value) {
                return true;
            }
            current = current->next;
        }
        return false;
    }
    void remove(int value) {
        Node* current = head;
        Node* prev = nullptr;
        
        while (current != nullptr && current->data != value) {
            prev = current;
            current = current->next;
        }
        
        if (current == nullptr) return;
        
        if (prev == nullptr) {
            head = current->next;
        } else {
            prev->next = current->next;
        }
        
        delete current;
    }
    LinkedList& operator=(const LinkedList& other) {
        if (this != &other) {
            clear();
            Node* current = other.head;
            while (current != nullptr) {
                push_front(current->data);
                current = current->next;
            }
        }
        return *this;
    }
    LinkedList(const LinkedList& other) : head(nullptr) {
        Node* current = other.head;
        while (current != nullptr) {
            push_front(current->data);
            current = current->next;
        }
    }
};

class Graph {
    int numVertices;
    LinkedList* adjLists;
public:
    Graph(int V);
    Graph(const Graph& other);
    Graph& operator=(const Graph& other);
    void addEdge(int src, int dest);
    void removeEdge(int src, int dest);
    bool hasEdge(int src, int dest) const;
    void printGraph() const;
    int getNumVertices() const { return numVertices; }
    const LinkedList& getAdjList(int vertex) const { return adjLists[vertex]; }
    ~Graph();
};
Graph::Graph(int vertices) {
    numVertices = vertices;
    adjLists = new LinkedList[vertices];
}
Graph::Graph(const Graph& other) {
    numVertices = other.numVertices;
    adjLists = new LinkedList[numVertices];
    
    for (int i = 0; i < numVertices; i++) {
        Node* current = other.adjLists[i].getHead();
        while (current != nullptr) {
            adjLists[i].push_front(current->data);
            current = current->next;
        }
    }
}
Graph& Graph::operator=(const Graph& other) {
    if (this != &other) {
        delete[] adjLists;
        
        numVertices = other.numVertices;
        adjLists = new LinkedList[numVertices];
        
        for (int i = 0; i < numVertices; i++) {
            Node* current = other.adjLists[i].getHead();
            while (current != nullptr) {
                adjLists[i].push_front(current->data);
                current = current->next;
            }
        }
    }
    return *this;
}
Graph::~Graph() {
    delete[] adjLists;
}

void Graph::addEdge(int src, int dest) {
    if (src >= 0 && src < numVertices && dest >= 0 && dest < numVertices) {
        if (!adjLists[src].contains(dest)) {
            adjLists[src].push_front(dest);
        }
    }
}
void Graph::removeEdge(int src, int dest) {
    if (src >= 0 && src < numVertices && dest >= 0 && dest < numVertices) {
        adjLists[src].remove(dest);
    }
}
bool Graph::hasEdge(int src, int dest) const {
    if (src >= 0 && src < numVertices && dest >= 0 && dest < numVertices) {
        return adjLists[src].contains(dest);
    }
    return false;
}
void Graph::printGraph() const {
    for (int i = 0; i < numVertices; i++) {
        cout << "Вершина " << i << ":";
        
        Node* current = adjLists[i].getHead();
        while (current != nullptr) {
            cout << " -> " << current->data;
            current = current->next;
        }
        cout << endl;
    }
    cout << endl;
}

Graph createGraph(int n) {
    Graph graph(n);
    
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

// Отождествление вершин
Graph identifyVertices(const Graph& graph, int v1, int v2) {
    if (v1 == v2 || v1 >= graph.getNumVertices() || v2 >= graph.getNumVertices() || v1 < 0 || v2 < 0) {
        cout << "Неверные вершины для отождествления!" << endl;
        return graph;
    }
    
    int newSize = graph.getNumVertices() - 1;
    Graph newGraph(newSize);
    
    int* mapping = new int[graph.getNumVertices()];
    int newIndex = 0;
    for (int i = 0; i < graph.getNumVertices(); i++) {
        if (i == v2) {
            mapping[i] = (v1 < v2) ? v1 : v1 - 1;
        } else {
            mapping[i] = newIndex++;
        }
    }  
    for (int i = 0; i < graph.getNumVertices(); i++) {
        if (i == v2) continue;
        
        Node* current = graph.getAdjList(i).getHead();
        while (current != nullptr) {
            int j = current->data;
            int newI = mapping[i];
            int newJ = mapping[j];
            
            if (newI != newJ) {
                newGraph.addEdge(newI, newJ);
            }
            current = current->next;
        }
    }
    delete[] mapping;
    return newGraph;
}

// Стягивание ребра
Graph contractEdge(const Graph& graph, int v1, int v2) {
    if (v1 == v2 || v1 >= graph.getNumVertices() || v2 >= graph.getNumVertices() || v1 < 0 || v2 < 0) {
        cout << "Неверные вершины для стягивания!" << endl;
        return graph;
    }
    if (!graph.hasEdge(v1, v2)) {
        cout << "Ребро между вершинами " << v1 << " и " << v2 << " не существует!" << endl;
        return graph;
    }
    
    return identifyVertices(graph, v1, v2);
}

Graph splitVertex(const Graph& graph, int v) {
    if (v >= graph.getNumVertices() || v < 0) {
        cout << "Неверная вершина для расщепления!" << endl;
        return graph;
    }
    
    int newSize = graph.getNumVertices() + 1;
    Graph newGraph(newSize);
    
    int newVertex = graph.getNumVertices();
    
    newGraph.addEdge(v, newVertex);
    newGraph.addEdge(newVertex, v);
    
    for (int i = 0; i < graph.getNumVertices(); i++) {
        Node* current = graph.getAdjList(i).getHead();
        while (current != nullptr) {
            int j = current->data;
            newGraph.addEdge(i, j);
            current = current->next;
        }
    }
    
    Node* current = graph.getAdjList(v).getHead();
    while (current != nullptr) {
        int neighbor = current->data;
        if (neighbor != v && rand() % 2 == 0) {
            newGraph.removeEdge(v, neighbor);
            newGraph.removeEdge(neighbor, v);
            newGraph.addEdge(newVertex, neighbor);
            newGraph.addEdge(neighbor, newVertex);
        }
        current = current->next;
    }
    return newGraph;
}

int main() {
    srand(time(0));
    int n;
    cout << "Введите количество вершин в графе: ";
    cin >> n;
    Graph graph = createGraph(n);
    int currentSize = n;
    cout << "Исходный граф:" << endl;
    graph.printGraph();
    int choice;
    bool running = true;
    while (running) {
        cout << "\nВыберите операцию:" << endl;
        cout << "1 - отождествление вершин" << endl;
        cout << "2 - стягивание ребра" << endl;
        cout << "3 - расщепление вершины" << endl;
        cout << "4 - показать текущий граф" << endl;
        cout << "5 - создать новый граф" << endl;
        cout << "6 - выход" << endl;
        cout << "Ваш выбор: ";
        cin >> choice;
        
        Graph resultGraph = graph;
        int newSize = currentSize;
        
        switch (choice) {
            case 1: {
                int v1, v2;
                cout << "Введите номера вершин для отождествления: ";
                cin >> v1 >> v2;
                resultGraph = identifyVertices(graph, v1, v2);
                newSize = currentSize - 1;
                break;
            }
            case 2: {
                int v1, v2;
                cout << "Введите номера вершин для стягивания ребра: ";
                cin >> v1 >> v2;
                resultGraph = contractEdge(graph, v1, v2);
                newSize = currentSize - 1;
                break;
            }
            case 3: {
                int v;
                cout << "Введите номер вершины для расщепления: ";
                cin >> v;
                resultGraph = splitVertex(graph, v);
                newSize = currentSize + 1;
                break;
            }
            case 4: {
                cout << "Текущий граф:" << endl;
                graph.printGraph();
                break;
            }
            case 5: {
                cout << "Введите количество вершин в новом графе: ";
                cin >> n;
                graph = createGraph(n);
                currentSize = n;
                cout << "Новый граф:" << endl;
                graph.printGraph();
                break;
            }
            case 6: {
                running = false;
                break;
            }
            default:
                cout << "Неверный выбор!" << endl;
        }
        if (choice >= 1 && choice <= 3) {
            graph = resultGraph;
            currentSize = newSize;
            cout << "Результат операции:" << endl;
            graph.printGraph();
        }
    }
    cout << "Программа завершена." << endl;
    return 0;
}