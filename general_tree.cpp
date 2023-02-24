#include <iostream>
using namespace std;

template <class Elem> class GTNode{
public:
    Elem element;
    GTNode<Elem>* leftMostChild;
    GTNode<Elem>* sibling;
    GTNode(Elem& e,GTNode<Elem>* lc=NULL,GTNode<Elem>* sb=NULL){
        element=e;
        leftMostChild=lc;
        sibling=sb;
    }
    GTNode(GTNode<Elem>* lc=NULL,GTNode<Elem>* sb=NULL){
        leftMostChild=lc;
        sibling=sb;
    }
    Elem& val(){return element;}
    bool isLeaf(){if(leftMostChild==NULL){return true;} else{return false;}}
    GTNode<Elem>* leftmost_child(){return leftMostChild;}
    GTNode<Elem>* right_sibling(){return sibling;}
    void setVal(Elem& e){element=e;}
    void insert_first(GTNode<Elem>* it){
        it->sibling=leftMostChild;
        leftMostChild=it;
    }
    void insert_next(GTNode<Elem>* it){
        it->sibling=sibling;
        sibling=it;
    }
    void remove_first(){
        if(leftMostChild==NULL){return;}
        GTNode<Elem>* temp=leftMostChild;
        leftMostChild=leftMostChild->sibling;
        delete temp;
    }
    void remove_next(){
        if(sibling==NULL){return;}
        GTNode<Elem>* temp=sibling;
        sibling=sibling->sibling;
        delete temp;
    }
};

template <class Elem> class GenTree{
public:
    GTNode<Elem>* theRoot;
    int nodeCount;
    GenTree(){
        theRoot=NULL;
        nodeCount=0;
    }
    void printhelp(GTNode<Elem>* subroot){
        if(subroot==NULL){return;}
        if(subroot->isLeaf()){
            cout<<"Leaf: ";
        } else{cout<<"Internal: ";}
        cout<<subroot->val()<<endl;
        printhelp(subroot->leftMostChild);
        printhelp(subroot->sibling);
    }
    void clear(GTNode<Elem>* subroot){
        if(subroot==NULL){return;}
        clear(subroot->leftMostChild());
        clear(subroot->right_sibling());
        delete subroot;
    }
    GTNode<Elem>* root(){return theRoot;}
    void newRoot(Elem& e,GTNode<Elem>* lc,GTNode<Elem>* sb){

    }
    void print(){};
};




int main() {
    std::cout << "Hello, World!" << std::endl;
    return 0;
}
