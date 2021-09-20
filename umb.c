#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void menu();
void menu2();
void signin();
void depo();
void withdraw();
void close();
void send();

typedef struct Node
{

    int id_no;
    char name[60];
    int secu;
    long long phone;
    float taka;
    struct Node *next;

} node;

node *root = NULL, *head = NULL, *use = NULL, *ser = NULL, *sign = NULL, *rsign = NULL, *transaction = NULL, *receiver = NULL;

int mexit, userid, usersecu, f = 0;

int headid, headsecu;
char headname[60];
long long headphone;
float headtaka;

void menu(void)
{
    int choice;
main_menu:
    system("cls");
    printf("\n\n\t\t\t       ULAB MOBILE BANKING");
    printf("\n\n\n\t\t\t====== WELCOME TO THE MAIN MENU ======");
    printf("\n\n\t\t[1] Sign Up\n\t\t[2] Login\n\t\t[3] Exit\n\n\n\t\t Enter your choice: ");
    scanf("%d", &choice);

    system("cls");
    switch (choice)
    {
    case 1:
        new_acc(ser, head);
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

void new_acc(node *ser, node *head)
{
    use = root;
    ser = root;

    int choice;
    char conf[5];

account_no:
    printf("\n\n\t\t\t==== ADD RECORD  ====");
    printf("\n\n\n\n\t\tEnter the ID number: ");
    scanf("%d", &userid);

    ser = ser->next;

    while (ser != NULL)
    {
        if (userid == ser->id_no)
        {
            printf("\n\t\tID no. already in use!\n");
        press:
            printf("\n\n\n\t\tPress 0 to exit.\n\t\tPress 1 to go to main menu.\n\t\tPress 2 to try again.\n\t\t---> ");
            scanf("%d", &mexit);
            system("cls");
            if (mexit == 1)
                main();
            else if (mexit == 2)
                goto account_no;
            else if (mexit == 0)
                close();
            else
            {
                printf("\n\t\tInvalid!\a");
                goto press;
            }
        }

        ser = ser->next;
    }

    head->next = (node *)malloc(sizeof(node));
    head = head->next;

    head->id_no = userid;

correct:

    printf("\n\t\tEnter the username(NO SPACE): ");
    scanf("%s", head->name);
    printf("\n\t\tEnter the Security PIN: :");
    scanf("%d", &head->secu);
    printf("\n\t\tEnter the phone number: (+880) ");
    scanf("%lld", &head->phone);

    system("cls");
    printf("\n\n\t\t\t\t===== ACCOUNT DETAILS =====\n\n\t\t\tID: %d\n\t\t\tUsername: %s\n\t\t\tSecurity PIN: %d\n\t\t\tPhone number: +880%lld\n\n\t\t\t CONFIRM?\n", head->id_no, head->name, head->secu, head->phone);
y_n:
    printf("\n\t\t\tEnter 'yes' or 'no'\n\t\t\t--->  ");
    scanf("%s", conf);

    if ((strcmp(conf, "yes") == 0) || (strcmp(conf, "YES") == 0))
    {
        printf("\n\n\t\tEnter Initial deposit in BDT: ");
        scanf("%f", &head->taka);

        head->next = NULL;

        /*use = use->next;

    while(use!=NULL){

        printf("%d %s %d %lld %f\n", use->id_no, use->name, use->secu, use->phone, use->taka);

        use = use->next;
    }*/

        FILE *ptr;
        ptr = fopen("database.dat", "a+");

        fprintf(ptr, "%d %s %d %lld %f\n", head->id_no, head->name, head->secu, head->phone, head->taka);

        fclose(ptr);
        printf("\n\t\tAccount created successfully!\n");
    }
    else if ((strcmp(conf, "no") == 0) || (strcmp(conf, "NO") == 0))
    {
        goto correct;
    }
    else
    {
        printf("\n\t\tInvalid!\a");
        goto y_n;
    }

use_invalid:
    printf("\n\n\n\t\tPress 1 to go to the main menu. \n\t\tPress 0 to exit.\n\t\t--> ");
    scanf("%d", &mexit);
    system("cls");
    if (mexit == 1)
        menu();
    else if (mexit == 0)
        close();
    else
    {
        printf("\n\t\tInvalid!\a");
        goto use_invalid;
    }

} //DONEEEEEEEEEEEE

void depo(int userid)
{
    sign = root;
    sign = sign->next;

    while (sign != NULL)
    {
        if (sign->id_no == userid)
        {
            break;
        }
        sign = sign->next;
    }

    node *transaction = NULL, *temp = NULL;

    float transactiontaka = 0;

    transaction = (node *)malloc(sizeof(node));

    transaction->id_no = sign->id_no;
    strcpy(transaction->name, sign->name);
    transaction->secu = sign->secu;
    transaction->phone = sign->phone;

    printf("\n\n\t\tEnter the amount you want to deposit (BDT) : ");
    scanf("%f", &transactiontaka);

    transaction->taka = sign->taka + transactiontaka;

    ser = root;

    if (sign->id_no != root->next->id_no)
    {
        ser = ser->next;
    }

    while (ser != NULL)
    {
        if (ser->next->id_no == userid)
        {
            break;
        }
        ser = ser->next;
    }

    //Deletion of the node
    temp = ser->next;
    ser->next = temp->next;
    free(temp);

    //Addition of the new node to that place
    if (ser != NULL)
    {
        transaction->next = ser->next;
        ser->next = transaction;
    }
    else if (ser == NULL)
    {
        ser->next = transaction;
    }

    //replacing the file
    FILE *newrec;
    newrec = fopen("new.dat", "a+");

    use = root;
    use = use->next;

    while (use != NULL)
    {
        fprintf(newrec, "%d %s %d %lld %f\n", use->id_no, use->name, use->secu, use->phone, use->taka);
        //printf("%d %s %d %lld %f\n", use->id_no, use->name, use->secu, use->phone, use->taka);    to see if the function works

        use = use->next;
    }

    printf("\n\n\t\tDeposit successful!");
    fclose(newrec);
    remove("database.dat");
    rename("new.dat", "database.dat");

    printf("\n\t\tEnter 1 to go to main menu.\n\t\tEnter 0 to exit.\n\t\t---> ");
    scanf("%d", &mexit);
    system("cls");
    if (mexit == 1)
        menu2();
    else
        close();
}

void withdraw(int userid)
{
    sign = root;
    sign = sign->next;

    while (sign != NULL)
    {
        if (sign->id_no == userid)
        {
            break;
        }
        sign = sign->next;
    }

    node *transaction = NULL, *temp = NULL;

    float transactiontaka = 0;

    transaction = (node *)malloc(sizeof(node));

    transaction->id_no = sign->id_no;
    strcpy(transaction->name, sign->name);
    transaction->secu = sign->secu;
    transaction->phone = sign->phone;

    printf("\n\n\t\tEnter the amount to withdraw (BDT) : ");
    scanf("%f", &transactiontaka);

    if (transactiontaka > sign->taka)
    {
        printf("\n\n\t\tNOT ENOUGH BALANCE!!\n\n");
    with_invalid:
        printf("\n\n\n\t\tEnter 0 to try again.\n\t\tEnter 1 to return to menu.\n\t\tEnter 2 to exit.\n\t\t---> ");
        scanf("%d", &mexit);
        system("cls");
        if (mexit == 0)
            withdraw(userid);
        else if (mexit == 1)
            menu2();
        else if (mexit == 2)
            close();
        else
        {
            printf("\n\t\tInvalid!");
            goto with_invalid;
        }
    }
    else
    {
        transaction->taka = sign->taka - transactiontaka;
    }

    ser = root;
    if (sign->id_no != root->next->id_no)
    {
        ser = ser->next;
    }

    while (ser != NULL)
    {
        if (ser->next->id_no = userid)
        {
            break;
        }
        ser = ser->next;
    }

    //Deletion of the node
    temp = ser->next;
    ser->next = temp->next;
    free(temp);

    //Addition of the new node to that place
    if (ser != NULL)
    {
        transaction->next = ser->next;
        ser->next = transaction;
    }
    else if (ser == NULL)
    {
        ser->next = transaction;
    }

    FILE *newrec;
    newrec = fopen("new.dat", "a+");

    use = root;
    use = use->next;

    while (use != NULL)
    {
        fprintf(newrec, "%d %s %d %lld %f\n", use->id_no, use->name, use->secu, use->phone, use->taka);

        use = use->next;
    }

    printf("\n\n\t\tWithdraw successful!");
    fclose(newrec);
    remove("database.dat");
    rename("new.dat", "database.dat");

    printf("\n\t\tEnter 1 to go to main menu.\n\t\tEnter 0 to exit.\n\t\t---> ");
    scanf("%d", &mexit);
    system("cls");
    if (mexit == 1)
        menu2();
    else
        close();
}

void send(int userid)
{
    int receiverid;

    node *transaction = NULL, *receiver = NULL, *temp = NULL, *rtemp = NULL, *rsign = NULL;

    float transactiontaka = 0;

rsignid:

    printf("\n\n\t\tEnter receiver ID : ");
    scanf("%d", &receiverid);

    rsign = root;
    rsign = rsign->next;

    while (rsign != NULL)
    {
        if (rsign->id_no == receiverid)
        {
            break;
        }
        rsign = rsign->next;
    }

    if (rsign == NULL)
    {
        printf("\n\t\tID does not exist!!");
        goto rsignid;
    }

    //======================================================sender upd========================

    sign = root;
    sign = sign->next;

    while (sign != NULL)
    {
        if (sign->id_no == userid)
        {
            break;
        }
        sign = sign->next;
    }

    transaction = (node *)malloc(sizeof(node));

    transaction->id_no = sign->id_no;
    strcpy(transaction->name, sign->name);
    transaction->secu = sign->secu;
    transaction->phone = sign->phone;

    printf("\n\n\t\tEnter the amount (BDT) : ");
    scanf("%f", &transactiontaka);

    if (transactiontaka > sign->taka)
    {
        printf("\n\n\t\tNOT ENOUGH BALANCE!!\n\n");
    withd_invalid:
        printf("\n\n\n\t\tEnter 0 to try again.\n\t\tEnter 1 to return to menu.\n\t\tEnter 2 to exit.\n\t\t---> ");
        scanf("%d", &mexit);
        system("cls");
        if (mexit == 0)
            send(userid);
        else if (mexit == 1)
            menu2();
        else if (mexit == 2)
            close();
        else
        {
            printf("\n\t\tInvalid!");
            goto withd_invalid;
        }
    }
    else
    {
        transaction->taka = sign->taka - transactiontaka;
    }

    ser = root;
    if (sign->id_no != root->next->id_no)
    {
        ser = ser->next;
    }

    while (ser != NULL)
    {
        if (ser->next->id_no = userid)
        {
            break;
        }
        ser = ser->next;
    }

    //Deletion of the node
    temp = ser->next;
    ser->next = temp->next;
    free(temp);

    //Addition of the new node to that place
    if (ser != NULL)
    {
        transaction->next = ser->next;
        ser->next = transaction;
    }
    else if (ser == NULL)
    {
        ser->next = transaction;
    }

    FILE *newrec;
    newrec = fopen("new.dat", "a+");

    use = root;
    use = use->next;

    while (use != NULL)
    {
        fprintf(newrec, "%d %s %d %lld %f\n", use->id_no, use->name, use->secu, use->phone, use->taka);

        use = use->next;
    }
    fclose(newrec);
    remove("database.dat");
    rename("new.dat", "database.dat");

    //==================================================================================receiver upd=============================

    receiver = (node *)malloc(sizeof(node));

    receiver->id_no = rsign->id_no;
    strcpy(receiver->name, rsign->name);
    receiver->secu = rsign->secu;
    receiver->phone = rsign->phone;
    receiver->taka = rsign->taka + transactiontaka;

    ser = root;

    if (rsign->id_no != root->next->id_no)
    {
        ser = ser->next;
    }

    while (ser != NULL)
    {
        if (ser->next->id_no = receiverid)
        {
            break;
        }
        ser = ser->next;
    }

    //Deletion of the node
    rtemp = ser->next;
    ser->next = rtemp->next;
    free(rtemp);

    //Addition of the new node to that place
    if (ser != NULL)
    {
        receiver->next = ser->next;
        ser->next = receiver;
    }
    else if (ser == NULL)
    {
        ser->next = receiver;
    }

    //replacing the file
    newrec = fopen("new.dat", "a+");

    use = root;
    use = use->next;

    while (use != NULL)
    {
        fprintf(newrec, "%d %s %d %lld %f\n", use->id_no, use->name, use->secu, use->phone, use->taka);
        //printf("%d %s %d %lld %f\n", use->id_no, use->name, use->secu, use->phone, use->taka);    to see if the function works

        use = use->next;
    }

    printf("\n\n\t\tTransaction successful!");
    fclose(newrec);
    remove("database.dat");
    rename("new.dat", "database.dat");

    printf("\n\t\tEnter 1 to go to main menu.\n\t\tEnter 0 to exit.\n\t\t---> ");
    scanf("%d", &mexit);
    system("cls");
    if (mexit == 1)
        menu2();
    else
        close();
}

void see(userid)
{
    system("cls");

    FILE *ptr;
    ptr = fopen("database.dat", "a+");

    while (fscanf(ptr, "%d %s %d %lld %f", &headid, headname, &headsecu, &headphone, &headtaka) != EOF)
    {
        if (headid == userid)
        {
            printf("\n\t\t\t==== ACCOUNT STATEMENT ====\n\n\t\tID : %d\n\t\tName: %s\n\t\tPIN: %d\n\t\tPhone number : %lld\n\t\tAccount Balance : %g (BDT)\n\n", headid, headname, headsecu, headphone, headtaka);

            break;
        }
    }

    fclose(ptr);

    printf("\n\t\tEnter 1 to go to the main menu.\n\t\tPress 0 to exit.\n\t\t---> ");
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
    printf("\nLamia Tabassum       203014019");
    printf("\nAbrar Saief          2030140  \n\n\n");

    exit(0);
}

void signin(void)
{
    int flag;
    sign = root;

    printf("\n\n\t\t\t       ULAB MOBILE BANKING");
    printf("\n\n\n\t\t\t===== WELCOME TO THE MAIN MENU =====");

    printf("\n\n\t\t\tEnter Your ID : ");
    scanf("%d", &userid);

    sign = sign->next;

    while (sign != NULL)
    {
        if (sign->id_no == userid)
        {
            flag = 1;

            printf("\n\n\t\t\tEnter PIN : ");
            scanf("%d", &usersecu);

            if (sign->secu == usersecu)
            {
                menu2();
            }
            else
            {
                printf("\n\t\t\tWrong Pin!!");
            press1:
                printf("\n\n\n\t\t\tPress 0 to exit.\n\t\t\tPress 1 to goto main menu.\n\t\t\tPress 2 to try again.\n\t\t\t---> ");
                scanf("%d", &mexit);
                system("cls");
                if (mexit == 1)
                    main();
                else if (mexit == 2)
                    signin();
                else if (mexit == 0)
                    close();
                else
                {
                    printf("\n\t\t\tInvalid!\a");
                    goto press1;
                }
            }
        }

        sign = sign->next;
    }

    if (flag != 1)
    {
        printf("\n\t\t\tID not found!!\n\n");

    press2:
        printf("\n\n\n\t\t\tPress 0 to exit.\n\t\t\tPress 1 to go to main menu.\n\t\t\tPress 2 to try again.\n\t\t\t---> ");
        scanf("%d", &mexit);
        system("cls");
        if (mexit == 1)
            main();
        else if (mexit == 2)
            signin();
        else if (mexit == 0)
            close();
        else
        {
            printf("\n\t\t\tInvalid!\a");
            goto press2;
        }
    }
}

int main()
{
    system("color f1");
    system("cls");

    FILE *ptr;
    ptr = fopen("database.dat", "a+");

    head = (node *)malloc(sizeof(node));
    head->next = NULL;
    root = head;
    ser = root;
    use = root;

    while (fscanf(ptr, "%d %s %d %lld %f", &headid, headname, &headsecu, &headphone, &headtaka) != EOF)
    {
        head->next = (node *)malloc(sizeof(node));
        head = head->next;

        head->id_no = headid;
        strcpy(head->name, headname);
        head->secu = headsecu;
        head->phone = headphone;
        head->taka = headtaka;
    }
    head->next = NULL;

    fclose(ptr);

    /*ser = ser->next;

    while(ser!=NULL){

        printf("%d %s %d %lld %f\n", ser->id_no, ser->name, ser->secu, ser->phone, ser->taka);

        ser = ser->next;
    }*/

    menu();

    return 0;
} //DONEEEEEEEEEEEEE

void menu2(void)
{
    int choice;
    system("cls");
home_menu:
    printf("\n\n\t\t\t         == ULAB MOBILE BANKING ==");
    printf("\n\n\n\t\t\t====== WELCOME TO THE HOME MENU ======");
    printf("\n\n\t\t[1] Deposit\n\t\t[2] Withdraw\n\t\t[3] Check details\n\t\t[4] Send Money\n\t\t[5] Sign Out\n\n\n\t\t Enter your choice: ");
    scanf("%d", &choice);
    system("cls");
    switch (choice)
    {
    case 1:
        depo(userid);
        break;
    case 2:
        withdraw(userid);
        break;
    case 3:
        see(userid);
        break;

    case 4:
        send(userid);
        break;

    case 5:
        menu();
        break;

    default:
        goto home_menu;
    }
}