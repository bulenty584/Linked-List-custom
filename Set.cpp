#include "Set.h"
#include <iostream>
using namespace std;

Set::Set()
 : m_size(0), head(nullptr), tail(nullptr)
{}

Set::~Set(){
    
    Node *p = head;
    
    //Check if empty list:
    if (m_size == 0)
        return;
    
    //Delete each node:
    while (p->next != nullptr){
        Node *n = p->next;
        delete p;
        p = n;
    }
    delete tail;
    
    m_size = 0;
}

Set::Set(const Set& other){
    
    //check if list is empty:
    if (other.m_size == 0){
        m_size = 0;
        head = nullptr;
        tail = nullptr;
        return;
    }
    
    //check if list is one node:
    if (other.m_size == 1){
        m_size = other.m_size;
        head = new Node;
        head->value = other.head->value;
        head->next = nullptr;
        head->prev = nullptr;
        tail = head;
    }
    
    else{
        //Declare new Pointers:
        Node* oHead;
        Node* newHead;
        
        //initialze size and make NewHead point to this->head;
        m_size = other.m_size;
        head = new Node;
        head->value = other.head->value;
        head->prev = nullptr;
        newHead = head;
        
        //Loop through other Linked List and add nodes to the copied List:
        for (oHead = other.head->next; oHead != nullptr; oHead = oHead->next){
            
            Node *temp = new Node;
            temp->value = oHead->value;
            temp->prev = newHead;
            temp->prev->next = temp;
            newHead = newHead->next;
        }
        
        //Initialize tail:
        tail = newHead;
        tail->next = nullptr;
    }
}


Set& Set::operator=(const Set &other){
    //Check if right side already equals left side:
    if (this == &other){
        return *this;
    }
    
    //Create new Set and swap with other:
    else{
        Set n(other);
        swap(n);
    }
    
    return *this;
        
}

bool Set::insert(const ItemType& value){
    
    if (contains(value))
        return false;
    //Check if List is empty:
    if (m_size == 0){
        Node *c = new Node;
        c->value = value;
        
        head = c;
        tail = c;
        tail->next = nullptr;
        head->prev = nullptr;
        m_size++;
    }
    
    // Check if value is in Set:
    
    else{
        //Create new Node at end of the list:
        Node *newN = new Node;
        newN->value = value;
        tail->next = newN;
        newN->prev = tail;
        
        //Set New Node's next pointer to null:
        newN->next = nullptr;
        
        //Make tail point to newN, the last node in the list:
        tail = newN;
        tail->next = nullptr;
        m_size++;
    }
    
    return true;
}

bool Set::erase(const ItemType& value){
    
    //Check if list is empty:
    if (m_size == 0)
        return false;
    
    //Initialize new Set Pointer to be killed:
    Node *kill = head;
    
    //Check if only one node and value matches kill:
    if (m_size == 1 && kill->value == value){
        delete kill;
        m_size--;
        return true;
    }
    
    //Check if kill's value matches value and adjust pointers:
    if (kill->value == value){
        head = kill->next;
        kill->prev = nullptr;
        kill->next->prev = nullptr;
        delete kill;
        m_size--;
        return true;
    }
    
    while(kill != nullptr){
        
        //Check if Last item in the list:
        if (kill->value == value && kill->next == nullptr){
            tail = kill->prev;
            kill->prev->next = nullptr;
            delete kill;
            m_size--;
            return true;
        }
        
        //For nodes in the middle of the list:
        else{
            if (kill->value == value){
                
                //Make the previous's next pointer and next's previous pointer point to each other.
                kill->prev->next = kill->next;
                kill->next->prev = kill->prev;
                kill->next = nullptr;
                kill->prev = nullptr;
                delete kill;
                m_size--;
                return true;
            }
        }
        
        kill = kill->next;
            
    }
    
    return false;
}

     
bool Set::get(int i, ItemType& value) const
{
    //Initialize a counter:
    int count = 0;
    
    //check if list is empty:
    if (m_size == 0)
        return false;
    
    //Check if list is one element and if i is in range:
    if (m_size == 1 && i == 0){
        value = head->value;
        return true;
    }
    
    //If list is one element and if i is out of range:
    if (m_size == 1 && i != 0){
        return false;
    }
    
    else{
        
        //Initialize two pointer variables to traverse list:
        Node *curr;
        
        Node *trav;
        
        //Outer for loop to look at a specific value in the list:
        for (curr = head; curr != nullptr; curr = curr->next){
            
            //Inner loop to examine each item in the list for one curr Node:
            for (trav = head; trav != nullptr; trav = trav->next){
                
                //Increment count if the value is greater than an item in the list:
                if (curr->value > trav->value){
                    count++;
                }
            }
            
            //Check if i is in range and if counter equals i:
            if (i >= 0 && i < m_size && count == i){
                value = curr->value;
                return true;
            }
            
            count = 0;
        }
    }
    
    
    return false;
}

void Set::swap(Set& other)
{
    //Swap sizes:
    int temp = m_size;
    m_size = other.m_size;
    other.m_size = temp;
    
    //Swap head pointers:
    Node *te = other.head;
    other.head = this->head;
    this->head = te;
    
    //Swap tail pointers:
    Node *t = other.tail;
    other.tail = this->tail;
    this->tail = t;
    
}


/// IMPLEMENTATION OF NON-SET FUNCTIONS
///
///

void unite(const Set& s1, const Set& s2, Set& result){
    
    //Declare temporary Set variable:
    Set temp;
    
    //Add s1's elements to the Set:
    for(int i = 0; i < s1.size(); i++){
        ItemType c = 0;
        s1.get(i, c);
        temp.insert(c);
    }
    
    //Insert s2's elements if not the same as s1:
    for(int i = 0; i < s2.size(); i++){
        ItemType v = 0;
        s2.get(i, v);
        temp.insert(v);
    }
    
    //Set result equal to temp:
    result = temp;
}

void butNot(const Set& s1, const Set& s2, Set& result){
    
    //Declare temporary set variable:
    Set temp;

    //Add s1's elements to the temp Set:
    for (int i = 0; i < s1.size(); i++){
        ItemType s = 0;
        s1.get(i,s);
        temp.insert(s);
            
    }
    
    //Check if s2's elements are in the Set, if they are, erase them from the Set:
    for (int i = 0; i < s2.size(); i++){
        ItemType x = 0;
        s2.get(i,x);
        if (temp.contains(x))
            temp.erase(x);
        
    }
    
    //Set result equal to temp:
    result = temp;
    
}

void Set::dump() const{
    
    for (int i = 0; i < this->size(); i++){
        
        ItemType x = 0;
        get(i,x);
        cerr << x << endl;
        
        
    }
}
