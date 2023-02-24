#include <iostream>
using namespace std;

int SIZEOfClass=100;

class Equivalent_Class{
public:
    int sizeOfClass;
    int* Class;
    Equivalent_Class(int soc=SIZEOfClass){
        sizeOfClass=soc;
        Class=new int[sizeOfClass];
        for(int i=0;i<sizeOfClass;i++){
            Class[i]=i;
        }
    }
    ~Equivalent_Class(){
        delete Class;
    }
    int FIND(int pos) const{
        if(Class[pos]==pos){return pos;}
        return FIND(Class[pos]);
    }
    void UNION(int pos1,int pos2){
        int root1= FIND(pos1);
        int root2= FIND(pos2);
        //如果root1和root2根系不同，那么root2的根系变为root1的子根
        if(root1!=root2){
            Class[root2]=root1;
        }
    }
    bool differ(int pos1,int pos2){
        int root1= FIND(pos1);
        int root2= FIND(pos2);
        return root1!=root2;
    }
};

int main() {
    std::cout << "Hello, World!" << std::endl;
    return 0;
}
