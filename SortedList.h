#pragma once

#include <iostream>
#include <stdexcept>


namespace mtm {
    template<typename T>

    class SortedList {
    private:
        struct Node {
            T data;
            Node *next;
        };

        int size;
        Node *head;

        void clearList() {
            Node *current = head;
            while (current != nullptr) {
                Node *next = current->next;
                delete current;
                current = next;
            }
            head = nullptr;
            size = 0;
        }

        void fillList(const SortedList &toAdd) {
            for (const T &t: toAdd) {
                insert(t);
            }
        }

    public:
        class ConstIterator;
        friend ConstIterator;

        SortedList(): size(0), head(nullptr) {
        }

        SortedList(const SortedList &other) : size(0), head(nullptr) {
            fillList(other);
        }

        ~SortedList() {
            clearList();
        }

        SortedList &operator=(const SortedList &other) {
            if (&other == this) {
                return *this;
            }
            try {
                SortedList toAssign(other);
                int tmpSize = size;
                size = toAssign.length();
                Node *tmp = this->head;
                head = toAssign.head;
                toAssign.head = tmp;
                toAssign.size = tmpSize;
                return *this;
            } catch (const std::runtime_error &e) {
                return *this;
            }
        }

        void insert(const T &toAdd) {
            if (head == nullptr || toAdd > head->data) {
                head = new Node{toAdd, head};
                size++;
                return;
            }
            Node *ptr = head;

            while (ptr != nullptr && ptr->next != nullptr && ptr->next->data > toAdd) {
                ptr = ptr->next;
            }
            ptr->next = new Node{toAdd, ptr->next};
            size++;
        }

        ConstIterator begin() const {
            return ConstIterator(head);
        }

        ConstIterator end() const {
            return ConstIterator();
        }

        void remove(ConstIterator toRemove) {
            if (toRemove.current == nullptr || head == nullptr) {
                return;
            }
            Node *ptr = head;
            if (head == toRemove.current) {
                head = head->next;
                delete ptr;
                size--;
                return;
            }
            while (ptr != nullptr && ptr->next != toRemove.current) {
                ptr = ptr->next;
            }
            if (!ptr || !ptr->next) {
                return;
            }
            Node *toDelete = ptr->next;
            ptr->next = toDelete->next;
            delete toDelete;
            size--;
        }

        int length() const {
            return size;
        }

        template<typename Operation>
        SortedList apply(Operation func) const {
            SortedList newList;

            for (const T &t: *this) {
                newList.insert(func(t));
            }
            return newList;
        }

        template<typename Predicate>
        SortedList filter(Predicate func) const {
            SortedList filtered;

            for (const T &t: *this) {
                if (func(t)) {
                    filtered.insert(t);
                }
            }
            return filtered;
        }
    };

    template<class T>
    class SortedList<T>::ConstIterator {
    private:
        Node *current;

    public:
        friend SortedList;

        ConstIterator() : current(nullptr) {
        }

        ConstIterator(const ConstIterator &toCopy) : current(toCopy.current) {
        }

        ConstIterator(Node *p) : current(p) {
        }

        ConstIterator &operator++() {
            if (!current) {
                throw std::out_of_range("Out of bound");
            }
            current = current->next;
            return *this;
        }

        const T &operator*() const {
            return current->data;
        }

        bool operator!=(const ConstIterator &toCompare) const {
            return current != toCompare.current;
        }
    };
}
