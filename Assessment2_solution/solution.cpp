#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

void *sample()
{
    printf("Pthread is created\n");
}

int main(void)
{
    pthread_t tid;
    int pthread_create(&tid,NULL,&sample,NULL);
    int pthread_join(tid,NULL);

    return 0;
}

// #include<stdio.h>
// #include<pthread.h>
// #include<unistd.h>

// void *PrintHello(void *threadid)
// {
// 	printf("\nHello World\n");
// 	printf("\nI am wating\n");
// 	while(1);
// }

// int main()
// {
// 	pthread_t thread;
// 	int re,t=0;	
// 	printf("\nCreating thread %d\n",t);
// 	re = pthread_create(&thread,NULL,PrintHello,NULL);
// 	printf("\nThread ID: %u", thread);
// 																			//pthread_join(thread,NULL);
// 	sleep(6);
// 	t = pthread_cancel(thread);
// 	if(t==0)
// 	{
// 		printf("Cancel thread\n");
// 	}
// 	printf("\nThread ID: %d\n",thread);
// }

#


