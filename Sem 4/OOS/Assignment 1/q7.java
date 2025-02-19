abstract class Publication {
    int noOfPages;
    double price;
    String publisherName;

    public Publication(int noOfPages, double price, String publisherName) {
        this.noOfPages = noOfPages;
        this.price = price;
        this.publisherName = publisherName;
    }

    int getNoOfPages() {
        return noOfPages;
    }

    double getPrice() {
        return price;
    }

    String getPublisherName() {
        return publisherName;
    }

    abstract void printDetails();
}

class Book extends Publication {
    String authorName;

    Book(int noOfPages, double price, String publisherName, String authorName) {
        super(noOfPages, price, publisherName);
        this.authorName = authorName;
    }

    String getAuthorName() {
        return authorName;
    }

    void setAuthorName(String authorName) {
        this.authorName = authorName;
    }


    void printDetails() {
        System.out.println("Book Details:");
        System.out.println("Pages: " + getNoOfPages());
        System.out.println("Price: " + getPrice());
        System.out.println("Publisher: " + getPublisherName());
        System.out.println("Author: " + authorName);
        System.out.println();
    }
}

class Journal extends Publication {
    String issueNumber;

    Journal(int noOfPages, double price, String publisherName, String issueNumber) {
        super(noOfPages, price, publisherName);
        this.issueNumber = issueNumber;
    }

    String getIssueNumber() {
        return issueNumber;
    }

    void setIssueNumber(String issueNumber) {
        this.issueNumber = issueNumber;
    }

    void printDetails() {
        System.out.println("Journal Details:");
        System.out.println("Pages: " + getNoOfPages());
        System.out.println("Price: " + getPrice());
        System.out.println("Publisher: " + getPublisherName());
        System.out.println("Issue: " + issueNumber);
        System.out.println();
    }
}

class Library {
    Publication[] publications;
    int count;

    public Library(int size) {
        publications = new Publication[size];
        count = 0;
    }

    public void addPublication(Publication pub) {
        if (count < publications.length) {
            publications[count] = pub;
            count++;
        } else {
            System.out.println("Library is full. Cannot add more publications.");
        }
    }

    public void displayPublications() {
        for (int i = 0; i < count; i++) {
            publications[i].printDetails();
        }
    }
}

class q7 {
    public static void main(String[] args) {
        Library library = new Library(5);

        Book book1 = new Book(200, 149.99, "Publisher A", "Author AXZ");
        Book book2 = new Book(300, 249.99, "Publisher B", "Author BFY");
        Book book3 = new Book(150, 149.99, "Publisher C", "Author CJZ");

        Journal journal1 = new Journal(100, 247.99, "Journal Publisher A", "Issue 1");
        Journal journal2 = new Journal(120, 258.99, "Journal Publisher B", "Issue 2");

        library.addPublication(book1);
        library.addPublication(book2);
        library.addPublication(book3);
        library.addPublication(journal1);
        library.addPublication(journal2);
        library.displayPublications();
    }
}
