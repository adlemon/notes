// doubly_linked_list.cpp
// Simple implementation of a doubly linked list.

#include <iostream>

struct LinkedListNode {
  LinkedListNode(int value, LinkedListNode *prev = nullptr,
                 LinkedListNode *next = nullptr)
      : value{value}, prev{prev}, next{next} {}

  int value;
  LinkedListNode *prev;
  LinkedListNode *next;
};

class LinkedList {
public:
  LinkedList() : head_{new LinkedListNode{0}}, tail_{new LinkedListNode{0}} {
    head_->next = tail_;
    tail_->prev = head_;
  }
  ~LinkedList() {
    LinkedListNode *cursor = head_;
    while (cursor) {
      LinkedListNode *next = cursor->next;
      delete cursor;
      cursor = next;
    }
  }

  std::ostream &print(std::ostream &os) const;

  void add_to_front(int x);
  void add_to_back(int x);

  void remove_from_front();
  void remove_from_back();

private:
  void delete_node(LinkedListNode *node);

  LinkedListNode *head_;
  LinkedListNode *tail_;
};

int main() {
  LinkedList lst;

  lst.add_to_back(3);
  lst.add_to_front(2);
  lst.add_to_back(4);
  lst.add_to_front(1);
  lst.add_to_back(5);
  lst.print(std::cout) << "\n";

  lst.remove_from_front();
  lst.print(std::cout) << "\n";

  lst.remove_from_back();
  lst.print(std::cout) << "\n";
}

std::ostream &LinkedList::print(std::ostream &os) const {
  for (LinkedListNode *cursor = head_->next; cursor != tail_;
       cursor = cursor->next) {
    if (cursor != head_->next) {
      os << " <-> ";
    }
    os << cursor->value;
  }
  return os;
}

void LinkedList::add_to_front(int x) {
  LinkedListNode *node = new LinkedListNode{x, head_, head_->next};
  head_->next->prev = node;
  head_->next = node;
}
void LinkedList::add_to_back(int x) {
  LinkedListNode *node = new LinkedListNode{x, tail_->prev, tail_};
  tail_->prev->next = node;
  tail_->prev = node;
}

void LinkedList::delete_node(LinkedListNode *node) {
  node->prev->next = node->next;
  node->next->prev = node->prev;
  delete node;
}

void LinkedList::remove_from_front() {
  if (head_->next == tail_) {
    throw std::runtime_error("remove_from_front called on empty list");
  }
  delete_node(head_->next);
}
void LinkedList::remove_from_back() {
  if (tail_->prev == head_) {
    throw std::runtime_error("remove_from_back called on empty list");
  }
  delete_node(tail_->prev);
}
