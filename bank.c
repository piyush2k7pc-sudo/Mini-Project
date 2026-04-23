#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>

/* ================= FILE INITIALIZATION ================= */

void initializeFile() {
    FILE *fp;

    fp = fopen("accounts_master.csv", "r");
    if (fp == NULL) {
        fp = fopen("accounts_master.csv", "w");
        fprintf(fp, "AccountNo,Name,PIN,AccountType\n");
    }
    fclose(fp);

    fp = fopen("transactions.csv", "r");
    if (fp == NULL) {
        fp = fopen("transactions.csv", "w");
        fprintf(fp, "AccountNo,Type,Amount,Balance\n");
    }
    fclose(fp);
}

/* ================= ACCOUNT NUMBER GENERATION ================= */

int generateAccountNumber() {
    FILE *fp = fopen("accounts_master.csv", "r");
    char line[200];
    int count = 0;

    if (fp == NULL)
        return 1001;

    fgets(line, sizeof(line), fp);

    while (fgets(line, sizeof(line), fp)) {
        count++;
    }

    fclose(fp);

    return 1000 + count + 1;
}

/* ================= CREATE ACCOUNT ================= */

void createAccount() {
    FILE *fp;
    char name[50], accountType[20];
    int pin, confirmPin, accountNo;
    float balance;
    char ch;
    int i;

    system("cls");

    accountNo = generateAccountNumber();

    printf("===== CREATE ACCOUNT =====\n\n");

    printf("Enter your name: ");
    scanf(" %[^\n]", name);

    while (1) {
        printf("Enter account type (Savings/Current): ");
        scanf("%s", accountType);
        while (getchar() != '\n');

        if (strcmp(accountType, "Savings") == 0 ||
            strcmp(accountType, "savings") == 0 ||
            strcmp(accountType, "Current") == 0 ||
            strcmp(accountType, "current") == 0) {
            break;
        } else {
            printf("Invalid account type. Try again.\n");
        }
    }

    while (1) {
        pin = 0;
        confirmPin = 0;

        printf("Set 4-digit PIN: ");
        i = 0;
        while (i < 4) {
            ch = _getch();
            if (ch >= '0' && ch <= '9') {
                printf("*");
                pin = pin * 10 + (ch - '0');
                i++;
            }
        }
        printf("\n");

        printf("Confirm PIN: ");
        i = 0;
        while (i < 4) {
            ch = _getch();
            if (ch >= '0' && ch <= '9') {
                printf("*");
                confirmPin = confirmPin * 10 + (ch - '0');
                i++;
            }
        }
        printf("\n");

        if (pin == confirmPin && pin >= 1000 && pin <= 9999)
            break;
        else
            printf("PIN mismatch or invalid. Try again.\n");
    }

    do {
        printf("Enter initial deposit (minimum 2000): ");
        scanf("%f", &balance);

        if (balance < 2000) {
            printf("Amount must be at least 2000. Please try again.\n");
        }

    } while (balance < 2000);

    fp = fopen("accounts_master.csv", "a");
    fprintf(fp, "%d,%s,%d,%s\n", accountNo, name, pin, accountType);
    fclose(fp);

    fp = fopen("transactions.csv", "a");
    fprintf(fp, "%d,CREATE,%.2f,%.2f\n", accountNo, balance, balance);
    fclose(fp);

    printf("Account created successfully!\n");
printf("Your Account Number is: %d\n", accountNo);

printf("\nPress any key to continue...");
getch();

}

/* ================= CHECK BALANCE ================= */

void checkBalance(int accountNo) {
    FILE *fp = fopen("transactions.csv", "r");
    char line[200];
    int accNo;
    char type[20];
    float amount, balance, lastBalance = 0;
    int found = 0;

    if (fp == NULL) {
        printf("Transaction file not found.\n");
        return;
    }

    fgets(line, sizeof(line), fp);

    while (fgets(line, sizeof(line), fp)) {
        sscanf(line, "%d,%[^,],%f,%f", &accNo, type, &amount, &balance);

        if (accNo == accountNo) {
            lastBalance = balance;
            found = 1;
        }
    }

    fclose(fp);

    if (found)
        printf("\nCurrent Balance: Rs %.2f\n", lastBalance);
    else
        printf("No transactions found for this account.\n");
}

/* ================= DEPOSIT ================= */

void depositMoney(int accountNo) {
    FILE *fp = fopen("transactions.csv", "r");
    char line[200];
    int accNo;
    char type[20];
    float amount, balance, currentBalance = 0;
    int found = 0;

    if (fp == NULL) {
        printf("Transaction file not found.\n");
        return;
    }

    fgets(line, sizeof(line), fp);

    while (fgets(line, sizeof(line), fp)) {
        sscanf(line, "%d,%[^,],%f,%f", &accNo, type, &amount, &balance);

        if (accNo == accountNo) {
            currentBalance = balance;
            found = 1;
        }
    }

    fclose(fp);

    if (!found) {
        printf("Account not found.\n");
        return;
    }

    printf("Enter amount to deposit: ");
    scanf("%f", &amount);

    if (amount <= 0) {
        printf("Invalid amount. Must be greater than 0.\n");
        return;
    }

    currentBalance += amount;

    fp = fopen("transactions.csv", "a");
    fprintf(fp, "%d,DEPOSIT,%.2f,%.2f\n", accountNo, amount, currentBalance);
    fclose(fp);

    printf("Deposit Successful.\nCurrent Balance: %.2f\n", currentBalance);
}

/* ================= WITHDRAW ================= */

void withdrawMoney(int accountNo) {
    FILE *fp = fopen("transactions.csv", "r");
    char line[200];
    int accNo;
    char type[20];
    float amount, balance, currentBalance = 0;
    int found = 0;

    if (fp == NULL) {
        printf("Transaction file not found.\n");
        return;
    }

    fgets(line, sizeof(line), fp);

    while (fgets(line, sizeof(line), fp)) {
        sscanf(line, "%d,%[^,],%f,%f", &accNo, type, &amount, &balance);

        if (accNo == accountNo) {
            currentBalance = balance;
            found = 1;
        }
    }

    fclose(fp);

    if (!found) {
        printf("Account not found.\n");
        return;
    }

    printf("Enter amount to withdraw: ");
    scanf("%f", &amount);

    if (amount <= 0) {
        printf("Invalid amount. Must be greater than 0.\n");
        return;
    }

    if (currentBalance - amount < 2000) {
        printf("Insufficient Balance.\nMinimum balance of 2000 must be maintained.\n");
        return;
    }

    currentBalance -= amount;

    fp = fopen("transactions.csv", "a");
    fprintf(fp, "%d,WITHDRAW,%.2f,%.2f\n", accountNo, amount, currentBalance);
    fclose(fp);

    printf("Withdraw Successful.\nCurrent Balance: %.2f\n", currentBalance);
}

/* ================= TRANSFER ================= */

void transferMoney(int fromAcc) {
    FILE *fp = fopen("transactions.csv", "r");
    char line[200];
    int accNo, toAcc;
    char type[20];
    float amount, balance;
    float fromBalance = 0, toBalance = 0;
    float tempAmount;
    int fromFound = 0, toFound = 0;

    printf("Enter receiver account number: ");
    scanf("%d", &toAcc);

    if (fromAcc == toAcc) {
        printf("Cannot transfer to your own account.\n");
        return;
    }

    printf("Enter amount to transfer: ");
    scanf("%f", &amount);

    fgets(line, sizeof(line), fp);

    while (fgets(line, sizeof(line), fp)) {
        sscanf(line, "%d,%[^,],%f,%f", &accNo, type, &tempAmount, &balance);

        if (accNo == fromAcc) {
            fromBalance = balance;
            fromFound = 1;
        }

        if (accNo == toAcc) {
            toBalance = balance;
            toFound = 1;
        }
    }

    fclose(fp);

    if (!fromFound) {
        printf("Sender account not found.\n");
        return;
    }

    if (!toFound) {
        printf("Receiver account not found.\n");
        return;
    }

    if (fromBalance - amount < 2000) {
        printf("Insufficient Balance.\nMinimum balance of 2000 must be maintained.\n");
        return;
    }

    fromBalance -= amount;
    toBalance += amount;

    fp = fopen("transactions.csv", "a");
    fprintf(fp, "%d,TRANSFER_OUT,%.2f,%.2f\n", fromAcc, amount, fromBalance);
    fprintf(fp, "%d,TRANSFER_IN,%.2f,%.2f\n", toAcc, amount, toBalance);
    fclose(fp);

    printf("Transfer Successful.\nYour Current Balance: %.2f\n", fromBalance);
}

/* ================= TRANSACTION HISTORY ================= */

void viewTransactions(int accountNo) {
    FILE *fp = fopen("transactions.csv", "r");
    char line[200];
    int accNo;
    char type[20];
    float amount, balance;
    int found = 0;

    if (fp == NULL) {
        printf("Transaction file not found.\n");
        return;
    }

    printf("\n===== TRANSACTION HISTORY =====\n");
    printf("Type\t\tAmount\t\tBalance\n");

    fgets(line, sizeof(line), fp);

    while (fgets(line, sizeof(line), fp)) {
        sscanf(line, "%d, %[^,],%f,%f", &accNo, type, &amount, &balance);

        if (accNo == accountNo) {
            printf("%-15s %-15.2f %-15.2f\n", type, amount, balance);
            found = 1;
        }
    }

    fclose(fp);

    if (!found) {
        printf("No transactions found.\n");
    }
}

/* ================= USER MENU ================= */

void userMenu(int accountNo) {
    int choice;

    do {
        printf("\n====================================");
        printf("\n            USER MENU");
        printf("\n====================================");
        printf("\n  1. Check Balance");
        printf("\n  2. Deposit Money");
        printf("\n  3. Withdraw Money");
        printf("\n  4. Transfer Money");
        printf("\n  5. View Transaction History");
        printf("\n  6. Logout");
        printf("\n------------------------------------");
        printf("\nEnter your choice: ");
        scanf("%d", &choice);

        system("cls");

        switch (choice) {
            case 1: checkBalance(accountNo); break;
            case 2: depositMoney(accountNo); break;
            case 3: withdrawMoney(accountNo); break;
            case 4: transferMoney(accountNo); break;
            case 5: viewTransactions(accountNo); break;
            case 6: printf("Logged out successfully.\n"); break;
            default: printf("Invalid choice.\n");
        }
    } while (choice != 6);
}

/* ================= LOGIN ================= */

void login() {
    FILE *fp;
    int acc, pin, attempts = 0;
    char line[200], ch;
    int i;

    system("cls");
    printf("===== LOGIN =====\n\n");

    while (attempts < 3) {
        int found = 0;
        pin = 0;

        printf("Enter Account Number: ");
        scanf("%d", &acc);
        while (getchar() != '\n');

        fp = fopen("accounts_master.csv", "r");
        if (fp == NULL) {
            printf("Master file not found.\n");
            return;
        }

        fgets(line, sizeof(line), fp);  

        while (fgets(line, sizeof(line), fp)) {
            int accNo, p;
            char name[50], type[20];

            sscanf(line, "%d,%[^,],%d,%[^,]", &accNo, name, &p, type);

            if (accNo == acc) {
                found = 1;
                break;  
            }
        }

        fclose(fp);

        if (!found) {
            printf("Account does not exist.\n");
            attempts++;
            continue;  
        }

        printf("Enter PIN: ");
        i = 0;
        while (i < 4) {
            ch = getch();
            if (ch >= '0' && ch <= '9') {
                printf("*");
                pin = pin * 10 + (ch - '0');
                i++;
            }
        }
        printf("\n");

        fp = fopen("accounts_master.csv", "r");
        fgets(line, sizeof(line), fp);  

        while (fgets(line, sizeof(line), fp)) {
            int accNo, p;
            char name[50], type[20];

            sscanf(line, "%d,%[^,],%d,%[^,]", &accNo, name, &p, type);

            if (accNo == acc && p == pin) {
                fclose(fp);
                system("cls");
                printf("Login successful!\n");
                userMenu(acc);
                return;
            }
        }

        fclose(fp);
        printf("Wrong PIN.\n");
        attempts++;
    }

    printf("Too many wrong attempts. Try again later.\n");
    printf("\nPress Enter to continue...");
    while (getchar() != '\n');
    getchar();
}

/* ================= MAIN ================= */

int main() {
    int choice;

    initializeFile();

    do {
        system("cls");
        printf("\n====================================");
        printf("\n      BANK MANAGEMENT SYSTEM");
        printf("\n====================================");
        printf("\n  1. Login");
        printf("\n  2. Create Account");
        printf("\n  3. Exit");
        printf("\n------------------------------------");
        printf("\nEnter your choice: ");
        if (scanf("%d", &choice) != 1) {
            choice = -1;
        }
        while (getchar() != '\n');

        switch (choice) {
            case 1: system("cls"); login(); break;
            case 2: system("cls"); createAccount(); break;
            case 3:
                printf("Thank you for using Bank Management System.\n");
                exit(0);
            default:
                printf("Invalid choice. Please enter 1, 2 or 3.\n");
        }
    } while (choice != 3);

    return 0;
}