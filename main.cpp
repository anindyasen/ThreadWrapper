// CPP program to demonstrate multithreading
// using three different callables.
// Compile the code with command : g++ -g -std=c++11 -lboost_system  -pthread -lboost_thread main.cpp
#include <signal.h>
#include "ThreadWrapper.hpp"
using namespace std;

void SigHandler(int signum);
modules module4;
int ThreadShouldRun = 1;

void InitializeFourThread()
{
    module4.CreateThreadArray(4);
    int i =0;
    void **arr = new void*[4];
    boost::barrier thread_barrier(4);
    NewThread1 *thread1 = new NewThread1(100,&thread_barrier);
    NewThread2 *thread2 = new NewThread2(200,&thread_barrier);
    NewThread3 *thread3 = new NewThread3(300,&thread_barrier);
    NewThread4 *thread4 = new NewThread4(400,&thread_barrier);
    arr[0] = thread1;
    arr[1] = thread2;
    arr[2] = thread3;
    arr[3] = thread4;
    module4.insert(arr);
   /* 
    thread1->ThreadStart();
    sleep(1);
    thread2->ThreadStart();
    sleep(1);
    thread3->ThreadStart();
    sleep(1);
    thread4->ThreadStart();
    sleep(1);
*/
    for(i = 0; i<4;i++)
    {
        switch(i)
        {
            case 0:
                ((NewThread1*)(module4.GetThread(i)))->ThreadStart();
                sleep(1);
                break;
            case 1:
                ((NewThread2*)(module4.GetThread(i)))->ThreadStart();
                sleep(1);
                break;
            case 2:
                ((NewThread3*)(module4.GetThread(i)))->ThreadStart();
                sleep(1);
                break;
            case 3:
                ((NewThread4*)(module4.GetThread(i)))->ThreadStart();
                sleep(1);
                break;
        }
    }

}

int main(int argc, char** argv)
{
    int noOfThreads = 0, i=0;
    if(argc > 1)
    {
        noOfThreads = atoi(argv[1]);
    }
    else
    {
        printf("Please Enter No of Thread\n");
        return 0;
    }

    if(signal(SIGINT, SigHandler) == SIG_ERR)
    {
        cout << "Faliure in catching SIG_INT\n";
    }

    switch(noOfThreads)
    {
        case 1:
        case 2:
        case 3:
        case 4:
              InitializeFourThread();
              break;
    }

    sleep(2);
    while(ThreadShouldRun)
    {
        sleep(1);
    }
    return 0;
}

void SigHandler(int signum)
{
    int i = 0;
    if(signum == SIGINT)
    {
        for(i = 0; i<4;i++)
        {
            switch(i)
            {
                case 0:
                    ((NewThread1*)(module4.GetThread(i)))->UnsetThreadRun();
                    ((NewThread1*)(module4.GetThread(i)))->ThreadJoin();
                    break;
                case 1:
                    ((NewThread2*)(module4.GetThread(i)))->UnsetThreadRun();
                    ((NewThread2*)(module4.GetThread(i)))->ThreadJoin();
                    break;
                case 2:
                    ((NewThread3*)(module4.GetThread(i)))->UnsetThreadRun();
                    ((NewThread3*)(module4.GetThread(i)))->ThreadJoin();
                    break;
                case 3:
                    ((NewThread4*)(module4.GetThread(i)))->UnsetThreadRun();
                    ((NewThread4*)(module4.GetThread(i)))->ThreadJoin();
                    break;
            }
        }
        ThreadShouldRun = 0;
    }
}

