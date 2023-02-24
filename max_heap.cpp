#include <iostream>
using namespace std;

int MAXSIZE=100;

template <class Elem>
bool Comlt(Elem a,Elem b){

}

template <class Elem>
bool Comgt(Elem a,Elem b){

}

template <class Elem>
void swap(Elem* array,int pos1,int pos2){
    Elem temp=array[pos1];
    array[pos1]=array[pos2];
    array[pos2]=temp;
}

template <class Elem> class max_Heap{
public:
    Elem* Heap;
    int size;
    int n;
    max_Heap(int s=MAXSIZE){
        size=s;
        n=0;
        Heap=new Elem[size];
    }
    void shifdown(int pos){
        while (!isLeaf(pos)){
            int j= leftchild(pos);
            int rc= rightchild(pos);
            if((rc<n)&&Comlt(Heap[j],Heap[rc])){
                j=rc;
            }
            if(!Comlt(Heap[pos],Heap[j])){return;}
            swap(Heap,pos,j);
            pos=j;
        }
    }
    int heapsize(){
        return n;
    }
    bool isLeaf(int pos){
        return ((pos*2+1)>=n);

    }
    int leftchild(int pos) const{
        return 2*pos+1;
    }
    int rightchild(int pos) const{
        return 2*pos+2;
    }
    int parent(int pos) const{
        return (pos-1)/2;
    }
    bool insert(const Elem& e){
        if(n>=size){return false;}
        int curr=n++;
        Heap[curr]=e;
        while (curr!=0 && Comgt(Heap[curr], Heap[parent(curr)])){
            swap(Heap,curr, parent(curr));
            curr= parent(curr);
        }
        return true;
    }
    bool removemax(Elem& e){
        if(n<=0){return false;}
        e=Heap[0];
        Heap[0]=Heap[--n];
        shifdown(0);
        return true;

    }
    bool remove(int pos,Elem& it){
        it=Heap[pos];
        Heap[pos]=Heap[--n];
        bool flag=true;
        while (pos!=0 && Comgt(Heap[pos],Heap[parent(pos)])){
            swap(Heap,pos, parent(pos));
            pos= parent(pos);
            flag= false;
        }
        if(flag){ shifdown(pos);}
        return true;
    }
    void buildHeap(){
        for(int i=n/2+1;i>=0;i--){
            shifdown(i);
        }
    }
};

int main() {
    std::cout << "Hello, World!" << std::endl;
    return 0;
}
