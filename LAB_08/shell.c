/*
CE007 :: Devang Bhalala
Linux shell program
*/

#include<stdio.h> 
#include<string.h> 
#include<stdlib.h> 
#include<unistd.h> 
#include<sys/types.h> 
#include<sys/wait.h> 
#include<readline/readline.h> 
#include<readline/history.h> 

#define WRDMAX 50 
#define CMDLENMAX 500 

int getIpstr(char* ipstrarg) 
{ 
	char* line; 
    char cwd[512]; 
	getcwd(cwd, sizeof(cwd)); 
	printf("\n%s", cwd);

	line = readline(" $ "); 
	if (strlen(line) != 0) { 
		add_history(line); 
		strcpy(ipstrarg, line); 
		return 0; 
	} else { 
		return 1; 
	} 
} 

void executeCmdWithoutPipe(char** parBeforePipeArg) 
{ 
	int pid = fork(); 
    int wst;
	if (pid == -1) { 
		printf("\nError while creaating the child.\n"); 
		return; 
	} else if (pid == 0) { 
		if (execvp(parBeforePipeArg[0], parBeforePipeArg) < 0) { 
			printf("\nError while executing the command."); 
		} 
		exit(0); 
	} else { 
		wait(&wst); 
		return; 
	} 
} 

void executeCmdWithPipe(char** parBeforePipeArg, char** parAfterPipeArg) 
{ 
    int pid1, pid2, wst, pret, pipefd[2];
    pret = pipe(pipefd); 
	if (pret < 0) { 
		printf("\nError while creating the pipe.\n"); 
		return; 
	} 

	pid1 = fork(); 
	if (pid1 < 0) { 
		printf("\n1_Error while creaating the child."); 
		return; 
	} 

	if (pid1 == 0) { 
		close(pipefd[0]); 
		dup2(pipefd[1], STDOUT_FILENO);     
		close(pipefd[1]);   

		if (execvp(parBeforePipeArg[0], parBeforePipeArg) < 0) { 
			printf("\n1_Error while executing the command."); 
			exit(0); 
		} 
	} else { 
		pid2 = fork(); 

		if (pid2 < 0) { 
			printf("\n2_Error while creaating the child."); 
			return; 
		} 

		if (pid2 == 0) { 
			close(pipefd[1]); 
			dup2(pipefd[0], STDIN_FILENO);
			close(pipefd[0]); 
			
            if (execvp(parAfterPipeArg[0], parAfterPipeArg) < 0) { 
				printf("\n2_Error while executing the command."); 
				exit(0); 
			} 
		} else { 
			wait(&wst); 
			wait(&wst); 
		} 
	} 
} 


int pipeParsingFunc(char* ipstrarg, char** befAftPipeDuoArg) 
{ 

    befAftPipeDuoArg[0] = strsep(&ipstrarg, "|");
    if (befAftPipeDuoArg[0] != NULL){
        befAftPipeDuoArg[1] = strsep(&ipstrarg, "|"); 
    }

	if (befAftPipeDuoArg[1] != NULL) 
		return 1; 
	else { 
		return 0; 
	} 
} 

void wordParsingFunc(char* ipstrarg, char** parPipeArg) 
{ 
	int i; 

	for (i = 0; i < WRDMAX; i++) { 
		parPipeArg[i] = strsep(&ipstrarg, " "); 

		if (parPipeArg[i] == NULL) 
			break; 
		if (strlen(parPipeArg[i]) == 0) 
			i--; 
	} 
} 

int strProcess(char* ipstrarg, char** parBeforePipeArg, char** parAfterPipeArg) 
{ 

	char* befAftPipeDuo[2]; 
	int cmdTypeRet = 0; 

	cmdTypeRet = pipeParsingFunc(ipstrarg, befAftPipeDuo); 

	if (cmdTypeRet) { 
		wordParsingFunc(befAftPipeDuo[0], parBeforePipeArg); 
		wordParsingFunc(befAftPipeDuo[1], parAfterPipeArg); 

	} else { 

		wordParsingFunc(ipstrarg, parBeforePipeArg); 
	} 

	return cmdTypeRet; 
} 

int main() 
{ 
	char ipstr[CMDLENMAX], *parBeforePipe[WRDMAX]; 
	char* parAfterPipe[WRDMAX]; 
	int cmdType = 0; 
	
    
    printf("\n\n:::Shell:::\n\n"); 

	while (1) { 
		
		if (getIpstr(ipstr)) 
			continue;       
		
		cmdType = strProcess(ipstr, parBeforePipe, parAfterPipe);  

		if(cmdType)
            executeCmdWithPipe(parBeforePipe, parAfterPipe);
        else
            executeCmdWithoutPipe(parBeforePipe); 
	} 
	return 0; 
} 
