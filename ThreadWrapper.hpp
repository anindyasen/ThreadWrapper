#include <iostream>
#include <stdio.h>
#include <unistd.h>
#include <thread>
#include <boost/thread/barrier.hpp>

struct threadArg{
    int i;
};

class ThreadWrapper{
private:
    std::thread thread;
    bool bShouldThreadRun;
    boost::barrier* thread_barrier;
public:
    ThreadWrapper(boost::barrier* cur_barrier){
        thread_barrier = cur_barrier;
    }
    ~ThreadWrapper(){}
    void ThreadStart(){
        SetThreadRun();
        thread = std::thread(ThreadWrapper::ThreadHandler,this);
    }
    void ThreadJoin(){
        if(thread.joinable())
            thread.join();
    }
    static void ThreadHandler(ThreadWrapper *ptr){
        ptr->init();
        printf("Waiting in Barrier\n");
        ptr->thread_barrier->wait();
        printf("Barrier Wait Over\n");
        while(ptr->bShouldThreadRun){
            ptr->body();
            //bShouldThreadRun = 0;
        }
        ptr->fini();
    }
    void SetThreadRun() {
        bShouldThreadRun = 1;
    }
    void UnsetThreadRun() {
        printf( "Unset\n");
        bShouldThreadRun = 0;
    }
    virtual void init() = 0;
    virtual void body() = 0;
    virtual void fini() = 0;
};

class NewThread1 : public ThreadWrapper{
private:
    struct threadArg var;
public:
    NewThread1(int i,boost::barrier* cur_barier):ThreadWrapper( cur_barier){
        var.i = i;
    }
    int GetThreadVar(){
        return var.i;
    }
    void init(){
        printf("Initialize Reciver %d\n",GetThreadVar());
    }
    void body(){
        printf("Reciver Body\n");sleep(1);
    }
    void fini(){
        printf("Finalize Reciver\n");
    }
};

class NewThread2 : public ThreadWrapper{
private:
    struct threadArg var;
public:
    NewThread2(int i,boost::barrier* cur_barier):ThreadWrapper( cur_barier){
        var.i = i;
    }
    int GetThreadVar(){
        return var.i;
    }
    void init(){
        printf("Initialize Router %d\n",GetThreadVar());
    }
    void body(){
        printf("Router Body\n");sleep(1);
    }
    void fini(){
        printf("Finalize Router\n");
    }
};

class NewThread3 : public ThreadWrapper{
private:
    struct threadArg var;
public:
    NewThread3(int i,boost::barrier* cur_barier):ThreadWrapper( cur_barier){
        var.i = i;
    }
    int GetThreadVar(){
        return var.i;
    }
    void init(){
        printf("Initialize Filter %d\n",GetThreadVar());
    }
    void body(){
        printf("Filter Body\n");sleep(1);
    }
    void fini(){
        printf("Finalize Filter\n");
    }
};

class NewThread4 : public ThreadWrapper{
private:
    struct threadArg var;
public:
    NewThread4(int i,boost::barrier* cur_barier):ThreadWrapper(cur_barier){
        var.i = i;
    }
    int GetThreadVar(){
        return var.i;
    }
    void init(){
        printf("Initialize Transmitter %d\n",GetThreadVar());
    }
    void body(){
        printf("Transmitter Body\n");sleep(1);
    }
    void fini(){
        printf("Finalize Transmitter\n");
    }
};

class modules{
private:
    void **arrThread;
    int size;
public:
    modules(){
    }
    ~modules(){
    }
    void CreateThreadArray(int length)
    {
        arrThread = new void*[length];
        size = length;
    }
    void insert(void **arr)
    {
        arrThread = arr;
    }
    void* GetThread(int i)
    {
        return arrThread[i];
    }


};
