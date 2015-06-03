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

   //This block done
   unsigned int capacity() const;         // return capacity of vector (in elements)
   unsigned int size() const;             // return the number of elements in the vector
   bool empty() const;

   //all done except iterator end()
   iterator begin();                      // return an iterator pointing to the first element
   iterator end();                        // return an iterator pointing to one past the last element
   T & front();                           // return a reference to the first element
   T & back();                            // return a reference to the last element
   void push_back(const T & value);       // add a new element
   void pop_back();                       // remove the last element

   //This block done(except del in reserve())
   void reserve(unsigned int capacity);   // adjust capacity
   void resize(unsigned int size);        // adjust size

   //This block done
   T & operator[](unsigned int index);    // return reference to numbered element
   Vector<T> & operator=(const Vector<T> &a); //assignment operator

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

//Deconstructor for the vector class
template <class T>
Vector<T>::~Vector(){ //declare it now just to make the linker happy.
   //as long as the vector isn't empty, go ahead and delete it.
   if (buffer != NULL)
         delete [] buffer;
} 

// return capacity of vector (in elements), cap.=amount it CAN hold
template <typename T>   
unsigned int Vector<T>::capacity() const{
   return my_capacity;
}        

// return size of vector (in elements), size=amount it is CURRENTLY holding 
template <typename T>
unsigned int Vector<T>::size() const{
   return my_size;
}

//return a bool of whether vector is empty or not.  -->Working
template <typename T>
bool Vector<T>::empty() const{
   return my_size == 0;
}

template <class T>
// This line doesn't compile: Vector<T>::iterator Vector<T>::begin()
// This line compiles:        T * Vector<T>::begin()
// But the follwoing line is the better solution:
typename Vector<T>::iterator Vector<T>::begin()
{
        return buffer;
}

// return an iterator pointing to one past the last element
template <typename T>
typename Vector<T>::iterator Vector<T>::end(){
         //I don't know what to return here/get there.
}            

// return a reference to the first element
template <typename T>
T & Vector<T>::front(){
   //throw an error if there is nothing in the vector
   if (my_size == 0)
      throw "Vector front(): vector empty";

   return buffer[0];
}   

template <typename T>                        
T & Vector<T>::back(){
   //throw an error if there is nothing in the vector
   if (my_size == 0)
      throw "Vector back(): vector empty";

   return buffer[my_size-1];
} 

//Push a const value onto the back of vector -->Working
template <typename T>
void Vector<T>::push_back(const T & value){
   //if size==capacity, vector is full, add 5 more spaces to capacity
   if (my_size == my_capacity){
         reserve (5);
   }
   buffer[my_size] = value;
   my_size++;
}

//Remove the last element of vector
template <typename T>
void Vector<T>::pop_back(){
   //If size=0, there is nothing to delete, throw exception
   if (my_size == 0){
      throw "Vector pop_back(): vector is empty";
   }
   my_size--;
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
      throw "Vector reserve(): memory allocation failure";
   }
   //else it initialized fine, copy the old buffer into the new one.
   else {
      for (i=0; i < my_size; i++){
         newBuffer[i] = buffer[i]; //place old buffer element in newBuffer
      }
   }


   //Need to fix this before finished, as it will eventually fill up RAM completely. 
   //For now, comment to make compiler happy.   
   //mal_alloc "pointer being freed was not allocated"  
   /*if (buffer !=NULL){
      delete [] buffer;
   }*/

   //update pointers
   buffer = newBuffer; //update data
   my_capacity = capacity;
}

// adjust size of vector. Two conditions: 1) New size is greater->copy 0 into all new spaces
//2) New size is lesser->delete from size until met
template <typename T>
void Vector<T>::resize(unsigned int size){
   //first condition
   if (size > buffer.size()){
      //int endIndex = buffer.size() - 1; //get last index before resize to know where to begin
      int origSize = buffer.size(); //get size before format
      //make sure there is enough capacity for the new numbers
      if (my_capacity < size){
         //if true, need to reserve more space, then resize
         reserve(size);
      }
      while (origSize < size){
            buffer[origSize] = 0; //starts at one past the original end Index
            origSize++;
   }
   //second condition
   if (size < buffer.size()){
      //get how many spaces I need to delete
      int d = buffer.size() - size;
      while (d != 0){
         my_size--; //delete last element
         d--; //decrement counter
      }
   }
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

//assignment operator, makes LHS same as RHS
template <typename T>
Vector<T> & Vector<T>::operator=(const Vector<T> &a){
   int i;

   // check capacity to see if a new array must be allocated
   if (my_capacity < a.size()){
      // make capacity of current object the size of RHS
      reserve(a.size());
   }
   // assign current object to have same size as RHS
   my_size = a.size();

   // copy items from a.buffer to buffer
   for (i = 0; i < my_size; i++)
      buffer[i] = a.buffer[i];

   return *this;
}

#endif

