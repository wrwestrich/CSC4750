#if !defined NULL
	#define NULL 0
#endif

#if !defined DOUBLE_NODE
#define DOUBLE_NODE

namespace CSC1310
{
template < class T >
class DoubleNode 
{

   private:
      DoubleNode<T>* prev;
      DoubleNode<T>* next;
      T* item;

   public:
      DoubleNode(T* item);
      ~DoubleNode();
      DoubleNode<T>* getPrev();
      DoubleNode<T>* getNext();
      void setPrev(DoubleNode<T>* prev);
      void setNext(DoubleNode<T>* next);
      T* getItem();

};

template < class T >
DoubleNode<T>::DoubleNode(T* itm)
{
   item = itm;
   prev = NULL;
   next = NULL;
}

template < class T >
DoubleNode<T>::~DoubleNode()
{
   item = NULL;
   prev = NULL;
   next = NULL;
}

template < class T >
T* DoubleNode<T>::getItem()
{
   return item;
}

template < class T >
DoubleNode<T>* DoubleNode<T>::getPrev()
{
   return prev;
}

template < class T >
DoubleNode<T>* DoubleNode<T>::getNext()
{
   return next;
}

template < class T >
void DoubleNode<T>::setPrev(DoubleNode<T>* prv)
{
   prev = prv;
}

template < class T >
void DoubleNode<T>::setNext(DoubleNode<T>* nxt)
{
   next = nxt;
}
}

#endif
