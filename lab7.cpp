#include <unistd.h>
#include <iostream>
#include <pthread.h>
#include <fstream>

#define PT_NUM 9

using namespace std;

pthread_rwlock_t lock = PTHREAD_RWLOCK_INITIALIZER;

void* wr(void *arg)
{ 
     int str = 1;
     char buffer[80];
     
     while(1)
     {
        pthread_rwlock_wrlock(&lock);
        time_t seconds = time(NULL);
        tm* timeinfo = localtime(&seconds);
        const char* format = "%A, %B %d, %Y %I:%M:%S";
        setlocale(LC_ALL, "");
        strftime(buffer, 80, format, timeinfo);
        cout << "Поток записи: " << pthread_self() << endl;
        ofstream file("Время.txt", ios::app);
        file << "Строка: " << str << ", ";
        file << "дата: " << buffer << endl;
        file.close();
        str++;
        pthread_rwlock_unlock(&lock);
	sleep(1);
     }
     
     pthread_exit(0);
}

void* rd(void *arg)
{
     char buffer[80];
     
     while(1)
     {
        
        pthread_rwlock_rdlock(&lock);
        ifstream file("Время.txt");
        cout << "Поток чтения: " << pthread_self() << endl;
        while (!file.eof())
        {
            file.getline(buffer, 80);
            cout << buffer << endl;
        }
        file.close();
        pthread_rwlock_unlock(&lock);
	sleep(1);
     }
     
     pthread_exit(0);
}

int main (int argc, char* argv[])
{
	pthread_t read [PT_NUM];
        pthread_t write;

        pthread_rwlock_init(&lock, NULL);
        
        pthread_create(&write, NULL, wr, NULL);
	for (int i = 0; i<PT_NUM; ++i)
	{
	       pthread_create(&read[i], NULL, rd, NULL);
	}
                
        pthread_join(write, NULL);
        for (int i = 0; i<PT_NUM; ++i)
	{
               pthread_join(read[i], NULL); 
	}

        pthread_rwlock_destroy(&lock);
        
	return 0;
}
