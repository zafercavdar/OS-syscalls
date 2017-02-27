#include <sys/types.h> 
#include <stdio.h> 
#include <unistd.h> 
 

int main(){ 
	pid_t child; 
  	child = fork();
	int i= 0;

	if (child == 0) {
		system("gnome-calculator");
  	}
  	else if (child > 0) { 
		sleep(2);
		kill(child,0);
		printf("Parent says: Child PID: %d\n", child);
		printf("Parent says: My PID: %d\n", getpid());
		exit(0);
	}

  return 0; 
} 
