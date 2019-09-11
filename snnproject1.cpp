// snnproject1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include <cstring>
#include <stdio.h>
#include <iostream>
#include <unistd.h>

#define MAXARGS 32



class Param {
private:char* inputRedirect;           /* file name or NULL */
		char* outputRedirect;          /* file name or NULL */
		int  background;               /* either 0 (false) or 1 (true) */
		int  argumentCount;            /* number of tokens in argument vector */
		char* argumentVector[MAXARGS]; /* array of strings */
		
	public : 

		Param() {
			
		}

		Param(std::string in) {
			char* pChar;
			argumentCount = 0;
			background = 0;

			char* buf = &in[0];

			pChar = strtok(buf, " \t");

			while (pChar != NULL)
			{
				if (pChar[0] == '<') {
					inputRedirect = (pChar + 1);
				}
				else if (pChar[0] == '>') {
					outputRedirect = (pChar + 1);
				}
				else if (pChar[0] == '&')
				{
					background = 1;
				}
				else {
					argumentVector[argumentCount] = pChar;
					argumentCount++;
				}
				pChar = strtok(NULL, " \n");


			}
		}

		int getFirstArg()
		{
			char quit[] = "quit";
			if (argumentVector[0] != NULL)
			{
				if (strcmp(quit, argumentVector[0])==0)
				{
					return 1;
				}
				return 0;
			}
			else {
				return 2;
			}

			
		}

		int parseInput(char *buf) {
			char* pChar;
			argumentCount = 0;
			background = 0;

			pChar = strtok(buf, " \t\n");

			while (pChar != NULL)
			{
				if (pChar[0] == '<') {
					inputRedirect = (pChar + 1);
				}
				else if (pChar[0] == '>') {
					outputRedirect = (pChar + 1);
				}
				else if (pChar[0] == '&')
				{
					background = 1;
				}
				else {
					argumentVector[argumentCount] = pChar;
					argumentCount++;
				}
				pChar = strtok(NULL, " \n");
			}

			return 0;

			
		}

		void printParams() 
		{ 
			std::cout << "InputRedirect: [" <<
				((inputRedirect!=NULL) ? inputRedirect : "NULL") << "]" <<std::endl<<
				"OutputRedirect:[" <<
				((outputRedirect != NULL) ? outputRedirect : "NULL") << "]" << std::endl <<
				"Background: [" << background << "]" << std::endl <<
				"ArgumentCount: [" << argumentCount << "]" << std::endl; 
			for (int i = 0; i < argumentCount; i++)
				std::cout << "ArgumentVector[" << i << "]: [" << argumentVector[i] << "]" << std::endl; 
		}
};

int main(int argc, const char* argv[])
{	
	char debug[] = "-Debug";


	//execl("/bin/ls", "ls", "-l", (char*)NULL);

	Param p = Param();
	while (p.getFirstArg()!=1)
	{
		char buf[256];
		std::cout << "$$$ ";
		fgets(buf, 256, stdin);

		p.parseInput(buf);
		if (argc > 1)
		{
			if (strcmp(debug, argv[1]) == 0)
			{
				p.printParams();
			}
		}
		
		
	}
}
