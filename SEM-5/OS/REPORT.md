# Producer Consumer Problem

## 1. Overview:

The **producer consumer** problem also known as the **bounded buffer problem** is a classic example of a multi-process synchronization problem. The problem invloves two processes, the producer and the consumer. Both these processes share a common, fixed-size buffer. The producer's job is to "produce", i.e., generate data, put it into the buffer and start again. At the same time, the consumer is "consuming", i.e., removing data from the buffer one at a time. The problem is to make sure that the producer won't try to add data into the buffer if it's full and that the consumer won't try to remove data from an empty buffer.

## 2. A Simple Approach:

Let us assume that the fixed size buffer acts like a queue, i.e., the producer produces at one end `in` of the queue and the consumer consumes from the other end `out`.


Code for Producer:

```
while (true)
{

    /* produce an item at in */

    while (counter == BUFFER_SIZE); // loop until buffer has space to add an item


    buffer[in] = item;
    in = (in+1)%BUFFER_SIZE;
    counter++;
}
```

Code for Consumer:

```
while (true)
{
    /* consume an item from out */

  ` while (counter == 0); // loop until buffer has an item`

    consumed_item = buffer[out];
    in = (in+1)%BUFFER_SIZE;
    counter--;
}
```

Variable names are self explanatory.

Although the producer and consumer routines shown above are correct seperately, they may not function correctly when executed concurrently. This is because, the buffer `buffer` and the variable `counter` are shared between the 2 processes. If these 2 processes access and manipulate the shared data concurrently then the outcome of the execution depends on the order in which the  access takes place. So we need to ensure that only one process will gain access to the shared resource at a time.

Consider the `counter++` and `counter--` statements in the producer and consumer processes respectively. `counter++` may be implemented in assembly language as:

```
mov r1,counter
inc r1
mov counter,r1
```

The concurrent execution of `counter++` and `counter--` may lead to several possible sequences of assembly statements interleaved in arbitrary order. One such would be:

```
mov r1,counter
inc r1
mov r2,counter
dec r2
mov counter,r1
mov counter,r2
```

Following this sequence, we end up with a wrong value of counter. So such a situaton must be avoided and only 1 process should be allowed to modify the counter value at a time.

The segment of code in which a process may be modifying shared resources is called a **critical section**. When one process will execute in its critical section, no other processes will be allowed access to the concerned shared resources.

## 3. Semaphores

Semaphores are synchronization tools which can be used to synchronize access to common resources by multiple processes in a concurrent system.

A semaphore **S** is an in integer variable that, apart from initialization, can be accessed only through two **atomic** operations `wait()` and `signal()`. An operation is called atomic if it is performed as one uninterruptable unit. Any process making an atomic operation cannot be interrupted and no other process can be scheduled in its place.

The definitions of `wait()` and `signal()` are:

```
wait(S)
{
    while (S<=0); // busy wait

    S--;
}
```
```
signal(S)
{
    S++;
}
```

Rather than engaging in busy waiting which wastes CPU time, a process can be sent to the waiting queue associated with the semaphore on which it needs to wait. Thus the process can **block** itself if it finds that the semaphore value is not positive.

To implement semaphores like this, we need to define a semaphore as:

```
typedef struct
{
    int value;
    struct process *list;
} semaphore;
```
Each semaphore has an integer value and a list of processes waiting on it. A `signal()` operation removes a process from the waiting list and places it in the ready queue, to be eventually scheduled by the scheduer. A `wait()` operation blocks a process if the value is not positive, and adds it to the list of processes. These operations are defined as follows:

```
wait(semaphore *S)
{
    S->value --;
    if (S->value < 0)
    {
        add_to_list(S->list,this_process);
        block(); // sends the process to waiting state
    }
}
```

```
signal(semaphore *S)
{
    S->value++;
    if (S->value <= 0)
    {
        if (S->list) // if some process is waiting
        {
            process p = remove_from_list(S->list);
            wakeup(p);  // bring the process to ready queue
        }
    }
}
```

POSIX semaphores can be created using the `sem_open()` or the `sem_init()` functions. `sem_open()` creates a named semaphore, and a semaphore thus created in a process is shared among all child processes of that parent. `sem_init()` creates an unnamned semaphore and needs to be placed in a region of shared memory if used among between parent and chlidren processes.

```
/* create a semaphore with name "Sema" and initial value 1
    0644 defines the permission placed on the semaphore, rw-r--r-- in this case */

sem_t *semaph = sem_open ("Sem", O_CREAT | O_EXCL, 0644, 1);
```

`sem_wait()` performs the wait operation on the semaphore and `sem_post()` performs the signal operation.


## 4. The Producer Consumer Problem using Semaphores

The problems with the naive implementation of the Producer-Consumer problem was discussed earlier. It can be solved using semaphores. The producer and consumer processes need to share to following:

```
    buffer[BUF_SIZE];
    semaphore mutex = 1, empty = BUF_SIZE, full = 0;
```
The `empty` and `full` semaphores count the number of empty and full slots in the buffer, and `mutex` is for ensuring mutual exclusion for access to the shared buffer.

Structure of producer process:

```                            
do                             
{                              
    wait(empty);               
    wait(mutex);               
    . . .                      
    /* add item to buffer */   
    . . .                      
    signal(mutex);             
    signal(full);              
}                              
```                             

Structure of consumer process:

```                            
do                             
{                              
    wait(full);               
    wait(mutex);               
    . . .                      
    /* remove item from buffer */   
    . . .                      
    signal(mutex);             
    signal(empty);              
}                              
```

As we can see, the consumer must wait until `full` is positive, which is only possible if the producer has produced some item on the buffer and made a `signal()` call. Similarly the producer must wait till the buffer is not full.

## 5. p-Producer c-Consumer Problem

Let us consider a situation where there are p producers and c consumers, sharing a circular buffer that can hold BUF_SIZE integers. Each of the producer processes stores the numbers 1 to n in the buffer one by one and then exits. Each of the consumer processes reads the numbers from the buffer and adds them to a shared variable TOTAL (initialized to 0). Though any consumer process can read any of the numbers in the buffer, the only constraint is every number written by some producer should be read exactly once by exactly one of the consumers.

This is an extension to the **Producer Consumer Problem** described above.

## 6. Implementation

We assume that a consumer process goes on consuming an item from the buffer until all producers have left and the buffer is empty.

We create a shared variable `buffer` which stores the actual buffer of items, along with 4 other variables. If the size of the item buffer is BUF_SIZE, then our definition of buffer is `int buffer[BUF_SIZE+4]` where:

 * `buffer[0]` = The sum TOTAL calculated by the consumer processes
 * `buffer[1]` = Producer end of the circular buffer
 * `buffer[2]` = Consumer head of the circular buffer
 * `buffer[3]` = A special variable which is set only when a consumer exits, marking that the buffer is empty and no producers are present
 * `buffer[4:BUF_SIZE+3]` = Actual area where items are stored

This shared memory is allocated in the parent process, which then forks p producer processes and c consumer processes, p and c are taken as input from the user.

We use 4 semaphores for our implementation `empty`, `full`, `mutex` and `prod`. The first 3 have the same usage as described in Section 4. Apart from them, we use a semaphore `prod` which is inialized to `p`. Every time a producer exits, the value of `prod` is reduced. It is to check whether all producers have exited.

In our implementation we take **n = 60** and **BUF_SIZE = 25**

**The main function :**
```
int main(int argc, char const *argv[])
{
    pid_t pid;
    int i, j, no_prod, no_cons, shmid, *buffer;
    key_t shmkey;
    sem_t *full, *empty, *mutex, *prod;
    printf ("Enter no of producers and consumers: \n");
    scanf ("%d %d",&no_prod, &no_cons);

    //shared memory
    shmkey = ftok ("/dev/null", 5);       /* valid directory name and a number */
    printf ("shmkey for p = %d\n", shmkey);
    shmid = shmget (shmkey, (BUF_SIZE+4)*sizeof (int), 0644 | IPC_CREAT);
    if (shmid < 0)
    {                           
        perror ("shmget\n");
        exit (1);
    }

    buffer = (int *) shmat (shmid, NULL, 0);   /* attach p to shared memory */
    for (i=0; i<(BUF_SIZE+4); i++) buffer[i] = 0;
    buffer[1] = buffer[2] = 4;
    printf ("buffer=%d is allocated in shared memory.\n\n", *buffer);

    empty = sem_open ("eSem", O_CREAT | O_EXCL, 0644, BUF_SIZE);     
    full = sem_open ("fSem", O_CREAT | O_EXCL, 0644, 0);     
    mutex = sem_open ("mSem", O_CREAT | O_EXCL, 0644, 1);     
    prod = sem_open("pSem", O_CREAT | O_EXCL, 0644, no_prod);

    //fork producers and consumers
    for (i=0; i<(no_prod+no_cons); i++)
    {
        pid = fork();
        if (pid < 0)
        {
            sem_unlink("eSem");
            sem_close(empty);
            sem_unlink("fSem");
            sem_close(full);
            sem_unlink("mSem");
            sem_close(mutex);
            sem_unlink("pSem");
            sem_close(prod);
            printf("Error forking\n");

        }

        else if (pid == 0) break;
    }

    if (pid != 0)
    {
        while (pid = waitpid (-1, NULL, 0))
        {
            if (errno == ECHILD)
                break;
        }
        printf ("\nParent: All children have exited.\n");
        printf ("Total: %d\n ", buffer[0]);
        shmdt (buffer);
        shmctl (shmid, IPC_RMID, 0);

        printf ("Shared memory detached\n");

        sem_unlink("eSem");
        sem_close(empty);
        sem_unlink("fSem");
        sem_close(full);
        sem_unlink("mSem");
        sem_close(mutex);
        sem_unlink("pSem");
        sem_close(prod);
        exit(0);
    }
    else
    {
        if (i < no_prod)   
            producer_main(buffer, empty, full, mutex, prod); //spawn producer
        else
            consumer_main(buffer, empty, full, mutex, prod); //spawn consumer

        exit(0);
    }

    return 0;
}
```

**The producer function :**

```
void producer_main(int *buf, sem_t *empty, sem_t *full, sem_t *mutex, sem_t *prod)
{
	int i;
	for (i = 1; i <= 60; i++)
	{
		sem_wait(empty); // wait if no more empty spaces
		sem_wait(mutex); // attain mutual exclusion for accessing the buffer

        /* critical section */

		buf[buf[1]] = i;
		printf ("Producer %d produced %d at index %d\n",getpid(), i, buf[1]-4);
		buf[1]++;
		buf[1]=(buf[1]>=BUF_SIZE+4)?4:buf[1]; // increment the producer head of queue

		sem_post(mutex);
		sem_post(full); // increment full and wakeup any consumer waiting on it.
	}
	sem_wait(prod);
	printf ("Producer %d exits. BYE!!!\n", getpid());

}
```

**The consumer function :**

```
void consumer_main(int *buf, sem_t *empty, sem_t *full, sem_t *mutex, sem_t *prod)
{
	int i, j, val, exit, flag=1;
	while (flag)
	{
		sem_wait(full); // wait if buffer is empty
		sem_wait(mutex); // attain mutual exclusion for accessing buffer
		if (!buf[3]) // if no consumer has exited and there is atleast a producer present
		{
			buf[0] += buf[buf[2]]; // calculate total sum
			printf ("Consumer %d consumed %d at %d\n",getpid(), buf[buf[2]], buf[2] );
			buf[buf[2]] = 0; // consume
			buf[2]++;
			buf[2]=(buf[2]>=BUF_SIZE+4)?4:buf[2]; // increment the consumer head of queue
		}
		sem_getvalue(prod,&val);
		if (val==0) // check if all producers have exited
		{
            /* Check whether buffer is empty */
			flag = 0;
			for (j=4; j<(BUF_SIZE+4); j++)
			{
				if (buf[j] > 0)
				{
					flag=1;
					break;
				}
			}
		}

		sem_post(mutex);
		sem_post(empty); // increment empty amd wakeup any producer waiting on it
	}
	printf("Consumer %d exits. BYE!!!\n", getpid());
	buf[3] = 1; // set flag if a consumer exits
	sem_post(full); // allow other consumers to terminate normally
}
