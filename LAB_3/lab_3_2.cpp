#include "fstream"
#include "iostream"

using namespace std;

template<typename T>
class List{
public:
    List();
    ~List();
    void pop_back();
    void clear();
    void pop_front();
    void push_back(T data);
    void push_front(T data);
    void printList();
    void reverset(T data);
    int GetSize(){ return Size; }
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
void List<T>::push_front(T data){
    head = new Node<T>(data, head);
    Size++;
}
template <typename T>
void List<T>::pop_front(){
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
void List<T>::reverset(T data){
    if (head == nullptr) {
        cout<<"Список пуст";
        return;
    }
    Node<T>* current = head;
    Node<T>* prev = nullptr;
    
    while (current != nullptr) {
        if (current->data == data) {
            if (prev == nullptr) {
                head = current->pNext;
                delete current;
                current = head;
                Size--;
            } else {
                prev->pNext = current->pNext;
                delete current;
                current = prev->pNext;
                Size--;
            }
        } else {
            prev = current;
            current = current->pNext;
        }
    }
    push_front(data);
}

template<typename T>
void List<T>::printList() {
    Node<T>* current = head;
    while(current != nullptr) {
        cout<<current->data<<endl;
        current = current->pNext;
    }
}

int main(){
    List<string> lst;
    lst.push_back("Николай");
    lst.push_back("Владимир");
    lst.push_back("Александр");
    lst.push_back("Петр");
    lst.push_back("Евгений");

    cout<<"Созданная очередь"<<endl;
    cout<<"==============================="<<endl;
    lst.printList();
    cout<<endl;
    cout<<"В очеред записались 2 человека"<<endl;
    cout<<"==============================="<<endl;
    lst.push_back("Генадий");
    lst.push_back("Аркадий");
    lst.printList();
    cout<<endl;
    cout<<"Очередь покинул первый человек"<<endl;
    cout<<"==============================="<<endl;
    lst.pop_front();
    lst.printList();
    cout<<endl;
    cout<<"Очередь покинул последний человек"<<endl;
    cout<<"==============================="<<endl;
    lst.pop_back();
    lst.printList();
    cout<<endl;
    lst.reverset("Петр");
    lst.printList();
}