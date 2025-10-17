//headers to include:
#include <sys/ipc.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>    // fork
#include <sys/wait.h>  //waitpid
#include <sys/types.h> //open
#include <sys/shm.h>
#include <sys/sem.h>
#include <sys/msg.h>
#include <string.h> 
#include <time.h>
#include <sys/stat.h>
#include <sys/mman.h>   
#include <fcntl.h> //open,creat


// create two children using fork
pid_t child = fork();
    if (child<0) { 
        perror("The fork calling was not succesful\n"); exit(1);
    }
    if(child > 0) { //parent
        pid_t child2 = fork(); // fork again to generate the second child processor
        if (child2 < 0) {
            perror("The fork2 calling was not succesful\n"); exit(1);
        }
        if(child2 > 0) { 
            // parent 
            waitpid(child,&status,0); 
            waitpid(child2,&status,0); 
            //waits the end of child process PID number=child, the returning value will be in status
            //0 means, it really waits for the end of child process - the same as wait(&status)
        } else { 
            // second child
        }
    } else { 
        // first child
    }


// signal handler 
void handler(int signumber){
  printf("Signal with number %i has arrived\n",signumber);
}

// signal, pass data from child to parent
signal(SIGTERM,handler);   
pid_t child=fork();
if (child>0)
{ 
  pause(); //waits till a signal arrive 
  int status;
  wait(&status);
  printf("Parent process ended\n");
}
else 
{
  sleep(3);
  kill(getppid(),SIGTERM);  
}

// unnamed pipe
int pipe_for_child1[2];
    if (pipe(pipe_for_child1) == -1) {
        perror("pipe_for_child1 opening error!");
        exit(EXIT_FAILURE);
    }
    
// write into pipe
close(pipe_for_child2[0]);
write(pipe_for_child2[1], message_to_child2, sizeof(message_to_child2));
close(pipe_for_child2[1]);


//read from pipe
close(pipe_from_child1[1]); // permits to write into pipe.
read(pipe_from_child1[0], &best_of_area1, sizeof(struct contestant));
close(pipe_from_child1[0]);

// message struct 
struct messg { 
    long mtype;
    char getWood[TEXTBUFFER];
}; 

// send massage 

int sendwood(int mqueue)
{ 
    const struct messg m = {5, "Collect 2 bundles of wood\n"};   
    int st;
    st = msgsnd(mqueue, &m, strlen(m.getWood) + 1, 0);
    if (st<0) perror("msgsnd error!");
    return 0; 
} 

// receive message
int receive(int mqueue)
{
    struct messg m;
    int st;
    st = msgrcv(mqueue, &m, TEXTBUFFER, 5, 0);
    if (st<0) perror("msgsnd error!");
    else printf("%s\n", m.getWood);
    return 0;
}

//init message
int messg;
key_t key = ftok(argv[0], 1);

messg = msgget(key, 0600 | IPC_CREAT);
if (messg < 0)
{
    perror("msgget error");
    return 1;
}
