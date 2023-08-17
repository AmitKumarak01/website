#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>

// int array[5] = {1,23,20,2,8};
// int temp ;

// void Assending_Descending()
// {
//     int i;
//     for(int i=0;i<5;i++)
//     {
//         if(array[i]>array[i+1])
//         {
//             //int temp ;
//             temp=array[i];
//             array[i]=array[i+1];
//             array[i+1]=temp;
//         }
//         //printf(" %d ", array[i+1]);
//         //printf(" %d ",temp);
//         printf(" %d ", array[i]);
//     }
//     //printf("%d",temp);
// }
void Ascending_Descending_Numbers(int order, int count, .............)
{
    va_list args;
    va_start(arg,count);

    int* num =(int*) malloc(count * sizeof(int));
    if(num == NULL)
    {
        printf("There is no memory allocation i.e memory allocation is failed");
    }

    for(int i=0;i<count;i++)
    {
        va_arg(args,int);
    }
    va_end(args);
    
}


int main(int argc, char* argv[])
{
    //int array[5] = {1,23,20,2,6};
    // Assending_Descending();
    // return 0;
}