#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

int mexit;
void menu();
void menu2();
void signin();
void depo();
void withdraw();
void close();
void sendu();
void send1();
void send2();
void cut();
typedef struct Node
{
    char name[60];
    int id_no;
    int secu;
    long long phone;

    float taka;

} node;

node *use, *check, *myid, *transaction, *receiver;

void new_acc()
{
    int choice;
    char conf[5];
    FILE *ptr;
    ptr = fopen("database.dat", "a+");

    use = (node *)malloc(sizeof(node));
    check = (node *)malloc(sizeof(node));

account_no:
    printf("\t\t\t==== ADD RECORD  ====");
    printf("\nEnter the ID number:\n");
    scanf("%d", &check->id_no);
    while (fscanf(ptr, "%d %s %d %lld %f\n", &use->id_no, use->name, &use->secu, &use->phone, &use->taka) != EOF)
    {
        if (check->id_no == use->id_no)
        {
            printf("ID no. already in use!\n");

            goto account_no;
        }
    }
    use->id_no = check->id_no;
correct:
    printf("\nEnter the username(NO SPACE): ");
    scanf("%s", use->name);
    printf("\nEnter the Security PIN: :");
    scanf("%d", &use->secu);
    printf("\nEnter the phone number: (+880) ");
    scanf("%lld", &use->phone);

    system("cls");
    printf("\n\n===== ACCOUNT DETAILS =====\n\nID: %d\nUsername: %s\nSecurity PIN: %d\nPhone number: +88%lld\n\n    CONFIRM?\n", use->id_no, use->name, use->secu, use->phone);
y_n:
    printf("\nPress 'yes' or 'no'.\n");
    scanf("%s", conf);

    if ((strcmp(conf, "yes") == 0) || (strcmp(conf, "YES") == 0))
    {
        printf("\nEnter Initial deposit in BDT: ");
        scanf("%f", &use->taka);

        fprintf(ptr, "%d %s %d %lld %f\n", use->id_no, use->name, use->secu, use->phone, use->taka);

        fclose(ptr);
        printf("\nAccount created successfully!\n");
        Beep(500, 500);
    }
    else if ((strcmp(conf, "no") == 0) || (strcmp(conf, "NO") == 0))
    {
        goto correct;
    }
    else
    {
        printf("\nInvalid!\a");
        goto y_n;
    }

use_invalid:
    printf("\n\n\n\t\tEnter 1 to go to the main menu and 0 to exit:");
    scanf("%d", &mexit);
    system("cls");
    if (mexit == 1)
        menu();
    else if (mexit == 0)
        close();
    else
    {
        printf("\nInvalid!\a");
        goto use_invalid;
    }
}

void depo(void)
{
    int choice, flag = 0;

    transaction = (node *)malloc(sizeof(node));

    FILE *old, *newrec;
    old = fopen("database.dat", "a+");
    newrec = fopen("new.dat", "a+");

    while (fscanf(old, "%d %s %d %lld %f ", &use->id_no, use->name, &use->secu, &use->phone, &use->taka) != EOF)
    {
        if (use->id_no == myid->id_no)
        {
            flag = 1;

            printf("Enter the amount you want to deposit BDT: ");
            scanf("%f", &transaction->taka);
            use->taka += transaction->taka;
            fprintf(newrec, "%d %s %d %lld %f\n", use->id_no, use->name, use->secu, use->phone, use->taka);
            printf("\n\nDeposited successfully!");
        }
        else
        {
            fprintf(newrec, "%d %s %d %lld %f\n", use->id_no, use->name, use->secu, use->phone, use->taka);
        }
    }
    fclose(old);
    fclose(newrec);
    remove("database.dat");
    rename("new.dat", "database.dat");
    if (flag != 1)
    {
        printf("\n\nRecord not found!!\n\n");
    depo_invalid:
        printf("\n\n\nEnter 0 to try again,1 to return to main menu and 2 to exit:");
        scanf("%d", &mexit);
        system("cls");
        if (mexit == 0)
            depo();
        else if (mexit == 1)
            menu();
        else if (mexit == 2)
            close();
        else
        {
            printf("\nInvalid!");
            goto depo_invalid;
        }
    }
    else
    {
        printf("\nEnter 1 to go to the home menu and 0 to exit:");
        scanf("%d", &mexit);
        system("cls");
        if (mexit == 1)
            menu2();
        else
            close();
    }
}

void withdraw(void)
{
    int choice, flag = 0;

    transaction = (node *)malloc(sizeof(node));

    FILE *old, *newrec;
    old = fopen("database.dat", "a+");
    newrec = fopen("new.dat", "a+");

    while (fscanf(old, "%d %s %d %lld %f ", &use->id_no, use->name, &use->secu, &use->phone, &use->taka) != EOF)
    {

        if (use->id_no == myid->id_no)
        {

            flag = 1;
        taka_nai:

            printf("Enter the amount you want to withdraw BDT: ");
            scanf("%f", &transaction->taka);
            if (use->taka > transaction->taka)
            {
                use->taka -= transaction->taka;
                fprintf(newrec, "%d %s %d %lld %f \n", use->id_no, use->name, use->secu, use->phone, use->taka);
                printf("\n\nWithdrawn successfully!\n");
            }
            else
            {
                printf("\n\nNot Enough Money!\n");
                goto taka_nai;
            }
        }
        else
        {
            fprintf(newrec, "%d %s %d %lld %f \n", use->id_no, use->name, use->secu, use->phone, use->taka);
        }
    }
    fclose(old);
    fclose(newrec);
    remove("database.dat");
    rename("new.dat", "database.dat");
    if (flag != 1)
    {
        printf("\n\nRecord not found!!");
    withdraw_invalid:
        printf("\n\n\nEnter 0 to try again,1 to return to home menu and 2 to exit:");
        scanf("%d", &mexit);
        system("cls");
        if (mexit == 0)
            withdraw();
        else if (mexit == 1)
            menu2();
        else if (mexit == 2)
            close();
        else
        {
            printf("\nInvalid!");
            goto withdraw_invalid;
        }
    }
    else
    {
        printf("\nEnter 1 to go to the home menu and 0 to exit:");
        scanf("%d", &mexit);
        system("cls");
        if (mexit == 1)
            menu2();
        else
            close();
    }
}

void send1(void)
{
    system("cls");
    int choice, flag = 0;
    printf("\n\n\t\t\t         ==ULAB MOBILE BANKING==");
    printf("\n\n\n\t\t\t====== WELCOME TO THE SENDMONEY MENU ======");

    receiver = (node *)malloc(sizeof(node));
    transaction = (node *)malloc(sizeof(node));

rid:
    printf("\n\nEnter Receiver's ID:");
    scanf("%d", &transaction->id_no);
    FILE *old, *newrec;
    old = fopen("database.dat", "a+");
    newrec = fopen("new.dat", "a+");

    while (fscanf(old, "%d %s %d %lld %f ", &receiver->id_no, receiver->name, &receiver->secu, &receiver->phone, &receiver->taka) != EOF)
    {
        if (receiver->id_no == transaction->id_no)
        {
            flag = 1;
            fprintf(newrec, "%d %s %d %lld %f\n", receiver->id_no, receiver->name, receiver->secu, receiver->phone, receiver->taka);
        }
        else
        {

            fprintf(newrec, "%d %s %d %lld %f \n", receiver->id_no, receiver->name, receiver->secu, receiver->phone, receiver->taka);
        }
    }
    fclose(old);
    fclose(newrec);
    remove("database.dat");
    rename("new.dat", "database.dat");
    if (flag != 1)
    {
        printf("\n\nID not found!!\n\n");
        goto rid;
    }
    else
    {
        send2();
    }
}

void send2(void)
{

    int choice, flag = 0;
    system("cls");
    printf("\n\n\t\t\t         ==ULAB MOBILE BANKING==");
    printf("\n\n\n\t\t\t====== WELCOME TO THE SENDMONEY MENU ======");

    transaction = (node *)malloc(sizeof(node));

rtaka:
    printf("\n\nEnter Send Money Amount BDT: ");
    scanf("%f", &transaction->taka);

    FILE *old, *newrec;
    old = fopen("database.dat", "a+");
    newrec = fopen("new.dat", "a+");

    while (fscanf(old, "%d %s %d %lld %f ", &use->id_no, use->name, &use->secu, &use->phone, &use->taka) != EOF)
    {
        if (use->id_no == myid->id_no)
        {
            if (use->taka > transaction->taka)
            {
                flag = 1;
            }
            fprintf(newrec, "%d %s %d %lld %f\n", use->id_no, use->name, use->secu, use->phone, use->taka);
        }
        else
        {
            fprintf(newrec, "%d %s %d %lld %f \n", use->id_no, use->name, use->secu, use->phone, use->taka);
        }
    }
    fclose(old);
    fclose(newrec);
    remove("database.dat");
    rename("new.dat", "database.dat");
    if (flag != 1)
    {
        printf("\n\nNot Enough Money!!\n\n");
        goto rtaka;
    }
    else
    {
        sendu();
    }
}

void sendu(void)
{
    int choice, flag = 0;

    transaction = (node *)malloc(sizeof(node));

    FILE *old, *newrec;
    old = fopen("database.dat", "a+");
    newrec = fopen("new.dat", "a+");
    while (fscanf(old, "%d %s %d %lld %f ", &use->id_no, use->name, &use->secu, &use->phone, &use->taka) != EOF)
    {

        if (use->id_no == transaction->id_no)
        {
            flag = 1;

            use->taka += transaction->taka;
            fprintf(newrec, "%d %s %d %lld %f\n", use->id_no, use->name, use->secu, use->phone, use->taka);
            printf("\n\nSend Money successful!");
        }

        else
        {
            fprintf(newrec, "%d %s %d %lld %f \n", use->id_no, use->name, use->secu, use->phone, use->taka);
        }
    }
    fclose(old);
    fclose(newrec);
    remove("database.dat");
    rename("new.dat", "database.dat");
    if (flag != 1)
    {
        printf("\n\nID not found!!");
    send_invalid:
        printf("\n\n\nEnter 0 to try again,1 to return to home menu and 2 to exit:");
        scanf("%d", &mexit);
        system("cls");
        if (mexit == 0)
            sendu();
        else if (mexit == 1)
            menu2();
        else if (mexit == 2)
            close();
        else
        {
            printf("\nInvalid!");
            goto send_invalid;
        }
    }
    else
    {
        cut();
    }
}

void cut(void)
{
    int choice;

    transaction = (node *)malloc(sizeof(node));

    FILE *old, *newrec;
    old = fopen("database.dat", "a+");
    newrec = fopen("new.dat", "a+");

    while (fscanf(old, "%d %s %d %lld %f", &use->id_no, use->name, &use->secu, &use->phone, &use->taka) != EOF)
    {

        if (use->id_no == myid->id_no)
        {

            use->taka -= transaction->taka;
            fprintf(newrec, "%d %s %d %lld %f\n", use->id_no, use->name, use->secu, use->phone, use->taka);
        }

        else
        {
            fprintf(newrec, "%d %s %d %lld %f \n", use->id_no, use->name, use->secu, use->phone, use->taka);
        }
    }
    fclose(old);
    fclose(newrec);
    remove("database.dat");
    rename("new.dat", "database.dat");

    printf("\nEnter 1 to go to the home menu and 0 to exit:");
    scanf("%d", &mexit);
    system("cls");
    if (mexit == 1)
        menu2();
    else
        close();
}

void see(void)
{
    FILE *ptr;
    int flag = 0;

    ptr = fopen("database.dat", "r");

    while (fscanf(ptr, "%d %s %d %lld %f", &use->id_no, use->name, &use->secu, &use->phone, &use->taka) != EOF)
    {
        if (use->id_no == myid->id_no)
        {
            system("cls");

            printf("\nID NO.:%d\nName:%s\nPIN:%d \nPhone number:%lld \nAmount deposited: BDT: %g \n\n", use->id_no, use->name, use->secu, use->phone, use->taka);
        }
    }
    fclose(ptr);

    printf("\nEnter 1 to go to the home menu and 0 to exit:");
    scanf("%d", &mexit);

    if (mexit == 1)
    {
        system("cls");
        menu2();
    }

    else
    {
        system("cls");
        close();
    }
}

void close(void)
{
    printf("\n\n\n\nProject By\n");
    printf("\nNur Hasan Masum      203014011");
    printf("\nFardeen Ameen Pranto 203014022");
    printf("\nLamia Tabassum       203014019\n\n\n");
}

void menu(void)
{
    int choice;
main_menu:
    system("cls");
    printf("\n\n\t\t\t       ULAB MOBILE BANKING");
    printf("\n\n\n\t\t\t====== WELCOME TO THE MAIN MENU ======");
    printf("\n\n\t\t[1] Sign Up\n\t\t[2] Login\n\t\t[3] Exit\n\n\n\t\t Enter your choice:");
    scanf("%d", &choice);

    system("cls");
    switch (choice)
    {
    case 1:
        new_acc();
        break;
    case 2:
        signin();
        break;
    case 3:
        close();
        break;
    default:

        goto main_menu;
    }
}

void signin(void)
{
    printf("\n\n\t\t\t       ULAB MOBILE BANKING");
    printf("\n\n\n\t\t\t===== WELCOME TO THE MAIN MENU =====");

    use = (node *)malloc(sizeof(node));
    myid = (node *)malloc(sizeof(node));

signin_again:
    printf("\n\n\t\t\t       Enter Your ID : ");
    scanf("%d", &myid->id_no);

    int choice, flag = 0;
    FILE *ptr;
    ptr = fopen("database.dat", "a+");

    while (fscanf(ptr, "%d %s %d %lld %f ", &use->id_no, use->name, &use->secu, &use->phone, &use->taka) != EOF)
    {

        if (use->id_no == myid->id_no)
        {
            flag = 1;

            printf("\n\n\t\t\t       Enter PIN: ");
            scanf("%d", &myid->secu);
            if (use->secu == myid->secu)
            {
                fclose(ptr);
                menu2();
            }
            else
            {
                fclose(ptr);
                printf("\n\nWrong Pin!!");
                goto signin_again;
            }
        }
    }
    if (flag != 1)
    {
        printf("\n\nID not found!!\n\n");
        fclose(ptr);
        goto signin_again;
    }
    fclose(ptr);
}

void menu2(void)
{
    int choice;
    system("cls");
home_menu:
    printf("\n\n\t\t\t         ==ULAB MOBILE BANKING==");
    printf("\n\n\n\t\t\t====== WELCOME TO THE HOME MENU ======");
    printf("\n\n\t\t[1] Deposit\n\t\t[2] Withdraw\n\t\t[3] Check details\n\t\t[4] Send Money\n\t\t[5] Sign Out\n\n\n\t\t Enter your choice:");
    scanf("%d", &choice);
    system("cls");
    switch (choice)
    {
    case 1:
        depo();
        break;
    case 2:
        withdraw();
        break;
    case 3:
        see();
        break;

    case 4:
        send1();
        break;

    case 5:
        menu();
        break;

    default:
        goto home_menu;
    }
}
int main()
{
    system("color e");
    system("cls");
    menu();
    return 0;
}