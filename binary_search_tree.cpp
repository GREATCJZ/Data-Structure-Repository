#include <iostream>
using namespace std;

template <class Elem> class BinNode{
public:
    Elem element;
    BinNode<Elem>* leftNode;
    BinNode<Elem>* rightNode;
    BinNode(Elem& e,BinNode<Elem>* ln=NULL,BinNode<Elem>* rn=NULL){
        element=e;
        leftNode=ln;
        rightNode=rn;
    }
    BinNode(BinNode<Elem>* ln=NULL,BinNode<Elem>* rn=NULL){
        leftNode=ln;
        rightNode=rn;
    }
    Elem& val(){return element;}
    inline BinNode<Elem>* left(){return leftNode;}
    inline BinNode<Elem>* right(){return rightNode;}
    void setLeft(BinNode<Elem>* lc){leftNode=lc;}
    void setRight(BinNode<Elem>* rc){rightNode=rc;}
    bool isLeaf(){return (leftNode==NULL)&&(rightNode==NULL);}
};

template <class Elem>
bool Complt(Elem& a,Elem& b){

}

template <class Elem>
bool Compeq(Elem& a,Elem& b){

}

template <class Elem>
class Binary_Search_Trees{
public:
    BinNode<Elem>* root;
    int nodeCount;
    Binary_Search_Trees(){
        root=NULL;
        nodeCount=0;
    }
    void clearhelp(BinNode<Elem>* subroot){
        if(subroot==NULL){return;}
        clearhelp(subroot->left());
        clearhelp(subroot->right());
        delete subroot;
        nodeCount--;
    }
    bool findhelp(BinNode<Elem>* subroot,BinNode<Elem>* it,Elem& e) const{
        if(subroot==NULL){it=NULL;return false;}
        if(Compeq(subroot->element,e)){it=subroot;return true;}
        if(Complt(e,subroot->element)){
            return findhelp(subroot->left(),it,e);
        }
        else{
            return findhelp(subroot->right(),it,e);
        }
    }
    BinNode<Elem>* inserthelp(BinNode<Elem>* subroot,const Elem& e){
        if(subroot==NULL){
            return new BinNode<Elem>(e);
        }
        if(Complt(e,subroot->element)){
            subroot->setLeft(inserthelp(subroot->left(),e));
        }
        else{
            subroot->setRight(inserthelp(subroot->right(),e));
        }
        //如果equal就相当于啥也没干，返回的subroot不是要插入位置的subroot，而是输进去的subroot
        return subroot;
    }
    BinNode<Elem>* deletemin(BinNode<Elem>* subroot,BinNode<Elem>* min){
        if(subroot->left()==NULL){
            min=subroot;
            nodeCount++;
            return subroot->right();
        }
        else{
            subroot->setLeft(deletemin(subroot->left(),min));
            return subroot;
        }
    }
    BinNode<Elem>* removehelp(BinNode<Elem>* subroot,Elem& e,BinNode<Elem>* it){
        if(subroot==NULL){return NULL;}
        if(Complt(e,subroot->element)){
            removehelp(subroot->left(),e,it);
        }
        else if(Compeq(e,subroot->element)){
            BinNode<Elem> temp;
            if(subroot->left()==NULL){
                subroot=subroot->right();
            }
            else if(subroot->right()==NULL){
                subroot=subroot->left();
            }
            else{
                deletemin(subroot->right(),temp);
                Elem te=subroot->val();
                subroot->val()=temp.val();
                temp.val()=te;
                it=temp;
            }
            return subroot;
        }
        else{
            removehelp(subroot->right(),e,it);
        }
    }
    void printhelp(BinNode<Elem>* subroot,int level) const{
        if(subroot==NULL){return;}
        printhelp(subroot->left(),level+1);
        for(int i=0;i<level;i++){
            cout<<" ";
        }
        cout<<subroot->val()<<"\n";
        printhelp(subroot->right(),level+1);
    }
    bool insert(BinNode<Elem>* subroot,const Elem& e){
        inserthelp(subroot, e);
        nodeCount++;
        return true;
    }
    bool remove(BinNode<Elem>* subroot,Elem& e){
        BinNode<Elem>* it=NULL;
        removehelp(subroot,e,it);
        //remove可能失败，但是insert不会失败.
        if(it==NULL){return false;}
        nodeCount++;
    }
    bool find(BinNode<Elem>* subroot,BinNode<Elem>* it,Elem& e) const{
        return findhelp(subroot,it,e);
    }
    int size(){return nodeCount;}
    void print() const{
        if(root=NULL){return;}
        //print也有可能失败.
        else {
            printhelp(root,0);
        }
    }
};


int main() {
    std::cout << "Hello, World!" << std::endl;
    return 0;
}
