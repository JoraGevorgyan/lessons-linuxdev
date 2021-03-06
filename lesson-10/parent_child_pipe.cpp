#include <iostream>
#include <unistd.h>
#include <cstdlib>
#include <sys/types.h>
#include <cerrno>
#include <cstring>
#include <sys/wait.h>

int main(){

	// create array to keep pipe descriptors
	int pipefd[2];

	// create pipe
	int pipeResult = pipe(pipefd);

	// check if failed
	if(pipeResult != 0){
		exit(errno);
	}

	// the string to send
	const char* str = "Hello World";

	// size of string to write
	int size = strlen(str);

	// create a process
	int child = fork();

	// exit on failure
	if(child == -1){
		exit(errno);
	}

	if(child == 0){

		char* buffer = new char[size + 1];
		std::cout << "Entered child process ..." << std::endl;	
	
		close(pipefd[1]);
		int readBytes = read(pipefd[0], buffer, size + 1); 

		std::cout << "Got text from parent: " << buffer << std::endl;
		
		delete [] buffer;
	}
	else {
		sleep(5);
		close(pipefd[0]);
		int written = write(pipefd[1], str, size + 1);		
		wait(NULL);
	}

	return 0;
}
