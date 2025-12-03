#include <iostream>
#include <ctime>
#include <random>
#include <queue>
#include <chrono>
#include <iomanip>

using namespace std;
using namespace std::chrono;

struct ListNode {
    int vertex;
    ListNode* next;
    
    ListNode(int v) : vertex(v), next(nullptr) {}
};

class Queue {
private:
    struct QueueNode {
        int data;
        QueueNode* next;
        QueueNode(int value) : data(value), next(nullptr) {}
    };
    
    QueueNode* front;
    QueueNode* rear;
    
public:
    Queue() : front(nullptr), rear(nullptr) {}
    
    ~Queue() {
        while (!isEmpty()) {
            pop();
        }
    }
    bool isEmpty() const {
        return front == nullptr;
    }
    void push(int value) {
        QueueNode* newNode = new QueueNode(value);
        if (rear == nullptr) {
            front = rear = newNode;
        } else {
            rear->next = newNode;
            rear = newNode;
        }
    }
    int pop() {
        if (isEmpty()) {
            return -1;
        }
        
        QueueNode* temp = front;
        int value = temp->data;
        front = front->next;
        
        if (front == nullptr) {
            rear = nullptr;
        }
        
        delete temp;
        return value;
    }
};

ListNode** createAdjacencyList(int n) {
    ListNode** adjList = new ListNode*[n];
    for (int i = 0; i < n; i++) {
        adjList[i] = nullptr;
    }
    
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if (rand() % 100 < 1) {
                ListNode* newNode = new ListNode(j);
                newNode->next = adjList[i];
                adjList[i] = newNode;
                
                newNode = new ListNode(i);
                newNode->next = adjList[j];
                adjList[j] = newNode;
            }
        }
    }
    
    return adjList;
}

void deleteAdjacencyList(ListNode** adjList, int n) {
    for (int i = 0; i < n; i++) {
        ListNode* current = adjList[i];
        while (current != nullptr) {
            ListNode* temp = current;
            current = current->next;
            delete temp;
        }
    }
    delete[] adjList;
}

void BFS(ListNode** adjList, int numG, int* visited, int start) {
    Queue q;
    visited[start] = 1;
    q.push(start);
    
    while (!q.isEmpty()) {
        int current = q.pop();
        
        ListNode* neighbor = adjList[current];
        while (neighbor != nullptr) {
            int neighborVertex = neighbor->vertex;
            if (visited[neighborVertex] == 0) {
                visited[neighborVertex] = 1;
                q.push(neighborVertex);
            }
            neighbor = neighbor->next;
        }
    }
}

void BFS_std(ListNode** adjList, int numG, int* visited, int start) {
    queue<int> q;
    
    visited[start] = 1;
    q.push(start);
    
    while (!q.empty()) {
        int current = q.front();
        q.pop();
        
        ListNode* neighbor = adjList[current];
        while (neighbor != nullptr) {
            int neighborVertex = neighbor->vertex;
            if (visited[neighborVertex] == 0) {
                visited[neighborVertex] = 1;
                q.push(neighborVertex);
            }
            neighbor = neighbor->next;
        }
    }
}

int main() {
    srand(time(0));
    
    int graphSizes[] = {100, 500, 1000, 2000, 5000, 10000, 30000, 50000};
    int numTests = sizeof(graphSizes) / sizeof(graphSizes[0]);
    int startVertex = 0;
    
    // Заголовок таблицы
    cout << "Сравнение производительности BFS с queue и оптимизированным List:\n";
    cout << "Размер графа | queue (мкс) | List (мкс) | Отношение (List/queue)\n";
    cout << "-------------|--------------|-------------|----------------------\n";
    
    for (int testIdx = 0; testIdx < numTests; testIdx++) {
        int numG = graphSizes[testIdx];
        
        ListNode** adjList = createAdjacencyList(numG);
        
        int* visited = new int[numG];
        for (int i = 0; i < numG; i++) visited[i] = 0;
        
        // Измеряем время для стандартной очереди
        auto start = high_resolution_clock::now();
        BFS_std(adjList, numG, visited, startVertex);
        auto end = high_resolution_clock::now();
        auto duration_std = duration_cast<microseconds>(end - start);
        
        // Сбрасываем visited
        for (int i = 0; i < numG; i++) visited[i] = 0;
        
        // Измеряем время для самописной очереди
        start = high_resolution_clock::now();
        BFS(adjList, numG, visited, startVertex);
        end = high_resolution_clock::now();
        auto duration_custom = duration_cast<microseconds>(end - start);
        
        // Вычисляем отношение
        double ratio = (double)duration_custom.count() / duration_std.count();
        
        // Выводим строку таблицы
        cout << setw(12) << numG << " | "
             << setw(11) << duration_std.count() << " | "
             << setw(11) << duration_custom.count() << " | "
             << setw(10) << fixed << setprecision(6) << ratio << endl;
        
        delete[] visited;
        deleteAdjacencyList(adjList, numG);
    }
    
    return 0;
}