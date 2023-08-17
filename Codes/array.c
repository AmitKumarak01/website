#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main()
{
    int n;
    scanf("%d",&n);
    int nums[n];
    int i;
    int avg = 0;
    for(i=0;i<n;i++)
    {
        scanf("%d",nums[i]);
    }
    
    // for(i=0;i<n;i++)
    // {
    //     avg = avg + i;
    // }
    printf("%d",avg);
    return 0;
}


