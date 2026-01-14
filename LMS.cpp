#include <iostream>
#include <fstream>
#include <string>
using namespace std;

struct Book{
    int bookID;
    string title;
    string author;
    bool isIssued;
    Book* next;
};

Book* head = NULL;

//add book
void addBook(){
    Book* newBook = new Book();
    cout<<"Enter Book ID: ";
    cin>>newBook->bookID;
    cin.ignore();
    cout<<"Enter Title: ";
    getline(cin,newBook->title);
    cout<<"Enter Author: ";
    getline(cin,newBook->author);

    newBook->isIssued = false;
    newBook->next = NULL;
    
    if(head == NULL){
        head = newBook;
    }else{
        Book* temp = head;
        while(temp->next != NULL)
            temp = temp->next;
        temp->next = newBook;
    }

    cout << "Book Added Successfully!\n";
}

//Display Books
void displayBooks(){
    if(head == NULL){
        cout<<"No Books Available!!!\n";
        return;
    }

    Book* temp = head;
    while(temp != NULL){
        cout<<"\nID: "<< temp->bookID;
        cout<<"\nTitle : "<< temp->title;
        cout<<"\nAuthor : "<< temp->author;
        cout<<"\nStatus : "<< (temp->isIssued ? "Issued" : "Available") << "\n";
        temp = temp->next;
    }
}

//Search Book
Book* searchBook(int id){
    Book* temp = head;
    while(temp != NULL){
        if(temp->bookID == id)
            return temp;
        temp = temp->next;
    }
    return NULL;
}

//Issue Book
void issueBook(){
    int id;
    cout<<"Enter Book ID to issue: ";
    cin>>id;

    Book* book = searchBook(id);
    if (book == NULL) {
        cout << "Book not found!\n";
    } else if (book->isIssued) {
        cout << "Book already issued!\n";
    } else {
        book->isIssued = true;
        cout << "Book issued successfully.\n";
    }
}

// Return Book
void returnBook() {
    int id;
    cout << "Enter Book ID to return: ";
    cin >> id;

    Book* book = searchBook(id);
    if (book == NULL) {
        cout << "Book not found!\n";
    } else if (!book->isIssued) {
        cout << "Book was not issued!\n";
    } else {
        book->isIssued = false;
        cout << "Book returned successfully.\n";
    }
}

// Delete Book
void deleteBook() {
    int id;
    cout << "Enter Book ID to delete: ";
    cin >> id;

    if (head == NULL) return;

    if (head->bookID == id) {
        Book* temp = head;
        head = head->next;
        delete temp;
        cout << "Book deleted.\n";
        return;
    }

    Book* curr = head;
    while (curr->next != NULL && curr->next->bookID != id)
        curr = curr->next;

    if (curr->next == NULL) {
        cout << "Book not found.\n";
    } else {
        Book* temp = curr->next;
        curr->next = temp->next;
        delete temp;
        cout << "Book deleted.\n";
    }
}

void saveToFile() {
    ofstream file("library.txt");

    Book* temp = head;
    while (temp != NULL) {
        file << temp->bookID << "|"
             << temp->title << "|"
             << temp->author << "|"
             << temp->isIssued << "\n";
        temp = temp->next;
    }

    file.close();
}

void loadFromFile() {
    ifstream file("library.txt");
    if (!file)
        return;

    while (!file.eof()) {
        Book* newBook = new Book();
        string issued;

        file >> newBook->bookID;
        if (file.fail()) break;
        file.ignore();

        getline(file, newBook->title, '|');
        getline(file, newBook->author, '|');
        getline(file, issued);

        newBook->isIssued = stoi(issued);
        newBook->next = NULL;

        if (head == NULL)
            head = newBook;
        else {
            Book* temp = head;
            while (temp->next != NULL)
                temp = temp->next;
            temp->next = newBook;
        }
    }

    file.close();
}


// Main Menu
int main() {
    loadFromFile();   

    int choice;
    do {
        cout << "\n--- Library Management System ---\n";
        cout << "1. Add Book\n2. Display Books\n3. Issue Book\n";
        cout << "4. Return Book\n5. Delete Book\n6. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
            case 1: addBook(); break;
            case 2: displayBooks(); break;
            case 3: issueBook(); break;
            case 4: returnBook(); break;
            case 5: deleteBook(); break;
            case 6:
                saveToFile();   
                cout << "Data saved. Exiting...\n";
                break;
            default:
                cout << "Invalid choice!\n";
        }
    } while (choice != 6);

    return 0;
}
