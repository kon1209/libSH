#ifndef SH_KEYVALMAP_H
#define SH_KEYVALMAP_H

#include <stddef.h>

template<typename K, typename T>
struct MapNode
{
    K key;
	T data;
	MapNode<K,T> *next;
};

template <typename K, typename T>
class SHMap{

protected:
	int _size;
	MapNode<K,T> *root;
	MapNode<K,T> *last;
    MapNode<K,T>* current;

public:
   SHMap();
    ~SHMap();  
   MapNode<K,T> * add( K key, T data);
   void del( K key);
   MapNode<K, T>* getNode(K key);
   T getValue(K key);
   T getValue(void);  
   K getKey(void){return current -> key;};  
   MapNode<K, T>* first(void);
   MapNode<K, T>* next(void);   
   MapNode<K, T>* tail(void);
   bool isLast(){return current==last;};
   int size(void){return _size;};
};

template <typename K, typename T>
SHMap<K, T>::SHMap(){
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

template <typename K, typename T>
MapNode<K,T> * SHMap<K, T>::add( K key, T data)
{
 MapNode<K,T> *tmp = getNode(key);
 if(tmp) return NULL; 
 tmp = new MapNode<K, T>();
 tmp->next=NULL;
 tmp->key=key;
 tmp->data=data;
 if(root){
    if(root==last){
    last=tmp;
    root->next=last;
    }else{
    last->next=tmp;
    last=tmp;
    }
 }
 else{   
   root=tmp;
   last=tmp;  
 }
 _size++;
}

template <typename K, typename T>
T  SHMap<K, T>::getValue(K key){
 MapNode<K, T>* tmpNode = getNode(key);
 if(tmpNode) return tmpNode->data;
return NULL;
}

template <typename K, typename T>
T  SHMap<K, T>::getValue(){
 if(current) return current->data;
return NULL;
}

template <typename K, typename T>
MapNode<K, T>* SHMap<K, T>::getNode(K key){
	MapNode<K,T>* curNode = root;
	while( curNode){
         if(curNode->key == key ) return curNode;
		curNode = curNode->next;
	}
	return NULL;
}

template <typename K, typename T>
void SHMap<K, T>::del( K key){
   switch (_size)
   {
   case 0: return;
   case 1: if(root->key==key){
            delete root;
            root=NULL;last=NULL;
            _size=0;
            }
        break;    
   default :
         MapNode<K,T>* nextNode = root->next;
         MapNode<K,T>* prevNode = root;
            if(root->key==key){
               delete root;
               root=nextNode;
               _size--;
               return;
            }
            do{
            if(nextNode->key == key){
               if(nextNode=last){
                last=prevNode;
               }
               prevNode->next=nextNode->next;
               delete nextNode;
               _size--;
               return;
               }
              prevNode=nextNode;
              nextNode=nextNode->next;
             }while(nextNode->next != NULL);
        break;
  }
};

template <typename K, typename T>
MapNode<K, T>* SHMap<K, T>::first(void){current = root; return current;}

template <typename K, typename T>
MapNode<K, T>* SHMap<K, T>::next(void){
   if(current==last) current =  NULL;
    else current = current->next; 
    return current;}

template <typename K, typename T>
MapNode<K, T>* SHMap<K, T>::tail(void){current = last; return current;}

#endif