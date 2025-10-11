#include <fstream>
#include <iostream>
#include <ctime>

using namespace std;

int main(){
    srand(time(0));
    int N, Size = 0;
    int** G = new int*[N];
    for (int i = 0; i < N; i++) {
        G[i] = new int[N];
    }
    int* loop = new int[N];
    int* deg = new int[N];

    cout<<"Введите кол-во вершин в матрице: ";
    cin>>N;
    for(int i = 0; i < N; i++){
        for(int j = i; j < N; j++){
            G[j][i] = G[i][j] = rand() % 2;
            Size += G[i][j];
        }
    }

    cout<<"=====РЕЗУЛЬТАТ====="<<endl;
    for(int i = 0; i < N; i++){
        cout<<i<<") ";
        for(int j = 0; j < N; j++){
            cout<<G[i][j]<<"   ";
        }
        cout<<endl;
    }

    for(int i = 0; i < N; i++){
        for(int j = 0; j < N; j++){
            if(i == j){
                loop[i] = G[i][j];

            }else{
                deg[i] += G[i][j];
            }
            deg[i] += loop[i] * 2;
        }
    }

    for(int i = 0; i < N; i++){
        if(loop[i] == 0 && deg[i] == 0 || loop[i] == 1 && deg[i] == 2){
            cout<<"Изолированная вершина: "<<i<<endl;
        }
        if(deg[i] == 1){
            cout<<"Концевая вершина: "<<i<<endl;
        }
        if((deg[i] - 2*loop[i]) == (N - 1)){
            cout<<"Доминирующая вершина:  "<<i<<endl;
        }
    }
    cout<<"Размер графа: "<<Size<<endl;

    for (int i = 0; i < N; i++) {
        delete[] G[i];
    }
    delete[] loop;
    delete[] deg;
}