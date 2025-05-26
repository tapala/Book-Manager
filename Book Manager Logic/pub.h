#pragma once
#include "pch.h"
#include <string>
#include <memory>

using namespace std;

// Base class for all publication types
class Publication {
public:
    int id;
    string name;

    Publication(int id, const string& name);
    virtual ~Publication() = default;

    virtual string publicationType() const = 0;
};

// Derived class: Book
class Book : public Publication {
public:
    Book(int id, const string& name);
    string publicationType() const override;
};

// Derived class: Paper
class Paper : public Publication {
public:
    Paper(int id, const string& name);
    string publicationType() const override;
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
    bool removePublicationById(int id);
    const Publication* getPublicationByIndex(int index) const;
    Publication* getPublicationByIndex(int index);
    Publication* getPublicationById(int id);

    int getSize() const;
    Publication& operator[](int index);
    const Publication& operator[](int index) const;
};

// File I/O functions
PublicationList readPublicationsFromCSV(const string& path);
bool savePublicationsToCSV(const string& path, const PublicationList& list, bool append = false);
