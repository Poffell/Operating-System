#include <time.h>
#include <iostream>
#include <unistd.h>
#include <fstream>

using namespace std;

int main()
{
    pid_t pid;
    pid = fork();
    if (pid > 0)
    {
        cout<< "Привет! Я родительский процесс." << endl;
        cout << "Мой PID: " << getpid() << endl;

        ofstream file("Родительский файл.txt");

        if (file ==0)
        {
            cout << "Файл не создан! Ошибка!" << endl;
        }
        else
        {
            cout << "Файл родителя создан успешно!" << endl;
        }
        
        file << "Я родительский процесс!!!";
        file.close();
    }
    
    if (pid == 0)
    {
        cout<<"Привет! Я дочерний процесс." << endl;
        cout << "Мой PID: " << getpid() << ". И PID моего родителя: " << getppid() << endl;

        ofstream file("Дочерний файл.txt");

        if (file ==0)
        {
            cout << "Файл не создан! Ошибка!" << endl;
        }
        else
        {
            cout << "Файл потомка создан успешно!" << endl;
        }
        
        file << "Я дочерний процесс!!!";
        file.close();
    }
    
    return 0;
}
