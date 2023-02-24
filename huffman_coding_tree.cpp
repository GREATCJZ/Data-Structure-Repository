#include <iostream>
using namespace std;

template <class Elem> class HuffNode{
public:
    virtual int weight() = 0;
    virtual bool isLeaf() = 0;
    virtual HuffNode<Elem>* left() const = 0;
    virtual void setLeft(HuffNode<Elem>*) = 0;
    virtual HuffNode<Elem>* right() const = 0;
    virtual void setRight(HuffNode<Elem>*) = 0;
};

template <class Elem> class FreqPair{
private:
    Elem it;
    int freq;
public:
    FreqPair(const Elem& e,int f){
        it=e;
        freq=f;
    }
    int weight(){return freq;}
    Elem& val() {return it;}
};

template <class Elem> class LeafNode: public HuffNode<Elem>{
private:
    FreqPair<Elem>* it;
public:
    LeafNode(const Elem& val,int freq){
        it=new FreqPair<Elem>(val,freq);
    }
    int weight(){return it->weight();}
    FreqPair<Elem>* val(){return it;}
    bool isLeaf(){return true;}
    virtual HuffNode<Elem>* left() const{return NULL;}
    virtual void setLeft(HuffNode<Elem>* e){}
    virtual HuffNode<Elem>* right() const{return NULL;}
    virtual void setRight(HuffNode<Elem>* e){}
};

template <class Elem> class InternalNode: public HuffNode<Elem>{
private:
    HuffNode<Elem>* leftNode;
    HuffNode<Elem>* rightNode;
    int wgt;
public:
    InternalNode(HuffNode<Elem>* ln,HuffNode<Elem>* rn){
        wgt=ln->weight()+rn->weight();
        leftNode=ln;
        rightNode=rn;
    }
    int weight(){return wgt;}
    bool isLeaf(){return false;}
    virtual HuffNode<Elem>* left() const{return leftNode;}
    virtual void setLeft(HuffNode<Elem>* e){leftNode=(HuffNode<Elem>*)e;}
    virtual HuffNode<Elem>* right() const{return rightNode;}
    virtual void setRight(HuffNode<Elem>* e){rightNode=(HuffNode<Elem>*)e;}
};

template <class Elem> class HuffTree{
private:
    HuffNode<Elem>* theRoot;
public:
    HuffTree(Elem& val,int freq){
        theRoot=new LeafNode<Elem>(val,freq);
    }
    HuffTree(HuffTree<Elem>* l,HuffTree<Elem>* r){
        theRoot=new InternalNode<Elem>(l,r);
    }

    HuffNode<Elem>* root(){return theRoot;}
    int weight(){return theRoot->weight();}
};

template <class Elem>
//treearray是原本建好的堆，放进来初始化，而count是节点个数
HuffTree<Elem>* buildHuffNode(HuffTree<Elem>** TreeArray, int count){
    //以weight为key的MinHeap
    //他的堆的初始化函数重载了拷贝类型的，参数列表包含拷贝的堆，由于单个单元节点是Huffmantree*,堆的形式则为数组Huffmantree**
    heap<HuffTree<Elem>*>* forest = new heap<HuffTree<Elem>*>(TreeArray,count);
    HuffTree<Elem>* temp1,* temp2,* temp3 =NULL;
    while (forest->size()>1){
        //前两子树值copy，然后delete
        forest->removemax(temp1);
        forest->removemax(temp2);
        //合并新中间节点
        temp3=new HuffTree<Elem>(temp1,temp2);
        forest->insert(temp3);
    }
    return temp3;
}

int main() {

}
