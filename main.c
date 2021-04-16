#include<stdio.h>
#include<unistd.h>
#include<signal.h>
int MAX_CHILDREN = 5;
int numChildren = 0;

void sig_handler_parent(int signum)
{
  printf("\nParent: Inside handler function\n");
}
void sig_handler_child(int signum)
{
  printf("\nChild:Inside handler function\n");
}

int main()
{
    int arrPID[MAX_CHILDREN];
    for(int a=0;a<MAX_CHILDREN; a++)
    {
        sleep(1);
        int pid = fork();
        if(pid == 0)
        {
            //child
            numChildren++;
            signal(SIGUSR1,sig_handler_child);
            //pause();
            //printf("\nChild dying\n");
        }
        else
        {
            arrPID[a] = pid;
            //printf("PID: %d", pid);
            sleep(1);
            signal(SIGUSR1,sig_handler_parent);
            while(1)
            {
                //raise(SIGUSR1);
                kill(pid, SIGUSR1);
                sleep(1);
            }
        }
        //signal(SIGINT,sig_handler); // Register signal handler
    }
    for(int a=0;a<MAX_CHILDREN; a++)
    {
        printf("PID: %d\n", arrPID[a]);
    }
}