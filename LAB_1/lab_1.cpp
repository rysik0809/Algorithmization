#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <functional>
#include <forward_list>
using namespace std;

struct Student{
    string first_name;
    string last_name;
    int age;
    string group_number;
};

void searchStudents(const vector<Student>& students, function<bool(const Student&)> predicate) {
    cout << "Результат поиска:" << endl;
    cout << "__________________________________________________" << endl << endl;
    
    int found_count = 0;
    for(const auto& s : students) {
        if(predicate(s)) {
            cout << s.first_name << "     \t   " 
                 << s.last_name << "\t"
                 << s.age << "\t" 
                 << s.group_number << endl;
            found_count++;
        }
    }
    
    if(found_count == 0) {
        cout << "Студент не найден :(" << endl;
    }
    cout << "__________________________________________________" << endl;
}

int main(){
    //адание 1
    int arr_1[10] = {0};
    int max = -1000000;
    int min = 1000000;

    cout<<"Задание 1"<<endl;
    cout<<"Заполните массив числами:"<<endl;
    for(int i = 0; i < 10; i++){
        cout<<"элемент "<<i+1<<": ";
        cin>>arr_1[i];
    }
    for(int i = 0; i < 10; i++){
        if(max < arr_1[i]){
            max = arr_1[i];
        }
    }
    for(int i = 0; i < 10; i++){
        if(min > arr_1[i]){
            min = arr_1[i];
        }
    }

    cout<<"максимальный элемент: "<<max<<endl;
    cout<<"Минимальный элемент: "<<min<<endl;
    cout<<"Разница между максимальным и минимальным элементом: "<<max-min<<endl;

    //Задание 2
    cout<<endl<<"Задание 2"<<endl;
    int arr_2[10];
    cout<<"Генерируется массив из 10 элементов с рандомными числами"<<endl;
    for(int i = 0; i < 10; i++){
        arr_2[i] = rand() % 100;
    }
    cout<<"Результат:"<<endl;
    for(int i = 0; i < 10; i++){
        cout<<"Элемент "<<i + 1<<": "<<arr_2[i]<<endl;
    }

    //Задание 3
    cout<<endl<<"Задание 3"<<endl;
    cout<<"Введите размер массива: ";

    int size = 0;
    cin>>size;
    int *arr_3 = new int[size];

    for(int i = 0; i < size; i++){
        arr_3[i] = rand() % 100;
    }
    cout<<"Результат: "<<endl;
    for(int i = 0; i < size; i++){
        cout<<arr_3[i]<<"; ";
    }
    delete [] arr_3;

    //Задание 4
    cout<<endl<<"Задание 4"<<endl;
    int const cols = 5;
    int const rows = 5;
    int arr_4[rows][cols];
    int sum[rows] = {0};

    for(int i = 0; i < rows; i++){
        for(int j = 0; j < cols; j++){
            arr_4[i][j] = rand() % 10;
        }
    }
    for(int i = 0; i < rows; i++){
        for(int j = 0; j < cols; j++){
            cout<<arr_4[i][j]<<"\t";
            sum[j] += arr_4[i][j];
        }
        cout<<endl;
    }
    cout<<"Суммы каждого из столбцов:"<<endl;
    for(int i = 0; i < rows; i++){
        cout<<sum[i]<<"\t";
    }
    
    //Задание 5
    cout<<endl<<"Задание 5"<<endl;
    vector<Student> students = {
        {"Иван", "Иванов", 20, "24ВВВ2"},
        {"Петр", "Петров", 21, "23ВВВ1"},
        {"Мария", "Сидорова", 19, "25ВВВ3"},
        {"Анна", "Смирнова", 20, "24ВВВ4"},
        {"Сергей", "Кузнецов", 22, "22ВВВ4"},
        {"Ольга", "Васильева", 19, "24ВВВ2"},
        {"Алексей", "Попов", 20, "23ВВВ1"},
        {"Екатерина", "Морозова", 21, "23ВВВ3"},
        {"Дмитрий", "Новиков", 20, "24ВВВ1"},
        {"Наталья", "Федорова", 19, "25ВВВ1"}
    };
    cout<<"Список всех студентов:"<<endl;
    cout<<"__________________________________________________"<<endl<<endl;
    for(const auto& i : students){
        cout<<i.first_name<<"     \t   "<<i.last_name<<"\t"
        <<i.age<<"\t"<<i.group_number<<endl;
    }
    cout<<"__________________________________________________"<<endl;
    cout<<"1) Имя  2) Фамилия  3) Возраст  4) Группа"<<endl;
    cout<<"Выберите способ поиска студента: ";
    string choice;
    cin>>choice;
    if(choice == "1" || choice == "Имя" || choice == "имя") {
        string name;
        cout << "Введите имя студента: ";
        cin >> name;
        searchStudents(students, [&name](const Student& s) { return s.first_name == name; });
    }
    else if(choice == "2" || choice == "Фамилия" || choice == "фамилия") {
        string surname;
        cout << "Введите фамилию студента: ";
        cin >> surname;
        searchStudents(students, [&surname](const Student& s) { return s.last_name == surname; });
    }
    else if(choice == "3" || choice == "Возраст" || choice == "возраст") {
        int age;
        cout << "Введите возраст студента: ";
        cin >> age;
        searchStudents(students, [&age](const Student& s) { return s.age == age; });
    }
    else if(choice == "4" || choice == "Группа" || choice == "группа") {
        string group;
        cout << "Введите группу студента: ";
        cin >> group;
        searchStudents(students, [&group](const Student& s) { return s.group_number == group; });
    }
    else {
        cout << "Неверный выбор!" << endl;
    }
}