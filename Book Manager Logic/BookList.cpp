#include "pch.h"
#include "BookList.h"
#include <stdexcept>

BookList::Node::Node(const Book& b) : book(b), prev(nullptr), next(nullptr) {}

BookList::BookList() : head(nullptr), tail(nullptr), size(0) {}

BookList::~BookList() {
    Node* current = head;
    while (current) {
        Node* toDelete = current;
        current = current->next;
        delete toDelete;
    }
}

void BookList::addBook(const Book& book) {
    Node* node = new Node(book);
    if (!head) {
        head = tail = node;
    }
    else {
        tail->next = node;
        node->prev = tail;
        tail = node;
    }
    ++size;
}

bool BookList::removeBookById(int id) {
    Node* current = head;
    while (current) {
        if (current->book.id == id) {
            if (current->prev) current->prev->next = current->next;
            else head = current->next;

            if (current->next) current->next->prev = current->prev;
            else tail = current->prev;

            delete current;
            --size;
            return true;
        }
        current = current->next;
    }
    return false;
}

Book* BookList::getBookByIndex(int index) {
    if (index < 0 || index >= size) return nullptr;
    Node* current = head;
    for (int i = 0; i < index; ++i) current = current->next;
    return &current->book;
}

Book* BookList::getBookById(int id) {
    Node* current = head;
    while (current) {
        if (current->book.id == id) return &current->book;
        current = current->next;
    }
    return nullptr;
}

int BookList::getSize() const {
    return size;
}

Book& BookList::operator[](int index) {
    if (index < 0 || index >= size) {
        throw std::out_of_range("Index out of bounds");
    }
    Node* current = head;
    for (int i = 0; i < index; ++i) {
        current = current->next;
    }
    return current->book;
}

const Book& BookList::operator[](int index) const {
    if (index < 0 || index >= size) {
        throw std::out_of_range("Index out of bounds");
    }
    Node* current = head;
    for (int i = 0; i < index; ++i) {
        current = current->next;
    }
    return current->book;
}
