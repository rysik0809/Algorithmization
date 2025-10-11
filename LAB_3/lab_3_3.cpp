#include "fstream"
#include "iostream"

using namespace std;

template<typename T>
class List{
public:
    List();
    ~List();
    void pop_back();
    void push_front(T data);
    void clear();
    void printList();
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
    if(head == nullptr) return;
    if(head->pNext == nullptr){
        delete head;
        head == nullptr;
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
template<typename T>
void List<T>::clear(){
    while(Size){
        pop_back();
    }
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
    List<int> lst;
    lst.push_front(1);
    lst.push_front(2);
    lst.push_front(3);
    lst.push_front(4);
    lst.push_front(5);

    cout<<"Созданная стек"<<endl;
    cout<<"==============================="<<endl;
    lst.printList();
    cout<<endl;

    cout<<"Внесли новое значение в стек"<<endl;
    cout<<"==============================="<<endl;
    lst.push_front(6);
    lst.printList();
    cout<<endl;
    cout<<"Удалили элемент из стека"<<endl;
    cout<<"==============================="<<endl;
    lst.pop_back();
    lst.printList();
}