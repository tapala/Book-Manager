#pragma once
#include "pch.h"
#include <string>
#include <memory>

using namespace std;
// Base class for all publication types
class Publication {
public:
    string uuid;
    string title;
    string author;
    string releaseDate;
    string genre;
    bool isRead;

    Publication(const string& uuid, const string& title, const string& author,
        const string& releaseDate, const string& genre, bool isRead);
    virtual ~Publication() = default;
    virtual unique_ptr<Publication> clone() const = 0;
    virtual string publicationType() const = 0;
};

// Derived class: Book
class Book : public Publication {
public:
    Book(const string& uuid, const string& title, const string& author,
        const string& releaseDate, const string& genre, bool isRead);
    string publicationType() const override;
    unique_ptr<Publication> clone() const override;

};

// Derived class: Paper
class Paper : public Publication {
public:
    Paper(const string& uuid, const string& title, const string& author,
        const string& releaseDate, const string& genre, bool isRead);
    string publicationType() const override;
    unique_ptr<Publication> clone() const override;

};

// List to store Publication objects
class PublicationList {
private:
    struct Node {
        unique_ptr<Publication> publication;
        Node* prev;
        Node* next;

        Node(unique_ptr<Publication> p);
    };

    Node* head;
    Node* tail;
    int size;

public:
    PublicationList();
    ~PublicationList();

    void addPublication(unique_ptr<Publication> publication);
    bool removePublicationById(const string& uuid);
    const Publication* getPublicationByIndex(int index) const;
    Publication* getPublicationByIndex(int index);
    Publication* getPublicationById(const string& uuid);
    void clear();

    int getSize() const;
    Publication& operator[](int index);
    const Publication& operator[](int index) const;

    bool replaceByUuid(const string& uuid, unique_ptr<Publication> newPub);

    class Iterator {
        Node* current;
    public:
        Iterator(Node* node) : current(node) {}
        Publication& operator*() const { return *current->publication; }
        Publication* operator->() const { return current->publication.get(); }
        Iterator& operator++() { current = current->next; return *this; }
        bool operator!=(const Iterator& other) const { return current != other.current; }
    };

    class ConstIterator {
        const Node* current;
    public:
        ConstIterator(const Node* node) : current(node) {}
        const Publication& operator*() const { return *current->publication; }
        const Publication* operator->() const { return current->publication.get(); }
        ConstIterator& operator++() { current = current->next; return *this; }
        bool operator!=(const ConstIterator& other) const { return current != other.current; }
    };

    Iterator begin() { return Iterator(head); }
    Iterator end() { return Iterator(nullptr); }

    ConstIterator begin() const { return ConstIterator(head); }
    ConstIterator end() const { return ConstIterator(nullptr); }
};

// File I/O functions
PublicationList readPublicationsFromCSV(const string& path);
bool savePublicationsToCSV(const string& path, const PublicationList& list, bool append = false);
void printList(const PublicationList& list);