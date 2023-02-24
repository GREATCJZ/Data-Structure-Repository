#include <iostream>
using namespace std;

template <class Elem> class queuesNode{
public:
    Elem element;
    queuesNode<Elem>* next;
    queuesNode(Elem& e,queuesNode<Elem>* n=NULL){
        element=e;
        next=n;
    }
    queuesNode(queuesNode<Elem>* n=NULL){
        next=n;
    }
};

template <class Elem> class Linked_Queues{
public:
    queuesNode<Elem>* front;
    queuesNode<Elem>* rear;
    int size;
    Linked_Queues(){
        front=rear=NULL;
        size=0;
    }
    bool enqueue(Elem& e){
        if(rear==NULL){
            front=rear=new queuesNode<Elem>(e,NULL);
        }
        else{
            rear->next=new queuesNode<Elem>(e,NULL);
            rear=rear->next;
        }
        size++;
        return true;
    }
    bool dequeue(Elem& it){
        if(size==0){return false;}
        queuesNode<Elem>* temp=front;
        front= front->next;
        it=temp->element;
        delete temp;
        size--;

        //非常重要的一步
        if(front==NULL){rear=NULL;}

        return true;
    }

};

int main() {
    std::cout << "Hello, World!" << std::endl;
    return 0;
}
