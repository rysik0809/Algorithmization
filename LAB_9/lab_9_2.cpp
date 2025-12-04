#include <iostream>
#include <ctime>
#include <random>
#include <queue>

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

void deleteGraph(AdjacencyList* graph, int n, int* distance) {
    delete[] graph;
    delete[] distance;
}

void BFSD(AdjacencyList* graph, int numG, int* distance, int s) {
    queue<int> q;
    int v = 0;
    distance[s] = 0;
    q.push(s);

    while (!q.empty()) {
        v = q.front();
        q.pop();
        cout << v << " ";

        ListNode* current = graph[v].head;
        while (current != nullptr) {
            int neighbor = current->vertex;
            if (distance[neighbor] == -1) {
                q.push(neighbor);
                distance[neighbor] = distance[v] + 1;
            }
            current = current->next;
        }
    }
    
    cout << endl << "Расстояния от вершины " << s << " до:" << endl;
    for (int i = 0; i < numG; i++) {
        cout << "Вершина " << i << ": " << distance[i] << endl;
    }
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
    
    int* distance = new int[numG];
    for (int i = 0; i < numG; i++) {
        distance[i] = -1;
    }

    AdjacencyList* graph = createGraph(numG);

    printAdjacencyLists(graph, numG);

    cout << "Введите начальную вершину обхода: ";
    cin >> startVertex;
    
    if (startVertex < 0 || startVertex >= numG) {
        cout << "Ошибка: неверный номер вершины!" << endl;
        deleteGraph(graph, numG, distance);
        return 1;
    }
    
    BFSD(graph, numG, distance, startVertex);
    cout << endl;
    
    deleteGraph(graph, numG, distance);
    
    return 0;
}