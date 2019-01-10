#ifndef SH_QUERY_H
#define SH_QUERY_H

#include <stddef.h>
/*
template<typename K, typename T>
struct MapNode
{
    K key;
	T data;
	MapNode<K,T> *next;
};
*/

template<typename A, typename V>
class SHQuery{

protected:
	int _size;
	byte first;
	byte last;
   // byte current;

public:
   SHQuery();
    ~SHQuery();  
   push( T data);
   T pop( );

   int size(void){return _size;};
};

template <typename K, typename T>
SHQuery<T>::SHMap(){
	root=NULL;
    current=NULL;
	last=NULL;
	_size=0;
}

template <typename K, typename T>
SHMap<K, T>::~SHMap()
{
	MapNode<K, T>* tmp;
	while(root!=NULL)
	{
		tmp=root;
		root=root->next;
		delete tmp;
	}
	last = NULL;
	_size=0;
}


#endif