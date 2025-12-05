#include <iostream>
#include <ctime>
#include <random>
#include <queue>
#include <chrono>
#include <iomanip>
#include <vector>

using namespace std;
using namespace chrono;

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

void deleteGraph(AdjacencyList* graph, int n) {
    delete[] graph;
}

void DFSDRecursive(AdjacencyList* graph, int numG, int* visited, int* distance, int current, int currentDistance) {
    visited[current] = 1;        
    distance[current] = currentDistance; 
    
    ListNode* neighbor = graph[current].head;
    while (neighbor != nullptr) {
        int neighborVertex = neighbor->vertex;
        if (visited[neighborVertex] == 0) {
            DFSDRecursive(graph, numG, visited, distance, neighborVertex, currentDistance + 1);
        }
        neighbor = neighbor->next;
    }
}

void DFSDistance(AdjacencyList* graph, int numG, int startVertex, int* distance) {
    int* visited = new int[numG];
    
    for (int i = 0; i < numG; i++) {
        visited[i] = 0;      
        distance[i] = -1;    
    }
    
    DFSDRecursive(graph, numG, visited, distance, startVertex, 0);
    
    delete[] visited;
}

void BFSD(AdjacencyList* graph, int numG, int startVertex, int* distance) {
    queue<int> q;
    
    for (int i = 0; i < numG; i++) {
        distance[i] = -1;
    }
    
    distance[startVertex] = 0;
    q.push(startVertex);

    while (!q.empty()) {
        int v = q.front();
        q.pop();

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
}

struct TestResult {
    int vertices;
    string algorithm;
    long long timeMicroseconds;
    double timeMilliseconds;
};

TestResult runTest(AdjacencyList* graph, int numVertices, int startVertex, 
                  const string& algorithm, int* distDFS, int* distBFS) {
    TestResult result;
    result.vertices = numVertices;
    result.algorithm = algorithm;
    
    auto start = high_resolution_clock::now();
    
    if (algorithm == "DFS") {
        DFSDistance(graph, numVertices, startVertex, distDFS);
    } else {
        BFSD(graph, numVertices, startVertex, distBFS);
    }
    
    auto end = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(end - start);
    
    result.timeMicroseconds = duration.count();
    result.timeMilliseconds = duration.count() / 1000.0;
    
    return result;
}

void printTable(const vector<TestResult>& results) {
    cout << "==================================================================" << endl;
    cout << "СРАВНЕНИЕ ВРЕМЕНИ ВЫПОЛНЕНИЯ DFS И BFS" << endl;
    cout << "==================================================================" << endl;
    cout << left << setw(12) << " Вершин " 
         << left << setw(12) << " Алгоритм " 
         << left << setw(20) << " Время (микросек) " 
         << left << setw(20) << " Время (миллисек) " << endl;
    cout << "------------------------------------------------------------------" << endl;
    
    for (const auto& result : results) {
        cout << left << setw(12) << result.vertices
             << left << setw(12) << result.algorithm
             << left << setw(20) << result.timeMicroseconds
             << fixed << setprecision(3) << left << setw(20) << result.timeMilliseconds << endl;
    }
    cout << "==================================================================" << endl;
}

void printComparison(const vector<TestResult>& results) {
    cout << "\n==================================================================" << endl;
    cout << "СРАВНЕНИЕ ПРОИЗВОДИТЕЛЬНОСТИ" << endl;
    cout << "==================================================================" << endl;
    cout << left << setw(12) << " Вершин " 
         << left << setw(15) << " Быстрее " 
         << left << setw(20) << " Разница (микросек) " 
         << left << setw(15) << " Выигрыш (%) " << endl;
    cout << "------------------------------------------------------------------" << endl;
    
    for (int i = 0; i < results.size(); i += 2) {
        if (i + 1 < results.size()) {
            const TestResult& dfs = results[i];
            const TestResult& bfs = results[i + 1];
            
            string faster;
            long long diff;
            double percentage;
            
            if (dfs.timeMicroseconds < bfs.timeMicroseconds) {
                faster = "DFS";
                diff = bfs.timeMicroseconds - dfs.timeMicroseconds;
                percentage = (double)diff / bfs.timeMicroseconds * 100;
            } else {
                faster = "BFS";
                diff = dfs.timeMicroseconds - bfs.timeMicroseconds;
                percentage = (double)diff / dfs.timeMicroseconds * 100;
            }
            
            cout << left << setw(12) << dfs.vertices
                 << left << setw(15) << faster
                 << left << setw(20) << diff
                 << fixed << setprecision(2) << left << setw(15) << percentage << "%" << endl;
        }
    }
    cout << "==================================================================" << endl;
}

int main() {
    srand(time(0));
    
    vector<int> graphSizes = {100, 400, 800, 2000, 5000, 10000};
    const int startVertex = 0;
    
    vector<TestResult> allResults;
    
    cout << "Запуск тестов производительности..." << endl;
    cout << "Размеры графов: ";
    for (int size : graphSizes) {
        cout << size << " ";
    }
    cout << "\n\n";
    
    for (int numVertices : graphSizes) {
        cout << "Тестирование графа с " << numVertices << " вершинами..." << endl;
        
        AdjacencyList* graph = createGraph(numVertices);
        
        int* distDFS = new int[numVertices];
        int* distBFS = new int[numVertices];
        
        TestResult dfsResult = runTest(graph, numVertices, startVertex, "DFS", distDFS, distBFS);
        allResults.push_back(dfsResult);
        
        TestResult bfsResult = runTest(graph, numVertices, startVertex, "BFS", distDFS, distBFS);
        allResults.push_back(bfsResult);
        
        bool resultsMatch = true;
        for (int i = 0; i < numVertices; i++) {
            if (distDFS[i] != distBFS[i]) {
                resultsMatch = false;
                break;
            }
        }
        
        if (!resultsMatch) {
            cout << "  ВНИМАНИЕ: результаты DFS и BFS не совпадают!" << endl;
        } else {
            cout << "  ✓ Результаты DFS и BFS совпадают" << endl;
        }
        
        int totalEdges = 0;
        for (int i = 0; i < numVertices; i++) {
            ListNode* current = graph[i].head;
            while (current != nullptr) {
                totalEdges++;
                current = current->next;
            }
        }
        totalEdges /= 2;
        
        cout << "  Ребра: " << totalEdges 
             << ", Плотность: " << fixed << setprecision(2) 
             << (2.0 * totalEdges) / (numVertices * (numVertices - 1)) * 100 << "%" << endl;
        
        delete[] distDFS;
        delete[] distBFS;
        deleteGraph(graph, numVertices);
        
        cout << endl;
    }
    
    printTable(allResults);
    
    printComparison(allResults);
    
    cout << "\n==================================================================" << endl;
    cout << "СТАТИСТИЧЕСКИЙ АНАЛИЗ" << endl;
    cout << "==================================================================" << endl;
    
    double totalDFSTime = 0;
    double totalBFSTime = 0;
    int dfsWins = 0;
    int bfsWins = 0;
    
    for (int i = 0; i < allResults.size(); i += 2) {
        if (i + 1 < allResults.size()) {
            const TestResult& dfs = allResults[i];
            const TestResult& bfs = allResults[i + 1];
            
            totalDFSTime += dfs.timeMilliseconds;
            totalBFSTime += bfs.timeMilliseconds;
            
            if (dfs.timeMicroseconds < bfs.timeMicroseconds) {
                dfsWins++;
            } else {
                bfsWins++;
            }
        }
    }
    
    cout << "Среднее время DFS: " << fixed << setprecision(3) 
         << totalDFSTime / (allResults.size() / 2) << " мс" << endl;
    cout << "Среднее время BFS: " << totalBFSTime / (allResults.size() / 2) << " мс" << endl;
    cout << "DFS был быстрее в " << dfsWins << " из " << (allResults.size() / 2) << " тестов" << endl;
    cout << "BFS был быстрее в " << bfsWins << " из " << (allResults.size() / 2) << " тестов" << endl;
    
    return 0;
}