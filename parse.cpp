/* FILE: parse.hpp
 * AUTHOR: Bryant Matt && STEPHEN LAMALIE
 * COURSE: COP4634
 * ASSIGNMENT: PROJECT 1 / myShell
 */
 
 #include "parse.hpp"
 
Parse::Parse()
{
	// holds the value of input redirect without the "<"
	inputRedirect = NULL;

	// holds the value of the output redirect without the ">"
	outputRedirect = NULL;

	// the number of arguments to be parsed.
	argumentCount = 0;

	// states if the process needs to be ran in the backround.
	// 0 for forground and a 1 sets to background
	background = 0;
}

/**
Compares first parameter to quit char array to know if to exit.

 @return 1 if command is quit, 0 if another command, 2 if no command
*/
int Parse::getFirstArg()
{
	//Char array to compare first parameter to
	char quit[] = "exit";
	if (argumentVector[0] != NULL)
	{
		if (strcasecmp(quit, argumentVector[0])==0)
		{
			return 1;
		}
		
		return 0;
	}
	else 
	{
		return 2;
	}
}

/* functioin to return the status of the backround as an int
 * retrun value of 1 will indicate process needs to run in backround
 */
int Parse::getBackround()
{
	return background;
}
/**
Parse user shell command in tokens
@param buf user inputted shell command 
*/
void Parse::parseInput(char *buf)
{
	//Houses char array pointer
	char* pChar;
	
	pChar = strtok(buf, " \t\n");  //pChar is the first token to be parsed, it will tell us if it will be a special token.

	while (pChar != NULL)
	{
		//Logic to check for input/output redirection or background character
		if (pChar[0] == '<') 
		{
			inputRedirect = (pChar + 1);
		}
		else if (pChar[0] == '>') 
		{
			outputRedirect = (pChar + 1);
		}
		else if (pChar[0] == '&')
		{
			background = 1;
		}
		else 
		{
		/* if its not a special character, the token is added to the argument vector
		 * and the argument count is incremented
		 */
			argumentVector[argumentCount] = pChar;
			argumentCount++;
		}
		
		pChar = strtok(NULL, " \n");
	}
}

/**
Prints variables apart of Param object
*/
void Parse::printParams()
{ 
	std::cout << "InputRedirect: [" <<
		((inputRedirect!=NULL) ? inputRedirect : "NULL") << "]" <<std::endl<<
		"OutputRedirect:[" <<
		((outputRedirect != NULL) ? outputRedirect : "NULL") << "]" << std::endl <<
		"Background: [" << background << "]" << std::endl <<
		"ArgumentCount: [" << argumentCount << "]" << std::endl;
	 
	for (int i = 0; i < argumentCount; i++)
	{
		std::cout << "ArgumentVector[" << i << "]: [" << argumentVector[i] << "]" << std::endl; 
	}
}
/*
 * refresh method that reverts all the parse objects fields back to NULL
 *
 */
void Parse::refresh()
{
	inputRedirect = NULL;
	outputRedirect = NULL;
	argumentCount = 0;
	background = 0;
	for(int i = 0; i < MAXARGS; i++)
	{
		argumentVector[i]= NULL;
	}
}

/**
 Runs command from tokened string, and sets apporiate input and output
*/
void Parse::execute() 
{
	if (inputRedirect != NULL) {
		freopen(inputRedirect, "r", stdin);
	}
	if (outputRedirect != NULL)
	{
		freopen(outputRedirect, "w+", stdout);
	}
	execvp(argumentVector[0], argumentVector);
}
