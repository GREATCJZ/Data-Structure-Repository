#include <iostream>
using namespace std;

template <class Elem> class listNode{
public:
    Elem element;
    listNode* next;
    listNode(Elem& e,listNode* n=NULL){
        element=e;
        next=n;
    }
    listNode(listNode* n=NULL){
        next=n;
    }
};

template <class Elem> class Linked_list{
public:
    listNode<Elem>* head;
    listNode<Elem>* tail;
    listNode<Elem>* fence;
    int rightcnt,leftcnt;
    Linked_list(){
        head=tail=fence=NULL;
        rightcnt=leftcnt=0;
    }
    void clear(){
        while(head!=tail) {
            fence=head;
            head = head->next;
            delete fence;
        }
        rightcnt=leftcnt=0;
    }
    bool insert(Elem& e){
        fence->next=new listNode<Elem>(e,fence->next);
        if (fence==tail){
            tail=fence->next;
        }
        rightcnt++;
        return true;
    }
    bool append(Elem& e){
        tail->next=new listNode<Elem>(e,tail->next);
        tail=tail->next;
        rightcnt++;
        return true;
    }
    bool remove(Elem& it){
        if(fence==tail){return false;}
        listNode<Elem>* temp=fence->next;
        fence->next=fence->next->next;
        it=temp->element;
        delete temp;
        rightcnt--;
        return true;
    }
    void setStart(){
        fence=head;
        rightcnt=leftcnt+rightcnt;
    }
    void setEnd(){
        fence=tail;
        leftcnt=leftcnt+rightcnt;
    }
    void prev(){
        if(fence==head){return;}
        listNode<Elem>* temp=head;
        while(temp->next!=fence){
            temp=temp->next;
        }
        fence=temp;
        leftcnt--;
        rightcnt++;
    }
    void next(){
        if (fence==tail){return;}
        fence= fence->next;
        leftcnt++;
        rightcnt--;
    }
    int leftLength(){
        //左边的匣子数
        return leftcnt;
    }
    int rightLength(){
        return rightcnt;
    }
    bool setPos(int pos){
        if(rightcnt+leftcnt<=pos){return false;}
        fence=head;
        rightcnt=leftcnt+rightcnt;
        leftcnt=0;
        while(pos--){
            fence=fence->next;
            leftcnt++;
            rightcnt--;
        }
        return true;
    }
    bool getValue(Elem& it){
        if(fence==tail){return false;}
        it=fence->next->element;
        return true;
    }
    void print(){
        listNode<Elem>* temp=head;
        cout<<"< ";
        while(temp!=fence){
            cout<<temp->next->element<<" ";
        }
        cout<<"| ";
        while(temp!=tail){
            cout<<temp->next->element<<" ";
        }
        cout<<">"<<endl;
    }

};

int main() {
    std::cout << "Hello, World!" << std::endl;
    return 0;
}
