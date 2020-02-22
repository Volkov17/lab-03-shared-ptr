//
// Created by Александр Волков on 04.11.18.
//

#ifndef SHAREDPTR_LAB_SHARED_H
#define SHAREDPTR_LAB_SHARED_H

#include <iostream>
#include <cstdio>
#include <atomic>



template <typename T>
class SharedPtr {
    T*ptr;
    std::atomic_uint* counter = new std::atomic_uint;
public:
    SharedPtr(){
        ptr = nullptr;
        counter = 1;
    }

    explicit SharedPtr(T*p){
        ptr = p ;
        ++(*counter);
    }

    ~SharedPtr(){
        if ( counter != nullptr ){
            --(*counter);
            if ( (*counter) == 0){
                delete ptr;
                delete counter;
                std::cout<< "bye" <<std::endl;
            }
        }
    }

    SharedPtr(const SharedPtr& r){
        ptr = r.ptr;
        counter = r.counter;
        if ( counter != nullptr ) {
            ++(*counter);
        }
    }

    SharedPtr(SharedPtr&& r){
        ptr = std::move(r);
        counter = std::move(r);
        if ( counter != nullptr ) {
            ++(*counter);
        }
    }

    SharedPtr& operator=(const SharedPtr& r) {

        /*
        if (*(--counter) != 0) {
            if (ptr != nullptr) {
                delete ptr;
            }
            delete counter;
        }
        ptr = r.ptr;
        counter = r.counter;
        *(++counter);
        return *this;
         */
        SharedPtr(r).swap(*this);
        return  *this;
    }

    SharedPtr& operator=(SharedPtr&& r) {
        this -> swap(std::move(ptr));
        return *this;
    }

    // проверяет, указывает ли указатель на объект
    operator bool() const{
        return (ptr != nullptr && counter != nullptr);
    }

    T& operator*() const{
        return *ptr;
    }

    T* operator->() const {
        return ptr;
    }

    T* get(){
        return ptr;
    }

    void reset(){
        this -> ~SharedPtr();
        ptr = nullptr;
        counter = 0;
    }

    void reset(T* p){
        reset();
        SharedPtr<T>(p).swap(*this);
    }

    void swap(SharedPtr& p){
        std::swap(ptr , p.ptr);
        std::swap(counter , p.counter);
    }
    // возвращает количество объектов SharedPtr, которые ссылаются на тот же управляемый объект
    size_t use_count() const{
        return (*counter);
    }
};


#endif //SHAREDPTR_LAB_SHARED_H
