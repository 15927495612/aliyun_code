
#ifndef MUDUO_BASE_THREADLOCALSINGLETON_H
#define MUDUO_BASE_THREADLOCALSINGLETON_H

#include "noncopyable.h"

#include <assert.h>
#include <pthread.h>


namespace muduo
{
template<typename T>
class ThreadLocalSingleton : noncopyable
{
private:
    static void destrucctor(void* obj)
    {
        assert(obj==t_value_);
        typedef char T_must_be_complete_type[sizeof(T)==0?-1:1];
        T_must_be_complete_type dummy;(void) dummy;
        delete t_value_;
        t_value_ = 0;
    }

    class Deleter
    {
    private:
        /* data */
    public:
        Deleter(/* args */)
        {
            pthread_key_create(&pket_,&ThreadLocalSingleton::destrucctor);

        }
        ~Deleter()
        {
            pthread_key_delete(pkey_);
        }
        void set(T* newObj)
        {
            assert(pthread_getspecific(pkey_)==NULL);
            pthread_setspecific(pkey_,newObj);
        }
    };
    
     
    pthread_key_t pkey_;
    static __thread T* t_value_;
    static Deleter deleter_;
public:
    ThreadLocalSingleton(/* args */) = delete;
    ~ThreadLocalSingleton() = delete;

    static T& instance()
    {
        if (!t_value_)
        {
            t_value_ = new T();
            deleter_.set(t_value_);
            
        }
        return t_value_;
    }

    static T* pointer()
    {
        return t_value_;
    }
};



} // namespace muduo



#endif