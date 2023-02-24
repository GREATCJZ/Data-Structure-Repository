#include <iostream>
using namespace std;

int listMaxSize=100;

template <class Elem> class Array_based_list{
public:
    int listSize,maxSize,fence;
    Elem* List;
    Array_based_list(int mS=listMaxSize){
        listSize=fence=0;
        maxSize=mS;
        List=new Elem[maxSize];
    }
    ~Array_based_list(){
        delete List;
    }
    void clear(){
        delete List;
        List=new Array_based_list<Elem>;
        fence=listSize=0;
    }
    bool insert(const Elem& e){
        if(listSize>=maxSize || fence<0 || fence>listSize){return false;}
        for(int i=listSize;i>fence;i--){
            List[i]=List[i-1];
        }
        List[fence]=e;
        listSize++;
        return true;
    }
    bool append(const Elem& e){
        if(listSize>=maxSize){return false;}
        List[listSize++]=e;
        return true;
    }
    bool remove(Elem& e){
        if(listSize==0 || fence>=listSize || fence<0){return false;}
        e=List[fence];
        for(int i=--listSize;i>fence;i--){
            List[i-1]=List[i];
        }
        return true;
    }
    void setStart(){
        fence=0;
    }
    void setEnd(){
        fence=listSize;
    }
    void prev(){
        fence--;
    }
    void next(){
        fence++;
    }
    int leftLength(){
        return fence;
    }
    // rightLength包括了fence自己
    int rightLength(){
        return listSize-fence;
    }
    bool setPos(int Pos){
        if(Pos>listSize || Pos<0){return false;}
        fence=Pos;
        return true;
    }
    bool getValue(Elem& e){
        if(listSize==0 || fence>=listSize || fence<0){return false;}
        e=List[fence];
        return true;
    }
    void print(){
        int temp=0;
        cout<<"< ";
        while(temp<fence){
            cout<<List[temp]<<" ";
            temp++;
        }
        cout<<"| ";
        while (temp<listSize){
            cout<<List[temp]<<" ";
            temp++;
        }
        cout<<">"<<endl;
    }
};

int main() {
    std::cout << "Hello, World!" << std::endl;
    return 0;
}
