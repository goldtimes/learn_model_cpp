#include <iostream>
#include <pthread.h>

using namespace std;

static long long total = 0;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

void* func(void *)
{
    long long i;
    for(i = 0; i < 100000000LL; ++i)
    {
        pthread_mutex_lock(&mutex);
        total += i;
        pthread_mutex_unlock(&mutex);
    }
}


int main(int argc, char** argv)
{
    pthread_t thread1, thread2;
    if(pthread_create(&thread1, NULL, &func, NULL))
    {
        throw;
    }
    if(pthread_create(&thread2, NULL, &func, NULL))
    {
       throw; 
    }
    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);
    cout << total << endl;
    return 0;
}