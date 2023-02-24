#include <iostream>
using namespace std;

int MAXSIZE=100;

template <class Elem> class Array_based_Queues{
public:
    int size;
    int front;
    int rear;
    Elem* List;
    Array_based_Queues(){
        size=rear=0;
        front=1;
        List=new Elem[MAXSIZE];
    }
    ~Array_based_Queues(){
        delete List;
    }
    bool enqueue(Elem& e){
        if((rear+2)%MAXSIZE==front){return false;}
        rear=(rear+1)%MAXSIZE;
        List[rear]=e;
        size++;
        return true;
    }
    bool dequeue(Elem& it){
        if(size==0){return false;}
        it=List[front];
        front=(front+1)%MAXSIZE;
        size--;
        return false;
    }
};

int main() {
    std::cout << "Hello, World!" << std::endl;
    return 0;
}
