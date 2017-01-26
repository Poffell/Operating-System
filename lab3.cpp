#include <stdio.h>
#include <iostream>
#include <pthread.h>

#define PT_NUM 10

using namespace std;

struct fib
{
	long double f_num;
	long double s_num;
};

void* formula_fib (void* arg)
{
	struct fib thr_num;
	thr_num.f_num = 0;
	thr_num.s_num = 1;
		
	long double new_num = 0, i = 0;
	for (i; i<99; i++)
	{
		new_num = thr_num.f_num + thr_num.s_num;
		printf("%.Lf ", thr_num.f_num);
		thr_num.f_num = thr_num.s_num;
		thr_num.s_num = new_num;
	}
	cout << endl << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
	pthread_exit(0);
}

int main (int argc, char* argv[])
{
	pthread_t threads [PT_NUM];

	for (int i = 0; i<PT_NUM; ++i)
	{
                cout << i+1 << " поток" << endl;
		pthread_create(&threads[i], NULL, formula_fib, &i);
                pthread_join(threads[i], NULL);
	}
	return 0;
}
