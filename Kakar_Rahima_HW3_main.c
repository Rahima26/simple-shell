/**************************************************************
* Class:  CSC-415-01 Fall 2022
* Name: Rahima Kakar
* Student ID:916192269
* GitHub ID:rahima26
* Project: Assignment 3 – Simple Shell
*
* File: Kakar_Rahima_HW3_main.c
*
* Description: we are creating a simple shell that runs on top of a regular command-line interpreter for LINUX
*
**************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>

// function to read command
void readCmd(char cmd[], char*par[]){
//saves user input into command line
if(fgets(cmd, 1440, stdin)){
//size of input string
size_t length = strlen(cmd);
if(cmd[length -1] == '\n'){
//if end of line then null terminate
cmd[length -1] = '\0';
}

char*token;
//tokenize the string using space delimiter
token = strtok(cmd, "");
int i = 0;
while (token != NULL){
par[i] = token;
token = strtok(NULL, "");
i++;
}
par[i] = NULL;
} else {
//end of file
exit(0);
}
}

//init errno  this we use for error status
extern int errno;

int main(){
//str input with buffer size as specified in program
char commandLine[1440];

//args we pass in prompt
char*args[100];

//path variable execvp()
char*path = "/bin/";
char fullPath[20];

while(1){
printf("prompt$ ");
char temp_user_input_str[50];

//read input from user
readCmd(commandLine, args);

//if user enters exit quit the program
if(strcmp(commandLine, "exit") == 0)
{
break;
}

//init pid type pid_y
pid_t childProcessID;

//create child
int pid = fork();

int stat; //exit status

//child
if(pid == 0){
//child process running
//copy "/bin/" to full path
strcpy(fullPath, path);
//concat path with args
strcat(fullPath, args[0]);
if(execvp(fullPath, args) < 0 ) { //if execvp fails
	printf("Invalid input failed. Exit with error %d\n",  (errno));
	exit(2);
}
} else {
//wait for parent
childProcessID = wait(&stat);
if (WIFEXITED(stat)) {
//print child ID and return status
printf("Child%d, exited with %d\n,", childProcessID, WEXITSTATUS(stat));
}
}
}
return 0;
}
