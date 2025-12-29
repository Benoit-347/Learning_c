#include <stdio.h>
#include <stdlib.h>

// Function to insert using Linear Probing
void linearProbing(int hashTable[], int m, int regNumbers[], int n) {
    for (int i = 0; i < n; i++) {
        int key = regNumbers[i];
        int hashIndex = key % m;
        int j = 0;
        while (hashTable[(hashIndex + j) % m] != -1 && j < m)
            j++; // linear probing
        if (j < m)
            hashTable[(hashIndex + j) % m] = key;
        else
            printf("Hash Table is full! Could not insert %d\n", key);
    }
}

// Function to insert using Quadratic Probing
void quadraticProbing(int hashTable[], int m, int regNumbers[], int n) {
    for (int i = 0; i < n; i++) {
        int key = regNumbers[i];
        int hashIndex = key % m;
        int j = 0;
        while (hashTable[(hashIndex + j * j) % m] != -1 && j < m)
            j++; // quadratic probing
        if (j < m)
            hashTable[(hashIndex + j * j) % m] = key;
        else
            printf("Hash Table is full! Could not insert %d\n", key);
    }
}

// Function to display Hash Table
void displayHashTable(int hashTable[], int m) {
    printf("\nHash Table State:\n");
    for (int i = 0; i < m; i++) {
        if (hashTable[i] == -1)
            printf("Slot %d : EMPTY\n", i);
        else
            printf("Slot %d : %d\n", i, hashTable[i]);
    }
}

int main() {
    int m, n, choice;

    printf("Enter number of storage locations (m): ");
    scanf("%d", &m);
    printf("Enter number of vehicle registrations to insert: ");
    scanf("%d", &n);

    int regNumbers[n];
    printf("Enter %d vehicle registration numbers (4-digit):\n", n);
    for (int i = 0; i < n; i++)
    scanf("%d", &regNumbers[i]);

    int hashTable[m];

    while (1) {

        // Initialize hash table as empty
        for (int i = 0; i < m; i++)
            hashTable[i] = -1;

        printf("\n==== Vehicle Registration Hashing ====\n");
        printf("1. Insert using Linear Probing\n");
        printf("2. Insert using Quadratic Probing\n");
        printf("3. Exit\n");

        printf("Enter your choice: ");
        scanf("%d", &choice);
        
        switch (choice) {
            case 1:
                linearProbing(hashTable, m, regNumbers, n);
                displayHashTable(hashTable, m);
                break;
            case 2:
                quadraticProbing(hashTable, m, regNumbers, n);
                displayHashTable(hashTable, m);
                break;
            case 3:
                exit(0);
            default:
                printf("Invalid choice! Try again.\n");
        }
    }
    return 0;
}