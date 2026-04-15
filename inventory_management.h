#ifndef INVENTORY_h
#define INVENTORY_h

// Role levels for RBAC
typedef enum { ADMIN = 0, GENERAL = 1, READONLY = 2 } Role;

struct inventory
{
    int product_ID;
    char product_desciption[100];
    char product_type[50];
    int qty_Number;
    double qty_Pound;
    int exp_year, exp_month, exp_day;
    struct inventory* next;
};

// Global variables shared across files
extern struct inventory* head;
extern Role current_role; // Stores the role of the logged-in user

// Function Prototypes
void inventory_Management();
void addItems();
void removeItems();
void search_ItemsId();
void search_ItemsDescription();
void displayAll_Products();

// File handling functions
void saveInventoryToFile();
void loadInventoryFromFile();

// Other main features
void dashboard();
void user_n_role();

#endif