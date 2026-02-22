#include <iostream>
#include <string>
#include <utility>
#include <queue>
#include <algorithm>
#include <limits>
using namespace std;

template <typename T>
struct AVLNode {
    int key;
    T data;
    AVLNode* left;
    AVLNode* right;
    int height;

    AVLNode(int k, const T& d)
        : key(k), data(d), left(nullptr), right(nullptr), height(1) {}
};

template <typename T>
class AVLTree {
private:
    AVLNode<T>* root;

    int height(AVLNode<T>* node) {
        return node ? node->height : 0;
    }

    int balanceFactor(AVLNode<T>* node) {
        return node ? height(node->left) - height(node->right) : 0;
    }

     AVLNode<T>* rightRotate(AVLNode<T>* y) {
        AVLNode<T>* x = y->left;
        AVLNode<T>* T2 = x->right;

        x->right = y;
        y->left = T2;

        y->height = max(height(y->left), height(y->right)) + 1;
        x->height = max(height(x->left), height(x->right)) + 1;

        return x;
    }
     AVLNode<T>* leftRotate(AVLNode<T>* x) {
        AVLNode<T>* y = x->right;
        AVLNode<T>* T2 = y->left;

        y->left = x;
        x->right = T2;

        x->height = max(height(x->left), height(x->right)) + 1;
        y->height = max(height(y->left), height(y->right)) + 1;

        return y;
    }
     AVLNode<T>* insert(AVLNode<T>* node, int key, const T& data) {
        if (!node) return new AVLNode<T>(key, data);

        if (key < node->key) node->left = insert(node->left, key, data);
        else if (key > node->key) node->right = insert(node->right, key, data);
        else return node; // duplicate keys not allowed

        node->height = 1 + max(height(node->left), height(node->right));
        int bf = balanceFactor(node);

        // Left Left Case
        if (bf > 1 && key < node->left->key) return rightRotate(node);
        // Right Right Case
        if (bf < -1 && key > node->right->key) return leftRotate(node);
        // Left Right Case
        if (bf > 1 && key > node->left->key) {
            node->left = leftRotate(node->left);
            return rightRotate(node);
        }
        // Right Left Case
        if (bf < -1 && key < node->right->key) {
            node->right = rightRotate(node->right);
            return leftRotate(node);
        }

        return node;
    }
 AVLNode<T>* search(AVLNode<T>* node, int key) {
        if (!node) return nullptr;
        if (key == node->key) return node;
        if (key < node->key) return search(node->left, key);
        return search(node->right, key);
    }

    void inOrder(AVLNode<T>* node) const {
        if (!node) return;
        inOrder(node->left);
        node->data.display();
        inOrder(node->right);
    }
    
    void destroy(AVLNode<T>* node) {
    if (!node) return;
    destroy(node->left);
    destroy(node->right);
    delete node;
}

   
public:
    AVLTree() : root(nullptr) {}
    
     ~AVLTree() {
    destroy(root);
}

    void insert(int key, const T& data) { root = insert(root, key, data); }

    T* search(int key) {
        AVLNode<T>* node = search(root, key);
        return node ? &(node->data) : nullptr;
    }

    void printInOrder() const { inOrder(root); }
};

    class Book{
       private:
         int id;
         string bookTitle;
         string bookAuthor;
         bool availabilityStatus;

       public:
         Book(int id, const string& title, const string& author)
         : id(id), bookTitle(title), bookAuthor(author), availabilityStatus(true) {}

         int getID() const { return id; }
         string getTitle() const { return bookTitle; }
         string getAuthor() const { return bookAuthor; }
         bool isAvailable() const { return availabilityStatus; }
         void setAvailability(bool status) { availabilityStatus = status; }
         void display(){
                cout << "ID: " << id
                     << ", Title: " << bookTitle
                     << ", Author: " << bookAuthor
                     << ", Available: "
                     << (availabilityStatus ? "Yes" : "No")
                     << endl;
         }
    };
    class Borrower{
        private:
          int borrower_ID;
          string name;
          int* loanHistory;
          int capacity;
          int currentSize;

        public:
          Borrower(int id, const string& name)
           : borrower_ID(id), name(name), capacity(5), currentSize(0)
          {
          loanHistory = new int[capacity];
          } 
          ~Borrower() {
         delete[] loanHistory;
         }

         Borrower(const Borrower& other)
        : borrower_ID(other.borrower_ID),
          name(other.name),
          capacity(other.capacity),
          currentSize(other.currentSize)
    {
        loanHistory = new int[capacity];
        for (int i = 0; i < currentSize; i++) {
            loanHistory[i] = other.loanHistory[i];
        }
    }
    
    Borrower& operator=(const Borrower& other) {
        if (this == &other)
            return *this;

        delete[] loanHistory;

        borrower_ID = other.borrower_ID;
        name = other.name;
        capacity = other.capacity;
        currentSize = other.currentSize;

        loanHistory = new int[capacity];
        for (int i = 0; i < currentSize; i++) {
            loanHistory[i] = other.loanHistory[i];
        }

        return *this;
    }

     int getID() const { return borrower_ID; }
   const string& getName() const { return name; }
           
    bool addLoan(int bookID) {
        if (currentSize == capacity) {
            cout << "Loan limit reached.\n";
            return false;
        }
        loanHistory[currentSize++] = bookID;
        return true;
    }
    void removeLoan(int bookID) {
        for (int i = 0; i < currentSize; i++) {
            if (loanHistory[i] == bookID) {
                for (int j = i; j < currentSize - 1; j++) {
                    loanHistory[j] = loanHistory[j + 1];
                }
                currentSize--;
                return;
            }
        }
    }


   
    void printLoans() const {
        if (currentSize == 0) {
            cout << "No loans\n";
            return;
        }

        for (int i = 0; i < currentSize; i++) {
            cout << loanHistory[i] << endl;
        }
    }
    
    void display() const {
    cout << "ID: " << borrower_ID
         << ", Name: " << name
         << endl;
}

bool isOverdue() const {
    return currentSize > 5;
}

bool hasLoan(int bookID) const {
    for (int i = 0; i < currentSize; i++) {
        if (loanHistory[i] == bookID)
            return true;
    }
    return false;
}


    };

    class LibraryManager {
private:
    AVLTree<Book> books;
    AVLTree<Borrower> borrowers;       
    struct OverdueRecord {
    int days;
    int bookID;

    bool operator<(const OverdueRecord& other) const {
        return days < other.days; // ensures max heap
    }
};

    priority_queue<OverdueRecord> overdueBooks;
    queue<pair<int,int>> transactionQueue; 
    bool bookExists(int bookID) {
    return books.search(bookID) != nullptr;
}
   bool borrowerExists(int borrowerID) {
    return borrowers.search(borrowerID) != nullptr;
}
public:
    void addBook(const Book& book) {
        if (bookExists(book.getID())) {
            cout << "Book ID already exists.\n";
            return;
        } 
        books.insert(book.getID(), book);
        cout << "Book added.\n";
    }
    void addBorrower(const Borrower& borrower) {
         if (borrowerExists(borrower.getID())) {
            cout << "Borrower ID already exists.\n";
            return;
        }  
        borrowers.insert(borrower.getID(), borrower);
        cout << "Borrower added.\n";
    }

    Book* getBookByID(int bookID) {
       return books.search(bookID);
    }

    Borrower* getBorrowerByID(int borrowerID) {
        return borrowers.search(borrowerID);
    }
    
    //edit
    void requestIssue(int bookID, int borrowerID) {
    transactionQueue.push({bookID, borrowerID});
    cout << "Transaction request added to queue.\n";
}
void processNextTransaction() {
    if (transactionQueue.empty()) {
        cout << "No pending transactions.\n";
        return;
    }

    auto request = transactionQueue.front();
    transactionQueue.pop();

    issueBook(request.first, request.second);
}
    void issueBook(int bookID, int borrowerID) {
    Book* book = getBookByID(bookID);
    Borrower* borrower = getBorrowerByID(borrowerID);

    if (!book) { 
        cout << "Book not found.\n"; 
        return; 
    }
    if (!borrower) { 
        cout << "Borrower not found.\n"; 
        return; 
    }

    // Check if the book is available
    if (!book->isAvailable()) { 
        cout << "Book is already issued.\n"; 
        return; 
    }

    // Check if borrower already has this book
    if (borrower->hasLoan(bookID)) {
        cout << "Borrower already has this book.\n";
        return;
    }

   if (!borrower->addLoan(bookID)) {
    return;
}
    // Issue book
    book->setAvailability(false);
    cout << "Book issued successfully.\n";
}


    void returnBook(int bookID, int borrowerID) {
    Book* book = getBookByID(bookID);
    Borrower* borrower = getBorrowerByID(borrowerID);

    if (!book) { 
        cout << "Book not found.\n"; 
        return; 
    }

    if (!borrower) { 
        cout << "Borrower not found.\n"; 
        return; 
    }

    if (!borrower->hasLoan(bookID)) {
        cout << "This borrower did not borrow this book.\n";
        return;
    }

    borrower->removeLoan(bookID);
    book->setAvailability(true);
    cout << "Book returned successfully.\n";
}


    void displayInventory() const {
    cout << "\nLibrary Inventory:\n";
    books.printInOrder();
    }

    void displayBorrowers() const {
    cout << "\nRegistered Borrowers:\n";
    borrowers.printInOrder();
    }

    void addOverdue(int bookID, int daysOverdue) {
        Book* book = getBookByID(bookID);
        if (!book || book->isAvailable()) {
            cout << "Book not found or already available.\n";
            return;
        }
        overdueBooks.push({daysOverdue, bookID});
        cout << "Book registered as overdue.\n";
    }

 void processOverdue() {
    if (overdueBooks.empty()) { 
        cout << "No overdue books.\n"; 
        return; 
    }
    OverdueRecord topOverdue = overdueBooks.top();
    int days = topOverdue.days;
    int bookID = topOverdue.bookID;
    
    overdueBooks.pop();
    cout << "Processing overdue book ID " << bookID
         << " with " << days << " days overdue.\n";
}
};


void displayMenu() {
    cout << "\n";
    cout << "========================================\n";
    cout << "        LIBRARY MANAGEMENT SYSTEM       \n";
    cout << "========================================\n";
    cout << " 1. Add Book\n";
    cout << " 2. Add Borrower\n";
    cout << " 3. Issue Book\n";
    cout << " 4. Return Book\n";
    cout << " 5. Display Inventory\n";
    cout << " 6. Display Borrowers\n";
    cout << " 7. Request Issue (Queue)\n";
    cout << " 8. Process Next Transaction\n";
    cout << " 9. Exit\n";
    cout << "----------------------------------------\n";
    cout << " Enter your menu option: ";
}

int main(){
    LibraryManager lib;
    int option;

  do{
  	displayMenu();
    cin >> option;
    
   


   if (cin.fail()) {
            cin.clear(); 
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
            cout << "Invalid input! Please enter a number between 1 and 9.\n\n";
            continue;
        }
   if (option < 1 || option > 9) {
            cout << "Invalid option! Please choose a number between 1 and 9.\n\n";
            continue;
        }
        
    cout<<endl<<endl; 
    
    if (option==1){
         int id; string title, author;
         cout << "Book ID: "; cin >> id; cin.ignore();
         cout << "Title: "; getline(cin, title);
         cout << "Author: "; getline(cin, author);
         lib.addBook(Book(id, title, author));
    }
   else if (option == 2) {
            int id; string name;
            cout << "Borrower ID: "; cin >> id; cin.ignore();
            cout << "Name: "; getline(cin, name);
            lib.addBorrower(Borrower(id, name));
        }
    else if (option == 3) {
            int bookID, borrowerID;
            cout << "Book ID: "; cin >> bookID;
            cout << "Borrower ID: "; cin >> borrowerID;
            lib.issueBook(bookID, borrowerID);
        }
 else if (option == 4) {
            int bookID, borrowerID;
            cout << "Book ID: "; cin >> bookID;
            cout << "Borrower ID: "; cin >> borrowerID;
            lib.returnBook(bookID, borrowerID);
        }
 else if (option == 5) {
    lib.displayInventory();
}
 else if (option == 6) {
 lib.displayBorrowers();
}
 else if (option == 7){
    int bookID, borrowerID;
    cout << "Book ID: "; cin >> bookID;
    cout << "Borrower ID: "; cin >> borrowerID;
    lib.requestIssue(bookID, borrowerID);
}
  else if (option == 8) {
    lib.processNextTransaction();
}
  } while(option!= 9);

  cout<<"Exiting..."<<endl;
  return 0;
 }
