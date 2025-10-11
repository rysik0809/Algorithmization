#include <iostream>
#include <cstdlib>
#include <ctime>
#include <stdexcept>
#include <chrono>
#include <fstream>
using namespace std;

int** create_matrix(int n) {
    int** arr = new int*[n];
    for (int i = 0; i < n; i++) {
        arr[i] = new int[n];
    }
    return arr;
}

void fill_matrix(int n, int** matrix, int range_type) {
    int min_val, max_val;
    
    switch(range_type) {
        case 1: // 0-10
            min_val = 0;
            max_val = 10;
            break;
        case 2: // 10-100
            min_val = 10;
            max_val = 100;
            break;
        case 3: // 100-1000
            min_val = 100;
            max_val = 1000;
            break;
        default:
            min_val = 0;
            max_val = 100;
    }
    
    int range = max_val - min_val + 1;
    
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            matrix[i][j] = rand() % range + min_val;
        }
    }
}

void delete_matrix(int** matrix, int n) {
    if (matrix == nullptr) return;
    
    for (int i = 0; i < n; i++) {
        delete[] matrix[i];
    }
    delete[] matrix;
}

double mult_matrix(int n, int range_type){
    int** a = create_matrix(n);
    int** b = create_matrix(n);
    int** c = create_matrix(n);
    fill_matrix(n, a, range_type);
    fill_matrix(n, b, range_type);
    auto start = chrono::high_resolution_clock::now();
    for(int i = 0; i < n; i++){
        for (int j = 0; j < n; j++){
            c[i][j] = 0;
            for (int k = 0; k < n; k++){
                c[i][j] += a[i][k] * b[k][j];
            }
        }
    }
    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double> duration = end - start;
    double seconds = duration.count();

    delete_matrix(a, n);
    delete_matrix(b, n);
    delete_matrix(c, n);
    return seconds;
}

int main() {
    srand(time(0));
    
    int sizes[] = {100, 200, 400, 1000, 2000, 4000, 10000};
    int num_sizes = sizeof(sizes) / sizeof(sizes[0]);
    const char* range_names[] = {"0-10", "10-100", "100-1000"};
    
    ofstream outfile("results.txt");
    
    cout << "Выполняются вычисления..." << endl;
    outfile << "Результаты умножения матриц для разных диапазонов значений:\n\n";
    
    for (int r = 0; r < 3; r++) {
        outfile << "Диапазон значений: " << range_names[r] << "\n";
        outfile << "Размер матрицы\tВремя (секунды)\n";
        outfile << "================================\n";
        
        cout << "\nДиапазон значений: " << range_names[r] << endl;
        cout << "================================" << endl;
        
        for (int i = 0; i < num_sizes; i++){
            double time = mult_matrix(sizes[i], r+1);
            outfile << sizes[i] << "x" << sizes[i] << ":\t    " << time << "\n";
            cout << "Матрица " << sizes[i] << "x" << sizes[i] 
                 << ":\t" << time << " сек" << endl;
        }
        outfile << "\n";
        cout << "\n";
    }
    
    outfile.close();
    cout << "\nРезультаты сохранены в файл 'results.txt'" << endl;
    
    return 0;
}