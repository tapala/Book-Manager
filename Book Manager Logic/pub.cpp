#include "pub.h"
#include "pch.h"
#include "Logger.h"
#include <fstream>
#include <sstream>
#include <iostream>

// --- Publication Base ---
Publication::Publication(int id, const string& name)
    : id(id), name(name) {}

// --- Book ---
Book::Book(int id, const string& name)
    : Publication(id, name) {}

string Book::publicationType() const {
    return "Book";
}

// --- Paper ---
Paper::Paper(int id, const string& name)
    : Publication(id, name) {}

string Paper::publicationType() const {
    return "Paper";
}

// --- Node Constructor ---
PublicationList::Node::Node(unique_ptr<Publication> p)
    : publication(move(p)), prev(nullptr), next(nullptr) {}

// --- PublicationList ---
PublicationList::PublicationList()
    : head(nullptr), tail(nullptr), size(0) {}

PublicationList::~PublicationList() {
    Node* current = head;
    while (current) {
        Node* next = current->next;
        delete current;
        current = next;
    }
    Logger::log("PublicationList destroyed. All nodes deallocated.");
}

void PublicationList::addPublication(unique_ptr<Publication> publication) {
    if (!publication) {
        Logger::log("Error: Tried to add null publication.");
        return;
    }

    Logger::log("Adding publication: ID=" + to_string(publication->id) +
        ", Type=" + publication->publicationType() +
        ", Name=\"" + publication->name + "\"");

    Node* newNode = new Node(move(publication));
    if (!head) {
        head = tail = newNode;
    }
    else {
        tail->next = newNode;
        newNode->prev = tail;
        tail = newNode;
    }
    ++size;
}

bool PublicationList::removePublicationById(int id) {
    Node* current = head;
    while (current) {
        if (current->publication->id == id) {
            Logger::log("Removing publication: ID=" + to_string(id));

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

    Logger::log("Warning: Tried to remove non-existent publication with ID=" + to_string(id));
    return false;
}

const Publication* PublicationList::getPublicationByIndex(int index) const {
    if (index < 0 || index >= size) {
        Logger::log("Error: Index out of bounds access in getPublicationByIndex (index=" + to_string(index) + ")");
        return nullptr;
    }

    Node* current = head;
    for (int i = 0; i < index; ++i) current = current->next;
    return current->publication.get();
}

Publication* PublicationList::getPublicationByIndex(int index) {
    if (index < 0 || index >= size) {
        Logger::log("Error: Index out of bounds access in getPublicationByIndex (index=" + to_string(index) + ")");
        return nullptr;
    }

    Node* current = head;
    for (int i = 0; i < index; ++i) current = current->next;
    return current->publication.get();
}

Publication* PublicationList::getPublicationById(int id) {
    Node* current = head;
    while (current) {
        if (current->publication->id == id) return current->publication.get();
        current = current->next;
    }
    return nullptr;
}

int PublicationList::getSize() const {
    return size;
}

Publication& PublicationList::operator[](int index) {
    Publication* ptr = getPublicationByIndex(index);
    if (!ptr) {
        Logger::log("Error: Attempted to access invalid index in operator[]: " + to_string(index));
        throw out_of_range("Index out of bounds");
    }
    return *ptr;
}

const Publication& PublicationList::operator[](int index) const {
    const Publication* ptr = getPublicationByIndex(index);
    if (!ptr) {
        Logger::log("Error: Attempted to access invalid index in const operator[]: " + to_string(index));
        throw out_of_range("Index out of bounds");
    }
    return *ptr;
}

// --- CSV File I/O ---
PublicationList readPublicationsFromCSV(const string& path) {
    PublicationList list;
    ifstream file(path);
    if (!file.is_open()) {
        Logger::log("Error: Failed to open file for reading: " + path);
        return list;
    }

    Logger::log("Reading publications from CSV: " + path);

    string line;
    while (getline(file, line)) {
        stringstream ss(line);
        string type, idStr, name;

        getline(ss, type, ',');
        getline(ss, idStr, ',');
        getline(ss, name);

        try {
            int id = stoi(idStr);
            if (type == "Book") {
                list.addPublication(make_unique<Book>(id, name));
            }
            else if (type == "Paper") {
                list.addPublication(make_unique<Paper>(id, name));
            }
            else {
                Logger::log("Warning: Unknown publication type in CSV: " + type);
            }
        }
        catch (const exception& e) {
            Logger::log("Error parsing CSV line: \"" + line + "\" - " + e.what());
        }
    }

    return list;
}

bool savePublicationsToCSV(const string& path, const PublicationList& list, bool append) {
    ofstream file(path, append ? ios::app : ios::trunc);
    if (!file.is_open()) {
        Logger::log("Error: Failed to open file for writing: " + path);
        return false;
    }

    Logger::log("Saving publications to CSV: " + path + " (append=" + (append ? "true" : "false") + ")");

    for (int i = 0; i < list.getSize(); ++i) {
        const Publication& pub = list[i];
        file << pub.publicationType() << "," << pub.id << "," << pub.name << "\n";
    }

    return true;
}
