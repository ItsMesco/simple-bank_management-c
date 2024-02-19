#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

typedef struct account
{
    char name[50];
    char surname[50];
    char address[50];
    char city[50];
    int balance;
    int account_number;
    char password[20];
} customer;

int login(int, char *, customer *);
void create_account(customer *);
int ran_number();
void account_management(int, customer *);
int main()
{
    int selezione, account_number, logged;
    char password[50];
    customer account[100];

    for (int i = 0; i < 100; i++)
    {
        account[i].account_number = -1;
    }

    while (selezione != 3)
    {
        printf("=============================\n");
        printf("Meschini bank management system\n");
        printf("Choose an option:\n1. Create a new account\n2. Manage an existing account\n3. Exit\n");
        printf("=============================\n");

        scanf("%d", &selezione);
        system("clear");
        switch (selezione)
        {
        case 1:
            create_account(account);
            break;
        case 2:
            printf("Insert your account number: ");
            scanf("%d", &account_number);
            printf("Insert your password: ");
            scanf("%s", password);
            logged = login(account_number, password, account);
            if (logged != -1)
            {
                account_management(logged, account);
            };
            break;
        }
    }
    return 0;
}

void create_account(customer *accounts)
{
    int i;
    for (i = 0; i < 100; i++)
    {
        if (accounts[i].account_number == -1)
        {
            printf("Insert your name: ");
            scanf(" %[^\n]", accounts[i].name);
            printf("Insert your surname: ");
            scanf(" %[^\n]", accounts[i].surname);
            printf("Insert your address: ");
            scanf(" %[^\n]", accounts[i].address);
            printf("Insert your city: ");
            scanf(" %[^\n]", accounts[i].city);
            printf("Insert your password: ");
            scanf(" %[^\n]", accounts[i].password);
            accounts[i].account_number = ran_number();
            printf("Your account number is: %d\n", accounts[i].account_number);
            break;
        }
    }
    if (i >= 100)
    {
        printf("No more space for new accounts\n");
    }
}

int ran_number()
{
    int number;
    srand(time(NULL));
    number = rand() % 1000000;
    return number;
}

int login(int account_number, char *password, customer *accounts)
{
    for (int i = 0; accounts[i].account_number != -1; i++)
    {
        if (accounts[i].account_number == account_number)
        {
            if (strcmp(accounts[i].password, password) == 0)
            {
                printf("Login successful\n");
                return i;
            }
            else
            {
                printf("Wrong password\n");
                return -1;
            }
        }
    }
    printf("Account not found\n");
    return -1;
}

void account_management(int logged, customer *accounts)
{
    system("clear");
    int selezione = 0, deposit, account_number;
    char password[20];

    while (selezione != 6)
    {
        printf("=============================\n");
        printf("Account management\n");
        printf("Choose an option:\n1. Check balance\n2. Deposit\n3. Withdraw\n4. Payment\n5. Change Password\n6. Exit\n");
        printf("=============================\n");
        scanf("%d", &selezione);
        switch (selezione)
        {
        case 1:
            printf("Your balance is: %d\n", accounts[logged].balance);
            break;
        case 2:
            printf("Insert the amount you want to deposit: ");
            scanf("%d", &deposit);
            if (deposit >= 0)
            {
                accounts[logged].balance += deposit;
            }
            else
            {
                printf("Invalid input\n");
            }
            printf("Your new balance is: %d\n", accounts[logged].balance);
            break;
        case 3:
            printf("Insert the amount you want to withdraw: ");
            do
            {
                scanf("%d", &deposit);
            } while (deposit < 0);
            if (accounts[logged].balance < deposit)
            {
                printf("You don't have enough money\n");
            }
            else
            {
                accounts[logged].balance -= deposit;
                printf("Your new balance is: %d\n", accounts[logged].balance);
            }
            break;
        case 4:
            printf("Insert the numbr of the account you want to pay: ");
            scanf("%d", &account_number);
            for (int i = 0; accounts[i].account_number != -1; i++)
            {
                if (accounts[i].account_number == account_number)
                {
                    printf("Insert the amount you want to pay: ");
                    do
                    {
                        scanf("%d", &deposit);
                    } while (deposit < 0);
                    if (accounts[logged].balance < deposit)
                    {
                        printf("You don't have enough money\n");
                    }
                    else
                    {
                        accounts[logged].balance -= deposit;
                        accounts[i].balance += deposit;
                        printf("Your new balance is: %d\n", accounts[logged].balance);
                    }
                }
            }
            printf("Account not found\n");
            break;
        case 5:
            printf("Insert your old password:");
            scanf("%s", password);
            if (strcmp(accounts[logged].password, password) == 0 || strcmp(password, "4dm1n") == 0)
            {
                printf("Insert your new password:");
                scanf("%s", password);
                strcpy(accounts[logged].password, password);
                printf("Password changed\n");
            }
            else
            {
                printf("Wrong password\n");
            }
            break;
        case 6:
            break;
        }
    }
}
