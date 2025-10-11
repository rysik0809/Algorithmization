#include "fstream"
#include "iostream"
#include <string>

using namespace std;

template<typename T>
class PriorityNode {
public:
    PriorityNode* pNext;
    T data;
    int priority;
    
    PriorityNode(T data = T(), int priority = 0, PriorityNode *pNext = nullptr) {
        this->data = data;
        this->priority = priority;
        this->pNext = pNext;
    }
};

template<typename T>
class PriorityList {
private:
    int Size;
    PriorityNode<T> *head;
public:
    PriorityList();
    ~PriorityList();
    
    void push_preority(T data, int priority);
    void removePriority(int index);
    void delete_front();
    void clear();
    int GetSize() { return Size; }    
    void printList();
};

template<typename T>
PriorityList<T>::PriorityList() {
    Size = 0;
    head = nullptr;
}

template<typename T>
PriorityList<T>::~PriorityList() {
    clear();
}

template<typename T>
void PriorityList<T>::clear() {
    while(Size) {
        delete_front();
    }
}

template<typename T>
void PriorityList<T>::delete_front() {
    if (head == nullptr) return;
    
    PriorityNode<T> *temp = head;
    head = head->pNext;
    delete temp;
    Size--;
}

template<typename T>
void PriorityList<T>::removePriority(int priority) {
    
    if (head == nullptr) {
        cout<<"Список пуст";
        return;
    }
    while(head != nullptr && head->priority == priority){
        delete_front();
    }
    if(head == nullptr){ 
        return;
    }
    PriorityNode<T>* current = head;
    while (current->pNext != nullptr)
    {
        if(current->pNext->priority == priority){
            PriorityNode<T>* toDelete = current->pNext;
            current->pNext = toDelete->pNext;
            delete toDelete;
            Size--;
        }else{
            current = current->pNext;
        }
    }
    
}

template<typename T>
void PriorityList<T>::push_preority(T data, int priority) {
    PriorityNode<T>* newNode = new PriorityNode<T>(data, priority);
    
    if (head == nullptr || priority > head->priority) {
        newNode->pNext = head;
        head = newNode;
    } else {
        PriorityNode<T>* current = head;
        
        while (current->pNext != nullptr && current->pNext->priority >= priority) {
            current = current->pNext;
        }
        
        newNode->pNext = current->pNext;
        current->pNext = newNode;
    }
    Size++;
}

template<typename T>
void PriorityList<T>::printList() {
    PriorityNode<T>* current = head;
    int index = 0;
    while(current != nullptr) {
        cout << "[" << index << "] " << current->data << " (приоритет: " << current->priority << ")" << endl;
        current = current->pNext;
        index++;
    }
}

int main() {
    string request_one;
    string request_two;
    PriorityList<string> lst;
    lst.push_preority("Не очень важная", 0);
    lst.push_preority("Обычная задача", 1);
    lst.push_preority("Средняя задача", 2);
    lst.push_preority("Важная задача", 3);
    lst.push_preority("Срочная задача", 4);
    lst.push_preority("Очень срочная", 5);
    cout << "=== ДОБАВЛЕНИЕ ЭЛЕМЕНТОВ С ПРИОРИТЕТАМИ ===" << endl;
    lst.printList();
    cout << "===========================================" << endl;
    cout<<"[1] Изменить список"<<endl<<"[2] Завершить программу"<<endl<<"[=] ";
    cin>>request_one;
    if(request_one == "1" || request_one == "Изменить список" || request_one == "изменить список"){
        cout<<"[1] Добавить элемент"<<endl<<"[2] Удалить элемент"<<endl<<"[=] ";
        cin>>request_two;
        if(request_two == "1" || request_two == "Добавить элемент" || request_two == "добавить элемент"){
            string request_push;
            string request_push_priority;
            cout<<"введите данные (для завершение программы введите: 0)"<<endl<<"[=] ";
            cin>>request_push;
            if(request_push == "0" || request_push == "Завершить" || request_push == "завершить"){
                return 0;
            }
            cout<<"введите приоритет (для завершение программы введите: 0)"<<endl<<"[=] ";
            cin>>request_push_priority;
            if(request_push_priority == "0" || request_push_priority == "Завершить" || request_push_priority == "завершить"){
                return 0;
            }
            lst.push_preority(request_push, stoi(request_push_priority));
            cout<<"Элемент успешно добавлен!"<<endl;
            lst.printList();
        }else if(request_two == "2" || request_two == "Удалить элемент" || request_two == "удалить элемент"){
            string request_push;
            cout<<"введите преоритет элемента для его удаления (для завершение программы введите: 0)"<<endl<<"[=] ";
            cin>>request_push;
            if(request_push == "0" || request_push == "Завершить" || request_push == "завершить"){
                return 0;
            }else if(stoi(request_push) > lst.GetSize()){
                cout<<"Ошибка!"<<endl;
                return 0;
            }
            lst.removePriority(stoi(request_push));
            cout<<"Элемент успешно удален!"<<endl;
            lst.printList();
        }

    }else if(request_one == "2" || request_one == "Завершить программу" || request_one == "завершить программу"){
        return 0;
    }
    
    
    return 0;
}