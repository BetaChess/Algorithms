
#include <iostream>

#include "linked_lists.hpp"


int main()
{
    LinkedList l;

    l.reverse();

    for (size_t i = 0; i < 10; i++)
        l.insert(i);

    for (LinkedList::Node* curr = l.getHead(); curr != nullptr; curr = curr->next)
        std::cout << curr->data << " ";
    std::cout << std::endl;

    l.reverse();

    for (LinkedList::Node* curr = l.getHead(); curr != nullptr; curr = curr->next)
        std::cout << curr->data << " ";

    return 0;
}
