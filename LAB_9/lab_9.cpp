#include <iostream>
#include <ctime>
#include <random>
#include <queue>

using namespace std;

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
void deleteM(int** m, int n, int* v) {
    for (int i = 0; i < n; ++i) {
        delete[] m[i];
    }
    delete[] m;
    delete[] v;
}

void BFSD(int** G, int numG, int* distance, int s) {
    queue<int> q;
    int v = 0;
    distance[s] = 0;
    q.push(s);

    while (!q.empty())
    {
        v = q.front();
        q.pop();
        cout<<v;

        for(int i = 0; i < numG; i++){
            if(G[v][i] == 1 && distance[i] == -1){
                q.push(i);
                distance[i] = distance[v] + 1;
            }
        }
    }
    cout<<endl;
    cout<<"Distance from "<<s<<" to: "<<endl;

    for(int i = 0; i < numG; i++){
        cout<<i<<" : "<<distance[i]<<endl;
    }
}

int main() {
    srand(time(0));
    int numG = 0;
    int n = 0;
    
    cout << "Введите количество вершин в графе: ";
    cin >> numG;
    if (numG <= 0) {
        cout << "Ошибка: количество вершин должно быть положительным!" << endl;
        return 1;
    }
    int* distance = new int[numG];
    for(int i = 0; i < numG; i++){
        distance[i] = -1;
    }

    int** G = createMatrix(numG);

    cout << "Матрица смежности графа:" << endl;
    printMatrix(G, numG);

    cout << "Введите начальную вершину обхода: ";
    cin >> n;
    BFSD(G, numG, distance, n);
    cout << endl;
    deleteM(G, numG, distance);
    
    return 0;
}