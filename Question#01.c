#include <stdio.h>
#include <string.h>
#include <stdlib.h> 

#define MAX_BOOKS 100
#define TITLE_LENGTH 50

void clearScreen();
void addNewBook(int isbns[], char titles[][TITLE_LENGTH], float prices[], int quantities[], int *count);
void processSale(int isbns[], char titles[][TITLE_LENGTH], float prices[], int quantities[], int count);
void generateLowStockReport(int isbns[], char titles[][TITLE_LENGTH], float prices[], int quantities[], int count);
int findBookIndexByISBN(int isbns[], int count, int isbn);

int main() {
    int isbns[MAX_BOOKS];
    char titles[MAX_BOOKS][TITLE_LENGTH];
    float prices[MAX_BOOKS];
    int quantities[MAX_BOOKS];
    int bookCount = 0;

    int choice;

    do {
        printf("\n=== Liberty Books Inventory Management System ===\n");
        printf("1. Add New Book\n");
        printf("2. Process a Sale\n");
        printf("3. Generate Low-Stock Report\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar(); 

        switch(choice) {
            case 1:
                addNewBook(isbns, titles, prices, quantities, &bookCount);
                break;
            case 2:
                processSale(isbns, titles, prices, quantities, bookCount);
                break;
            case 3:
                generateLowStockReport(isbns, titles, prices, quantities, bookCount);
                break;
            case 4:
                printf("Exiting program.\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }

    } while(choice != 4);

    return 0;
}


void clearScreen() {
    system("cls");
}

void addNewBook(int isbns[], char titles[][TITLE_LENGTH], float prices[], int quantities[], int *count) {
    if (*count >= MAX_BOOKS) {
        printf("\nInventory is full. Cannot add more books.\n");
        printf("Press Enter to continue...");
        getchar();
        clearScreen();
        return;
    }

    int isbn;
    printf("Enter ISBN: ");
    scanf("%d", &isbn);
    getchar(); 

    if (findBookIndexByISBN(isbns, *count, isbn) != -1) {
        printf("Error: A book with ISBN %d already exists.\n", isbn);
        printf("Press Enter to continue...");
        getchar();
        clearScreen();
        return;
    }

    char title[TITLE_LENGTH];
    float price;
    int quantity;

    printf("Enter Title: ");
    fgets(title, TITLE_LENGTH, stdin);
    title[strcspn(title, "\n")] = 0; 

    printf("Enter Price: ");
    scanf("%f", &price);

    printf("Enter Quantity: ");
    scanf("%d", &quantity);
    
    isbns[*count] = isbn;
    strcpy(titles[*count], title);
    prices[*count] = price;
    quantities[*count] = quantity;

    (*count)++;

    printf("\nBook added successfully.\n");
    printf("Press Enter to continue...");
    getchar(); getchar(); 
    clearScreen();
}

void processSale(int isbns[], char titles[][TITLE_LENGTH], float prices[], int quantities[], int count) {
    if (count == 0) {
        printf("\nNo books in inventory.\n");
        printf("Press Enter to continue...");
        getchar(); getchar();
        clearScreen();
        return;
    }

    int isbn, soldQty;
    printf("Enter ISBN to sell: ");
    scanf("%d", &isbn);

    int index = findBookIndexByISBN(isbns, count, isbn);
    if (index == -1) {
        printf("\nBook with ISBN %d not found.\n", isbn);
        printf("Press Enter to continue...");
        getchar(); getchar();
        clearScreen();
        return;
    }

    printf("\nEnter quantity to sell: ");
    scanf("%d", &soldQty);

    if (soldQty <= 0) {
        printf("\nInvalid quantity.\n");
        printf("Press Enter to continue...");
        getchar(); getchar();
        clearScreen();
        return;
    }

    if (quantities[index] < soldQty) {
        printf("Out of stock. Only %d copies available.\n", quantities[index]);
        printf("Press Enter to continue...");
        getchar(); getchar();
        clearScreen();
        return;
    }

    quantities[index] -= soldQty;
    printf("\nSale processed. \n%d copies of \"%s\" sold.\n", soldQty, titles[index]);
    printf("Press Enter to continue...");
    getchar(); getchar();
    clearScreen();
}

void generateLowStockReport(int isbns[], char titles[][TITLE_LENGTH], float prices[], int quantities[], int count) {
    int found = 0;
    printf("\nLow-Stock Report (Quantity < 5):\n");
    printf("ISBN\tTitle\t\tPrice\tQuantity\n");
    printf("---------------------------------------------------\n");
    
    int i;
    for (i = 0; i < count; i++) {
        if (quantities[i] < 5) {
            printf("%d\t%s\t\t%.2f\t%d\n", isbns[i], titles[i], prices[i], quantities[i]);
            found = 1;
        }
    }
    if (!found) {
        printf("No books with low stock.\n");
    }

    printf("Press Enter to continue...\n");
    getchar(); getchar();
    clearScreen();
}

int findBookIndexByISBN(int isbns[], int count, int isbn) {
	int i;
    for (i = 0; i < count; i++) {
        if (isbns[i] == isbn) {
            return i;
        }
    }
    return -1;
}

