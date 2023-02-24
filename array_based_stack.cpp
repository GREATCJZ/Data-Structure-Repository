#include <iostream>
using namespace std;

int MAXSIZE=100;

template <class Elem> class Array_based_Stack{
public:
    int top;
    int maxSize;
    Elem* List;
    Array_based_Stack(int mS=MAXSIZE){
        top=0;
        maxSize=mS;
        List=new Elem(maxSize);
    }
    ~Array_based_Stack(){
        delete List;
    }
    bool push(const Elem& e){
        if(top==maxSize){return false;}
        List[top]=e;
        top++;
        return true;
    }
    bool pop(Elem& it){
        if(top==0){return false;}
        it=List[--top];
        return true;
    }
};

int main() {
    std::cout << "Hello, World!" << std::endl;
    return 0;
}
