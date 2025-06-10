#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <termios.h>
#include <unistd.h>

// Structures
struct pass {
    char username[50];
    char date[2], month[2], year[4];
    char pnumber[15];
    char adharnum[20];
    char fname[20];
    char lname[20];
    char fathname[20];
    char mothname[20];
    char address[50];
    char typeaccount[20];
    char balance[10];
};

struct money {
    char usernameto[50];
    char userpersonfrom[50];
    long int money1;
};

struct userpass {
    char password[50];
};

// Doubly Linked List for Transactions
struct TransactionNode {
    struct money data;
    struct TransactionNode* prev;
    struct TransactionNode* next;
};

struct TransactionNode* head = NULL;

// Function declarations
void clear_screen();
int portable_getch();
void transfermoney(void);
void display(char*);
void checkbalance(char*);
void login(void);
void signin(void);
void accountcreated(void);
void account(void);
void logout(void);
int isValidNumeric(char num[]);
int isValidAdhar(char num[]);
void loadTransactions();

// Utilities
void clear_screen() {
    printf("\033[2J\033[H");
}

int portable_getch() {
    struct termios oldt, newt;
    int ch;
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    ch = getchar();
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    return ch;
}

// Load transactions from file into doubly linked list
void loadTransactions() {
    FILE* fm = fopen("mon.txt", "rb");
    struct money m1;
    if (!fm) return;

    while (fread(&m1, sizeof(struct money), 1, fm)) {
        struct TransactionNode* newNode = (struct TransactionNode*)malloc(sizeof(struct TransactionNode));
        newNode->data = m1;
        newNode->prev = newNode->next = NULL;

        if (head == NULL) {
            head = newNode;
        } else {
            struct TransactionNode* temp = head;
            while (temp->next != NULL) temp = temp->next;
            temp->next = newNode;
            newNode->prev = temp;
        }
    }
    fclose(fm);
}

// Main Menu
int main() {
    int choice;
    clear_screen();
    printf("WELCOME TO BANK ACCOUNT SYSTEM\n\n");
    printf("1. CREATE A BANK ACCOUNT\n");
    printf("2. SIGN IN\n");
    printf("3. EXIT\n\n");
    printf("ENTER YOUR CHOICE: ");
    scanf("%d", &choice);

    switch (choice) {
    case 1:
        clear_screen();
        account();
        break;
    case 2:
        login();
        break;
    case 3:
        exit(0);
    default:
        printf("Invalid choice!\n");
        portable_getch();
        main();
    }
    return 0;
}

// Account Creation
void account() {
    char password[50], ch;
    FILE* fp = fopen("username.txt", "ab");
    struct pass u1;
    int i;

    clear_screen();
    printf("CREATE ACCOUNT\n");

    printf("FIRST NAME: ");
    scanf("%s", u1.fname);
    printf("LAST NAME: ");
    scanf("%s", u1.lname);
    printf("FATHER'S NAME: ");
    scanf("%s", u1.fathname);
    printf("MOTHER'S NAME: ");
    scanf("%s", u1.mothname);
    printf("ADDRESS: ");
    scanf("%s", u1.address);
    printf("ACCOUNT TYPE: ");
    scanf("%s", u1.typeaccount);
    printf("DATE OF BIRTH (DD MM YYYY): ");
    scanf("%s %s %s", u1.date, u1.month, u1.year);
    printf("AADHAR NUMBER: ");
    scanf("%s", u1.adharnum);
    isValidAdhar(u1.adharnum);
    printf("PHONE NUMBER: ");
    scanf("%s", u1.pnumber);
    isValidNumeric(u1.pnumber);
    printf("USERNAME: ");
    scanf("%s", u1.username);

    printf("PASSWORD: ");
    for (i = 0; i < 50; i++) {
        ch = portable_getch();
        if (ch == 13) break;
        password[i] = ch;
        printf("*");
    }
    password[i] = '\0';

    printf("\nDEPOSIT AMOUNT (min ₹1000): ");
    scanf("%s", u1.balance);

    fwrite(&u1, sizeof(u1), 1, fp);
    fclose(fp);

    accountcreated();
}

void accountcreated() {
    clear_screen();
    printf("PLEASE WAIT... CREATING ACCOUNT...\n");
    for (int i = 0; i < 200000000; i++) { i++; i--; }
    printf("ACCOUNT CREATED SUCCESSFULLY!\nPress Enter to login...\n");
    portable_getch();
    login();
}

// Login
void login() {
    clear_screen();
    char username[50], password[50], ch;
    FILE* fp = fopen("username.txt", "rb");
    struct pass u1;
    int found = 0, i;

    if (!fp) {
        printf("Error opening file.\n");
        return;
    }

    printf("LOGIN\nUSERNAME: ");
    scanf("%s", username);
    printf("PASSWORD: ");
    for (i = 0; i < 50; i++) {
        ch = portable_getch();
        if (ch == 13) break;
        password[i] = ch;
        printf("*");
    }
    password[i] = '\0';

    while (fread(&u1, sizeof(u1), 1, fp)) {
        if (strcmp(username, u1.username) == 0) {
            found = 1;
            break;
        }
    }
    fclose(fp);

    if (found) {
        signin();
        loadTransactions();  // Load linked list from file
        display(username);
    } else {
        printf("\nInvalid credentials.\n");
        portable_getch();
        login();
    }
}

void signin() {
    clear_screen();
    printf("Fetching account details...\n");
    for (int i = 0; i < 20000; i++) { i++; i--; }
    printf("LOGIN SUCCESSFUL!\nPress Enter to continue...\n");
    portable_getch();
}

// Display dashboard
void display(char username1[]) {
    clear_screen();
    FILE* fp = fopen("username.txt", "rb");
    struct pass u1;
    int choice;

    if (!fp) {
        printf("Error opening user file.\n");
        return;
    }

    while (fread(&u1, sizeof(u1), 1, fp)) {
        if (strcmp(username1, u1.username) == 0) {
            printf("Welcome, %s %s\n", u1.fname, u1.lname);
            printf("Account Type: %s\n", u1.typeaccount);
            printf("Phone: %s\n", u1.pnumber);
            printf("DOB: %s-%s-%s\n", u1.date, u1.month, u1.year);
            break;
        }
    }
    fclose(fp);

    printf("\n1. Check Balance\n2. Transfer Money\n3. Logout\n4. Exit\nEnter your choice: ");
    scanf("%d", &choice);

    switch (choice) {
    case 1: checkbalance(username1); break;
    case 2: transfermoney(); break;
    case 3: logout(); login(); break;
    case 4: exit(0);
    default: display(username1);
    }
}

// Check Balance using linked list
void checkbalance(char username2[]) {
    clear_screen();
    struct TransactionNode* current = head;
    int i = 1;
    long total = 0;

    printf("=== Transaction History for %s ===\n", username2);
    printf("S.No\tFrom\t\tAmount\n");

    while (current != NULL) {
        if (strcmp(username2, current->data.usernameto) == 0) {
            printf("%d\t%s\t\t%ld\n", i++, current->data.userpersonfrom, current->data.money1);
            total += current->data.money1;
        }
        current = current->next;
    }

    printf("\nTotal Received: ₹%ld\n", total);
    printf("Press any key to return...");
    portable_getch();
    display(username2);
}

// Transfer money and append to file + list
void transfermoney(void) {
    FILE* fm = fopen("mon.txt", "ab");
    FILE* fp = fopen("username.txt", "rb");
    struct pass
