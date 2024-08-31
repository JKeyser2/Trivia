/*****************************************************************************
 ** File: Lqueue.cpp
 ** Project: CMSC 202 Project 5, Spring 2022
 ** Author:  Kush Shah and CMSC202
 ** Date:    04/05/2022
 ** Email:   k216@umbc.edu
 **
 Description: CPP file for Trivia class. Includes both class definition and
 class function definitions. Loads a file of trivia questions
*****************************************************************************/
#ifndef LQUEUE_CPP
#define LQUEUE_CPP
#include <string>
#include <iostream>
#include <iomanip>
#include <cmath>
using namespace std;

//Templated node class used in templated linked list
template <class T>
class Node {
   public:
  Node( const T& data ); //Constructor
  T& GetData(); //Gets data from node
  void SetData( const T& data ); //Sets data in node
  Node<T>* GetNext(); //Gets next pointer
  void SetNext( Node<T>* next ); //Sets next pointer
private:
  T m_data;
  Node<T>* m_next;
};

//Overloaded constructor for Node
template <class T>
Node<T>::Node( const T& data ) {
   m_data = data;
   m_next = NULL;
}

//Returns the data from a Node
template <class T>
T& Node<T>::GetData() {
   return m_data;
}

//Sets the data in a Node
template <class T>
void Node<T>::SetData( const T& data ) {
   m_data = data;
}

//Gets the pointer to the next Node
template <class T>
Node<T>* Node<T>::GetNext() {
   return m_next;
}

//Sets the next Node
template <class T>
void Node<T>::SetNext( Node<T>* next ) {
   m_next = next;
}

template <class T>
class Lqueue {
 public:
  // Name: Lqueue() (Linked List Queue) - Default Constructor
  // Desc: Used to build a new linked queue (as a linked list)
  // Preconditions: None
  // Postconditions: Creates a new lqueue where m_head and m_tail point to nullptr
  // Required
 Lqueue();
  // Name: ~Lqueue() - Destructor
  // Desc: Used to destruct a Lqueue
  // Preconditions: There is an existing lqueue with at least one node
  // Postconditions: An lqueue is deallocated (including dynamically allocated nodes)
  //                 to have no memory leaks!
  // Required
 ~Lqueue();
  // Name: Lqueue (Copy Constructor)
  // Preconditions: Creates a copy of existing LQueue
  //                Requires a Lqueue
  // Postconditions: Copy of existing Lqueue
  // Required
  Lqueue(const Lqueue& other);
  // Name: operator= (Overloaded Assignment Operator)
  // Preconditions: Copies an Lqueue into an existing Lqueue
  //                Requires a Lqueue
  // Postconditions: Copy of existing Lqueue
  // Required
  Lqueue<T>& operator= (Lqueue& other);
  // Name: Push
  // Preconditions: Takes in data. Creates new node.
  //                Requires a Lqueue
  // Postconditions: Adds a new node to the end of the lqueue.
  // Required
  void Push(const T& data);
  // Name: Pop
  // Preconditions: Lqueue with at least one node.
  // Postconditions: Removes first node in the lqueue, returns data from first node.
  // Required
  T Pop();
  // Name: Display
  // Preconditions: Outputs the lqueue.
  // Postconditions: Displays the data in each node of lqueue
  // Required (used only for testing)
  void Display();
  // Name: Front
  // Preconditions: Requires a populated lqueue
  // Postconditions: Returns whatever data is in front
  // Required
  T Front();
  // Name: IsEmpty
  // Preconditions: Requires a lqueue
  // Postconditions: Returns if the lqueue is empty.
  // Required
  bool IsEmpty();
  // Name: GetSize
  // Preconditions: Requires a lqueue
  // Postconditions: Returns m_size
  // Required
  int GetSize();
  // Name: Find()
  // Preconditions: Requires a lqueue
  // Postconditions: Iterates and if it finds the thing, returns index, else -1
  // Required
  int Find(T& lookingForThing);
  // Name: Swap(int)
  // Preconditions: Requires a lqueue
  // Postconditions: Swaps the nodes at the index with the node prior to it.
  // Required
  void Swap(int index);
  // Name: Clear
  // Preconditions: Requires a lqueue
  // Postconditions: Removes all nodes in a lqueue
  // Required
  void Clear();
  // Name: At
  // Precondition: Existing Lqueue
  // Postcondition: Returns object from Lqueue at a specific location
  // Desc: Iterates to node x and returns data from Lqueue
  // Required
  T At (int index);
private:
  Node <T> *m_head; //Node pointer for the head
  Node <T> *m_tail; //Node pointer for the tail
  int m_size; //Number of nodes in queue
};

//**********Implement Lqueue Class Here***********
//**********All Functions Are Required Even If Not Used for Trivia**************

template <class T>
Lqueue<T>::Lqueue(){
   // Default Constructor
   m_head = nullptr;
   m_tail = nullptr;
   m_size = 0;
}

template <class T>
Lqueue<T>::~Lqueue(){
   Clear();
}

template <class T>
Lqueue<T>::Lqueue(const Lqueue& other){
   // Sets the head of the linked list to be nullptr
  // m_head = nullptr;
   // Creates a node for traversing. Sets it equal to the head of the linked list
 //  Node<T> *curr = other.m_head;

  // Node<T> *myCurr = m_head;

      // While we have yet to reach the end of the other linked list
    //  while(curr != nullptr){
         // Push the data from the other linked list
     //    Push(curr->GetData());
         // Move curr 1 index
      //   curr = curr->GetNext();
     // }

  // while(curr != nullptr){
    //  myCurr->SetData(curr->GetData());
    //  myCurr = myCurr->GetNext();
     // curr = curr->GetNext();
 //  }


    if (other.m_head == nullptr) {
        m_head = nullptr;
    }
    else {
        m_head = new Node<T>(other.m_head->GetData());

        
        Node<T> *current = m_head;
        Node<T> *currentOther = other.m_head;
        while (currentOther != nullptr) {
            current = new Node<T>(currentOther->GetData());
            currentOther = currentOther->GetNext();
            current = current->GetNext();
        }
    }

     // Set tail and size to be equal to the tail and size of the other linked list
      m_tail = other.m_tail;
      m_size = other.m_size;




}

template <class T>
Lqueue<T>& Lqueue<T>::operator=(Lqueue& other){
   // We are looking to make sure that the memory address of other is not equal to the memory address...
   // ... of the thing we are working on.
   if(this != &other){

      // Removing each node of our linked list until it we have removed them all
      //while(m_head != nullptr){
        // Pop();
     // }

      Clear();


      // Create a node for traversing the other linked list
      Node<T> *curr = other.m_head;

      // While we have yet to reach the end of the other linked list
      while(curr != nullptr){
         // Push the data from the other linked list
         Push(curr->GetData());
         // Move curr 1 index
         curr = curr->GetNext();
      }

      // Set the tail and size to be equal to the other linked list
      m_tail = other.m_tail;
      m_size = other.m_size;

      return *this;
   }
}

template <class T>
void Lqueue<T>::Push(const T& data){

   // Creates a dynamically allocated node object for inserting at the end of the Lqueue
    Node<T> *newNode = new Node<T>(data);
    // Sets the pointer to the next node on the Lqueue to be nullptr
    newNode->SetNext(nullptr);


    // If the linked list for the Lqueue is empty
    if(m_head == nullptr){
        // Sets the node to be the head of the Lqueue
        m_head = newNode;
    }
    // If the linked list for the Lqueue already has at least 1 port
    else{
        // Creates a temporary node for looping through all of the nodes until the end is reached
        // Sets the temporary node to be the head of the linked list
        Node<T> *tempNode = m_head;

        // While we have yet to reach the end of the linked list
        while(tempNode->GetNext() != nullptr){
            // Sets the temporary node equal to the next node
            tempNode = tempNode->GetNext();
        }
        // When the end of the linked list is reached, sets the node to be last in the linked list
        tempNode->SetNext(newNode);
        // Sets the node to also be the tail of the linked list
        m_tail = newNode;
    }
    // Increments the size of the route by 1
    m_size++;
}

template <class T>
T Lqueue<T>::Pop(){
   // Crates a pointer to the head of the linked list
   Node<T> *tempNode = m_head;
   // Gets the data from the head of the linked list, stores it
   T value = m_head->GetData();
   // Sets the head of the linked list to be the next value
   m_head = m_head->GetNext();
   // Removes the head of the linked list
   delete tempNode;
   // Reduces the size of the linked list by 1
   m_size--;
   // Returns the value of the old head
   return value;
}

template <class T>
void Lqueue<T>::Display(){
    // If the linked list is empty
    if(m_size == 0){
        cout << "Linked list is empty!" << endl;
    // If the linked list is not empty
    }else{
        // Creates a a pointer to the head of the linked list
        Node<T> *tempNode = m_head;
        // While we have yet to reach the end of the linked list
        while(tempNode != nullptr){
            //cout << m_size << endl;
            // Prints out all of the information about the port
            cout << tempNode->GetData() << endl;
            // Goes to the next port
            tempNode = tempNode->GetNext();
        }
    }
}

template <class T>
T Lqueue<T>::Front(){
   // Sets variable equal to the data of the head of the linked list
   T data = m_head->GetData();
   // Returns the data at the head of the linked list
   return data;
}

template <class T>
bool Lqueue<T>::IsEmpty(){
   // If size is 0, linked list is empty
   if(m_size == 0){
      return true;
   // If size is not 0
   }else{
      return false;
   }
}

template <class T>
int Lqueue<T>::GetSize(){
   return m_size;
}

template <class T>
int Lqueue<T>::Find(T& lookingForThing){
   // Creates a tempNode for looping through all the nodes
   Node<T> *tempNode = m_head;

   // Creates a template variable for storing the data of the node
   T nodeData = tempNode->GetData();

   // Declares and initializes an int variable for storing the index of the data we are looking for
   int counter = 0;

   // Loops through all of the nodes
   while(tempNode != nullptr){
      // Stores the data of the node at current index
      nodeData = tempNode->GetData();
      // If the data of the node equals what you are looking for
      if(nodeData == lookingForThing){
         // Return the index position in which you found it at
         return counter;
      // If not the data we are looking for
      }else{
         // Goes to next node
         tempNode = tempNode->GetNext();
         // Increments counter by 1
         counter++;
      }
   }
   // If the thing looking for is not found
   return -1;
}

template <class T>
void Lqueue<T>::Swap(int index){
   Node<T> *prev = m_head;
   Node<T> *curr = m_head;
   
   T tempData;
   T prevData;
   T currData;

   // Creates a counter for tracking index position
  int counter = 0;

   // Can't swap first node
   if(index == 0){
      cout << "Can't swap the first node!" << endl; 
   }else{
      // So we don't go off the end of the linked list
   while(counter < m_size){
      // If we are at the index position we want
      if(counter == index){
         tempData = curr->GetData();
         currData = prev->GetData();
         prevData = tempData;

         curr->SetData(currData);
         prev->SetData(prevData);

         counter++;
      // If not yet at the index position that we want
      }else{
         // Increments the counter by 1
         counter++;
         // Shifts the prev node by 1
         prev = curr;
         // Shifts the current node by 1
         curr = curr->GetNext();
      }
   }
   }
  
}

template <class T>
void Lqueue<T>::Clear(){
    // Creates dynamically allocated node. Sets it equal to the head
    Node<T> *curr = m_head;
    // While we have yet to reach the end of the linked list
    while(curr != nullptr){
        // Sets the head to be curr
        m_head = curr;
        // Sets curr to be the next node
        curr = curr->GetNext();
        // Deletes the head node
        delete m_head;
        m_head = nullptr;
    }
    m_head = nullptr;
    m_tail = nullptr;
    m_size = 0;
}

template <class T>
T Lqueue<T>::At(int index){
  // Creates a temporary node for traversing the linked list
  Node<T> *tempNode = m_head;
  // Creates a counter for tracking index position
  int counter = 0;

  // So we don't go off the end of the linked list
  while(counter < m_size){
     // If we are at the index position we want
     if(counter == index){
        // Store the data of the node
        T value = tempNode->GetData();
        // Return the data
        return value;
     // If not yet at the index position that we want
     }else{
        // Increments the counter by 1
        counter++;
        // Shifts the tempNode by 1
        tempNode = tempNode->GetNext();
     }
  }
   T value = tempNode->GetData();
   return value;
}


#endif
