#ifndef ArrayQueue_h
#define ArrayQueue_h

#include "Arduino.h"

template <class T>
class ArrayQueue {
  private:
    unsigned int maxSize;
    unsigned int currentPosition;
    unsigned int size;
    T * queue;
  public:
    ArrayQueue(unsigned int maxSize) {
      this->maxSize = maxSize;
      this->queue = new T[maxSize];
      this->currentPosition = 0;
      this->size = 0;
    }
    
    virtual ~ArrayQueue() {
      delete this->queue;
    }
    
    T peek() {
      if(this->size > 0) return this->queue[currentPosition];
      return NULL;
    }
    
    T pop() {
      if(this->size > 0) {
        T retVal = this->queue[currentPosition];
        this->size--;
        if(this->size > 0) {
          this->currentPosition++;
          if(this->currentPosition == this->maxSize) this->currentPosition = 0;
        } 
      }
    }
    
    boolean push(T value) {
      if(this->size < this->maxSize) {
        unsigned int i = this->currentPosition + this->size;
        if(i >= this->maxSize) i -= this->maxSize;
        this->queue[i] = value;
        return true;
      }
      
      return false;
    }
    
    unsigned int getSize() {
      return this->size;
    }
};

#endif
