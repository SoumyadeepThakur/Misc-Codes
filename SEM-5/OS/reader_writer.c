#include <stdio.h>          
#include <stdlib.h>         
#include <sys/types.h>      
#include <sys/shm.h>        
#include <sys/stat.h>
#include <errno.h>          
#include <semaphore.h>      
#include <fcntl.h>          
#include <sys/wait.h>
#include <unistd.h>

void mem_setup();
void reader(int **cnt, sem_t **rmutex_sem, sem_t ** mutex_sem, sem_t **rdtry_sem)

{
	printf("Entered reader: %d\n", (int)getpid());
	int *count = *cnt;
	sem_wait(*rdtry_sem);
	sem_wait(*rmutex_sem);
	count[0]++;
	if (count[0] == 1)
		sem_wait(*mutex_sem);
	sem_post(*rmutex_sem);
	sem_post(*rdtry_sem);
	printf ("Reader Lock attained: %d\n", (int)getpid());

	// critical section

	printf ("Reader is reading: %d\n", (int)getpid());
	printf("Read %d %d\n",count[2], (int)getpid() );
	sleep(1);
	printf("Reading over %d\n", (int)getpid());
	sem_wait(*rmutex_sem);
	count[0]--;
	if (count[0]==0)
		sem_post(*mutex_sem);

	sem_post(*rmutex_sem);

	printf ("Reader exits: %d\n",(int)getpid());

}
void writer(int **cnt, sem_t **wmutex_sem, sem_t **mutex_sem, sem_t **rdtry_sem)
{
	printf("Writer entered: %d\n",(int)getpid() );
	int *count = *cnt;
	sem_wait(*wmutex_sem);
	count[1]++;
	if (count[1] == 1)
		sem_wait(*rdtry_sem);
	sem_post(*wmutex_sem);

	sem_wait(*mutex_sem);
	printf ("Writer Lock attained: %d\n",(int)getpid());

	// critical section

	printf ("Writer is writing: %d\n", (int)getpid());
	count[2] = (int)getpid();
	printf("Writer writes: %d\n", (int)getpid());
	sleep(1);
	printf("Writing over %d \n",(int)getpid());

	sem_post(*mutex_sem);

	// remainder section
	sem_wait(*wmutex_sem);
	count[1]--;
	if (count[1] == 0)
		sem_post(*rdtry_sem);
	printf("Writer exits: %d\n",(int)getpid());
	sem_post(*wmutex_sem);


}
int main(int argc, char const *argv[])
{
	key_t shmkey;
	pid_t pid;
	int shmid, i;
	int rd_no, wr_no;

	printf("Enter no of readers and writers: \n");

	scanf("%d %d",&rd_no,&wr_no);

	sem_t *rmutex_sem, *wmutex_sem, *mutex_sem, *rdtry_sem;
	unsigned int init_val = 1;
	shmkey = ftok ("/dev/null", 5);       /* valid directory name and a number */
    printf ("shmkey for p = %d\n", shmkey);
    shmid = shmget (shmkey, 3*sizeof (int), 0644 | IPC_CREAT);
    if (shmid < 0){                           /* shared memory error check */
        perror ("shmget\n");
        exit (1);
    }
    int *count = (int*)shmat(shmid,NULL,0);
    count[0] = 0;
    count[1] = 0;
    count[2] = 1000; // shared mem


    // do the work

    rmutex_sem = sem_open ("rSem", O_CREAT | O_EXCL, 0644, init_val);     
    wmutex_sem = sem_open ("wSem", O_CREAT | O_EXCL, 0644, init_val);     
    mutex_sem = sem_open ("mSem", O_CREAT | O_EXCL, 0644, init_val);     
    rdtry_sem = sem_open ("tSem", O_CREAT | O_EXCL, 0644, init_val);

    int n=7;
    for (i = 0; i < (rd_no+wr_no); i++){
        pid = fork ();
        printf ("%d\n",pid);
        if (pid < 0) {
        /* check for error      */
            sem_unlink ("rSem");   
            sem_close(rmutex_sem);  
            sem_unlink ("wSem");   
            sem_close(wmutex_sem);
            sem_unlink ("mSem");   
            sem_close(mutex_sem);
            sem_unlink ("tSem");   
            sem_close(rdtry_sem);
            
            /* unlink prevents the semaphore existing forever */
            /* if a crash occurs during the execution         */
            printf ("Fork error.\n");
        }
        else if (pid == 0)
            break;                  /* child processes */
    }

	if (pid != 0){
        /* wait for all children to exit */
        while (pid = waitpid (-1, NULL, 0)){
            if (errno == ECHILD)
                break;
        }
        
        printf ("\nParent: All children have exited.\n");
        //sem_post(sem);
        /* shared memory detach */
        shmdt (count);
        shmctl (shmid, IPC_RMID, 0);

        /* cleanup semaphores */
        sem_unlink ("rSem");   
        sem_close(rmutex_sem);  
        sem_unlink ("wSem");   
        sem_close(wmutex_sem);
        sem_unlink ("mSem");   
        sem_close(mutex_sem);
        sem_unlink ("tSem");   
        sem_close(rdtry_sem);
            
            /* unlink prevents the semaphore existing forever */
        /* if a crash occurs during the execution         */
        exit (0);
    }
    else
    { 
    	printf("i = %d\n", i);
    	//printf ("ppp\n");
        if (i < wr_no)
        {
            writer(&count,&wmutex_sem, &mutex_sem, &rdtry_sem);
        }
        else
        {
        	reader(&count,&rmutex_sem, &mutex_sem, &rdtry_sem);          
        }

        //*p += i % 3;              /* increment *p by 0, 1 or 2 based on i */
        //printf ("  Child(%d) new value of *p=%d.\n", i, *p);
        //sem_post (sem);           /* V operation */
        exit (0);
    }

	return 0;
}
