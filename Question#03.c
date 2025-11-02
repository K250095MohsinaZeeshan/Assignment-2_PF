#include <stdio.h>
#include <stdlib.h>

#define ROWS 3
#define COLS 3


#define POWER_STATUS       1 << 0  
#define OVERLOAD_WARNING   1 << 1 
#define MAINTENANCE_REQ    1 << 2  


void updateSectorStatus(int grid[ROWS][COLS]);
void querySectorStatus(int grid[ROWS][COLS]);
void runSystemDiagnostic(int grid[ROWS][COLS]);
void printSectorStatus(int status);
void clearScreen();

int main() {
    int grid[ROWS][COLS] = {0}; 
    int choice;

    do {
        printf("\n=== IESCO Power Grid Monitoring ===\n");
        printf("1. Update Sector Status\n");
        printf("2. Query Sector Status\n");
        printf("3. Run System Diagnostic\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch(choice) {
            case 1:
                updateSectorStatus(grid);
                break;
            case 2:
                querySectorStatus(grid);
                break;
            case 3:
                runSystemDiagnostic(grid);
                break;
            case 4:
                printf("Exiting program.\n");
                break;
            default:
                printf("Invalid choice, try again.\n");
        }

        if (choice != 4) {
            printf("\nPress Enter to continue...");
            getchar(); 
            getchar(); 
            clearScreen();
        }

    } while(choice != 4);

    return 0;
}

void clearScreen() {
    system("cls");
}

void updateSectorStatus(int grid[ROWS][COLS]) {
    int row, col, flagChoice, action;

    printf("\n=== Update Sector Status ===\n");
    printf("Enter sector coordinates (row and column) [0-%d] [0-%d]: ", ROWS-1, COLS-1);
    scanf("%d %d", &row, &col);

    if(row < 0 || row >= ROWS || col < 0 || col >= COLS) {
        printf("Invalid coordinates!\n");
        return;
    }

    printf("Select status flag to update:\n");
    printf("1. Power Status (ON/OFF)\n");
    printf("2. Overload Warning (Set/Clear)\n");
    printf("3. Maintenance Required (Set/Clear)\n");
    printf("Enter choice: ");
    scanf("%d", &flagChoice);

    if(flagChoice < 1 || flagChoice > 3) {
        printf("Invalid flag choice.\n");
        return;
    }

    printf("Enter action (1 = Set, 0 = Clear): ");
    scanf("%d", &action);
    if(action != 0 && action != 1) {
        printf("Invalid action.\n");
        return;
    }

    int mask = 0;
    switch(flagChoice) {
        case 1: mask = POWER_STATUS; break;
        case 2: mask = OVERLOAD_WARNING; break;
        case 3: mask = MAINTENANCE_REQ; break;
    }

    if(action == 1) {
        grid[row][col] |= mask; 
        if(flagChoice == 1)
            printf("Power turned ON for sector (%d,%d).\n", row, col);
        else
            printf("Flag set for sector (%d,%d).\n", row, col);
    } else {
        grid[row][col] &= ~mask;
        if(flagChoice == 1)
            printf("Power turned OFF for sector (%d,%d).\n", row, col);
        else
            printf("Flag cleared for sector (%d,%d).\n", row, col);
    }
}

void querySectorStatus(int grid[ROWS][COLS]) {
    int row, col;

    printf("\n=== Query Sector Status ===\n");
    printf("Enter sector coordinates (row and column) [0-%d] [0-%d]: ", ROWS-1, COLS-1);
    scanf("%d %d", &row, &col);

    if(row < 0 || row >= ROWS || col < 0 || col >= COLS) {
        printf("Invalid coordinates!\n");
        return;
    }

    printf("\nSector (%d,%d) Status:\n", row, col);
    printSectorStatus(grid[row][col]);
}
void printSectorStatus(int status) {
    printf("Power Status: %s\n", (status & POWER_STATUS) ? "ON" : "OFF");
    printf("Overload Warning: %s\n", (status & OVERLOAD_WARNING) ? "Overloaded" : "Normal");
    printf("Maintenance Required: %s\n", (status & MAINTENANCE_REQ) ? "Yes" : "No");
}

void runSystemDiagnostic(int grid[ROWS][COLS]) {
    int overloadedCount = 0;
    int maintenanceCount = 0;
    int r, c;

    for(r = 0; r < ROWS; r++) {
        for(c = 0; c < COLS; c++) {
            if(grid[r][c] & OVERLOAD_WARNING) overloadedCount++;
            if(grid[r][c] & MAINTENANCE_REQ) maintenanceCount++;
        }
    }

    printf("\n=== System Diagnostic Report ===\n");
    printf("Total sectors overloaded: %d\n", overloadedCount);
    printf("Total sectors requiring maintenance: %d\n", maintenanceCount);
}

