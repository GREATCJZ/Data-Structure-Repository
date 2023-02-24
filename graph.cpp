#include <iostream>
using namespace std;
#define NOTPATH 999999

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

template <class Elem> class queuesNode{
public:
    Elem element;
    queuesNode<Elem>* next;
    queuesNode(Elem& e,queuesNode<Elem>* n=NULL){
        element=e;
        next=n;
    }
    queuesNode(queuesNode<Elem>* n=NULL){
        next=n;
    }
};

template <class Elem> class Linked_Queues{
public:
    queuesNode<Elem>* front;
    queuesNode<Elem>* rear;
    int size;
    Linked_Queues(){
        front=rear=NULL;
        size=0;
    }
    bool enqueue(Elem& e){
        if(rear==NULL){
            front=rear=new queuesNode<Elem>(e,NULL);
        }
        else{
            rear->next=new queuesNode<Elem>(e,NULL);
            rear=rear->next;
        }
        size++;
        return true;
    }
    bool dequeue(Elem& it){
        if(size==0){return false;}
        queuesNode<Elem>* temp=front;
        front= front->next;
        it=temp->element;
        delete temp;
        size--;

        //非常重要的一步
        if(front==NULL){rear=NULL;}

        return true;
    }

};

int MAXSIZE=100;

template <class Elem>
bool Comlt(Elem a,Elem b){
    return a.distance>b.distance;
}

template <class Elem>
bool Comgt(Elem a,Elem b){
    return a.distance<b.distance;
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

class Graph{
public:
    Linked_list<int>** graph;
    int n;
    int e;
    int** Weight;
    bool* Mark;

    Graph(int tempn=10){
        n=tempn;
        e =0;
        graph=new Linked_list<int>*[n];
        for(int i=0;i<n;i++){
            graph[i]=new Linked_list<int>();
        }
        Weight=new int*[n];
        for(int i=0;i<n;i++){
            Weight[i]=new int[n];
            for(int k=0;k<n;k++){
                if(i==k){Weight[i][k]=0;}
                else{Weight[i][k]=NOTPATH;}
            }
        }
        Mark=new bool[n];
        for(int i=0;i<n;i++){
            Mark[i]= false;
        }
    }
    ~Graph(){
        delete Weight;
        delete Mark;
        delete graph;
    }
    int getn(){return n;}
    int gete(){return e;}
    int first(int a){
        if(graph[a]->head==graph[a]->tail){return getn();}
        graph[a]->setPos(0);
        int result;
        graph[a]->getValue(result);
        return result;
    }
    int next(int a,int b){
        graph[a]->setPos(0);
        while(graph[a]->fence!=graph[a]->tail&&graph[a]->fence->next->element!=b) {
            graph[a]->next();
        }
        if(graph[a]->fence==graph[a]->tail){return getn();}
        graph[a]->next();
        int result;
        graph[a]->getValue(result);
        return result;
    }
    void setEdge(int ver1,int ver2,int wei){
        if(Weight[ver1][ver2]==NOTPATH){
            graph[ver1]->append(ver2);
        }
        Weight[ver1][ver2]=wei;
        e++;
        //有向图和无向图
        if(Weight[ver2][ver1]==NOTPATH){
            graph[ver2]->append(ver1);
        }
        Weight[ver2][ver1]=wei;
        //n++;
    }
    bool delEdge(int ver1,int ver2){
        if(Weight[ver1][ver2]==NOTPATH){return false;}
        graph[ver1]->setPos(0);
        while (graph[ver1]->fence!=graph[ver1]->tail&&graph[ver1]->fence->next->element!=ver2){

        }
        if(graph[ver1]->fence->next==graph[ver1]->tail){return false;}
        graph[ver1]->remove(ver2);
        Weight[ver1][ver2]=NOTPATH;
        e--;
        //有向图和无向图
        if(Weight[ver2][ver1]==NOTPATH){return false;}
        graph[ver2]->setPos(0);
        while (graph[ver2]->fence!=graph[ver2]->tail&&graph[ver2]->fence->next->element!=ver1){

        }
        if(graph[ver2]->fence->next==graph[ver2]->tail){return false;}
        graph[ver2]->remove(ver1);
        Weight[ver2][ver1]=NOTPATH;
        //n--;
        return true;
    }
    int weight(int ver1,int ver2){
        return Weight[ver1][ver2];
    }
    bool getMark(int ver){return Mark[ver];}
    void setMark(int ver,bool flag=true){
        Mark[ver]=flag;
    }
};

//some action在搜索的时候
void PreVisit(Graph* g,int v){

}

void PostVisit(Graph* g,int v){

}

//for循环里面递归进去，但这个for循环是是围绕起点的，如果选的起点不好可能遍历不了整个图
void DFS(Graph* g,int v){
    PreVisit(g,v);
    g->setMark(v);
    for(int w=g->first(v);w<g->getn();w=g->next(v,w)){
        if(g->getMark(w)== false){
            DFS(g,w);
        }
    }
    PostVisit(g,v);
}

//判断成功就应该Mark上并塞入队列。
//在循环里进行PreVisit和PostVisit的操作
void BFS(Graph* g,int start,Linked_Queues<int>* Q){
    Q->enqueue(start);
    g->setMark(start);
    int temp;
    while (Q->size!=0){
        Q->dequeue(temp);
        PreVisit(g,temp);
        for(int w=g->first(temp);w<g->getn();w=g->next(temp,w)){
            if(g->getMark(w)== false){
                g->setMark(w);
                Q->enqueue(w);
            }
        }
        PostVisit(g,temp);
    }
}

//多任务优化
//先遍历了所有后面的事件（high level的事件）再print现在的事件，类似于DFS的操作
//在Sort函数还要保证所有事件都要print到，for选了所有的点作为DFS的起点
void Topological_Sort_Print(Graph*g,int ver){

}
void Topological_Sort_help(Graph* g,int ver){
    g->setMark(ver);
    for(int w=g->first(ver);w<g->getn();w=g->next(ver,w)){
        if(g->getMark(w)==false){
            Topological_Sort_help(g,w);
        }
    }
    Topological_Sort_Print(g,ver);
}
void Topological_Sort(Graph* g){
    for(int i=0;i<g->getn();i++){
        g->setMark(i,false);
    }
    for(int i=0;i<g->getn();i++){
        if(g->getMark(i)== false){
            Topological_Sort_help(g,i);
        }
    }
}

//最短路径问题
//Linear的dijkstra算法
int minVertex_Linear(Graph* g,int* D){
    int i,min;
    for(i=0;i<g->getn();i++){
        if(g->getMark(i)== false){
            min=i;
        }
    }
    for(i;i<g->getn();i++){
        if(g->getMark(i)== false&&D[i]<D[min]){
            min=i;
        }
    }
    return min;
}
void Dijkstra_Linear(Graph* g,int* D,int start){
    int ver;
    for(int i=0;i<g->getn();i++){
        D[i]=NOTPATH;
    }
    D[start]=0;
    for(int i=0;i<g->getn();i++){
        ver= minVertex_Linear(g,D);
        if(ver==NOTPATH){return;}
        g->setMark(ver);
        for(int w=g->first(ver);w<g->getn();w=g->next(ver,w)){
            if(D[w]>D[ver]+g->weight(ver,w)){
                D[w]=D[ver]+g->weight(ver,w);
            }
        }
    }
}

//MinHeap的dijkstra算法
class DijkstraElem{
public:
    int vertex,distance;
    DijkstraElem(){}
    DijkstraElem(int ver,int dis){
        vertex=ver;
        distance=dis;
    }
};
void Dijkstra_MinHeap(Graph* g,int* D,int start){
    int ver;
    max_Heap<DijkstraElem>* minheap=new max_Heap<DijkstraElem>(g->gete());
    DijkstraElem temp(start,0);
    minheap->insert(temp);
    for(int i=0;i<g->getn();i++){
        do{
            if(!minheap->removemax(temp)){return;}
            ver=temp.vertex;
        }while(g->getMark(ver)== true);
        g->setMark(ver);
        if(D[ver]==NOTPATH){return;}
        for(int w=g->first(ver);w<g->getn();w=g->next(ver,w)){
            if(D[w]>D[ver]+g->weight(ver,w)){
                D[w]=D[ver]+g->weight(ver,w);
                temp.distance=D[w];temp.vertex=w;
                minheap->insert(temp);
            }
        }
    }
}

//Floyd's Algorithm
void Floyd(Graph* g){
    int D[g->getn()][g->getn()];
    for(int i=0;i<g->getn();i++){
        for(int k=0;k<g->getn();k++){
            D[i][k]=g->weight(i,k);
        }
    }
    for(int i=0;i<g->getn();i++){
        for(int j=0;j<g->getn();j++){
            for(int k=0;k<g->getn();k++){
                if(D[j][k]>D[j][i]+D[i][k]){
                    D[j][k]=D[j][i]+D[i][k];
                }
            }
        }
    }
}

//最小生成树
//Peim's Alogorithm
void AddEdgetoMST(int ver1,int ver2){
    cout<<"Add Edge to MST "<<ver1<<" "<<ver2<<endl;
    //一些action表示这条边被加进最小生成树了
}
void Peim(Graph* g,int* D,int start){
    int V[g->getn()];
    for(int i=0;i<g->getn();i++){
        int ver= minVertex_Linear(g,D);
        g->setMark(ver, true);
        if(D[ver]==NOTPATH){return;}
        if(ver!=start){ AddEdgetoMST(V[ver],ver);}
        for(int w=g->first(ver);w<g->getn();w=g->next(ver,w)){
            if(D[w]>g->weight(ver,w)){
                D[w]=g->weight(ver,w);
                V[w]=ver;
            }
        }
    }
}

//Kruskal's Algorithm


int main() {
    std::cout << "Hello, World!" << std::endl;
    return 0;
}
