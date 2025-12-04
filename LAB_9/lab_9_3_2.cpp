#include <iostream>
#include <ctime>
#include <random>

using namespace std;

struct ListNode {
    int vertex;      
    ListNode* next;  
    
    ListNode(int v) : vertex(v), next(nullptr) {}
};

struct AdjacencyList {
    ListNode* head; 
    int size;        
    
    AdjacencyList() : head(nullptr), size(0) {}
    
    void add(int v) {
        ListNode* newNode = new ListNode(v);
        newNode->next = head;
        head = newNode;
        size++;
    }
    
    bool contains(int v) {
        ListNode* current = head;
        while (current != nullptr) {
            if (current->vertex == v) {
                return true;
            }
            current = current->next;
        }
        return false;
    }
    
    ~AdjacencyList() {
        ListNode* current = head;
        while (current != nullptr) {
            ListNode* next = current->next;
            delete current;
            current = next;
        }
        head = nullptr;
        size = 0;
    }
};

void printAdjacencyLists(AdjacencyList* graph, int n) {
    cout << "Списки смежности графа:" << endl;
    for (int i = 0; i < n; i++) {
        cout << "Вершина " << i << ": ";
        ListNode* current = graph[i].head;
        while (current != nullptr) {
            cout << current->vertex << " ";
            current = current->next;
        }
        cout << endl;
    }
    cout << endl;
}

AdjacencyList* createGraph(int n) {
    AdjacencyList* graph = new AdjacencyList[n];
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if (rand() % 2 == 1) { 
                graph[i].add(j);
                graph[j].add(i);
            }
        }
    }
    
    return graph;
}

// Удаление графа
void deleteGraph(AdjacencyList* graph, int n, int* distance, int* visited) {
    delete[] graph;
    delete[] distance;
    if (visited != nullptr) {
        delete[] visited;
    }
}

void DFSDRecursive(AdjacencyList* graph, int numG, int* visited, int* distance, 
    int current, int currentDistance) {
    visited[current] = 1;        
    distance[current] = currentDistance; 
    cout << current << " ";          
    
    ListNode* neighbor = graph[current].head;
    while (neighbor != nullptr) {
        int neighborVertex = neighbor->vertex;
        if (visited[neighborVertex] == 0) {
            DFSDRecursive(graph, numG, visited, distance, 
                         neighborVertex, currentDistance + 1);
        }
        neighbor = neighbor->next;
    }
}

void DFSDistance(AdjacencyList* graph, int numG, int startVertex) {
    int* visited = new int[numG];
    int* distance = new int[numG];
    
    for (int i = 0; i < numG; i++) {
        visited[i] = 0;      
        distance[i] = -1;    
    }
    
    DFSDRecursive(graph, numG, visited, distance, startVertex, 0);
    cout << endl;
    
    cout << "Расстояния от вершины " << startVertex << " до:" << endl;
    for (int i = 0; i < numG; i++) {
        if (distance[i] != -1) {
            cout << "Вершина " << i << ": " << distance[i] << endl;
        } else {
            cout << "Вершина " << i << ": недостижима" << endl;
        }
    }
    
    delete[] visited;
    delete[] distance;
}

int main() {
    srand(time(0));
    int numG = 0;
    int startVertex = 0;
    
    cout << "Введите количество вершин в графе: ";
    cin >> numG;
    
    if (numG <= 0) {
        cout << "Ошибка: количество вершин должно быть положительным!" << endl;
        return 1;
    }

    AdjacencyList* graph = createGraph(numG);
    
    printAdjacencyLists(graph, numG);

    cout << "Введите начальную вершину обхода: ";
    cin >> startVertex;
    
    if (startVertex < 0 || startVertex >= numG) {
        cout << "Ошибка: неверный номер вершины!" << endl;
        deleteGraph(graph, numG, nullptr, nullptr);
        return 1;
    }
    
    DFSDistance(graph, numG, startVertex);
    deleteGraph(graph, numG, nullptr, nullptr);
    
    return 0;
}