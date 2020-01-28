#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

int main(){

	int shmid;
	char name[30];
	pid_t p;

	shmid = shmget(10000);
	printf("ID: %d\n",shmid);
	p = fork();
	if(p==0){
		printf("\tCHILD: \n");
		sleep(2);
		shmread(shmid,name,2,3);
		printf("Name: %s\n",name);

	}
	else{
		printf("Parent\n");
		strcpy(name,"Thomas123");
		shmwrite(shmid,name,2,3);
		wait(NULL);
	}
	return 0;

}
