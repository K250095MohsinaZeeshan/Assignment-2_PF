#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_PRODUCTS 4
#define MAX_CART_ITEMS 100
#define NAME_LENGTH 50
#define CNIC_LENGTH 20

typedef struct {
    char code[4];  
    int quantity;
    float price;
} Product;

typedef struct {
    char productCode[4];
    int quantity;
} CartItem;

typedef struct {
    char name[NAME_LENGTH];
    char cnic[CNIC_LENGTH];
} Customer;

void enterCustomerInfo(Customer *customer);
void displayInventory(Product products[], int size);
void addItemToCart(Product products[], int size, CartItem cart[], int *cartCount);
void updateInventory(Product products[], int size, CartItem cart[], int cartCount);
float calculateTotalBill(Product products[], int size, CartItem cart[], int cartCount);
void showInvoice(Customer customer, float totalBill, int discountApplied);
int findProductIndex(Product products[], int size, char *code);
void clearScreen();

int main() {
    Product products[MAX_PRODUCTS] = {
        {"001", 50, 100},
        {"002", 10, 200},
        {"003", 20, 300},
        {"004", 8,  150}
    };

    CartItem cart[MAX_CART_ITEMS];
    int cartCount = 0;

    Customer customer = {"", ""};
    int customerEntered = 0;

    float totalBill = 0.0;
    int discountApplied = 0;

    int choice;

    do {
        printf("\n=== Supermarket Inventory Management System ===\n");
        printf("1. Enter Customer Information\n");
        printf("2. Display Inventory\n");
        printf("3. Add Item to Cart\n");
        printf("4. Display Total Bill\n");
        printf("5. Show Invoice\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar();
        switch(choice) {
            case 1:
                enterCustomerInfo(&customer);
                customerEntered = 1;
                break;
            case 2:
                displayInventory(products, MAX_PRODUCTS);
                break;
            case 3:
                if (!customerEntered) {
                    printf("Please enter customer information first.\n");
                    break;
                }
                addItemToCart(products, MAX_PRODUCTS, cart, &cartCount);
                break;
            case 4:
                if (!customerEntered) {
                    printf("Please enter customer information first.\n");
                    break;
                }
                if (cartCount == 0) {
                    printf("Cart is empty. Add items first.\n");
                    break;
                }
                totalBill = calculateTotalBill(products, MAX_PRODUCTS, cart, cartCount);

                printf("Do you have a promocode? (yes/no): ");
                char response[10];
                fgets(response, sizeof(response), stdin);
                response[strcspn(response, "\n")] = 0;

                if (strcmp(response, "yes") == 0) {
                    char code[20];
                    printf("Enter promocode: ");
                    fgets(code, sizeof(code), stdin);
                    code[strcspn(code, "\n")] = 0;
                    if (strcmp(code, "Eid2025") == 0) {
                        totalBill *= 0.75;
                        discountApplied = 1;
                        printf("Promocode applied! 25%% discount granted.\n");
                    } else {
                        printf("Invalid promocode. No discount applied.\n");
                        discountApplied = 0;
                    }
                } else {
                    discountApplied = 0;
                }
                updateInventory(products, MAX_PRODUCTS, cart, cartCount);
                break;
            case 5:
                if (!customerEntered) {
                    printf("Please enter customer information first.\n");
                    break;
                }
                if (cartCount == 0) {
                    printf("Cart is empty. Add items first.\n");
                    break;
                }
                showInvoice(customer, totalBill, discountApplied);
                break;
            case 6:
                printf("Exiting program.\n");
                break;
            default:
                printf("Invalid choice, please try again.\n");
        }

        if (choice != 6) {
            printf("\n\nPress Enter to continue...");
            getchar();
            clearScreen(); 
        }

    } while(choice != 6);

    return 0;
}



void clearScreen() {
    system("cls"); 
}

void enterCustomerInfo(Customer *customer) {
    printf("\n--- Enter Customer Information ---\n");
    printf("Enter Customer Name: ");
    fgets(customer->name, NAME_LENGTH, stdin);
    customer->name[strcspn(customer->name, "\n")] = 0;

    printf("Enter CNIC Number: ");
    fgets(customer->cnic, CNIC_LENGTH, stdin);
    customer->cnic[strcspn(customer->cnic, "\n")] = 0;

    printf("Customer information recorded successfully.\n");
}

void displayInventory(Product products[], int size) {
    printf("\n=== Inventory List ===\n");
    printf("Product Code\tQuantity in Stock\tPrice per Product\n");
    printf("-------------------------------------------------------\n");
    int i;
    for (i = 0; i < size; i++) {
        printf("%s\t\t%d\t\t\t%.2f\n", products[i].code, products[i].quantity, products[i].price);
    }
}

int findProductIndex(Product products[], int size, char *code) {
    int i;
    for (i = 0; i < size; i++) {
        if (strcmp(products[i].code, code) == 0) {
            return i;
        }
    }
    return -1;
}

void addItemToCart(Product products[], int size, CartItem cart[], int *cartCount) {
    char code[4];
    int quantity;

    printf("\n--- Add Item to Cart ---\n");
    printf("Enter product code: ");
    fgets(code, sizeof(code), stdin);
    code[strcspn(code, "\n")] = 0;

    int index = findProductIndex(products, size, code);
    if (index == -1) {
        printf("Product code not found.\n");
        return;
    }

    printf("Enter quantity: ");
    scanf("%d", &quantity);
    getchar();

    if (quantity <= 0) {
        printf("Invalid quantity.\n");
        return;
    }

    if (quantity > products[index].quantity) {
        printf("Insufficient stock. Available quantity: %d\n", products[index].quantity);
        return;
    }

    int i;
    for (i = 0; i < *cartCount; i++) {
        if (strcmp(cart[i].productCode, code) == 0) {
            cart[i].quantity += quantity;
            printf("Updated quantity in cart for product %s.\n", code);
            return;
        }
    }

    if (*cartCount < MAX_CART_ITEMS) {
        strcpy(cart[*cartCount].productCode, code);
        cart[*cartCount].quantity = quantity;
        (*cartCount)++;
        printf("Item added to cart successfully.\n");
    } else {
        printf("Cart is full, cannot add more items.\n");
    }
}

void updateInventory(Product products[], int size, CartItem cart[], int cartCount) {
    int i;
    for (i = 0; i < cartCount; i++) {
        int prodIndex = findProductIndex(products, size, cart[i].productCode);
        if (prodIndex != -1) {
            products[prodIndex].quantity -= cart[i].quantity;
        }
    }
    printf("Inventory updated after purchase.\n");
}

float calculateTotalBill(Product products[], int size, CartItem cart[], int cartCount) {
    float total = 0.0;
    printf("\n--- Cart Summary ---\n");
    printf("Product Code\tQuantity\tPrice per Unit\tSubtotal\n");
    printf("--------------------------------------------------------\n");
    int i;
    for (i = 0; i < cartCount; i++) {
        int prodIndex = findProductIndex(products, size, cart[i].productCode);
        if (prodIndex != -1) {
            float subtotal = cart[i].quantity * products[prodIndex].price;
            total += subtotal;
            printf("%s\t\t%d\t\t%.2f\t\t%.2f\n", cart[i].productCode, cart[i].quantity, products[prodIndex].price, subtotal);
        }
    }
    printf("Total Bill (before discount): %.2f\n", total);
    return total;
}

void showInvoice(Customer customer, float totalBill, int discountApplied) {
    printf("\n====== Invoice ======\n");
    printf("Customer Name: %s\n", customer.name);
    printf("CNIC Number: %s\n", customer.cnic);
    printf("Final Bill Amount: %.2f\n", totalBill);
    if (discountApplied) {
        printf("Discount Applied: 25%% (Eid2025 promocode)\n");
    } else {
        printf("No discount applied.\n");
    }
    printf("=====================\n");
}

