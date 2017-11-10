#include <stdio.h>          
#include <stdlib.h>         
#include <sys/types.h>      
#include <sys/shm.h>        
#include <sys/stat.h>
#include <errno.h>          
#include <semaphore.h>     
#include <fcntl.h>          
#include <sys/wait.h>
#include <pthread.h>
#include <unistd.h>
#define BUF_SIZE 25

sem_t empty, full, mutex, prod;
int buffer[29];
void *producer_main(void *param)
{
	int tno = *((int*)param);
	//printf("Enter producer %d\n", tno);
	int i;
	//int *buf = *buffer;
	for (i = 1; i <= 60; i++)
	{
	//	printf("Enter loop %d\n",tno);
		sem_wait(&empty);	
		sem_wait(&mutex);

		buffer[buffer[1]] = i;
		printf ("Producer %d produced %d at %d\n",getpid(), i, buffer[1] );
		buffer[1]++;
		buffer[1]=(buffer[1]>=BUF_SIZE+4)?4:buffer[1];

		sem_post(&mutex);
		sem_post(&full);					
	}
	sem_wait(&prod);
	printf ("Producer %d exits. BYE!!!\n", getpid());

}
void *consumer_main(void *param)
{
	int tno = *((int*)param);

	//printf("Enter consumer %d\n", tno);
	int i, j, flag=1;
	//int *buffer = *bufferfer;
	int val, exit;
	while (flag)
	{
		
		sem_wait(&full);
		sem_wait(&mutex);
		if (!buffer[3])
		{
			buffer[0] += buffer[buffer[2]];
			printf ("Consumer %d consumed %d at %d\n",getpid(), buffer[buffer[2]], buffer[2] );
			//printf ("Current Total: %d\n", buffer[0]);
			buffer[buffer[2]] = 0;
			buffer[2]++;
			buffer[2]=(buffer[2]>=BUF_SIZE+4)?4:buffer[2];
		}
		sem_getvalue(&prod,&val);
		//printf ("%d\n",val);
		//flag = 0;
		if (val==0)
		{
			flag = 0;
			for (j=4; j<(BUF_SIZE+4); j++)
			{
				if (buffer[j] > 0) 
				{
					flag=1;
					break;
				}
			}
		}

		sem_post(&mutex);
		sem_post(&empty);
	}
	printf("Consumer %d exits. BYE!!!\n", getpid());
//	sem_post(*exits);
	buffer[3] = 1;
	sem_post(&full); // allow other consumers to terminate normally

}
int main(int argc, char const *argv[])
{
	pthread_t *tid;
	pthread_attr_t attr;
	int i, j, no_prod, no_cons, shmid;
	//key_t shmkey;
	//sem_t *full, *empty, *mutex, *prod;
	//int *bufferfer;

	printf ("Enter no of producers: \n");
	scanf ("%d",&no_prod);
	printf ("Enter no of consumers: \n");
	scanf ("%d",&no_cons);


	

	//shared memory 
	//shmkey = ftok ("/dev/null", 5);       /* valid directory name and a number */
    //printf ("shmkey for p = %d\n", shmkey);
    //shmid = shmget (shmkey, (BUF_SIZE+4)*sizeof (int), 0644 | IPC_CREAT); // 0th elem of buf to hold the total value
    //if (shmid < 0){                           /* shared memory error check */
      //  perror ("shmget\n");
       // exit (1);
    //}

    //buffer = (int *) shmat (shmid, NULL, 0);   /* attach p to shared memory */

	tid = (pthread_t*)malloc((no_prod+no_cons)*sizeof(pthread_t));

	printf("tids inited\n");
    for (i=0; i<(BUF_SIZE+4); i++)
    {
    	//printf("%d\n",i );
    	buffer[i] = 0;
    }
    buffer[1] = buffer[2] = 4;
    //printf ("buffer=%d is allocated in shared memory.\n\n", *buffer);
	

    //printf("hello\n");
	sem_init(&empty,0,BUF_SIZE-1);     
	sem_init(&full,0, 0);     
	sem_init(&mutex, 0, 1);     
	sem_init(&prod,0, no_prod);
	//exits = sem_open("xSem", O_CREAT | O_EXCL, 0644, 0);
	printf("semaphores created\n");
	//make producer and consumer threads
	for (i=0; i<(no_prod+no_cons); i++)
	{
		//printf("%d creating\n",i );
		if (i < no_prod)
		{
			pthread_create(&tid[i], NULL, producer_main, &i);
		}
		else
		{
			pthread_create(&tid[i], NULL, consumer_main, &i);
		}
		//printf("%d created\n",i );
	}
	free(tid);
	printf("Loop exited\n");

	sem_destroy(&prod);
	sem_destroy(&mutex);
	sem_destroy(&full);
	sem_destroy(&empty);
/*
	sem_unlink("eSem");
	sem_close(empty);
	sem_unlink("fSem");
	sem_close(full);
	sem_unlink("mSem");
	sem_close(mutex);
	sem_unlink("pSem");
	sem_close(prod);
*/			

	for (i = 0; i < no_cons+no_prod; i++)
		pthread_join(tid[i],NULL);

	printf("Sum = %d\n", buffer[0]);
	return 0;
}


/*
	The program was suspiciously encountering a segmentation fault when I had used sem_t * type for the 4 semaphores.
	When I changed them to sem_t and modified to code accordingly, it worked

	Also with System V semaphores, I was getting seg-fault
*/