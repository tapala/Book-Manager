#pragma once
#include "pch.h"
#include "Book.h"

class BookList {
private:
    struct Node {
        Book book;
        Node* prev;
        Node* next;

        Node(const Book& b);
    };

    Node* head;
    Node* tail;
    int size;

public:
    BookList();
    ~BookList();

    void addBook(const Book& book);
    bool removeBookById(int id);
    Book* getBookByIndex(int index);
    Book* getBookById(int id);

    int getSize() const;
    Book& operator[](int index);
    const Book& operator[](int index) const;
};
