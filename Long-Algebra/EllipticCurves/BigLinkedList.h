#pragma once
#include "../BigNumber/BigNumber.h"

template <typename T>
class Node {
public:
   T data;
   Node* prev, *next;

   Node(T data) : data(data), prev(nullptr), next(nullptr) {}
   Node(T data, Node* prev, Node* next) : data(data), prev(prev), next(next) {}
};

template <typename T>
class BigLinkedList {
private:
   Node<T>* start, *end;
   BigNumber size;

public:
   BigLinkedList() : start(nullptr), end(nullptr), size("0") {}
   BigNumber get_size() const;
   T get(BigNumber index) const;
   void push_back(T data);
   void pop_back();
   ~BigLinkedList();
};

template <typename T>
BigNumber BigLinkedList<T>::get_size() const {
   return size;
}

template <typename T>
T& BigLinkedList<T>::get(BigNumber index) const {
   if (index >= size) throw std::invalid_argument("list out of range");
   Node<T>* current = start;
   for (BigNumber i = BigNumber("0"); index > i; i = i + BigNumber("1")) {
       current = current->next;
   }
   return current->data;
}

template <typename T>
void BigLinkedList<T>::push_back(T data) {
   if (size == BigNumber("0")) {
       start = end = new Node<T>(data);
   }
   else {
       end = end->next = new Node<T>(data, end, nullptr);
   }
   size = size + BigNumber("1");
}

template <typename T>
void BigLinkedList<T>::pop_back() {
   if (size == BigNumber("0")) return;
   else if (size == BigNumber("1")) {
       delete start;
       start = end = nullptr;
   }
   else {
       Node<T>* temp = end;
       end = end->prev;
       end->next = nullptr;
       delete temp;
   }
   size = size - BigNumber("1");
}

template <typename T>
BigLinkedList<T>::~BigLinkedList() {
   Node<T>* current = start, *to_delete;
   while (current) {
       to_delete = current;
       current = current->next;
       delete to_delete;
   }
}
