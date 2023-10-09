#pragma once

class LinkedList
{
public:
    struct Node
    {
        int data;
        Node* next;
    };

public:
    void insert(int n)
    {
        if (head_ == nullptr) {
            head_ = new Node(n, nullptr);
            return;
        }

        Node* curr = head_;
        while (curr->next != nullptr)
            curr = curr->next;

        curr->next = new Node(n, nullptr);
    }

    void reverse()
    {
        Node* curr = head_;
        if (head_ == nullptr)
            return;

        Node* prevprev = nullptr;
        Node* prev = curr;

        while (curr->next != nullptr)
        {
            curr = curr->next;
            prev->next = prevprev;
            prevprev = prev;
            prev = curr;
        }

        curr->next = prevprev;
        head_ = curr;
    }

    Node* getHead()
    {
        return head_;
    }

private:
    Node* head_ = nullptr;
};