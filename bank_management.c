#include <stdio.h>
#include <stdlib.h>

struct account {
    int acc_no;
    char name[50];
    float balance;
};

void createAccount() {
    FILE *fp = fopen("bank.txt", "a");
    struct account a;

    printf("Enter Account Number: ");
    scanf("%d", &a.acc_no);
    printf("Enter Name: ");
    scanf(" %[^\n]", a.name);
    printf("Enter Initial Balance: ");
    scanf("%f", &a.balance);

    fwrite(&a, sizeof(a), 1, fp);
    fclose(fp);

    printf("Account Created Successfully!\n");
}

void deposit() {
    FILE *fp = fopen("bank.txt", "r+");
    struct account a;
    int acc, found = 0;
    float amount;

    printf("Enter Account Number: ");
    scanf("%d", &acc);

    while (fread(&a, sizeof(a), 1, fp)) {
        if (a.acc_no == acc) {
            printf("Enter amount to deposit: ");
            scanf("%f", &amount);

            a.balance += amount;

            fseek(fp, -sizeof(a), SEEK_CUR);
            fwrite(&a, sizeof(a), 1, fp);

            printf("Deposit Successful!\n");
            found = 1;
            break;
        }
    }

    if (!found)
        printf("Account Not Found!\n");

    fclose(fp);
}

void withdraw() {
    FILE *fp = fopen("bank.txt", "r+");
    struct account a;
    int acc, found = 0;
    float amount;

    printf("Enter Account Number: ");
    scanf("%d", &acc);

    while (fread(&a, sizeof(a), 1, fp)) {
        if (a.acc_no == acc) {
            printf("Enter amount to withdraw: ");
            scanf("%f", &amount);

            if (a.balance >= amount) {
                a.balance -= amount;

                fseek(fp, -sizeof(a), SEEK_CUR);
                fwrite(&a, sizeof(a), 1, fp);

                printf("Withdraw Successful!\n");
            } else {
                printf("Insufficient Balance!\n");
            }

            found = 1;
            break;
        }
    }

    if (!found)
        printf("Account Not Found!\n");

    fclose(fp);
}

void checkBalance() {
    FILE *fp = fopen("bank.txt", "r");
    struct account a;
    int acc, found = 0;

    printf("Enter Account Number: ");
    scanf("%d", &acc);

    while (fread(&a, sizeof(a), 1, fp)) {
        if (a.acc_no == acc) {
            printf("Name: %s | Balance: %.2f\n", a.name, a.balance);
            found = 1;
            break;
        }
    }

    if (!found)
        printf("Account Not Found!\n");

    fclose(fp);
}

int main() {
    int choice;

    while (1) {
        printf("\n--- Bank Management ---\n");
        printf("1. Create Account\n");
        printf("2. Deposit\n");
        printf("3. Withdraw\n");
        printf("4. Check Balance\n");
        printf("5. Exit\n");

        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: createAccount(); break;
            case 2: deposit(); break;
            case 3: withdraw(); break;
            case 4: checkBalance(); break;
            case 5: exit(0);
            default: printf("Invalid choice!\n");
        }
    }

    return 0;
}