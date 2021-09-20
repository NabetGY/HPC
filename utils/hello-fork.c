//Padre con 3 hijos
#include <stdio.h>
#include <unistd.h>
main(void)
{
    pid_t pid;
    int x;
    
    for(x=1;x<=3;x++)
    {
        pid=fork(); 
        if(pid)
        {
            printf("Soy el proceso %d\n",getpid());
            sleep(2);
        }
        else
        {
            printf("soy el hijo %d, mi padre es %d\n",getpid(),getppid());
            sleep(2);
            exit(0);
        }   
    }
    return 0;
}