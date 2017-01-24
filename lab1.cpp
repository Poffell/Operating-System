#include <time.h>
#include <iostream>
#include <unistd.h>

using namespace std;

int main()
{
    pid_t pid;
    pid = fork();
    if (pid > 0)
    {
        cout<< "Привет! Я родительский процесс." << endl;
        cout << "Мой PID: " << getpid() << endl;
    }
    
    if (pid == 0)
    {
        cout<<"Привет! Я дочерний процесс." << endl;
        cout << "Мой PID: " << getpid() << ". И PID моего родителя: " << getppid() << endl;
    }
    
    return 0;
}
