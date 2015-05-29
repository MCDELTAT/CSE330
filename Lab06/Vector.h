#ifndef VECTOR_H
#define VECTOR_H

// Vector.h

using namespace std;

template &lt;class T>
class Vector
{
public:

   typedef T * iterator;

   Vector();
   Vector(unsigned int size);
   Vector(unsigned int size, const T & initial);
   Vector(const Vector&lt;T> & v);           // copy constructor
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
   Vector&lt;T> & operator=(const Vector&lt;T> &);

private:
   unsigned int my_size;
   unsigned int my_capacity;
   T * buffer;
};

// Two sample methods follow

template &lt;class T>
Vector&lt;T>::Vector()
{
	my_size = 0;
	my_capacity = 0;
	buffer = 0;
}

template &lt;class T>
// This line doesn't compile: Vector&lt;T>::iterator Vector&lt;T>::begin()
// This line compiles:        T * Vector&lt;T>::begin()
// But the follwoing line is the better solution:
typename Vector&lt;T>::iterator Vector&lt;T>::begin()
{
        return buffer;
}

// Rest of your code goes here ...

#endif