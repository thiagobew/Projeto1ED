// Copyright 2022 Thiago Augusto Bewiahn
#ifndef STRUCTURES_LINKED_LIST_H
#define STRUCTURES_LINKED_LIST_H

#include <cstdint>
#include <stdexcept>

namespace structures {

    template <typename T>
    class DDLinkedList {
    public:
        DDLinkedList();
        ~DDLinkedList();
        void clear();

        void push_back(const T &data);
        void push_front(const T &data);
        void insert(const T &data, std::size_t index);
        void insert_sorted(const T &data);

        T pop(std::size_t index);
        T pop_back();
        T pop_front();
        void remove(const T &data);

        bool empty() const;
        bool contains(const T &data) const;

        T &at(std::size_t index);
        const T &at(std::size_t index) const;

        std::size_t find(const T &data) const;
        std::size_t size() const;

    private:
        class Node {
        public:
            explicit Node(const T &data) : data_{data} {
            }
            Node(const T &data, Node *next);
            Node(const T &data, Node *prev, Node *next);

            T &data() {
                return data_;
            }
            const T &data() const {
                return data_;
            }

            Node *prev() {
                return prev_;
            }
            const Node *prev() const {
                return prev_;
            }

            void prev(Node *node) {
                prev_ = node;
            }

            Node *next() {
                return next_;
            }
            const Node *next() const {
                return next_;
            }

            void next(Node *node) {
                next_ = node;
            }

        private:
            T data_;
            Node *prev_{nullptr};
            Node *next_{nullptr};
        };

        Node *head;
        Node *tail;
        std::size_t size_;
    };

} // namespace structures

#endif

template <typename T>
structures::DDLinkedList<T>::DDLinkedList() {
    head = NULL;
    tail = NULL;
    size_ = 0;
}

template <typename T>
structures::DDLinkedList<T>::~DDLinkedList() {
    while (!empty()) {
        pop_front();
    }
}

template <typename T>
bool structures::DDLinkedList<T>::empty() const {
    return size_ == 0;
}

template <typename T>
void structures::DDLinkedList<T>::clear() {
    size_t fixed_size = size_;

    for (size_t i = 0; i < fixed_size; i++) {
        pop_front();
    }
}

template <typename T>
void structures::DDLinkedList<T>::push_front(const T &data) {
    Node *new_node = new Node(data);

    if (new_node == NULL) {
        throw std::runtime_error("Erro ao alocar memória");
    }

    if (head == NULL) {
        head = new_node;
    } else {
        new_node->next(head);
        new_node->next()->prev(new_node);
        head = new_node;
    }
    size_++;
}

template <typename T>
void structures::DDLinkedList<T>::push_back(const T &data) {
    Node *new_node = new Node(data);

    if (new_node == NULL) {
        throw std::runtime_error("Erro ao alocar memória");
    }

    if (head == NULL) {
        tail = new_node;
        head = new_node;
    } else {
        new_node->prev(tail);
        tail->next(new_node);
        tail = new_node;
    }

    size_++;
}

template <typename T>
void structures::DDLinkedList<T>::insert(const T &data, std::size_t index) {
    if (index > size_) {
        throw std::out_of_range("Index out of range - Insert");
    }

    Node *new_node = new Node(data);

    if (new_node == NULL) {
        throw std::runtime_error("Erro ao alocar memória");
    }

    if (index == 0) {
        push_front(data);
    } else {
        Node *aux = head;
        for (std::size_t i = 0; i < index - 1; ++i) {
            aux = aux->next();
        }
        new_node->next(aux->next());
        aux->next(new_node);
        size_++;
    }
}

template <typename T>
T structures::DDLinkedList<T>::pop_front() {
    if (head == NULL || empty()) {
        throw std::out_of_range("Empty List");
    }

    T data = head->data();
    Node *aux = head;

    if (size_ == 1) {
        head = NULL;
    } else {
        head->next()->prev(NULL);
        head = head->next();
    }

    size_--;
    delete aux;
    return data;
}

template <typename T>
T structures::DDLinkedList<T>::pop_back() {
    if (head == NULL || empty()) {
        throw std::out_of_range("Empty List");
    }

    Node *last = tail;
    T data = tail->data();

    if (size_ == 1) {
        tail = NULL;
        head = NULL;
    } else {
        tail->prev()->next(nullptr);
        tail = tail->prev();
    }

    size_--;
    delete last;
    return data;
}

template <typename T>
T structures::DDLinkedList<T>::pop(std::size_t index) {
    if (index > size_ - 1 || index < 0) {
        throw std::out_of_range("Index out of range - POP");
    }

    if (index == 0) {
        return pop_front();
    } else if (index == size_ - 1) {
        return pop_back();
    }

    Node *node = head;
    for (std::size_t i = 0; i < index; i++) {
        node = node->next();
    }

    node->prev()->next(node->next());
    node->next()->prev(node->prev());
    T data = node->data();
    size_--;

    delete node;
    return data;
}

template <typename T>
void structures::DDLinkedList<T>::insert_sorted(const T &data) {
    Node *new_node = new Node(data);

    if (new_node == NULL) {
        throw std::runtime_error("Erro ao alocar memória");
    }

    if (head == NULL) {
        head = new_node;
        tail = new_node;
    } else {
        Node *current = head;

        while (current->next() != NULL && current->next()->data() < data) {
            current = current->next();
        }

        if (data > current->data()) {
            new_node->next(current->next());
            new_node->prev(current);
            current->next(new_node);
        } else {
            new_node->next(head);
            head = new_node;
        }
    }
    size_++;
}

template <typename T>
void structures::DDLinkedList<T>::remove(const T &data) {
    if (head == NULL) {
        return;
    }

    if (head->data() == data) {
        pop_front();
    } else {
        std::size_t index = find(data);
        if (index != size_) {
            pop(index);
        }
    }
}

template <typename T>
std::size_t structures::DDLinkedList<T>::size() const {
    return size_;
}

template <typename T>
std::size_t structures::DDLinkedList<T>::find(const T &data) const {
    if (head == NULL) {
        return size_;
    }

    Node *current = head;
    std::size_t index = 0;
    while (current != NULL && current->data() != data) {
        current = current->next();
        index++;
    }

    if (current == NULL) {
        return size_;
    }
    return index;
}

template <typename T>
bool structures::DDLinkedList<T>::contains(const T &data) const {
    return find(data) != size_;
}

template <typename T>
T &structures::DDLinkedList<T>::at(std::size_t index) {
    if (index > size_) {
        throw std::out_of_range("Index out of range - AT");
    }

    Node *current = head;
    for (std::size_t i = 0; i < index; ++i) {
        current = current->next();
    }
    return current->data();
}
