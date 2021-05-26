
#include "Node.h"

Node::Node(Tile* tile, Node* next, Node* prev)
{
   this->tile = tile;
   this->next = next;
   this->prev = prev;
}

Node::Node(Node& other)
{
   /*
    * Below code section will make it so the copy constructor uses
    * shallow copy.
    */
   this->tile = other.tile;
   this->next = other.next;
   this->prev = other.prev;

   /*
    * Below code section will make it so the copy constructor uses
    * deep copy everytime it is called.
    * This might NOT be the intended behaviour, as the recursion that occurs
    * will result in the whole node list (i.e. the whole linked list)
    * getting copied.
    */
   // this->tile = new Tile(other.tile);
   // if(other.next == nullptr)
   //    this->next = nullptr;
   // else
   //    this->next = new Node(*other.next);
   // if(other.prev == nullptr)
   //    this->prev = nullptr;
   // else
   //    this->prev = new Node(*other.next);
}
