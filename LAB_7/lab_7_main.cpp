#include <iostream>
#include <ctime>
#include <random>
#include <stack>

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


//список смежности
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
void DFS(Graph& graph, int* visited, int s){
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
void runDFS(Graph& graph, int startVertex) {
    int numVertices = graph.getNumVertices();
    
    if (startVertex < 0 || startVertex >= numVertices) {
        cout << "Ошибка: начальная вершина " << startVertex << " не существует!" << endl;
        return;
    }
    
    int* visited = new int[numVertices]();
    
    DFS(graph, visited, startVertex);
    cout << endl;
    
    delete[] visited;
}


//матрица смежности
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
void DFS_matrix(int** G, int numG, int* visited, int s){
    visited[s] = 1;
    cout<<s<<" ";
    for(int i = 0; i < numG; i++){
        if(G[s][i] == 1 && visited[i] == 0){
            DFS_matrix(G, numG, visited, i);
        }
    }
}

//перевод матрицы смежности в список смежности
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

//решение без рекурсии
void DFS_stack(int** G, int numG, int* visited, int start){
    stack<int> st;
    st.push(start);
    visited[start] = 1;
    cout << start << " ";
    
    while (!st.empty()) {
        int current = st.top();
        bool found = false;
        
        for (int i = 0; i < numG; i++) {
            if (G[current][i] == 1 && visited[i] == 0) {
                visited[i] = 1;
                cout << i << " ";;
                st.push(i);
                found = true;
                break;
            }
        }
        
        if (!found) {
            st.pop();
        }
    }
}

int main(){
    int n = 0;
    int startVertex = 0;
    cout << "Введите количество вершин в графе: ";
    cin >> n;
    if (n <= 0) {
        cout << "Ошибка: количество вершин должно быть положительным!" << endl;
        return 1;
    }

    int* visited = new int[n];
    int* visited_stack = new int[n];
    for(int i = 0; i < n; i++){
        visited[i] = 0;
    }
    for(int i = 0; i < n; i++){
        visited_stack[i] = 0;
    }
    cout<<"Матрица смежности:"<<endl;
    int** M = createMatrix(n);
    printMatrix(M, n);

    Graph g = matrixToList(M, n);
    cout << "\nСтруктура графа:" << endl;
    g.printGraph();

    cout << "Введите начальную вершину (0-" << n-1 << "): ";
    cin >> startVertex;

    cout<<"Результат для матрицы смежности:"<<endl;
    DFS_matrix(M, n, visited, startVertex);
    cout << endl;
    cout<<"Результат для матрицы смежности без рекурсии:"<<endl;
    DFS_stack(M, n, visited_stack, startVertex);
    cout << endl;
    cout<<"Результат для списков смежности:"<<endl;
    runDFS(g, startVertex);
    deleteM(M, n, visited, visited_stack);
    return 0;
}