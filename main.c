#include <stdio.h>   // for printf and scanf
#include <stdlib.h>  // exit(0)
#include <stdbool.h> // true or false
#include <time.h>
#include <windows.h>


int balanceupdater(); // funtion to update balance in file
int transactions();   // function to save the transaction details
int mainmenu();
int transactionmenu();
int transactionprocess();
int balancemenu();
int accholdernameinmenu();
double inputuser();
double inputpass();
int checkingdata();
int delay();
int timmer();
void textcolor();
struct userdetails
{
    char name[8];double accnum;
    int accpin;int accbal;
};
int main()
{
    int usercount = 6;

    struct userdetails person[usercount];
    FILE *userdata;
    userdata = fopen("userdetails.txt", "r");


    for (int i = 1; i <= 4; i++)
    {
        char tempchar[30];fscanf(userdata, "%s", &tempchar);
    }


    for (int i = 0; i < usercount; i++)
    {
        fscanf(userdata, "%s", person[i].name);fscanf(userdata, "%lf", &person[i].accnum);
        fscanf(userdata, "%d", &person[i].accpin);fscanf(userdata, "%d", &person[i].accbal);
    }
    fclose(userdata);
    while (true)
    {
        mainmenu();
        double inputusernumber = inputuser();
        int viraccnum;
        bool testacc = false;
        for (int i = 0; i < usercount; i++)
        {
            if (inputusernumber == person[i].accnum)
            {
                viraccnum = i;
                testacc = true;
            }
        }
        double inputpassword = inputpass();
        bool testpass = false;
        if (testacc)
        {
            if (inputpassword == person[viraccnum].accpin){testpass = true;}
        }
        checkingdata();
        if (testpass && testacc)
        {
            int userbalance = person[viraccnum].accbal;int choice = transactionmenu();
            system("cls");mainmenu();
            switch (choice)
            {
            case (1): // withdraw from balance
                accholdernameinmenu(person[viraccnum].name, 1);
                int withdrawamount;
                scanf("%d", &withdrawamount);
                if (withdrawamount % 100 == 0)
                {
                    if (userbalance - withdrawamount >= 1000)
                    {
                        transactionprocess();
                        userbalance = userbalance - withdrawamount;
                        balanceupdater(viraccnum, userbalance, usercount, -withdrawamount);
                        break;
                    }
                    if (userbalance - withdrawamount < 1000)
                    {
                        accholdernameinmenu(person[viraccnum].name, 3);
                        delay(5000);break;
                    }
                }
                else
                {
                    printf("ONLY 100,500,1000 NOTES ONLY AVAILABLE");
                    break;
                }
            case (2):
                accholdernameinmenu(person[viraccnum].name, 2);
                int depositamount;
                scanf("%d", &depositamount);
                if (depositamount % 100 == 0)
                {
                    transactionprocess();
                    userbalance = userbalance + depositamount;
                    balanceupdater(viraccnum, userbalance, usercount, depositamount);
                    break;
                }
                else
                {
                    printf("PLEASE ENTER AMOUNT MUTIPLE OF 100");
                    break;
                }
            case (3): // checking balance


                textcolor(7);printf("\n\n\t\t\t\t\tYOUR CURRENT BALANCE IS %d\n", userbalance);
                delay(5000);break;


            case (4):
                break;


            default:
                printf("\n\n\t\t\t\t\tINVALID CHOICE");delay(4000);
            }
        }
        else if (inputusernumber == 0 && inputpassword == 0)
        {
            system("cls");mainmenu();
            textcolor(7);printf("\n\n\t\t\t\t\t \tEXITING PROGRAM\n\n\n\n");
            textcolor(7);
            delay(10000);
            exit(0);
        }


        else{textcolor(9);printf("\n\n\t\t\t \t\t\tINVALID USER NUMBER ORPASSWORD\n");delay(5000);}


        timmer(7);
    }
}
int balanceupdater(int virtualusernumber, int updatedbalance, int usercount, int balchange)
{
    struct userdetails person[usercount];
    FILE *userdata;
    userdata = fopen("userdetails.txt", "r");


    for (int i = 1; i <= 4; i++)
    {
        char tempchar[30];fscanf(userdata, "%s", &tempchar);
    }
    for (int i = 0; i < usercount; i++)
    {
        fscanf(userdata, "%s", person[i].name);fscanf(userdata, "%lf", &person[i].accnum);
        fscanf(userdata, "%d", &person[i].accpin);fscanf(userdata, "%d", &person[i].accbal);
    }
    fclose(userdata);
    userdata = fopen("userdetails.txt", "w");
    fprintf(userdata, "%s\t", "USERNAME");fprintf(userdata, "%s\t\t", "ACCOUNTNUMBER");
    fprintf(userdata, "%s\t\t", "PIN");fprintf(userdata, "%s\n", "CURRENTBALANCE");


    for (int i = 0; i < usercount; i++)
    {
        fprintf(userdata, "%s\t", person[i].name);fprintf(userdata, "%0.lf\t\t\t", person[i].accnum);
        fprintf(userdata, "%d\t\t", person[i].accpin);
        if (i == virtualusernumber)
        {
            fprintf(userdata, "%d\n", updatedbalance);
        }
        if (i != virtualusernumber)
        {
            fprintf(userdata, "%d\n", person[i].accbal);
        }
    }
    fclose(userdata);
    transactions(person[virtualusernumber].name, person[virtualusernumber].accbal, balchange);
}


int transactions(char name[8], int virtualuserintialbal, int balchange)
{
    time_t tm;time(&tm);


    FILE *transaction;
    transaction = fopen("transactionhistory.txt", "a");
    if (balchange >= 0)
    {
        if (balchange < 1000)
        {
            fprintf(transaction, "%s  \t%d\t\tDEPOSITED\t\t%d\t\t\t%s", name, virtualuserintialbal, balchange, ctime(&tm));
        }
        if (balchange >= 1000)
        {
            fprintf(transaction, "%s  \t%d\t\tDEPOSITED\t\t%d\t\t%s", name, virtualuserintialbal, balchange, ctime(&tm));
        }
    }
    if (balchange < 0)
    {
        if (-balchange < 1000)
        {
            fprintf(transaction, "%s  \t%d\t\tWITHDRAWN\t\t%d\t\t\t%s", name, virtualuserintialbal, -balchange, ctime(&tm));
        }
        if (-balchange >= 1000)
        {
            fprintf(transaction, "%s  \t%d\t\tWITHDRAWN\t\t%d\t\t%s", name, virtualuserintialbal, -balchange, ctime(&tm));
        }
    }
    fclose(transaction);
}


int mainmenu()
{
    system("cls");
    textcolor(5);printf("\t\t\t\t\t..............................................\n");
    printf("\t\t\t\t\t\t   WELCOME TO  RUPNI BANK\n\t\t\t\t\t..............................................\n\n\n");
}
double inputuser()
{
    textcolor(6);printf("\n\t\tENTER YOUR USER NUMBER :");
    double inputusernumber;
    textcolor(7);scanf("%lf", &inputusernumber);
    return inputusernumber;
}


double inputpass()
{
    double inputpassword;
    textcolor(3);printf("\t\tENTER YOUR PASSWORD :");
    textcolor(7);scanf("%lf", &inputpassword);
    return inputpassword;
}
int transactionmenu()
{
    mainmenu();
    textcolor(1);printf("\t\t\t1). WITHDRAW\n");textcolor(2);printf("\t\t\t2). DEPOSIT\n");
    textcolor(3);printf("\t\t\t3). CHECK BALANCE\n");textcolor(4);printf("\t\t\t4). QUIT\n");
    textcolor(6);printf("\n\t\t\tENTER OPTION :");
    int choice;
    textcolor(7);scanf("%d", &choice);
    return choice;
}


int delay(int m)
{
    clock_t time = m + clock();while (time > clock());
}


int timmer(int s)
{
    while (s >= 0)
    {
        mainmenu();
        textcolor(7);printf("\n\n\t\t\t\t\t\tNEXT TRANSACTION AVAILABLE IN\n\n\n\t\t\t\t\t\t\t");
        printf("00 : 0%d", s);
        delay(1000);
        s--;
    }
}
int transactionprocess()
{
    mainmenu();
    textcolor(4);printf("\n\n\t\t\t\t\t\tTRANSACTION ON PROCESS\n\n\n\t\t\t\t\t\t");
    for (int i = 0; i <= 25; i++)
    {
        textcolor(7);
        if (i % 2 == 0)
        {
            printf("/");delay(500);
        }
        else
        {
            printf(".");delay(500);
        }
    }
    system("cls");
    mainmenu();
    textcolor(7);printf("\n\n\t\t\t\t\t\tTRANSACTION COMPLETED\n\n\n");
    delay(3000);
}
int accholdernameinmenu(char name[8], int chosen)
{
    textcolor(1);printf("\n\n\t\t\t\t\tACCOUNT HOLDER NAME :");
    textcolor(2);printf("%s\n\n\n\t\t\t\t\t", name);
    if (chosen == 1)
    {
        textcolor(3);printf("ENTER YOUR WITHDRAW AMOUNT :");
    }
    if (chosen == 2)
    {
        textcolor(3);printf("ENTER YOUR WITHDRAW AMOUNT :");
    }
    if (chosen == 3)
    {
        textcolor(7);printf("INSUFFIENT BALANCE");
    }
    textcolor(7);
}


void textcolor(int color)
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}


int checkingdata()
{
    system("cls");
    mainmenu();
    textcolor(4);printf("\n\n\t\t\t\t\t\tCHECKING OUR DATA PLEASE WAIT\n\n\n\t\t\t\t\t\t");
    for (int i = 0; i <= 25; i++)
    {
        textcolor(7);
        if (i % 2 == 0)
        {
            printf("/");delay(500);
        }
        else
        {
            printf(".");delay(500);
        }
    }
}

