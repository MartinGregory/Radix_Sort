//
//  LinkedListQueue.hpp
//  Radix_Sort
//
//  Created by Martin Gregory Sendrowicz on 5/25/23.
//  Note to Future Self: Create LinkedList class then make it a Base Class for Queue inheritance.

#ifndef _LinkedListQueue_H_
#define _LinkedListQueue_H_

//||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||
template< class T>
class LinkedListQueue {
    
    //||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||
    struct Node {
        T data ;
        Node * next ;   // by default is initialized to nullptr
        
        Node( const T value ): data{value}, next{nullptr} {} ;
        //............................................................................................
        std::string show_node() {
            return "(" + std::to_string( (*this).data ) + ")->" ;  //e.g. (7)->
        }//...........................................................................................
    } ;
    //||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||
    Node * front ;
    Node * back ;
    int size ;
    
public:
    //................................................................................................
    LinkedListQueue(): front{nullptr}, back{nullptr}, size{0} {}
    //................................................................................................
    const int get_size() const {
        return (*this).size ;
    }
    //................................................................................................
    /* Insert data into the back of the queue. */
    void enqueue( const T data ) {
        
        Node * new_back = new Node( data ) ;
        
        if( (*this).front ==  nullptr  ){
            (*this).front = new_back ;
            (*this).back = new_back ;
        } else {
            (*(*this).back).next = new_back ;
            (*this).back = new_back ;
        }
        (*this).size++ ;
    }
    //................................................................................................
    /* Returns and Removes data from the front of the queue. Returns -1 if the queue is empty. */
    T dequeue() {
        if( (*this).front != nullptr ){
            Node * current_front = (*this).front ;
            T data = (*current_front).data ;
            (*this).front = (*this).front->next ;
            delete current_front ;
            (*this).size-- ;
            return data ;
        } else {
            //std::cout << "LinkedListQueue::dequeue: the Queue is empty!\n" ;
            return -1 ;
        }
    }
    //................................................................................................
    /* Returns (but NOT removes) a reference to the data at the front of the queue. Returns -1, if
    the queue is empty. */
    T& get_front() {
        if( (*this).front != nullptr ){
            return (*(*this).front).data ;
        } else {
            std::cout << "LinkedListQueue::get_front: the Queue is empty!\n" ;
            return -1 ;
        }
    }
    //................................................................................................
    std::string show_queue() {
        
        if( (*this).front == nullptr ){
            std::cout << "The Queue is empty\n" ; return "" ;
        }
        std::string output = "Front-->" ;
        
        Node* current = (*this).front ;
        while( current != nullptr ) {
            output += current->show_node();
            current = current->next ;
        }
        output = output + "NULL\n" ;
        
        return output ;
    }
    //................................................................................................
} ;
//||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||

#endif /* _LinkedListQueue_H_p */
