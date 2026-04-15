#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "inventory_management.h"

extern Role current_role;
struct inventory* head = NULL;

void inventory_Management() {
    int choice;
    while(1) {
        printf("\n1. Restock (Add)\n2. Dispatch (Remove)\n5. Display All\n0. Return\nChoice: ");
        scanf("%d", &choice);
        if (choice == 0) return;

        switch (choice) {
            case 1: addItems(); break;
            case 2: removeItems(); break;
            case 5: displayAll_Products(); break;
            default: printf("Invalid choice.\n");
        }
    }
}

// Save the linked list to inventory.txt
void saveInventoryToFile() {
    FILE *fp = fopen("inventory.txt", "w");
    struct inventory* temp = head;
    while(temp) {
        fprintf(fp, "%d %s %s %d %lf %d %d %d\n", 
                temp->product_ID, temp->product_desciption, temp->product_type,
                temp->qty_Number, temp->qty_Pound, 
                temp->exp_year, temp->exp_month, temp->exp_day);
        temp = temp->next;
    }
    fclose(fp);
}

// Load data from inventory.txt into the linked list
void loadInventoryFromFile() {
    FILE *fp = fopen("inventory.txt", "r");
    if (fp == NULL) return;
    while(!feof(fp)) {
        struct inventory* newNode = (struct inventory*)malloc(sizeof(struct inventory));
        if(fscanf(fp, "%d %s %s %d %lf %d %d %d", 
                  &newNode->product_ID, newNode->product_desciption, newNode->product_type,
                  &newNode->qty_Number, &newNode->qty_Pound, 
                  &newNode->exp_year, &newNode->exp_month, &newNode->exp_day) == 8) {
            newNode->next = head;
            head = newNode;
        } else {
            free(newNode);
        }
    }
    fclose(fp);
}

void addItems() {
    // RBAC Check: READONLY users cannot add
    if (current_role == READONLY) {
        printf("\n[ACCESS DENIED] Your role does not allow adding items.\n");
        return;
    }
    // ... Existing code to add a node ...
    saveInventoryToFile(); // Save changes immediately
}

void removeItems() {
    // RBAC Check: Only ADMIN can remove
    if (current_role != ADMIN) {
        printf("\n[ACCESS DENIED] Only Admins can remove items.\n");
        return;
    }
    // ... Existing code to remove a node ...
    saveInventoryToFile(); // Save changes immediately
}

void displayAll_Products() {
    struct inventory* temp = head;
    while(temp) {
        printf("ID: %d | Name: %s\n", temp->product_ID, temp->product_desciption);
        temp = temp->next;
    }
}