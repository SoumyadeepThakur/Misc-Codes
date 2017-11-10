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

To implement semaphores like this, we need to implement it as:
`
