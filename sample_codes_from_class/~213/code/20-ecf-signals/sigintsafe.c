#include "csapp.h"

#ifndef NEW
// Old
void sigint_handler(int sig) /* Safe SIGINT handler */
{
    Sio_puts("So you think you can stop the bomb with ctrl-c, do you?\n");
    sleep(2);
    Sio_puts("Well..."); 
    sleep(1);
    Sio_puts("OK. :-)\n");
    _exit(0);                   
}                              
#endif

#ifdef NEW
#include "sio_printf.h"

void sigint_handler(int sig) /* Safe SIGINT handler */
{
    Sio_printf("So you think you can stop the bomb (process %d) with ctrl-%c, do you?\n",
	       (int) getpid(), 'c');
    sleep(2);
    Sio_puts("Well..."); 
    sleep(1);
    Sio_puts("OK. :-)\n");
    _exit(0);                   
}                              
#endif


int main() 
{
    /* Install the SIGINT handler */         
    if (signal(SIGINT, sigint_handler) == SIG_ERR)
	unix_error("signal error");               
    
    /* Wait for the receipt of a signal */
    pause(); 
    
    return 0;
}
