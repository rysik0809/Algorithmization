#include <iostream>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <chrono>
#include <fstream> 

using namespace std;

double sort_arr(int* items, int n){
    auto start = chrono::high_resolution_clock::now();
    sort(items, items + n);
    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double> duration = end - start;
    double seconds = duration.count();
    return seconds;
}

double shell(int* items, int count) {
    int i, j, gap, k;
    int x, arr[5] = {9, 5, 3, 2, 1};
    auto start = chrono::high_resolution_clock::now();
    for (k = 0; k < 5; k++) {
        gap = arr[k];
        for (i = gap; i < count; i++) {
            x = items[i];
            for (j = i - gap; j >= 0 && x < items[j]; j = j - gap) {
                items[j + gap] = items[j];
            }
            items[j + gap] = x;
        }
    }
    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double> duration = end - start;
    double seconds = duration.count();
    return seconds;
}

void quick_sort_helper(int* items, int left, int right) {
    int i, j;
    int x, y;

    i = left; j = right;
    x = items[(left+right)/2];
    
    do {
        while ((items[i] < x) && (i < right)) {
            i++;
        }
        while ((x < items[j]) && (j > left)) {
            j--;
        }
        if(i <= j) {
            y = items[i];
            items[i] = items[j];
            items[j] = y;
            i++; j--;
        }
    } while (i <= j);
    
    if(left < j) quick_sort_helper(items, left, j);
    if(i < right) quick_sort_helper(items, i, right);
}

double qs(int* items, int left, int right) {
    auto start = chrono::high_resolution_clock::now();
    quick_sort_helper(items, left, right);
    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double> duration = end - start;
    double seconds = duration.count();
    return seconds;
}

void create_arr(int* items, int n, int sp){
    switch (sp){
    case 0:
        for(int i = 0; i < n; i++){
            items[i] = i;
        }
        break;
    case 1:
        for(int i = 0; i < n; i++){
            items[i] = n - i;
        }
        break;
    case 2:
        for(int i = 0; i < n; i++){
            if(i <= (n / 2)){
                items[i] = i;
            }
            else{
                items[i] = n - i;
            }
        }
        break;
    default:
        for(int i = 0; i < n; i++){
            items[i] = rand() % 101;
        }
        break;
    }
}

void delete_arr(int* items, int n){
    for(int i = 0; i < n; i++){
        items[i] = 0;
    }
}

string get_array_type_name(int type) {
    switch(type) {
        case 0: return "По возрастанию  ";
        case 1: return "По убыванию     ";
        case 2: return "Смешанный       ";
        default: return "Случайный       ";
    }
}

int main() {
    srand(time(0));
    int n = 100000;
    int* main_arr = new int[n];
    
    ofstream outfile("sorting_results.txt");
    
    if (!outfile.is_open()) {
        cerr << "Ошибка открытия файла для записи!" << endl;
        return 1;
    }
    
    cout << "=== СРАВНЕНИЕ АЛГОРИТМОВ СОРТИРОВКИ ===" << endl;
    cout << "\tРазмер массива: " << n << " элементов" << endl;
    cout << "=======================================" << endl << endl;
    
    outfile << "=== СРАВНЕНИЕ АЛГОРИТМОВ СОРТИРОВКИ ===" << endl;
    outfile << "\tРазмер массива: " << n << " элементов" << endl;
    outfile << "=======================================" << endl << endl;

    cout << "1. СОРТИРОВКА ШЕЛЛА (SHELL SORT):" << endl;
    cout << "---------------------------------" << endl;
    outfile << "1. СОРТИРОВКА ШЕЛЛА (SHELL SORT):" << endl;
    outfile << "---------------------------------" << endl;
    
    for(int i = 0; i < 4; i++){
        create_arr(main_arr, n, i);
        double seconds = shell(main_arr, n);
        delete_arr(main_arr, n);
        string result = "   " + get_array_type_name(i) + to_string(seconds) + " секунд";
        cout << result << endl;
        outfile << result << endl;
    }
    cout << endl;
    outfile << endl;
    
    cout << "2. БЫСТРАЯ СОРТИРОВКА (QUICK SORT):" << endl;
    cout << "-----------------------------------" << endl;
    outfile << "2. БЫСТРАЯ СОРТИРОВКА (QUICK SORT):" << endl;
    outfile << "-----------------------------------" << endl;
    
    for(int i = 0; i < 4; i++){
        create_arr(main_arr, n, i);
        double seconds = qs(main_arr, 0, n-1);
        delete_arr(main_arr, n);
        string result = "   " + get_array_type_name(i) + to_string(seconds) + " секунд";
        cout << result << endl;
        outfile << result << endl;
    }
    cout << endl;
    outfile << endl;
    
    cout << "3. СТАНДАРТНАЯ СОРТИРОВКА (STD::SORT):" << endl;
    cout << "--------------------------------------" << endl;
    outfile << "3. СТАНДАРТНАЯ СОРТИРОВКА (STD::SORT):" << endl;
    outfile << "--------------------------------------" << endl;
    
    for(int i = 0; i < 4; i++){
        create_arr(main_arr, n, i);
        double seconds = sort_arr(main_arr, n);
        delete_arr(main_arr, n);
        string result = "   " + get_array_type_name(i) + to_string(seconds) + " секунд";
        cout << result << endl;
        outfile << result << endl;
    }
    cout << endl;
    outfile << endl;
    
    cout << "=======================================" << endl;
    cout << "ТЕСТИРОВАНИЕ ЗАВЕРШЕНО" << endl;
    cout << "Результаты сохранены в файл: sorting_results.txt" << endl;
    
    outfile << "=======================================" << endl;
    outfile << "ТЕСТИРОВАНИЕ ЗАВЕРШЕНО" << endl;

    
    
    outfile.close();
    
    delete[] main_arr;
    return 0;
}