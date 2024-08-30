#include <iostream>
#include <string>
#include <map>
#include <set>

using namespace std;

class Book
{
private:
    string isbn;
    string title;
    string authors[3]; 
    double price;

public:
    Book(string isbn, string title, string auths[3], double price)
        : isbn(isbn), title(title), price(price)
    {
        for (int i = 0; i < 3; ++i)
        {
            authors[i] = auths[i];
        }
    }

    string getISBN() const
    {
        return isbn;
    }

    string getTitle() const
    {
        return title;
    }

    double getPrice() const
    {
        return price;
    }

    void disp() const
    {
        cout << "ISBN: " << isbn << endl;
        cout << "Title: " << title << endl;
        cout << "Authors: ";
        for (int i = 0; i < 3; ++i)
        {
            if (!authors[i].empty())
            {
                cout << authors[i] << " ";
            }
        }
        cout << endl;
        cout << "Price: " << price << endl;
    }
};

class BookStore
{
private:
    map<string, pair<Book, int>> books; 

public:
    void addBook(const Book &book, int copies)
    {
        string isbn = book.getISBN();
        if (books.find(isbn) != books.end())
        {
            books[isbn].second += copies;
        }
        else
        {
            books[isbn] = make_pair(book, copies);
        }
    }

    set<string> books() const
    {
        set<string> isbnSet;
        for (const auto &entry : books)
        {
            isbnSet.insert(entry.first);
        }
        return isbnSet;
    }

    int noOfCopies(const string &isbn) const
    {
        if (books.find(isbn) != books.end())
        {
            return books.at(isbn).second;
        }
        return 0;
    }

    double totalPrice() const
    {
        double total = 0;
        for (const auto &entry : books)
        {
            total += entry.second.first.getPrice() * entry.second.second;
        }
        return total;
    }

    void displayBookCopies() const
    {
        for (const auto &entry : books)
        {
            cout << "Title: " << entry.second.first.getTitle()
                 << ", Copies: " << entry.second.second << endl;
        }
    }
};

int main()
{
    string authors1[3] = {"Author A", "Author B", "Author C"};
    Book book1("ISBN123", "Book Title 1", authors1, 250.0);

    string authors2[3] = {"Author X", "Author Y", "Author Z"};
    Book book2("ISBN456", "Book Title 2", authors2, 300.0);

    string authors3[3] = {"Author P", "Author Q", ""}; 
    Book book3("ISBN789", "Book Title 3", authors3, 150.0);

    BookStore store;

    store.addBook(book1, 10); 
    store.addBook(book2, 5);  
    store.addBook(book3, 7);  
    store.addBook(book1, 3); 

    store.displayBookCopies();

    cout << "Total Price of all books: " << store.totalPrice() << endl;

    return 0;
}
