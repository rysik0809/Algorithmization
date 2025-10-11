#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <functional>
#include <iomanip>
using namespace std;

struct Student{
    string first_name;
    string last_name;
    int age;
    string group_number;
    Student* next;
};

class  Link{
    private:
        Student* head;
        void printStudent(const Student& s) {
        cout<<s.first_name <<"     \t   "<< s.last_name<<"\t"<< s.age<<"\t"<<s.group_number<<endl;
        }
    public:
        Link() : head(nullptr) {};
        void addStudent(string new_first_name, string new_last_name, int new_age, string new_group_number){
            Student* newStudent = new Student;
            newStudent -> first_name = new_first_name;
            newStudent -> last_name = new_last_name;
            newStudent -> age = new_age;
            newStudent -> group_number = new_group_number;
            newStudent -> next = head;
            head = newStudent;
        }

        void deleteStudent() {
            if (head == nullptr) {
                cout << "Список студентов пуст!" << endl;
                return;
            }
            
            cout << "Список всех студентов:" << endl;
            display();
            
            string first_name, last_name;
            cout << "Введите имя студента для удаления: ";
            cin >> first_name;
            cout << "Введите фамилию студента для удаления: ";
            cin >> last_name;
            
            Student* current = head;
            Student* prev = nullptr;
            bool found = false;
            
            while (current != nullptr) {
                if (current->first_name == first_name && current->last_name == last_name) {
                    found = true;
                    break;
                }
                prev = current;
                current = current->next;
            }
            
            if (!found) {
                cout << "Студент с именем " << first_name << " и фамилией " << last_name << " не найден!" << endl;
                return;
            }
            
            if (prev == nullptr) {
                head = current->next;
            } else {
                prev->next = current->next;
            }
            
            delete current;
            cout << "Студент " << first_name << " " << last_name << " успешно удален!" << endl;
        }

        void display(){
            Student* current = head;
            while (current != nullptr){
                cout << current -> first_name<<"     \t   "<< current -> last_name <<"\t" << current -> age << "\t" << current -> group_number<<endl;
                current = current -> next;
            }
        }
        void searchStudents(function<bool(const Student&)> predicate) {
        
            int found_count = 0;
            Student* current = head;
            cout << "----------------------------------------" << endl;
            while (current != nullptr) {
                if (predicate(*current)) {
                    printStudent(*current);
                    found_count++;
                }
                current = current->next;
            }
            
            if (found_count == 0) {
                cout << "Студент не найден :(" << endl;
            }
            cout << "----------------------------------------" << endl;
        }
};

int main(){
    // //задание 1
    // int arr_1[10] = {0};
    // int max = -1000000;
    // int min = 1000000;

    // cout<<"Задание 1"<<endl;
    // cout<<"Заполните массив числами:"<<endl;
    // for(int i = 0; i < 10; i++){
    //     cout<<"элемент "<<i+1<<": ";
    //     cin>>arr_1[i];
    // }
    // for(int i = 0; i < 10; i++){
    //     if(max < arr_1[i]){
    //         max = arr_1[i];
    //     }
    // }
    // for(int i = 0; i < 10; i++){
    //     if(min > arr_1[i]){
    //         min = arr_1[i];
    //     }
    // }

    // cout<<"максимальный элемент: "<<max<<endl;
    // cout<<"Минимальный элемент: "<<min<<endl;
    // cout<<"Разница между максимальным и минимальным элементом: "<<max-min<<endl;

    // //Задание 2
    // cout<<endl<<"Задание 2"<<endl;
    // int arr_2[10];
    // cout<<"Генерируется массив из 10 элементов с рандомными числами"<<endl;
    // for(int i = 0; i < 10; i++){
    //     arr_2[i] = rand() % 100;
    // }
    // cout<<"Результат:"<<endl;
    // for(int i = 0; i < 10; i++){
    //     cout<<"Элемент "<<i + 1<<": "<<arr_2[i]<<endl;
    // }

    // //Задание 3
    // cout<<endl<<"Задание 3"<<endl;
    // cout<<"Введите размер массива: ";

    // int size = 0;
    // cin>>size;
    // int *arr_3 = new int[size];

    // for(int i = 0; i < size; i++){
    //     arr_3[i] = rand() % 100;
    // }
    // cout<<"Результат: "<<endl;
    // for(int i = 0; i < size; i++){
    //     cout<<arr_3[i]<<"; ";
    // }
    // delete [] arr_3;

    // //Задание 4
    // cout<<endl<<"Задание 4"<<endl;
    // int const cols = 5;
    // int const rows = 5;
    // int arr_4[rows][cols];
    // int sum[rows] = {0};

    // for(int i = 0; i < rows; i++){
    //     for(int j = 0; j < cols; j++){
    //         arr_4[i][j] = rand() % 10;
    //     }
    // }
    // for(int i = 0; i < rows; i++){
    //     for(int j = 0; j < cols; j++){
    //         cout<<arr_4[i][j]<<"\t";
    //         sum[j] += arr_4[i][j];
    //     }
    //     cout<<endl;
    // }
    // cout<<"Суммы каждого из столбцов:"<<endl;
    // for(int i = 0; i < rows; i++){
    //     cout<<sum[i]<<"\t";
    // }
    
    //Задание 5
    Link studentList;
    
    studentList.addStudent("Наталья", "Федорова", 19, "25ВВВ1");
    studentList.addStudent("Дмитрий", "Новиков", 20, "24ВВВ1");
    studentList.addStudent("Екатерина", "Морозова", 21, "23ВВВ3");
    studentList.addStudent("Алексей", "Попов", 20, "23ВВВ1");
    studentList.addStudent("Ольга", "Васильева", 19, "24ВВВ2");
    studentList.addStudent("Сергей", "Кузнецов", 22, "22ВВВ4");
    studentList.addStudent("Анна", "Смирнова", 20, "24ВВВ4");
    studentList.addStudent("Мария", "Сидорова", 19, "25ВВВ3");
    studentList.addStudent("Петр", "Петров", 21, "23ВВВ1");
    studentList.addStudent("Иван", "Иванов", 20, "24ВВВ2");
    
    cout << "Список всех студентов:" << endl;
    studentList.display();
    
    cout << "1) Имя  2) Фамилия  3) Возраст  4) Группа" << endl;
    cout << "Выберите способ поиска студента: ";
    string choice;
    cin >> choice;
    if (choice == "1" || choice == "Имя" || choice == "имя") {
        string name;
        cout << "Введите имя студента: ";
        cin >> name;
        studentList.searchStudents([&name](const Student& s) { return s.first_name == name; });
    }
    else if (choice == "2" || choice == "Фамилия" || choice == "фамилия") {
        string surname;
        cout << "Введите фамилию студента: ";
        cin >> surname;
        studentList.searchStudents([&surname](const Student& s) { return s.last_name == surname; });
    }
    else if (choice == "3" || choice == "Возраст" || choice == "возраст") {
        int age;
        cout << "Введите возраст студента: ";
        cin >> age;
        studentList.searchStudents([&age](const Student& s) { return s.age == age; });
    }
    else if (choice == "4" || choice == "Группа" || choice == "группа") {
        string group;
        cout << "Введите группу студента: ";
        cin >> group;
        studentList.searchStudents([&group](const Student& s) { return s.group_number == group; });
    }
    else {
        cout << "Неверный выбор!" << endl;
    }
    
    studentList.deleteStudent();
    studentList.display();


    return 0;
}