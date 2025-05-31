// Book Manager Logic.cpp : Definiuje funkcje biblioteki statycznej.
//

#include "pch.h"
#include "framework.h"
#include "pub.h"
#include "logger.h"
#include <iostream>

using namespace std;

// TODO: To jest przykład funkcji biblioteki
void fnBookManagerLogic()
{
}
void printList(const PublicationList& list) {
    cout << "\n--- Current Publications ---" << endl;
    for (int i = 0; i < list.getSize(); ++i) {
        try {
            const Publication& pub = list[i];
            cout << pub.uuid << ": [" << pub.publicationType() << "] "
                << pub.title << " by " << pub.author
                << ", Released: " << pub.releaseDate
                << ", Genre: " << pub.genre
                << ", Read: " << (pub.isRead ? "Yes" : "No")
                << endl;
        }
        catch (const exception& e) {
            cerr << "Error accessing publication at index " << i << ": " << e.what() << endl;
            Logger::log(string("Exception during printList: ") + e.what());
        }
    }
}

int main() {
    try {
        Logger::log("=== Program started ===");

        PublicationList list;

        Logger::log("Test 1: Adding publications...");
        list.addPublication(make_unique<Book>(string("1"), "The C++ Programming Language", "Bjarne Stroustrup", "2013-05-19", "Programming", false));
        list.addPublication(make_unique<Paper>(string("2"), "AI Research 2025", "Jane Doe", "2024-11-01", "Technology", true));
        list.addPublication(make_unique<Book>(string("3"), "Data Structures in Depth", "John Smith", "2020-01-01", "CS Theory", true));

        printList(list);

        Logger::log("Test 2: Accessing invalid index...");
        try {
            const Publication& p = list[100];  // should throw
            cout << "Unexpected: " << p.title << endl;
        }
        catch (const out_of_range& e) {
            cerr << "Caught out_of_range: " << e.what() << endl;
            Logger::log(string("Expected exception on invalid index: ") + e.what());
        }

        Logger::log("Test 3: Removing publication ID 2...");
        if (list.removePublicationById("2")) {
            cout << "Removed successfully." << endl;
        }

        Logger::log("Test 4: Trying to remove non-existent ID 999...");
        list.removePublicationById("999");

        printList(list);

        Logger::log("Test 5: Saving to file...");
        const string path = "publications.csv";
        if (savePublicationsToCSV(path, list, false)) {
            cout << "File saved successfully." << endl;
        }

        Logger::log("Test 6: Appending another publication and saving...");
        list.addPublication(make_unique<Paper>(string("4"), "Quantum Computing Today", "Alice Quantum", "2025-04-15", "Physics", false));
        savePublicationsToCSV(path, list, true);

        Logger::log("Test 7: Reading from CSV file...");
        PublicationList fromFile = readPublicationsFromCSV(path);
        printList(fromFile);

        Logger::log("Test 8: Reading from non-existent file...");
        PublicationList empty = readPublicationsFromCSV("nonexistent.csv");
        cout << "Finished reading nonexistent file. Size = " << empty.getSize() << endl;

        Logger::log("=== Program completed successfully ===");
    }
    catch (const exception& e) {
        cerr << "Unhandled exception: " << e.what() << endl;
        Logger::log(string("Fatal exception: ") + e.what());
    }
    catch (...) {
        cerr << "Unknown exception occurred!" << endl;
        Logger::log("Fatal unknown exception.");
    }

    return 0;
}