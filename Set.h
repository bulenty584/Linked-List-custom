#ifndef SET_INCLUDED
#define SET_INCLUDED

#include <string>

using ItemType = std::string;

class Set
{
  public:
    Set();               // Create an empty set (i.e., one with no items).
    bool empty() const;  // Return true if the set is empty, otherwise false.
    int size() const;    // Return the number of items in the set.

    ~Set();
    
    Set(const Set& other);
    
    Set& operator=(const Set& rhs);
    
    void dump() const;
    
    bool insert(const ItemType& value);

    bool erase(const ItemType& value);

    bool contains(const ItemType& value) const;
     
    bool get(int i, ItemType& value) const;

    void swap(Set& other);


  private:
    int m_size;
    
    struct Node{
        Node *next;
        ItemType value;
        Node *prev;
    };
    
    Node *head;
    Node *tail;
};

// Inline implementations

inline
int Set::size() const
{
    return m_size;
}

inline
bool Set::empty() const
{
    return m_size == 0;
}

inline
bool Set::contains(const ItemType& value) const
{
    //check if Set is empty:
    if (m_size == 0)
        return false;
    
    //Initalize a new Node and point to head:
    Node *p = head;
    
    //check if List has one node:
    if (m_size == 1){
        if (p->value == value)
            return true;
        return false;
    }
    
    
    //Loop through every element and check if the node's value equals value:
    while (p != nullptr){
        if (p->value == value){
            return true;
        }
        
        p = p->next;
    }
    
    return false;
}


/// NON-MEMBER FUNCTIONS
///
///

void unite(const Set& s1, const Set& s2, Set& result);

void butNot(const Set& s1, const Set& s2, Set& result);

#endif // SET_INCLUDED
