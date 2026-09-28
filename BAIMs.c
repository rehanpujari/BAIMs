#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Structure Definitions
struct Item {
    char name[50];     // Item name
    int itemCode;      // Unique item code
    int quantity;      // Quantity in stock
    float price;       // Price per unit
};

// Function Prototypes
void viewItems();     // Displays all items stored in items.txt
void searchItems();   // Searches for an item by its item code
void addItems();      // Adds new items to items.txt
void billing();       // Handles the billing system and updates stock
void dataBackup();    // Creates/updates a backup file of items
int itemExists(int code); // Helper to check duplicate codes

int main() {
    int choice;

    do {
        // Menu Display
        printf("============== BAIM System ==============\n");
        printf("================= MENU ================= \n");
        printf("[1] Add Items\n");
        printf("[2] Search Items\n");
        printf("[3] View All Items\n");
        printf("[4] Billing\n");
        printf("[5] Exit\n");
        printf("Enter your choice: ");

        if (scanf("%d", &choice) != 1) {
            printf("Invalid input. Numbers only!\n");
            while(getchar()!='\n'); // clear buffer
            choice = 0;
        }

        switch(choice) {
            case 1: addItems(); break;
            case 2: searchItems(); break;
            case 3: viewItems(); break;
            case 4: billing(); break;
            case 5:
                printf("Exiting. ByeBye\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }

    } while(choice != 5);

    return 0;
}

// Helper to check if itemCode already exists
int itemExists(int code) {
    struct Item temp;
    FILE *f = fopen("items.txt", "r");
    if (!f) return 0; // no file means no duplicates
    while (fscanf(f, "%d,%49[^,],%d,%f", &temp.itemCode, temp.name, &temp.quantity, &temp.price) == 4) {
        if (temp.itemCode == code) {
            fclose(f);
            return 1; // found duplicate
        }
    }
    fclose(f);
    return 0;
}

// Adds a new item
void addItems() {
    int choice;
    struct Item newItem;
    FILE *f;

    do {
        printf("Enter Item Code: ");
        if (scanf("%d", &newItem.itemCode) != 1) {
            printf("Invalid input. Must be an integer!\n");
            while(getchar()!='\n');
            continue;
        }

        if (itemExists(newItem.itemCode)) {
            printf("Error: Item Code already exists!\n");
            continue;
        }

        printf("Enter Item Name: ");
        scanf("%49s", newItem.name);

        printf("Enter Quantity: ");
        if (scanf("%d", &newItem.quantity) != 1) {
            printf("Invalid input. Must be an integer!\n");
            while(getchar()!='\n');
            continue;
        }

        printf("Enter Price: ");
        if (scanf("%f", &newItem.price) != 1) {
            printf("Invalid input. Must be a number!\n");
            while(getchar()!='\n');
            continue;
        }

        f = fopen("items.txt", "a");
        if (!f) { printf("Error opening file!\n"); return; }
        fprintf(f, "%d,%s,%d,%.2f\n", newItem.itemCode, newItem.name, newItem.quantity, newItem.price);
        fclose(f);

        printf("Item added successfully!\n");
        dataBackup();

        printf("[1] Add More Items\n[2] Main Menu\nEnter choice: ");
        scanf("%d", &choice);
    } while(choice == 1);
}

// Searches for an item by code
void searchItems() {
    struct Item temp;
    int searchItemcode, choice, found;
    FILE *file;

    do {
        file = fopen("items.txt", "r");
        if (!file) { printf("No items available.\n"); return; }

        printf("Enter Item Code to search: ");
        if (scanf("%d", &searchItemcode) != 1) {
            printf("Invalid input!\n");
            while(getchar()!='\n');
            fclose(file);
            return;
        }

        found = 0;
        printf("Code\tName\tQuantity\tPrice\n");
        while (fscanf(file, "%d,%49[^,],%d,%f", &temp.itemCode, temp.name, &temp.quantity, &temp.price) == 4) {
            if (temp.itemCode == searchItemcode) {
                printf("%d\t%s\t%d\t\t%.2f\n", temp.itemCode, temp.name, temp.quantity, temp.price);
                found = 1;
            }
        }
        if (!found) printf("Item code %d not found!\n", searchItemcode);

        fclose(file);

        printf("[1] Search Again\n[2] Main Menu\nEnter choice: ");
        scanf("%d", &choice);
    } while(choice == 1);
}

// Displays all items
void viewItems() {
    struct Item temp;
    FILE *file = fopen("items.txt", "r");
    if (!file) { printf("No items available.\n"); return; }

    printf("Code\tName\tQuantity\tPrice\n");
    int count = 0;
    while (fscanf(file, "%d,%49[^,],%d,%f", &temp.itemCode, temp.name, &temp.quantity, &temp.price) == 4) {
        printf("%d\t%s\t%d\t\t%.2f\n", temp.itemCode, temp.name, temp.quantity, temp.price);
        count++;
    }
    if (count == 0) printf("No items in file.\n");
    fclose(file);
}

// Handles billing
void billing() {
    int code, qty, found, choice;
    float total = 0;
    struct Item temp;

    do {
        FILE *file = fopen("items.txt", "r");
        FILE *tempFile = fopen("temp.txt", "w");
        if (!file || !tempFile) { printf("File error.\n"); return; }

        printf("Enter Item Code to purchase: ");
        if (scanf("%d", &code) != 1) { printf("Invalid input!\n"); while(getchar()!='\n'); fclose(file); fclose(tempFile); return; }
        printf("Enter Quantity: ");
        if (scanf("%d", &qty) != 1) { printf("Invalid input!\n"); while(getchar()!='\n'); fclose(file); fclose(tempFile); return; }

        found = 0;
        while (fscanf(file, "%d,%49[^,],%d,%f", &temp.itemCode, temp.name, &temp.quantity, &temp.price) == 4) {
            if (temp.itemCode == code) {
                found = 1;
                if (qty <= temp.quantity) {
                    float subtotal = qty * temp.price;
                    total += subtotal;
                    printf("%s (x%d) = %.2f\n", temp.name, qty, subtotal);
                    temp.quantity -= qty;
                } else {
                    printf("Insufficient stock. Available: %d\n", temp.quantity);
                }
            }
            fprintf(tempFile, "%d,%s,%d,%.2f\n", temp.itemCode, temp.name, temp.quantity, temp.price);
        }

        if (!found) printf("Item code %d not found!\n", code);

        fclose(file);
        fclose(tempFile);

        remove("items.txt");
        rename("temp.txt", "items.txt");

        printf("[1] Add More Items\n[2] Finish Billing\nEnter choice: ");
        scanf("%d", &choice);

    } while(choice == 1);

    printf("Total Bill Amount = %.2f\n", total);
    dataBackup();
}

// Backup function
void dataBackup() {
    FILE *source = fopen("items.txt", "r");
    FILE *dest = fopen("backup_items.txt", "w");
    if (!source || !dest) { printf("Backup error!\n"); return; }

    char ch;
    while ((ch = fgetc(source)) != EOF) {
        fputc(ch, dest);
    }

    fclose(source);
    fclose(dest);
}
