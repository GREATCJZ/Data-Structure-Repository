#include <iostream>
using namespace std;
#include <queue>
#include <time.h>
#include <fstream>

template <class Elem> class Comp{
public:
    static bool lt(Elem a,Elem b){
        return a<b;
    }
    static bool eq(Elem a,Elem b){
        return a==b;
    }
    static bool gt(Elem a,Elem b){
        return a>b;
    }
};

template <class Elem>
void swap(Elem* A,int pos1,int pos2){
    Elem temp=A[pos1];
    A[pos1]=A[pos2];
    A[pos2]=temp;
}

//此处实现的都是升序

//Bubble sort的特点是前面部分先排好，未来都不会再变动
//其后面也会呈现于由小到大的趋势，但是趋势可能并不明显
template <class Elem>
void Bubble_Sort(Elem* A, int n){
    for(int i=0;i<n-1;i++){
        for(int j=n-1;j>i;j--){
            if(Comp<Elem>::lt(A[j],A[j-1])){
                swap(A,j,j-1);
            }
        }
    }
}

//Selection sort的特点是其比Bubble sort少了swap的次数
//但相对的，其后面部分不会呈现趋于由小到大的反映
template <class Elem>
void Selection_Sort(Elem* A,int n){
    for(int i=0;i<n-1;i++){
        int Min=A[n-1];
        int target=n-1;
        for(int j=n-2;j>=i;j--){
            if(Comp<Elem>::lt(A[j],Min)){
                target=j;
                Min=A[j];
            }
        }
        swap(A,i,target);
    }
}

//Insertion Sort的特点是每次加入一个新的
//因此前面排好的部分还会不断调整
template <class Elem>
void Insertion_Sort(Elem* A,int n){
    for(int i=1;i<n;i++){
        for(int j=i;j>0;j--){
            if(Comp<Elem>::lt(A[j],A[j-1])){
                swap(A,j,j-1);
            }
        }
    }
}

//跳跃的insertion sort，比较抽象
template <class Elem>
void Shell_Sort(Elem* A,int n){
    for(int gap=n/2;gap>0;gap/=2){
        for(int i=gap;i<n;i++){
            int j=i;
            Elem current = A[i];
            while (j-gap>=0&&Comp<Elem>::lt(current,A[j-gap])){
                A[j]=A[j-gap];
                j=j-gap;
            }
            A[j]=current;
        }
    }
}

inline int findpivot(int i,int j){
    return (i+j)/2;
}

template <class Elem>
inline int partition(Elem* A,int l,int r,Elem& pivot){
    do{
        while (Comp<Elem>::lt(A[++l],pivot));
        while ((l<r)&&Comp<Elem>::gt(A[--r],pivot));
        //第二个while把r拦下来了，所以最后l会等于r等于第一个大于pivot的数的索引
        //在Qsort交换该数字与pivot
        //经典的写法是让l成为第一个大于pivot的，r成为最后一个小于pivot的，即不拦住r，swap后在
        //退出循环的位置再swap l和r一次还原(l<r)改为(r!=0)
        //经典的写法需要swap element多一次，element很大时不佳
        //本写法虽然减免了这一次swap，但是swap是自己和自己swap，可能会有bug
        swap(A,l,r);
    } while (l<r);
    return l;
}

//快速排序
template <class Elem>
void Quick_Sort(Elem* A,int left,int right){
    if(right<=left){return;}
    int pivotindex= findpivot(left,right);
    swap(A,pivotindex,right);
    int k= partition(A,left-1,right,A[right]);
    //由于是++l，--r的写法，所以要输入left-1
    swap(A,k,right);
    //还原pivot的位置
    Quick_Sort<Elem>(A,left,k-1);
    Quick_Sort<Elem>(A,k+1,right);
}

//分治排最大的特点是其左边(left到mid)和右边(mid+1到right)的顺序都是排好的
//其需要把left==right的情况放出来(在这里隐含在i2>right的action里)
//其余的只需要用i1，i2做index排列放进更大的匣子即可
template <class Elem>
void Merge_Sort(Elem* A,Elem* temp,int left,int right){
    int mid=(left+right)/2;
    if(left>=right){return;}
    Merge_Sort<Elem>(A,temp,left,mid);
    Merge_Sort<Elem>(A,temp,mid+1,right);
    for(int i=left;i<=right;i++){
        temp[i]=A[i];
    }
    int i1=left;
    int i2=mid+1;
    for(int curr=left;curr<=right;curr++){
        if(i1==mid+1){
            A[curr]=temp[i2++];
        }
        //如果mid左边的都被填上去了，就把右边的直接按顺序补上去
        else if(i2>right){
            A[curr]=temp[i1++];
        }
        //如果mid右边都被填上去了，就把左边的直接按顺序补上去
        else if(Comp<Elem>::lt(temp[i1],temp[i2])){
            A[curr]=temp[i1++];
        }
        else{A[curr]=temp[i2++];}
    }
}


//利用堆的性质来排
template <class Elem>
void Heap_Sort(Elem* A,int n){
    Elem mval;
    max_Heap<Elem> h(A,n);
    for(int i=0;i<n;i++){
        h.removemax(mval);
        //这个removemax仅把max放在最后，不delete
    }
}

//类似于哈希算法的Bin sort,桶排
template <class Elem>
void Bin_Sort(Elem* A,int n,int MaxkeyValue=100){
    queue<Elem> B[MaxkeyValue];

    for(int i=0;i<n;i++){
        B[A[i]].push(A[i]);
    }
    int x=0;
    for(int i=0;i<MaxkeyValue;i++){
        while (!B[i].empty()){
            A[x++]=B[i].front();
            B[i].pop();
        }
    }
}

//桶排升级，由小到大位数一个个排，防止MAXVAL太大
template <class Elem>
void radix_Sort(Elem* A,int n,int r,int MaxkeyValue=100) {
    for (int rtoi = 1; rtoi < MaxkeyValue; rtoi *= r) {
        queue<Elem> B[r];

        for (int i = 0; i < n; i++) {
            B[A[i]/rtoi%r].push(A[i]);
        }
        int x = 0;
        for (int i = 0; i < r; i++) {
            while (!B[i].empty()) {
                A[x++] = B[i].front();
                B[i].pop();
            }
        }
    }
}

int main() {

}
