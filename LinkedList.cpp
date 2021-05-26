
#include "LinkedList.h"

#include <iostream>


/*
 * It is important to note that head Node's prev node will always be nullptr
 * and tail Node's next node will always be nullptr
 */

LinkedList::LinkedList() {

    head = nullptr;
    tail = nullptr;
    size = 0;

}



LinkedList::~LinkedList(){
    clear();
}



unsigned int LinkedList::getSize()
{

    return this->size;

}



void LinkedList::clear(){

    if (head == nullptr) {

        return;

    }

     

    Node *upto = head;

    while (upto != nullptr) {

        Node *to_be_deleted = upto;

        upto = upto->next;

        delete to_be_deleted;

    }

    head = nullptr;

    size = 0;

}



Tile* LinkedList::get(unsigned int i)
{
    if(i >= this->size)
        throw std::invalid_argument("trying to remove a node of index larger than size");

    Node * upto = this->head;
    for (unsigned int count = 0; count < i; count++) 
    {

        upto = upto->next;

    }

    return upto->tile;

}

int LinkedList::getTileIndex(Tile* repTile)
{
    int index = 0;
    Node * upto = this->head;
    for (unsigned int count = 0; count < size; count++) 
    {
        if(upto->tile == repTile)
        {
            index = count;
            return index;
        }
        upto = upto->next;

    }
    
    return index;
    std::cout << "Tile not Found" << std::endl;

}

void LinkedList::removeFront()
{
    Node* newHead = this->head->next;
    newHead->prev = nullptr;

    delete this->head;

    this->head = newHead;

    this->size--;
}

void LinkedList::removeBack()
{
    Node* newTail = this->tail->prev;
    newTail->next = nullptr;

    delete this->tail;

    this->tail = newTail;

    this->size--;
}

void LinkedList::remove(unsigned int i)
{
    if(i >= this->size)
        throw std::invalid_argument("trying to remove a node of index larger than size");

    if(i == 0) // remove front
        this->removeFront();
    else if(i == size-1) // remove back
        this->removeBack();
    else
    {
        Node *upto = head;
        for(unsigned int index = 0; index < i; ++index)
            upto = upto->next;

        Node* nodeBefore = (upto->prev);
        nodeBefore->next = upto->next;

        Node* to_be_deleted = upto;
        Node* nodeAfter = upto->next;
        delete to_be_deleted;

        nodeAfter->prev = nodeBefore;

        // Note that removeFront and removeBack methods also subtract
        // size by one in its own implementation
        size--;
    }
    

    return;
}



void LinkedList::addFront(Tile* data){

     

    // what's head currently pointing at?

    // Node *temp = this->head;

     

    // ok, lets make a new node that also points at

    // whatever head is pointing at...

    // Node *n = new Node(data, temp);

     

    // now make head point at the brand new node.

    // this->head = n;

     

    // or write it like this...

    // since we're adding to the front, then previous node would always be
    // a nullptr
    head = new Node(data, head, nullptr);

    // if size is 0, then tail is nullptr, thus tail should have the
    // same Node as head when first time adding a Node.
    // otherwise, tail don't change if a Node added from front.
    if(this->size == 0)
        this->tail = this->head;

    // Note that if head is currently nullptr (i.e. size = 0), then the "next" attribute
    // for the new Node would be nullptr, which is the intended behaviour as the "next"
    // attribute for the last Node object should be a nullptr.

    size++;

}



void LinkedList::addBack(Tile* data) {

    // two possible conditions

    

    if (head == nullptr) 
    {
        // list is empty => we need to modify the LinkedList object
        head = new Node(data, nullptr, nullptr);
        this->tail = this->head;
    } 
    else 
    {

        // list is not empty => we need to modify the last Node element.
  
        Node * upto = this->head;
 
        while (upto->next != nullptr) 
        {

            upto = upto->next;


        }
       
        upto->next = new Node(data, nullptr, upto);

        this->tail = upto->next;

    }

    size++;

}