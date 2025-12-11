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

void printAdjacencyList(ListNode** adjList, int n) {
    cout << "Список смежности графа:" << endl;
    for (int i = 0; i < n; i++) {
        cout << i << ": ";
        ListNode* current = adjList[i];
        while (current != nullptr) {
            cout << current->vertex << " ";
            current = current->next;
        }
        cout << endl;
    }
    cout << endl;
}

ListNode** createAdjacencyList(int n) {
    ListNode** adjList = new ListNode*[n];
    for (int i = 0; i < n; i++) {
        adjList[i] = nullptr;
    }
    
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if (rand() % 2 == 1) {
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

void deleteAdjacencyList(ListNode** adjList, int n, int* visited) {
    for (int i = 0; i < n; i++) {
        ListNode* current = adjList[i];
        while (current != nullptr) {
            ListNode* temp = current;
            current = current->next;
            delete temp;
        }
    }
    delete[] adjList;
    delete[] visited;
}

bool isIsolatedVertex(ListNode** adjList, int vertex) {
    // Вершина изолирована, если у неё нет соседей (список пустой)
    return adjList[vertex] == nullptr;
}

void BFS(ListNode** adjList, int numG, int* visited, int start) {
    queue<int> q;
    visited[start] = 1;
    q.push(start);
    
    cout << "Порядок обхода графа в ширину: ";
    
    while (!q.empty()) {
        int current = q.front();
        q.pop();
        cout << current << " ";
        
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
    cout << endl;
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
    
    int* visited = new int[numG];
    for (int i = 0; i < numG; i++) {
        visited[i] = 0;
    }
    
    ListNode** adjList = createAdjacencyList(numG);
    
    printAdjacencyList(adjList, numG);
    
    cout << "Введите начальную вершину обхода: ";
    cin >> startVertex;
    
    if (startVertex < 0 || startVertex >= numG) {
        cout << "Ошибка: начальная вершина должна быть в диапазоне [0, " << numG - 1 << "]!" << endl;
        deleteAdjacencyList(adjList, numG, visited);
        return 1;
    }
    
    // Проверка на изолированную вершину
    if (isIsolatedVertex(adjList, startVertex)) {
        cout << "ВНИМАНИЕ: Выбранная вершина " << startVertex << " является изолированной!" << endl;
        cout << "Обход начнется только с этой вершины и завершится сразу." << endl;
        cout << "Продолжить? (y/n): ";
        char choice;
        cin >> choice;
        if (choice == 'n' || choice == 'N') {
            cout << "Обход отменен." << endl;
            deleteAdjacencyList(adjList, numG, visited);
            return 0;
        }
    }
    
    BFS(adjList, numG, visited, startVertex);
    
    deleteAdjacencyList(adjList, numG, visited);
    
    return 0;
}