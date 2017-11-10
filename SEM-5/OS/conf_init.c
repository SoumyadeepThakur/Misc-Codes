// AUTHOR(S):  SOUMYADEEP THAKUR
// DATE: 3 NOV 2017

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

int fd;
void sig_handler(int signo)
{
    if (signo ==  SIGINT)
    {
        printf("\nClosing fifo fie descriptor...\n");
        //close(fd);
        printf("\n*****EXITING CONFERENCE CALL*****\n");
        _exit(EXIT_SUCCESS);   
    }
}

int main()
{
    int i=0, i1, i2;
    char *id_fifo = "/tmp/id_fifo";
    if (signal(SIGINT, sig_handler) == SIG_ERR)
        printf("\ncan't catch SIGINT\n");
    mkfifo(id_fifo, 0666);


    char *cur_id = (char*)malloc(sizeof(char));
    

    while (i<3)
    {
        *cur_id = i;
        fd = open(id_fifo, O_WRONLY);
        i++;
        write (fd, cur_id, strlen(cur_id)+1);
        printf("%d\n", i);
        close (fd);
        sleep(1);
    }
    //close(fd);
    //while(1) {}
    return 0;
}
