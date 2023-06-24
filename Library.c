#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_BOOKS 100

typedef struct {
    char title[100];
    char author[100];
    int isBorrowed;
} Book;

typedef struct {
    Book books[MAX_BOOKS];
    int count;
} Library;

void initializeLibrary(Library* library) {
    library->count = 0;
}

void addBook(Library* library, const char* title, const char* author) {
    if (library->count < MAX_BOOKS) {
        Book* newBook = &(library->books[library->count]);
        strcpy(newBook->title, title);
        strcpy(newBook->author, author);
        newBook->isBorrowed = 0;
        library->count++;
        printf("Book added successfully!\n");
    } else {
        printf("Cannot add book. Library is full.\n");
    }
}

int findBookByTitle(Library* library, const char* title) {
    for (int i = 0; i < library->count; i++) {
        if (strcmp(library->books[i].title, title) == 0) {
            return i;
        }
    }
    return -1;
}

void removeBook(Library* library, const char* title) {
    int index = findBookByTitle(library, title);
    if (index != -1) {
        for (int i = index; i < library->count - 1; i++) {
            library->books[i] = library->books[i + 1];
        }
        library->count--;
        printf("Book removed successfully!\n");
    } else {
        printf("Book not found in the library.\n");
    }
}

void borrowBook(Library* library, const char* title) {
    int index = findBookByTitle(library, title);
    if (index != -1) {
        if (library->books[index].isBorrowed) {
            printf("Book is already borrowed.\n");
        } else {
            library->books[index].isBorrowed = 1;
            printf("Book borrowed successfully!\n");
        }
    } else {
        printf("Book not found in the library.\n");
    }
}

void returnBook(Library* library, const char* title) {
    int index = findBookByTitle(library, title);
    if (index != -1) {
        if (library->books[index].isBorrowed) {
            library->books[index].isBorrowed = 0;
            printf("Book returned successfully!\n");
        } else {
            printf("Book is not currently borrowed.\n");
        }
    } else {
        printf("Book not found in the library.\n");
    }
}

void searchBooksByTitle(Library* library, const char* title) {
    int found = 0;
    for (int i = 0; i < library->count; i++) {
        if (strstr(library->books[i].title, title) != NULL) {
            printf("Title: %s, Author: %s, Borrowed: %s\n",
                   library->books[i].title,
                   library->books[i].author,
                   library->books[i].isBorrowed ? "Yes" : "No");
            found = 1;
        }
    }
    if (!found) {
        printf("No books found with the given title.\n");
    }
}

void searchBooksByAuthor(Library* library, const char* author) {
    int found = 0;
    for (int i = 0; i < library->count; i++) {
        if (strstr(library->books[i].author, author) != NULL) {
            printf("Title: %s, Author: %s, Borrowed: %s\n",
                   library->books[i].title,
                   library->books[i].author,
                   library->books[i].isBorrowed ? "Yes" : "No");
            found = 1;
        }
    }
    if (!found) {
        printf("No books found by the given author.\n");
    }
}

void listAllBooks(Library* library) {
    for (int i = 0; i < library->count; i++) {
        printf("Title: %s, Author: %s, Borrowed: %s\n",
               library->books[i].title,
               library->books[i].author,
               library->books[i].isBorrowed ? "Yes" : "No");
    }
}

void listBorrowedBooks(Library* library) {
    int found = 0;
    for (int i = 0; i < library->count; i++) {
        if (library->books[i].isBorrowed) {
            printf("Title: %s, Author: %s\n",
                   library->books[i].title,
                   library->books[i].author);
            found = 1;
        }
    }
    if (!found) {
        printf("No books are currently borrowed.\n");
    }
}

void listAvailableBooks(Library* library) {
    int found = 0;
    for (int i = 0; i < library->count; i++) {
        if (!library->books[i].isBorrowed) {
            printf("Title: %s, Author: %s\n",
                   library->books[i].title,
                   library->books[i].author);
            found = 1;
        }
    }
    if (!found) {
        printf("No books are currently available.\n");
    }
}

void countBooks(Library* library) {
    printf("Total number of books: %d\n", library->count);
}

int main() {
    Library library;
    initializeLibrary(&library);

    int choice;
    char title[100], author[100];

    do {
        printf("========== Library Management System ==========\n");
        printf("1. Add Book\n");
        printf("2. Remove Book\n");
        printf("3. Borrow Book\n");
        printf("4. Return Book\n");
        printf("5. Search Book by Title\n");
        printf("6. Search Book by Author\n");
        printf("7. List All Books\n");
        printf("8. List Borrowed Books\n");
        printf("9. List Available Books\n");
        printf("10. Count Books\n");
        printf("11. Exit\n");
        printf("==============================================\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        printf("\n");

        switch (choice) {
            case 1:
                printf("Enter book title: ");
                scanf(" %[^\n]", title);
                printf("Enter book author: ");
                scanf(" %[^\n]", author);
                addBook(&library, title, author);
                break;

            case 2:
                printf("Enter book title to remove: ");
                scanf(" %[^\n]", title);
                removeBook(&library, title);
                break;

            case 3:
                printf("Enter book title to borrow: ");
                scanf(" %[^\n]", title);
                borrowBook(&library, title);
                break;

            case 4:
                printf("Enter book title to return: ");
                scanf(" %[^\n]", title);
                returnBook(&library, title);
                break;

            case 5:
                printf("Enter book title to search: ");
                scanf(" %[^\n]", title);
                searchBooksByTitle(&library, title);
                break;

            case 6:
                printf("Enter author name to search: ");
                scanf(" %[^\n]", author);
                searchBooksByAuthor(&library, author);
                break;

            case 7:
                listAllBooks(&library);
                break;

            case 8:
                listBorrowedBooks(&library);
                break;

            case 9:
                listAvailableBooks(&library);
                break;

            case 10:
                countBooks(&library);
                break;

            case 11:
                printf("Exiting the program...\n");
                break;

            default:
                printf("Invalid choice! Please try again.\n");
                break;
        }

        printf("\n");
    } while (choice != 11);

    return 0;
}
