#include <stack>
#include <random>
#include <iostream>
#include <time.h>
#include "llist.h"
#include "bstree.h"
#include "rbtree.h"
#include "hasht.h"


using namespace std;

void shuffle(int *arr, size_t n)
{
    if (n > 1)
    {
        size_t i;
        srand(time(NULL));
        for (i = 0; i < n - 1; i++)
        {
          size_t j = i + rand() / (RAND_MAX / (n - i) + 1);
          int t = arr[j];
          arr[j] = arr[i];
          arr[i] = t;
        }
    }
}

int main()
{
    hasht<int> tabla=hasht<int>(1000000);
    hasht<int> tabla2=hasht<int>(1000000);
    int * array=new int[1000000];



    for(int i=1;i<=1000000;i++){
        array[i]=i;
    }
    shuffle(array,1000000);


    rbtree<int>RBTREE;
     rbtree<int>RBTREE2;
    std::random_device rd;

      /* Random number generator */
      std::default_random_engine generator(rd());

      /* Distribution on which to apply the generator */
      std::uniform_int_distribution<int> distribution(0,0xFFFFFF);


    for(long i=1;i<=1000000;i++){
      rbnode<int>*nodo=new rbnode<int>(i);
      RBTREE.treeInsert(nodo);
    }
    for(long i=1;i<=1000000;i++){
      rbnode<int>*nodo=new rbnode<int>(array[i]);
      RBTREE.treeInsert(nodo);
    }
     time_t start, end,start2,start3,start4;

     double seconds_since_start=0;
     int iteracione=0;


     int t1=0,t2=0;

     for(long i=1;i<=1000000;i++){

       tabla.insert(i);
     }
     for(long i=1;i<=1000000;i++){

       tabla2.insert(array[i]);
     }
     iteracione=0;
     seconds_since_start=0;
     start3=time(NULL);
     while(seconds_since_start<=10){
         tabla.search(rand()%61*2000000);
         ++t1;
         seconds_since_start = difftime( time(NULL), start3);
     }
     std::cout<<t1<<endl;
     iteracione=0;
     seconds_since_start=0;
     start4=time(NULL);
     while(seconds_since_start<=10){
         tabla2.search(rand()%61*2000000);
         ++t2;
         seconds_since_start = difftime( time(NULL), start4);
     }
     std::cout<<t2<<endl;



    return 0;
}
