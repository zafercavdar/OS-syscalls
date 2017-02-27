#include <sys/types.h>
#include <sys/time.h>
#include <sys/wait.h>

#include <stdio.h> 
#include <unistd.h> 
#include <string.h>
#include <stdlib.h>
 
#define READ_END 0
#define WRITE_END 1
#define BUFFER_SIZE 25
#define SLEEP_TIME 1


int main(void){ 
	pid_t childB, childC, wpid; 
	int fd[2]; // pipe between A and B
	int fd2[2]; // pipe between B and C

	char read_message[BUFFER_SIZE];
	char write_msg[BUFFER_SIZE] = "A";

	struct timeval tv;
	time_t nowsec,nowusec;

	if (childB == 0) {
		close(fd[WRITE_END]);
		read(fd[READ_END], read_message, BUFFER_SIZE);
		printf("ProcessB says(received from parent A): Time of day is %s\n", read_message);
		close(fd[READ_END]);

		sleep(SLEEP_TIME);

		childC = fork();
		
		if (childC == 0) { 
			close(fd2[WRITE_END]);
			read(fd2[READ_END], read_message, BUFFER_SIZE);
			printf("ProcessC says(received from parent B): Time of day is %s\n", read_message);
			close(fd2[READ_END]);

			sleep(SLEEP_TIME);
			close(fd2[READ_END]);
			write(fd2[WRITE_END], write_msg, strlen(write_msg) +1);
			close(fd2[WRITE_END]);

		} else{
			wait(NULL);
		
			close(fd2[WRITE_END]);
			read(fd2[READ_END], read_message, BUFFER_SIZE);
			printf("ProcessB says(received from child C): Time of day is %s\n", read_message);
			close(fd2[READ_END]);

			sleep(SLEEP_TIME);
			close(fd[READ_END]);
			write(fd[WRITE_END], write_msg, strlen(write_msg) + 1);
			close(fd[WRITE_END]);
			//kill(childC,0);
		}

  	}
	else if (childB > 0){
		childB = fork();
		close(fd[READ_END]);

		/*gettimeofday(&tv, NULL);
		nowsec = tv.tv_sec;
		nowusec = tv.tv_usec;
		printf ("%ld.%06ld\n", nowsec, nowusec);*/
		
		write(fd[WRITE_END], write_msg,strlen(write_msg) + 1);
		close(fd[WRITE_END]);
		wait(NULL);

		close(fd[WRITE_END]);
		read(fd[READ_END], read_message,BUFFER_SIZE);
		printf("ProcessA says(received from child B): Time of day is %s\n", read_message);
		close(fd[READ_END]);
		//kill(childB,0);
	}

  return 0; 
} 
