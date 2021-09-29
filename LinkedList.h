
#ifndef ASSIGN2_LINKEDLIST_H
#define ASSIGN2_LINKEDLIST_H

#include "Node.h"

#define NULL_INDEX   99

class LinkedList {
public:

   LinkedList();
   ~LinkedList();

   Tile* get(unsigned int i);
   int getTileIndex(Tile* tile);
   void addFront(Tile* data);
   void addBack(Tile* data);
   unsigned int getSize();
   void remove(unsigned int i);
   void removeFront();
   void removeBack();
   void clear();

private:
   Node* head;
   Node* tail;
   unsigned int size;
};

#endif // ASSIGN2_LINKEDLIST_H
