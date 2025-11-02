#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void encodeMessage(char message[]);
void decodeMessage(char message[]);
void reverseString(char str[]);
char shiftEncode(char ch);
char shiftDecode(char ch);

void reverseString(char str[]) {
    int len = strlen(str);
    int i;
    for (i = 0; i < len / 2; i++) {
        char temp = str[i];
        str[i] = str[len - i - 1];
        str[len - i - 1] = temp;
    }
}

char shiftEncode(char ch) {
    if (ch >= 32 && ch <= 126) {
        return 32 + ((ch - 32 + 3) % 95); 
    }
    return ch;
}

char shiftDecode(char ch) {
    if (ch >= 32 && ch <= 126) {
        return 32 + ((ch - 32 - 3 + 95) % 95); 
    }
    return ch;
}

void encodeMessage(char message[]) {
    reverseString(message);
    int i;
    for (i = 0; message[i] != '\0'; i++) {
        message[i] = shiftEncode(message[i]);
    }
    printf("\nEncoded Message: %s\n", message);
}

void decodeMessage(char message[]) {
	int i;
    for (i = 0; message[i] != '\0'; i++) {
        message[i] = shiftDecode(message[i]);
    }
    reverseString(message);
    printf("\nDecoded Message: %s\n", message);
}

int main() {
    char message[500];
    int choice;

    while (1) {
        printf("\n==============================");
        printf("\n  TCS Secure Message Utility  ");
        printf("\n==============================");
        printf("\n1. Encode Message");
        printf("\n2. Decode Message");
        printf("\n3. Exit");
        printf("\nEnter your choice: ");
        scanf("%d", &choice);
        getchar(); 

        switch (choice) {
            case 1:
                printf("\nEnter message to encode: ");
                fgets(message, sizeof(message), stdin);
                message[strcspn(message, "\n")] = '\0';
                encodeMessage(message);
                break;

            case 2:
                printf("\nEnter message to decode: ");
                fgets(message, sizeof(message), stdin);
                message[strcspn(message, "\n")] = '\0';
                decodeMessage(message);
                break;

            case 3:
                printf("\nExiting program...\n");
                exit(0);

            default:
                printf("\nInvalid choice! Please try again.\n");
        }
    }

    return 0;
}

