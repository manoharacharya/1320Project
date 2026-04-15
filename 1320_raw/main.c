/*This is a sample  main file */

/* This main.c looks mess so i would redisrtibute this into seperate .c files 
as per main menu features, will create linked list to store , 
access and modify .txt file which act as our data store point 

***Note*** this is like a sandbox .. so not production ready after building evrything here we 
will migrate codes to different projects and compile it with header and all .c files

RBAC is harder to implement using enum but the best options.
We can still use if/else statements to validate username to do the job. 
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "inventory_management.h"

Role current_role; // Definition of the global role

int check_login(char* user, char* pass) {
    FILE *file = fopen("user_credentials.txt", "r");
    if (file == NULL) {
        printf("Error: Could not open user_credentials.txt\n");
        return 0;
    }

    char file_user[30], file_pass[30];
    int file_role;

    // Reads 3 lines at a time: Username, Password, and Role (0, 1, or 2)
    while (fscanf(file, "%s %s %d", file_user, file_pass, &file_role) != EOF) {
        if (strcmp(user, file_user) == 0 && strcmp(pass, file_pass) == 0) {
            current_role = (Role)file_role; // Save the role for RBAC
            fclose(file);
            return 1;
        }
    }
    fclose(file);
    return 0;
}

int main() {
    int choice;
    int login_attempts = 0;
    char input_user[30], input_pass[30];
    int authenticated = 0;

    // Load existing inventory data from the text file first
    loadInventoryFromFile();

    printf("\n****** Inventory Management System ******\n");
    printf("Developed By: Manohar Acharya | Tess | Kaeden\n");

    while (login_attempts < 4) {
        printf("\n--- Login (Attempt %d/4) ---\n", login_attempts + 1);
        printf("Username: ");
        scanf("%s", input_user);
        printf("Password: ");
        scanf("%s", input_pass);

        if (check_login(input_user, input_pass)) {
            printf("\nLogin Successful! Role Assigned: %d\n", current_role);
            authenticated = 1;
            break;
        } else {
            printf("Invalid credentials.\n");
            login_attempts++;
        }
    }

    if (!authenticated) exit(0);

    while(1) {
        printf("\n1. Dashboard\n2. Inventory Management\n3. Users & Role\n0. Logout\nChoice: ");
        scanf("%d", &choice);
        switch (choice) {
            case 1: dashboard(); break;
            case 2: inventory_Management(); break;
            case 3: user_n_role(); break;
            case 0: exit(0);
            default: printf("Invalid choice.\n");
        }
    }
    return 0;
}