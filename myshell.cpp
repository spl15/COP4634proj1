
#include "parse.hpp"

int main(int argc, const char* argv[])
{	
	//Char array to compare user command line argument to set mode to Debug
	char debug[] = "-Debug";
	
	//Char array to store user input
	char buf[256];

	//create pid that will fork and be used to control parent/child branching
	pid_t pid;

	//result will hold the return value of waitpid
	pid_t result;

	//int to store that status of the child when calling wait & waitpid
	int status;

	//Create new parse object
	Parse p = Parse();

	while (p.getFirstArg()!=1)
	{
		//Command prompt
		std::cout << "$$$ ";
		fgets(buf, 256, stdin);
		
		//Parse user command
		p.parseInput(buf);
		if (p.getFirstArg() != 1) {
			
			//Debug mode selected print parameters
			if (argc > 1)
			{
				if (strcasecmp(debug, argv[1]) == 0)
				{
					p.printParams();
				}
			}
			//fork process
			pid = fork();
			
			//if child 
			if (pid == 0) {
				p.execute();
				exit(1);
			}
			else {
				//if process needs to run in background
				if (p.getBackround() != 1)
				{
					result = waitpid(pid, &status, 0);
					if(result == -1)
					{
						perror("The following error occured with waitpid: ");
						exit(EXIT_FAILURE);
					}
				}
			}

			
			//reassigns the input, output, and argument vector back to NULL
			p.refresh();
		
		}
		else {
			//if quit command wait for children to exit
			while ((pid = wait(&status)) > 0);
		}
		
				
	}
}

