#include <iostream>
using namespace std;

template <class Elem> class stackNode{
public:
    Elem element;
    stackNode<Elem>* next;
    stackNode(Elem& e,stackNode<Elem>* n=NULL){
        element=e;
        next=n;
    }
    stackNode(stackNode<Elem>* n=NULL){
        next=n;
    }
};

template <class Elem> class Linked_Stack{
public:
    stackNode<Elem>* top;
    int size;
    Linked_Stack(){
        top=NULL;
        size=0;
    }
    bool push(Elem& e){
        top=new stackNode<Elem>(e,top);
        size++;
        return true;
    }
    bool pop(Elem& it){
        if(size==0){return false;}
        stackNode<Elem>* temp=top;
        top=top->next;
        it=temp->element;
        delete temp;
        size--;
        return true;
    }
};


int main() {
    std::cout << "Hello, World!" << std::endl;
    return 0;
}
