#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <fcntl.h>

#define READ_END 0
#define WRITE_END 1



int main(){

  pid_t pid;
	
	int pipefd[2];

      

  int fd = open("outfile", O_RDWR | O_CREAT, S_IRUSR | S_IWUSR);
  
  dup2(fd, 1);   // make stdout go to file
  dup2(fd, 2);   
  
  close(fd);
      
	pipe(pipefd);
  
  if ((pid = fork()) == 0) {  //child

    close(pipefd[0]);    // close reading end in the child    
    dup2(pipefd[1], 1);  // send stdout to the pipe
    dup2(pipefd[1], 2);  // send stderr to the pipe    
    close(pipefd[1]); 
    
    execlp("ls", "ls", "-1", NULL);  
  
  } else { // parent


    close(pipefd[1]);  // close the write end of the pipe in the parent
    
    dup2(pipefd[0],0);
    close(pipefd[0]);

    execlp("sort", "sort","-r", NULL);
    
    exit(0);  
  }
  
  return 1;
}