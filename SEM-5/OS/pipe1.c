/*
TELEPHONIC CALL WITH PIPES
LOG FILES CREATED	

AUTHOR: SOUMYADEEP THAKUR
DATE: 6 NOV 2017
B.C.S.E - II, JADAVPUR UNIVERSITY
*/


#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>
#define BUFFER 128
#define LENGTH_OF_CALL 32
/* Write COUNT copies of MESSAGE to STREAM, pausing for a second
between each. */


FILE *caller_log;
FILE *receiver_log;
void sig_handler(int signo)
{
    if (signo ==  SIGINT)
    {
    	printf("*****CLOSING OG FILES*****\n");
    	fclose (caller_log);
    	fclose (receiver_log);
        printf("Exiting!\n");
        _exit(EXIT_FAILURE);   
    }
}
void writer (const char* message, int count, FILE* stream, FILE* logfile)
{
    // Write the message to the stream, and send it off immediately.
    //printf("Writer %p\n", stream);
    fprintf (logfile, "Sent: %s\n", message); // SEGFAULT
    fprintf(stream, "%s\n", message);
    fflush (stream);
    /* Snooze a while. */
    //sleep (1);
       
}
/* Read random strings from the stream as long as possible.
*/
void reader (FILE* stream, FILE* logfile)
{
    char buffer[BUFFER];
    /* Read until we hit the end of the stream. fgets reads until
    either a newline or the end-of-file. */
    while (!feof (stream) && !ferror (stream) && fgets (buffer, sizeof (buffer), stream) != NULL)
    {
        fputs (buffer, stdout);
        if (strcmp(buffer,""))
        	fprintf(logfile, "Received: %s\n", buffer);
    }
}
int main ()
{
    int fds_c2r[LENGTH_OF_CALL][2];
    int fds_r2c[LENGTH_OF_CALL][2]; 
    pid_t pid; int i;
	char msg[BUFFER];
	caller_log = fopen("caller_logs.txt", "w");
	receiver_log = fopen("receiver_logs.txt", "w");
    if (signal(SIGINT, sig_handler) == SIG_ERR)
    printf("\ncan't catch SIGINT\n");
    // Create a pipe. File descriptors for the two ends of the pipe are placed in fds.
    for (i=0; i<LENGTH_OF_CALL; i++) pipe (fds_c2r[i]);
    for (i=0; i<LENGTH_OF_CALL; i++) pipe (fds_r2c[i]);
    /* Fork a child process. */
    pid = fork ();
    if (pid == (pid_t) 0) 
    {
        FILE *stream1, *stream2;
        // This is the child process. Close our copy of the write end of the file descriptor.
        int no1=0;
        while(no1 < LENGTH_OF_CALL)
        {
            close (fds_c2r[no1][1]); 
            // Convert the read file descriptor to a FILE object, and read from it.
            stream1 = fdopen (fds_c2r[no1][0], "r");
            reader (stream1, receiver_log);
            close (fds_c2r[no1][0]);

            close (fds_r2c[no1][0]);

            stream2 = fdopen (fds_r2c[no1][1], "w");
            //printf("%d - ",getpid());
            printf("Receiver: \n");
            fgets(msg, BUFFER-1, stdin);
            writer (msg, 1, stream2, receiver_log);
            close (fds_r2c[no1][1]);
            no1++;
        }
    }
    else    
    {
        /* This is the parent process. */
        //CALLER
        FILE *stream1, *stream2;
        int no2=0;
        while (no2 < LENGTH_OF_CALL)
        {
            /* Close our copy of the read end of the file descriptor. */
            close (fds_c2r[no2][0]);
            // Convert the write file descriptor to a FILE object, and write to it.
            stream1 = fdopen (fds_c2r[no2][1], "w");
            printf("Caller: \n");
            fgets(msg, BUFFER-1, stdin);
            writer(msg, 1, stream1, caller_log);
            printf("Msg read\n");
            close (fds_c2r[no2][1]);

            close (fds_r2c[no2][1]);

            stream2 = fdopen (fds_r2c[no2][0], "r");
            reader(stream2, caller_log);
            close(fds_r2c[no2][0]);
            //pipe(fds_r2c);
            //pipe(fds_c2r);
            no2++;
        }
    }

    fclose(caller_log);
    fclose(receiver_log);
    return 0;
}
