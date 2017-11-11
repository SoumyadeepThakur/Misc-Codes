# Producer Consumer Problem using Semaphores

## Overview:

The **producer consumer** problem also known as the **bounded buffer problem** is a classic example of a multi-process synchronization problem. The problem invloves two processes, the producer and the consumer. Both these processes share a common, fixed-size buffer. The producer's job is to "produce", i.e., generate data, put it into the buffer and start again. At the same time, the consumer is "consuming", i.e., removing data from the buffer one at a time. The problem is to make sure that the producer won't try to add data into the buffer if it's full and that the consumer won't try to remove data from an empty buffer.

## A Simple Approach:

Let us assume that the fixed size buffer acts like a queue, i.e., the producer produces at one end `in` of the queue and the consumer consumes from the other end `out`.

A simple approach will be:

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

Although the producer and consumer routines shown above are correct seperately, they may not function correctly when executed concurrently. This is because, the buffer `buffer` and the variable `counter` are shared between the 2 processes and there 

## Semaphores

Semaphores are synchronization tools which can be used to synchronize access to common resources by multiple processes in a concurrent system.

A semaphore **S** is an in integer variable that, apart from initialization, can be accessed only through two **atomic** operations `wait()` and `signal()`. An operation is called atomic if it is performed as one uninterrable unit. Any process making an atomic operation cannot be interrupted and no other process can be scheduled in its place.

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
Each semaphore has an integer value and a list of processes waiting on it. A `signal()` operation removes a process from the waiting list and places it in the ready queue, to be eventually scheduled by the scheduer. `A wait()` operation blocks a process if the value is not positive, and adds it to the list of processes. These operations are defined as follows:

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
        process p = remove_from_list(S->list);
        wakeup(p);  // bring the process to ready queue 
    }
}
```

POSIX semaphores can be created using `sem_open()` or the `sem_init()` functions. `sem_open()` creates a named semaphore, and a semaphore thus created in a process is shared among all child processes of that parent. `sem_init()` creates an unnamned semaphore and needs to be located in a region of shared memory if used among between parent and chlidren processes.

```
/* create a semaphore with name "Sema" and initial value 1
    0644 defines the permission placed on the semaphore, rw-r--r-- in this case */

sem_t *semaph = sem_open ("Sem", O_CREAT | O_EXCL, 0644, 1); 
```

`sem_wait()` performs the wait operation on the semaphore and `sem_post()` performs the signal operation.


## The Producer Consumer Problem using Semaphores

The problems with the naive implementation of the Producer-Consumer problem was discussed earlier. It can be solved using semaphores. The producer and consumer processes need to share to following:

```
    int n;
    buffer[BUF_SIZE];
    semaphore mutex = 1, empty = n, full = 0;
```
The `empty` and `full` semaphores count the number of empty and full slots in the buffer, and `mutex` is for ensuring mutual exclusion for access to the shared buffer

| Structure of producer process: | Structure of consumer process: |
|:-------------------------------|------------------------------- |
| ```                            |```                             |
| do                             |do                              |
| {                              |{                               |
|     wait(empty);               |    wait(full);                 |
|     wait(mutex);               |    wait(mutex);                |
|     . . .                      |    . . .                       |
|     /* add item to buffer */   |    /* remove from buffer */    |
|     . . .                      |    . . .                       |
|     signal(mutex);             |    signal(mutex);              |
|     signal(full);              |    signal(empty);              |
| }                              |}                               |
| ```                            |```                             |
