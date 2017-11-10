# Producer Consumer Problem using Semaphores

## Overview:

The producer consumer problem also known as the bounded buffer problem is a classic example of a multi-process synchronization problem. The problem invloves two processes, the producer and the consumer. Both these processes share a common, fixed-size buffer. The producer's job is to "produce", i.e., generate data, put it into the buffer and start again. At the same time, the consumer is "consuming", i.e., removing data from the buffer one at a time. The problem is to make sure that the producer won't try to add data into the buffer if it's full and that the consumer won't try to remove data from an empty buffer.

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

`while (true)`
`{
  /* consume an item from out */`
  `while (counter == 0); // loop until buffer has an item`
  
  `consumed_item = buffer[out];`
  `in = (in+1)%BUFFER_SIZE;`
  `counter--;`
`}`
`
