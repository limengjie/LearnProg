#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

/*
exec: 
execv: v is vector (char * path, char * argv[]), 
e.g. execv("/bin/ps", buf), char * buf[] = {"ps", "ajx", NULL}
execl: l is list (char * path, char * arg0, char * arg1, ..., NULL);
e.g. execl("/bin/ps", "ps", "ajx", NULL)
exevp/exelp: p is path, it will search the executable file from the path defined in $PATH 
execpe: e is environment, it can pass environment variables to the new process
*/

int main() 
{
	int pid = fork();
	if (pid == 0) //if return val == 0, child process
	{
		printf("I'm childish.\n");
		//execl("/bin/ls", "ls", "-al", NULL);
		execlp("ls", "ls", "-al", NULL); //alternative
		printf("after exec\n");
	} else {//the parent process will return child's pid
		printf("I'm old and parental. %d\n", getpid());
		wait(NULL);
	}

	return 0;
}
