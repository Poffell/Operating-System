#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <string.h>
#include <fcntl.h>
#include <time.h>
#include <errno.h>

#define BUFFER_SIZE 100
#define MEM_SIZE    50

int main (void)
{
	key_t key;
	int fd;
	int shmid, id = 1523; 
	char *shm, buffer[BUFFER_SIZE], fifoBuf[BUFFER_SIZE];
	time_t t;

	if ((mkfifo("file" , 0744)) < 0)
		perror("Файл уже создан!");
	
	if ((fd = open("file", O_RDWR)) < 0)
		perror("Ошибка открытия файла!");
	
	if ((key = ftok("file", id)) == (key_t)-1)
		perror("Ошибка создания ключа!"); 

	if ((shmid = shmget(key, MEM_SIZE, IPC_CREAT | IPC_EXCL | 0666)) < 0)
	{
		if (errno == EEXIST)
		{		
			if ((shmid = shmget(key, MEM_SIZE,  0666)) < 0)
				perror("Ошибка доступа!");
		}else
		{
			perror("Ошибка доступа!");
		}
	}
	
	if ((shm = shmat(shmid, NULL, 0)) == (char*)-1)
		perror("Ошибка присоединения!");

	while(1)
	{
		while (read(fd, fifoBuf, BUFFER_SIZE) <= 0)
			usleep(700);

		sleep(2);
		printf("Клиент читает из FIFO:\n");
		printf("%s\n\n", fifoBuf);
		
		write(fd, fifoBuf, strlen(fifoBuf));
		memcpy(buffer, shm, strlen(shm));
		printf("Клиент читает из разделяемой памяти:\n");
		printf("%s\n\n", buffer);

		sleep(4);
		time(&t);
		sprintf(buffer, "Процесс: %x,\tДата: %s\n", getpid(), ctime(&t));
		
		if (write(fd, fifoBuf, strlen(fifoBuf)) < 0)
			perror("Ошибка записи!");
		
		memcpy(shm, buffer, strlen(buffer));
		printf("\nКлиент записывает в файл\n");	
		
	}
	return 0;
}
