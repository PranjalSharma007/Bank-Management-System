#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <termios.h>
#include <unistd.h>

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

void transfermoney(void);
void display(char *);
void checkbalance(char *);
void login(void);
void signin(void);
void accountcreated(void);
void account(void);
void logout(void);
int isValidNumeric(char num[]);
int isValidAdhar(char num[]);

struct pass
{
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

struct money
{
    char usernameto[50];
    char userpersonfrom[50];
    long int money1;
};

struct userpass
{
    char password[50];
};

int len = 0;

int main()
{
    int i, a, b, choice;
    int passwordlength;

    printf("WELCOME TO BANK ACCOUNT SYSTEM\n\n");
    printf("************\n");
    printf("1.... CREATE A BANK ACCOUNT\n");
    printf("2.... ALREADY A USER? SIGN IN\n");
    printf("3.... EXIT\n\n");
    printf("\n\nENTER YOUR CHOICE..\n");
    scanf("%d", &choice);

    switch (choice)
    {
    case 1:
        clear_screen();
        account();
        break;
    case 2:
        login();
        break;
    case 3:
        exit(0);
        break;
    default:
        printf("Invalid Choice Entered!\n");
        main();
        portable_getch();
    }
}

void account(void)
{
    char password[20];
    int passwordlength, i, seek = 0;
    char ch;
    FILE *fp, *fu;
    struct pass u1;
    struct userpass p1;
    struct userpass u2;

    fp = fopen("username.txt", "ab");
    clear_screen();
    printf("\n\n!!!!!CREATE ACCOUNT!!!!!\n");

    printf("\n\nFIRST NAME..\n");
    scanf("%s", u1.fname);

    printf("\n\n\nLAST NAME..\n");
    scanf("%s", u1.lname);

    printf("\n\nFATHER's NAME..\n");
    scanf("%s", u1.fathname);

    printf("\n\nMOTHER's NAME..\n");
    scanf("%s", u1.mothname);

    printf("\n\nADDRESS..\n");
    scanf("%s", u1.address);

    printf("\n\nACCOUNT TYPE\n");
    scanf("%s", u1.typeaccount);

    printf("\n\nDATE OF BIRTH..\n");
    printf("DATE-");
    scanf("%s", u1.date);

    printf("MONTH-");
    scanf("%s", u1.month);

    printf("YEAR-");
    scanf("%s", u1.year);

    printf("\n\nADHAR NUMBER\n");
    scanf("%s", u1.adharnum);
    isValidAdhar(u1.adharnum);

    printf("\n\nPHONE NUMBER\n");
    scanf("%s", u1.pnumber);

    isValidNumeric(u1.pnumber);

    printf("\n\n USERNAME 50 CHARACTERS MAX!!\n");
    printf("\n\n PASSWORD 50 CHARACTERS MAX!!\n");

    printf("\n\nUSERNAME..\n");
    scanf("%s", u1.username);

    printf("\n\nPASSWORD..\n");
    for (i = 0; i < 50; i++)
    {
        ch = portable_getch();
        if (ch != 13)
        {
            password[i] = ch;
            ch = '*';
            printf("%c", ch);
        }
        else
            break;
    }

    printf("Enter the Deposit Amount(min:1000/-)");
    scanf("%s", u1.balance);

    fwrite(&u1, sizeof(u1), 1, fp);
    fclose(fp);
    accountcreated();
}

void accountcreated(void)
{
    int i;
    char ch;
    clear_screen();
    printf("PLEASE WAIT....\n\nYOUR DATA IS PROCESSING....\n");
    for (i = 0; i < 200000000; i++)
    {
        i++;
        i--;
    }
    printf("ACCOUNT CREATED SUCCESSFULLY....\nPress enter to login\n");
    portable_getch();
    login();
}

void login(void)
{
    clear_screen();
    char username[50];
    char password[50];
    int i, j, k;
    char ch;
    FILE *fp, *fu;
    struct pass u1;
    struct userpass u2;

    fp = fopen("username.txt", "rb");

    if (fp == NULL)
    {
        printf("ERROR IN OPENING FILE");
    }
    printf(" ACCOUNT LOGIN \n");
    printf("********************"
           "************\n");
    printf("==== LOG IN ====\n");

    printf("USERNAME..\n");
    scanf("%s", username);
    printf("PASSWORD..\n");

    for (i = 0; i < 50; i++)
    {
        ch = portable_getch();
        if (ch != 13)
        {
            password[i] = ch;
            ch = '*';
            printf("%c", ch);
        }
        else
            break;
    }

    while (fread(&u1, sizeof(u1), 1, fp))
    {
        if (strcmp(username, u1.username) == 0)
        {
            signin();
            display(username);
        }
    }
    fclose(fp);
}

void signin(void)
{
    int i;
    FILE *fp;
    struct pass u1;
    clear_screen();
    printf("Fetching account details.....\n");
    for (i = 0; i < 20000; i++)
    {
        i++;
        i--;
    }
    printf("LOGIN SUCCESSFUL....\nPress enter to continue\n");
    portable_getch();
}

void display(char username1[])
{
    clear_screen();
    FILE *fp;
    int choice, i;
    fp = fopen("username.txt", "rb");
    struct pass u1;

    if (fp == NULL)
    {
        printf("error in opening file");
    }

    while (fread(&u1, sizeof(u1), 1, fp))
    {
        if (strcmp(username1, u1.username) == 0)
        {
            printf("WELCOME, %s %s\n", u1.fname, u1.lname);
            printf("..........................\n");
            printf("=== YOUR ACCOUNT INFO ===\n");
            printf("*********\n");
            printf("NAME..%s %s\n", u1.fname, u1.lname);
            printf("FATHER's NAME..%s %s\n", u1.fathname, u1.lname);
            printf("MOTHER's NAME..%s\n", u1.mothname);
            printf("ADHAR CARD NUMBER..%s\n", u1.adharnum);
            printf("MOBILE NUMBER..%s\n", u1.pnumber);
    printf("DATE OF BIRTH.. %s-%s-%s\n", u1.date, u1.month, u1.year);
            printf("ADDRESS..%s\n", u1.address);
            printf("ACCOUNT TYPE..%s\n", u1.typeaccount);
        }
    }
    fclose(fp);
    printf(" HOME \n");
    printf("**\n");
    printf(" 1....CHECK BALANCE\n");
    printf(" 2....TRANSFER MONEY\n");
    printf(" 3....LOG OUT\n\n");
    printf(" 4....EXIT\n\n");
    printf(" ENTER YOUR CHOICES..\n");
    scanf("%d", &choice);

    switch (choice)
    {
    case 1:
        checkbalance(username1);
        break;
    case 2:
        transfermoney();
        break;
    case 3:
        logout();
        login();
        break;
    case 4:
        exit(0);
        break;
    }
}

void transfermoney(void)
{
    int i, j;
    FILE *fm, *fp;
    struct pass u1;
    struct money m1;
    char usernamet[20];
    char usernamep[20];
    clear_screen();
    fp = fopen("username.txt", "rb");
    fm = fopen("mon.txt", "ab");

    printf("---- TRANSFER MONEY ----");
    printf("========================");

    printf("FROM (your username).. ");
    scanf("%s", usernamet);

    printf(" TO (username of person)..");
    scanf("%s", usernamep);

    while (fread(&u1, sizeof(u1), 1, fp))
    {
        if (strcmp(usernamep, u1.username) == 0)
        {
            strcpy(m1.usernameto, u1.username);
            strcpy(m1.userpersonfrom, usernamet);
        }
    }

    printf("ENTER THE AMOUNT TO BE TRANSFERRED..");
    scanf("%ld", &m1.money1);

    fwrite(&m1, sizeof(m1), 1, fm);

    printf(
        "--------------------------------------------------"
        "--------------------------------------------");

    printf(
        "--------------------------------------------------"
        "--------------------------------------------");

    printf("Transferring Amount, Please Wait..");

    for (i = 0; i < 70; i++)
    {
        for (j = 0; j < 1200000; j++)
        {
            j++;
            j--;
        }
        printf("*");
    }

    printf("AMOUNT SUCCESSFULLY TRANSFERRED....");
    portable_getch();
    fclose(fp);
    fclose(fm);
    display(usernamet);
}

void checkbalance(char username2[])
{
    clear_screen();
    FILE *fm;
    struct money m1;
    char ch;
    int i = 1, summoney = 0;
    fm = fopen("mon.txt", "rb");

    int k = 5, l = 10;
    int m = 30, n = 10;
    int u = 60, v = 10;

    printf("==== BALANCE DASHBOARD ====");
    printf("*********");
    printf("S no.");
    printf("TRANSACTION ID");
    printf("AMT");

    while (fread(&m1, sizeof(m1), 1, fm))
    {
        if (strcmp(username2, m1.usernameto) == 0)
        {
            printf("%d", i);
            i++;
            printf("%s", m1.userpersonfrom);

    printf("%ld", m1.money1);
            summoney = summoney + m1.money1;
        }
    }

    printf("TOTAL AMT");
    printf("%d", summoney);
    portable_getch();
    fclose(fm);
    display(username2);
}

void logout(void)
{
    int i, j;
    clear_screen();
    printf("Please Wait, Logging Out");

    for (i = 0; i < 10; i++)
    {
        for (j = 0; j < 25000000; j++)
        {
            i++;
            i--;
        }
        printf(".");
    }

    printf("Sign out successfully..\n");
    printf("Press any key to continue....");
    portable_getch();
}

int isValidNumeric(char num[])
{
    len = 0;
    for (int cnt = 0; cnt < 255; cnt++)
    {
        if (num[cnt] == '\0')
            break;
        len++;
        if (isdigit(num[cnt]) == 0)
        {
            len = 0;
            return 4;
        }
    }

    if (len != 10)
    {
        printf("ERROR: Phone No. must be of 10 digits. \n");
        main();
    }
    else
        return 1;

    return 0;
}

int isValidAdhar(char num[])
{
    len = 0;
    for (int cnt = 0; cnt < 255; cnt++)
    {
        if (num[cnt] == '\0')
            break;
        len++;
        if (isdigit(num[cnt]) == 0)
        {
            len = 0;
            return 4;
        }
    }

    if (len != 12)
    {
        printf("ERROR: Aadhar number must be of 12 digits. \n");
        main();
    }
    else
        return 1;

    return 0;
}
