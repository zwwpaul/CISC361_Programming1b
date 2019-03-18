#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>
#include<fcntl.h>
#include<sys/types.h>
#include <sys/stat.h>

#define PERMISSION 0666
#define BUFFERSIZE 4096
#define BUFFERCHAR 128
int main(int argc,char *argv[]){
char* notification;
char* file1=argv[1];
char* file2=argv[2];
int src, dst,length,i,len;
int buf[BUFFERSIZE];
//To examine whether the number of arguements are correct
if(file1==NULL || file2==NULL){
	printf("Error: One of the file cannot be accessed!\n");
	exit(1);
}
if(argc!=3){
	printf("Error: The number of arguements is not correct!\n");
	exit(2);
}

//If the source file doen't exist, release all the memory and exit the program.
if(access(file1,F_OK)<0){
	printf("Error: The source file doesn't exist!!\n");
        exit(3);
}else{
//This is the senario source file exists.
	if(access(file2,F_OK)==0){
		notification = malloc(sizeof(char));
		printf("Would you like to overwrite this file? (yes / no): \n");
		if(fgets (notification, BUFFERCHAR, stdin)!=NULL){
			len=strlen(notification);
                        notification[len-1]='\0';
		}
		if(strcmp(notification, "yes") == 0){
			printf("File has been overwriten! \n");
		}
		if(strcmp(notification,"no")==0){
			printf("Will not process overwriting! \n");
			free(notification);
			exit(0);
                }
	}else{
		printf("Destination file has been created!\n");
	}	
}
//To control two files have the same permission.
struct stat fileStat;
if(stat(argv[1],&fileStat) < 0){
	return 1;
}
src=open(file1,O_RDONLY);
dst=open(file2, O_TRUNC | O_RDWR | O_CREAT,fileStat.st_mode);
while(length=read(src,buf,BUFFERSIZE)){
i=write(dst, buf, length);
}
close(src);
close(dst);
free(notification);
printf("SUCCESS!\n");
return 0;
}
