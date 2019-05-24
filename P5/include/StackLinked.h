#if !defined STACK_LINKED
#define STACK_LINKED

#include "NextNode.h"

namespace CSC1310
{
template < class T >
class StackLinked
{

   private:
      NextNode<T>* top;
      int sz;  

   public:
      StackLinked();
      ~StackLinked();

      bool isEmpty();
      int size();
      void popAll();

      T* pop();
      void push(T* item);
      T* peek();

};

template < class T >
StackLinked<T>::StackLinked()
{
   top = NULL;
   sz = 0;
}

template < class T >
StackLinked<T>::~StackLinked()
{
   popAll();
}

template < class T >
bool StackLinked<T>::isEmpty()
{
   return sz == 0;
}

template < class T >
int StackLinked<T>::size()
{
   return sz;
}

template < class T >
T* StackLinked<T>::peek()
{
   T* item = NULL;
   if (!isEmpty()) 
   {  
     item = top->getItem();
   }
   return item;
}

template < class T >
void StackLinked<T>::push(T* item)
{
   NextNode<T>* node = new NextNode<T>(item);
   node->setNext(top);
   top = node;
   sz++;
}

template < class T >
T* StackLinked<T>::pop()
{
   if (sz == 0) return NULL;

   T* item = top->getItem();
   NextNode<T>* temp = top->getNext();
   delete top;
   top = temp;
   sz--;
   return item;
}

template < class T >
void StackLinked<T>::popAll()
{
   //could just keep calling pop until the stack is empty

   //loop over the stack, deleting the nodes
   //the actual items are not deleted
   if (sz == 0) return;

   NextNode<T>* curr = top;
   NextNode<T>* prev = NULL;
   while (curr != NULL)
   {
      prev = curr;
      curr = curr->getNext();
      prev->setNext(NULL);
      delete prev;
   }

   top = NULL;
   sz = 0;
}
}

#endif
