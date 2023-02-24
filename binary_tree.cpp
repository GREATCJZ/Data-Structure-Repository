#include <iostream>
using namespace std;

template <class Elem> class binNode{
private:
    Elem element;
    binNode<Elem>* lc;
    binNode<Elem>* rc;
public:
    binNode(){lc=NULL;rc=NULL;}
    binNode(Elem& e,binNode<Elem>* l,binNode<Elem>* r){
        element=e;
        lc=l;
        rc=r;
    }
    Elem& val() {return element;}
    void setVal(const Elem& e){element=e;}
    inline binNode<Elem>* left() const{return lc;}
    void setLeft(binNode<Elem>* l){lc=l;}
    inline binNode<Elem>* right() const{return rc;}
    void setRight(binNode<Elem>* r){rc=r;}
    bool isLeaf(){return (lc==NULL)&&(rc==NULL);}
};



//访问的action
template <class Elem>
void visit(binNode<Elem>* subroot){

    //中间节点和叶子不同的action
//    if(subroot->isLeaf()){
//        cout<<"Leaf: "<<subroot->val()<<endl;
//    }
//    else{
//        cout<<"Internal: "<<subroot->val()<<endl;
//    }
//  不加判断的话可以通过继承来实现,LeafNode和InternalNode
}

//前序
template <class Elem>
void preorder(binNode<Elem>* subroot){
    if(subroot==NULL) return;
    visit(subroot);
    preorder(subroot->left());
    preorder(subroot->right());
}
//后序
template <class Elem>
void postorder(binNode<Elem>* subroot){
    if(subroot==NULL)return;
    postorder(subroot->left());
    postorder(subroot->right());
    visit(subroot);
}
//中序
template <class Elem>
void inorder(binNode<Elem>* subroot){
    if(subroot==NULL)return;
    inorder(subroot->left());
    visit(subroot);
    inorder(subroot->right());
}





int main() {
    std::cout << "Hello, World!" << std::endl;
    return 0;
}
