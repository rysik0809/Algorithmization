#include <iostream>
#include <ctime>
#include <random>
#include <queue>
#include <chrono>

using namespace std;
using namespace std::chrono;

template<typename T>
class List{
public:
    List();
    ~List();
    void pop_back();
    void clear();
    void pop_front();
    void push_back(T data);
    T front();
    bool empty();
    int GetSize() { return Size; }
private:
    template<typename U>
    class Node{
    public:
        Node* pNext;
        U data;
        Node(T data = T(), Node *pNext = nullptr){
            this->data = data;
            this->pNext = pNext;
        }
    };
    int Size;
    Node<T> *head;
};

template<typename T>
List<T>::List(){
    Size = 0;
    head = nullptr;
}

template<typename T>
List<T>::~List(){
    clear();
}

template <typename T>
void List<T>::pop_back(){
    if (head == nullptr) return;
    
    if (head->pNext == nullptr) {
        delete head;
        head = nullptr;
    } else {
        Node<T> *current = head;
        while (current->pNext->pNext != nullptr) {
            current = current->pNext;
        }
        delete current->pNext;
        current->pNext = nullptr;
    }
    Size--;
}

template <typename T>
void List<T>::pop_front(){
    if (head == nullptr) return;
    
    Node<T> *temp = head;
    head = head->pNext;
    delete temp;
    Size--;
}

template<typename T>
void List<T>::clear(){
    while(Size){
        pop_front();
    }
}

template <typename T>
void List<T>::push_back(T data){
    if(head == nullptr){
        head = new Node<T>(data);
    }
    else{
        Node<T>* current = this->head;
        while (current->pNext != nullptr)
        {
            current = current->pNext;
        }
        current->pNext = new Node<T>(data);
    }
    Size++;
}

template <typename T>
T List<T>::front(){
    if (head == nullptr) {
        throw runtime_error("List is empty");
    }
    return head->data;
}

template <typename T>
bool List<T>::empty(){
    return head == nullptr;
}

// Матрица смежности
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

void deleteM(int** m, int n) {
    for (int i = 0; i < n; ++i) {
        delete[] m[i];
    }
    delete[] m;
}

// BFS с использованием стандартной queue
void BFS_Q(int** G, int v, bool* NUM, int size_G) {
    queue<int> Q;
    Q.push(v);
    NUM[v] = true;
    
    while (!Q.empty()) {
        v = Q.front();
        Q.pop();
        
        for (int i = 0; i < size_G; i++) {
            if (G[v][i] == 1 && !NUM[i]) {
                Q.push(i);  
                NUM[i] = true;
            }
        }
    }
}

void POH_Q(int** G, int size_G) {
    bool* NUM = new bool[size_G];
    for (int i = 0; i < size_G; i++) {
        NUM[i] = false;
    }
    
    for (int v = 0; v < size_G; v++) {
        if (!NUM[v]) {
            BFS_Q(G, v, NUM, size_G);
        }
    }
    
    delete[] NUM;
}

// BFS с использованием самодельного List
void BFS_List(int** G, int v, bool* NUM, int size_G) {
    List<int> Q;
    Q.push_back(v);
    NUM[v] = true;
    
    while (!Q.empty()) {
        v = Q.front();
        Q.pop_front();
        
        for (int i = 0; i < size_G; i++) {
            if (G[v][i] == 1 && !NUM[i]) {
                Q.push_back(i);  
                NUM[i] = true;
            }
        }
    }
}

void POH_List(int** G, int size_G) {
    bool* NUM = new bool[size_G];
    for (int i = 0; i < size_G; i++) {
        NUM[i] = false;
    }
    
    for (int v = 0; v < size_G; v++) {
        if (!NUM[v]) {
            BFS_List(G, v, NUM, size_G);
        }
    }
    
    delete[] NUM;
}

// Функция для тестирования производительности
void performanceTest() {
    int sizes[] = {100, 500, 1000, 2000, 5000}; // Различные размеры графов
    
    cout << "Сравнение производительности BFS с queue и List:" << endl;
    cout << "Размер графа | queue (мкс) | List (мкс) | Отношение" << endl;
    cout << "---------------------------------------------------" << endl;
    
    for (int n : sizes) {
        // Создаем граф
        int** M = createMatrix(n);
        
        // Тестируем queue
        auto start = high_resolution_clock::now();
        POH_Q(M, n);
        auto end = high_resolution_clock::now();
        auto duration_q = duration_cast<microseconds>(end - start);
        
        // Тестируем List
        start = high_resolution_clock::now();
        POH_List(M, n);
        end = high_resolution_clock::now();
        auto duration_l = duration_cast<microseconds>(end - start);
        
        double ratio = static_cast<double>(duration_l.count()) / duration_q.count();
        
        cout << n << "          | " 
             << duration_q.count() << "        | " 
             << duration_l.count() << "       | " 
             << ratio << endl;
        
        deleteM(M, n);
    }
}

int main() {
    srand(time(0));
    
    // Запускаем тест производительности
    performanceTest();
    
    return 0;
}