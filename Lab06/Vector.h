#ifndef VECTOR_H
#define VECTOR_H

#include <exception>
// Vector.h

using namespace std;

template <class T>
class Vector
{
public:

   typedef T * iterator;

   Vector();
   Vector(unsigned int size);
   Vector(unsigned int size, const T & initial);
   Vector(const Vector<T> & v);           // copy constructor
   ~Vector();

   unsigned int capacity() const;         // return capacity of vector (in elements)
   unsigned int size() const;             // return the number of elements in the vector
   bool empty() const;

   iterator begin();                      // return an iterator pointing to the first element
   iterator end();                        // return an iterator pointing to one past the last element
   T & front();                           // return a reference to the first element
   T & back();                            // return a reference to the last element
   void push_back(const T & value);       // add a new element
   void pop_back();                       // remove the last element

   void reserve(unsigned int capacity);   // adjust capacity
   void resize(unsigned int size);        // adjust size

   T & operator[](unsigned int index);    // return reference to numbered element
   Vector<T> & operator=(const Vector<T> &);

private:
   unsigned int my_size;
   unsigned int my_capacity;
   T *buffer; //the changing array
};

// Two sample methods follow

template <class T>
Vector<T>::Vector()
{
	my_size = 0;
	my_capacity = 0;
	buffer = 0;
}

//Constructor for n values of default template value
template <class T>
Vector<T>::Vector(unsigned int size){
      int i;
      //If size == 0 both capacity and size are zero and buffer is NULL
      if (size == 0){
         return;
      }
      reserve(size);
      //assign function size to internal size
      my_size = size;
      //copy the default template parameter into each element of buffer
      for (i=0; i<my_size; i++){
         buffer[i] = T();
      }
}


/*//Constructor for Vector with n elements of the same value
template <class T>
Vector<T>::Vector(size, &initial){
   my_size = size;
   my_capacity = 

}*/


template <class T>
// This line doesn't compile: Vector<T>::iterator Vector<T>::begin()
// This line compiles:        T * Vector<T>::begin()
// But the follwoing line is the better solution:
typename Vector<T>::iterator Vector<T>::begin()
{
        return buffer;
}

//Deconstructor for the vector class
template <class T>
Vector<T>::~Vector(){ //declare it now just to make the linker happy.
   //as long as the vector isn't empty, go ahead and delete it.
   if (buffer != NULL)
         delete [] buffer;
} 

//Reserve is called only on two occasions, for initialization and any other time when 
//size==capactity, in which case it need be increased. 
template <class T>
void Vector<T>::reserve(unsigned int capacity){
   T *newBuffer;
   int i;

   //allocate new buffer, where #elements=capacity
   newBuffer = new T[capacity];
   //If the new Buffer is still null, then it didn't initialize properly, throw exception
   if (newBuffer == NULL){
      throw "miniVector reserve(): memory allocation failure";
   }
   //else it initialized fine, copy the old buffer into the new one.
   else {
      for (i=0; i < my_size; i++){
         newBuffer[i] = buffer[i]; //place old buffer element in newBuffer
      }
   }
   //delete the old buffer, only if there were elements inside to start
   //------>>>>>Must uncomment this before further testing, will fill RAM.
   //throws error: "pointer being freed was not allocated"
   /*if (buffer !=NULL){
      delete [] buffer;
   }*/

   //update pointers
   buffer = newBuffer;
   my_capacity = capacity;
}

//Operator to allow element access
template <class T>
T & Vector<T>::operator[](unsigned int index){
   //by using unsigned int, value can't be neg so check to make sure index isn't past
   //upper limits
   if (index >= my_size)
      throw "Vector: index is above the allowed range";

   return buffer[index];

}


#endif

