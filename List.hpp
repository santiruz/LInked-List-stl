//
// Created by Santi on 9/25/2020.
//

#ifndef HW2_LIST_HPP
#define HW2_LIST_HPP

template <typename T>
List<T> :: List()
{
    init();

}

template <typename T>
List<T> :: List(std::initializer_list<T> iList)
{
    init();
  auto it = iList.begin();

    while(it != iList.end())
    {
        push_back(*it);
        ++it;
    }

}

template <typename T>
 List<T> & List<T> :: operator=(std::initializer_list<T> iList)
{
   clear();
    init();
    auto it = iList.begin();

    while(it != iList.end())
    {
        push_back(*it);
        ++it;
    }
}

template<typename T>	// move assignment
List<T> & List<T>::operator=(List<T> && rhs)
{
    std::swap(theSize, rhs.theSize);
    std::swap(head,rhs.head);
    std::swap( tail, rhs.tail );
    return *this;

}

template <typename T>
List<T> :: ~List()
{
    clear();
    delete head;
    delete tail;

}

template <typename T>
List<T> :: List(const List<T> & rhs)
{
    init();
    for(auto itr = rhs.begin(); itr != rhs.end();itr++)
        push_back(*itr);

}
template<typename T> // move constructor
List<T>::List( List<T> && rhs ) : theSize(rhs.theSize), head{rhs.head}, tail{rhs.tail}
{
    rhs.theSize = 0;
    rhs.head = nullptr;
    rhs.tail = nullptr;
}
template<typename T> // copy assignment
const List<T> & List<T>::operator=(const List<T> & rhs)
{
    auto temp = rhs;  // swap by reference
    std::swap(*this, temp);
    return *this;
}

template<typename T>
List<T>::List(int num, const T & v)
{
    init();
    int i;
    for(i = 0; i < num; i++)
        push_back(v); // insert val ahead of itr
}
template<typename T> // constructor w/ element [start, end)
List<T>::List(typename List<T>::const_iterator start, typename List<T>::const_iterator end)
{
    init();
    for(auto itr= start; itr != end; ++itr)
        push_back( *itr );
}
template<typename T>   // number of elements
int List<T>::size() const
{
    return theSize;
}
template<typename T>
void List<T>::reverse() // reverse the order of elements
{
    if(!empty())
    {
        auto currptr = head;
        while(currptr != nullptr)
        {
            std::swap(currptr->next, currptr->prev);
            currptr=currptr->prev;
        }
    }
    std::swap(head, tail);
}
template<typename T> // first element
T & List<T>::front()
{
    return *begin();
}
template<typename T>
const T & List<T>::front() const
{
    return *begin();
}
template<typename T> //  last element
T & List<T>::back()
{
    return *(--end());
}
template<typename T> //
const T & List<T>::back() const
{
    return *(--end());
}
template<typename T>
void List<T>::push_front( T && value)
{
    insert(begin(), std::move( value));
}
// insert to the beginning
template<typename T>
void List<T>::push_front(const T & val)
{
    insert(begin(), val);  // insert after Node head
}
template<typename T>
void List<T>::push_back(T && val) // move version insert_back
{
    insert( end(), std::move( val));
}
template<typename T>
void List<T>::pop_front() // delete first element
{
    erase(begin());
}
template<typename T>
void List<T>::clear()
{
    while(!empty())
        pop_back(); // delete all the elements
}
// insert to the end
template<typename T>
void List<T>::push_back(const T & val)
{
    insert(end(), val);
}
template<typename T>
void List<T>::pop_back()
{
    erase(--end()); // erase last element
}
template<typename T>
bool List<T>::empty() const
{
    return size() == 0; //  check if list is empty of nodes
}

template<typename T>
void List<T>::remove(const T & val) // remove all elements with value val
{
    auto itr = begin();

    while(itr != end())
    {
        if(*itr == val)
          itr = erase(itr);

        else
            itr++;
    }

}
template<typename T>
typename List<T>::iterator List<T>::begin()
{
    if(!empty())
    {
        typename List<T>::iterator itr{head->next};
        return itr; // begining node
    }
}
template<typename T>
typename List<T>::const_iterator List<T>::begin() const
{
    if(!empty())
    {
        typename List<T>::const_iterator const_itr{head->next};
        return const_itr;
    }
}
template<typename T>
typename List<T>::iterator List<T>::end()
{
    typename List<T>::iterator itr{ tail };
    return itr; // return the end node
}
template<typename T>
typename List<T>::const_iterator List<T>::end() const
{
    typename List<T>::const_iterator constItr{tail};
    return constItr;
}
template<typename T>
typename List<T>::iterator List<T>::insert(typename List<T>::iterator itr, const T & val)
{
    auto* temptr = itr.current;
    theSize++;
    auto* nptr = new List<T>::Node{val, temptr->prev, temptr};
    temptr->prev->next = nptr;
    temptr->prev = nptr;
    typename List<T>::iterator iter{nptr};
    return iter;
}
template<typename T>
typename List<T>::iterator List<T>::insert(typename List<T>::iterator itr, T && val)
{
    auto* p = itr.current;
    theSize++;
    auto* nptr = new List<T>::Node{ std::move( val ), p->prev, p};
    p->prev->next = nptr;
    p->prev = nptr;
    typename List<T>::iterator iter{nptr};
    return iter;
}
template<typename T>
typename List<T>::iterator List<T>::erase(typename List<T>::iterator start, typename List<T>::iterator end)
{
    for(auto itr = start; itr != end;) // erase from start to end
        itr = erase(itr);

    return end;
}

template<typename T>
typename List<T>::iterator List<T>::erase(typename List<T>::iterator itr)
{  // erase one element
    Node *p = itr.current;
    iterator retVal( p->next );
    p->prev->next = p->next;
    p->next->prev = p->prev;
    delete p;
    --theSize;
    return retVal;

}
template<typename T>
void List<T>::init()  // initalizes list
{
    theSize = 0;
    head = new Node;
    tail = new Node;
    head->next = tail;
    tail->prev = head;
}
// overloading comparison
template<typename T>
bool operator!=(const List<T> & lhs, const List<T> & rhs)
{
    return !(lhs == rhs);
}
template<typename T>
bool operator==(const List<T> & lhs, const List<T> & rhs)
{
    bool f = true;
    if( lhs.size() == rhs.size())
    {
        auto rhs_itr = rhs.begin();
        for(auto lhs_itr=lhs.begin(); lhs_itr !=lhs.end(); ++lhs_itr,++rhs_itr)
        {
            if(*lhs_itr != *rhs_itr)
            {
                f = false;
                break;
            }

        }
        return f;
    }
    else
        return false;
}
// overloading output
template<typename T>
std::ostream & operator<<(std::ostream & os, const List<T> & l)
{
    l.print(os);
    return os;
}
// print out all elements
template<typename T>
void List<T>::print(std::ostream & os, char ofc) const
{
    for(auto itr = begin(); itr != end(); ++itr)
        os << *itr << ofc;  // ofc is the deliminitor

}

template <typename T>
template <typename PREDICATE>
void List<T> :: remove_if(PREDICATE pred)
{
    auto itr = begin();

    while(itr != end())
    {
        if (pred(*itr) == true)
           itr = erase(itr);
        else
        itr++;
    }

}
// End of List Definitions
//-------------------------------------------------------------------------------------------------


template<typename T>
List<T>::const_iterator::const_iterator() : current{nullptr}
{}
// operator* returns the element
template<typename T>
const T & List<T>::const_iterator::operator*() const
{
    return retrieve();
}
// operators various
template<typename T>
typename List<T>::const_iterator & List<T>::const_iterator::operator++()
{  // increment operator, pointer to the next node
    current = current->next;
    return *this;
}
template<typename T>
typename List<T>::const_iterator List<T>::const_iterator::operator++(int)  // ++(int) postfix increment
{ // return a copy of original object and then increment by 1
    const_iterator o = *this;
    ++( *this );
    return o;

}
template<typename T>
typename List<T>::const_iterator & List<T>::const_iterator::operator--() // decrement
{
    current = current->prev;
    return *this;
}
template<typename T>
typename List<T>::const_iterator List<T>::const_iterator::operator--(int) //--(int) posfix decrement
{
    const_iterator o = *this;
    --( *this );
    return o;

}
// comparisons
template<typename T>
bool List<T>::const_iterator::operator==(const typename List<T>::const_iterator & rhs) const
{
    return current == rhs.current; // refer to same element
}
template<typename T>
bool List<T>::const_iterator::operator!=(const typename List<T>::const_iterator & rhs) const
{
    return current != rhs.current; // they don't refer to same element
}
// protected constructor
template<typename T>
List<T>::const_iterator::const_iterator(typename List<T>::Node* p) : current{p}
{
}

template<typename T>
List<T>::iterator::iterator()  // constructor of iterator class
{
}
template<typename T>
T & List<T>::iterator::operator*() // returns data in current node
{
    return const_iterator::retrieve();
}
// refers to current node's data
template<typename T>
T & List<T>::const_iterator::retrieve() const
{
    return current->data;
}
template<typename T>
const T & List<T>::iterator::operator*() const
{
    return const_iterator::operator*();
}
// operator for const iterator
template<typename T>
typename List<T>::iterator & List<T>::iterator::operator++()
{  //puts iterator on next piece of data
    this->current = this->current->next;
    return *this;
}

//pre - increment
template<typename T>
typename List<T>::iterator List<T>::iterator::operator++(int)
{
    auto cpy = *this;
    this->current = this->current->next;
    return cpy;

}
template<typename T>
typename List<T>::iterator & List<T>::iterator::operator--()
{
    this->current = this->current->prev;
    return *this;
}
template<typename T>
typename List<T>::iterator List<T>::iterator::operator--(int)
{
    auto cpy = *this;
    this->current = this->current->prev;	return *this;
}
template<typename T>
List<T>::iterator::iterator(typename List<T>::Node* p) : List<T>::const_iterator{p}
{
    
}
#endif //HW2_LIST_HPP
