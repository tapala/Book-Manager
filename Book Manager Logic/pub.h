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

    virtual string publicationType() const = 0;
};

// Derived class: Book
class Book : public Publication {
public:
    Book(const string& uuid, const string& title, const string& author,
        const string& releaseDate, const string& genre, bool isRead);
    string publicationType() const override;
};

// Derived class: Paper
class Paper : public Publication {
public:
    Paper(const string& uuid, const string& title, const string& author,
        const string& releaseDate, const string& genre, bool isRead);
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
    bool removePublicationById(const string& uuid);
    const Publication* getPublicationByIndex(int index) const;
    Publication* getPublicationByIndex(int index);
    Publication* getPublicationById(const string& uuid);

    int getSize() const;
    Publication& operator[](int index);
    const Publication& operator[](int index) const;
};

// File I/O functions
PublicationList readPublicationsFromCSV(const string& path);
bool savePublicationsToCSV(const string& path, const PublicationList& list, bool append = false);