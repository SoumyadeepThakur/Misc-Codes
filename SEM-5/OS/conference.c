// AUTHOR(S): AISHIK PYNE, SOUMYADEEP THAKUR
// DATE: 3 NOV 2017

// C program to implement one side of FIFO
// This side reads first, then reads
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
// struct message {
//   char username[20];
//   char msg[10];
//   int flag[3];
// }
int main()
{
    int fd, ifd;
    char *id_fifo = "/tmp/id_fifo";
    char* conference_fifo = "/tmp/conference_fifo";
    char *idc = (char*)malloc(sizeof(char));
    mkfifo(conference_fifo, 0666);
    mkfifo(id_fifo, 0666);

    ifd = open(id_fifo, O_RDONLY);
    read(ifd, idc, 1);
    printf("id=%u\n", (unsigned int)(*idc));
    close(ifd);
    printf("Reading closed\n");



    // Accepts username of person
    char username[20];int id;
    id = (int)(*idc);
    printf("I.D = %d\nEnter your username : " ,id);
    fgets (username, 20, stdin);
    username[strlen(username)-1] = ':';
    strcat(username, " ");
    printf("Welcome %s !!\n", username);


    /*
    Fork out a child
    The Parent reads whatever anyone types into the FIFO
    The Child process waits for current user to write to in the FIFO
    */
    pid_t pid = fork();
    char str_rec[123], str_send[100];
    if(pid != 0)
    {
        // Parent process is the reading end of FIFO
        while (1)
        {
            int done=1;
            // First open in read only and read
            fd = open(conference_fifo,O_RDONLY);
            read(fd, str_rec, 123);
            // Print the read string and close
            char flag[3];
            int i;
            for(i=0;i<3;i++)
            {
                flag[i] = str_rec[i];
                if(str_rec[i] == '0')
                    done = 0;
            }
            if(flag[id] == '0')
            {
                if(strlen(str_rec)>1)
                    printf("\n%s\n", str_rec+3);
                str_rec[id] = '1';
            }
            close(fd);
            if(done == 0)
            {
                fd = open(conference_fifo,O_WRONLY);
                write(fd, str_rec, strlen(str_rec)+1);
                close(fd);
            }
        }
    }
    else
    {
        //Child process sends data to FIFO
        while (1) 
        {
            fd = open(conference_fifo,O_WRONLY);
            fgets(str_send, 100, stdin);
            if(strcmp(str_send, "exit") == 0)
                break;
            char msg[123];
            strcpy(msg, "000");
            strcat(msg, username);
            strcat(msg, str_send);
            write(fd, msg, strlen(msg)+1);
            close(fd);
        }
    }
}
