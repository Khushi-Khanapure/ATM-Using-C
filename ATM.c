#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int checkPin(char pin[6],char fname[6])
{
    FILE *fp;
    fp=fopen(fname,"r");
    if(fp==NULL)
    {
        printf("\n\t %s File Open Error",fname);
    }
    else
    {
        char pin1[6];
        fscanf(fp,"%s",pin1);
        fclose(fp);
        if(strcmp(pin,pin1)==0)
        {
            return 1;
        }
    }
    return 0;
}
struct ATM
{
    int a,accountNo,amount;
    char card[10],name[20];
};
void addBalance()
{
    struct ATM A;
    int choice,accNo, dAmount, found = 0;
    char ch;
    FILE *fp = fopen("ATM.txt", "r");
    FILE *temp = fopen("Temp.txt", "w");

    if (fp == NULL || temp == NULL) 
    {
        printf("\n\t File open error!");
        return;
    }
    do
    {
        system("cls");
        printf("\n\t 1.New account detected");
        printf("\n\t 2.Existing account");
        printf("\n\t 3.Exit");
        printf("\n\n\t Enter your choice (1-3):-");
        scanf("%d",&choice);
        switch(choice)
        {
            case 1:
                if (!found)
                {
                    FILE *fpAppend = fopen("ATM.txt", "a");
                    printf("\n\t New account detected.");
                    printf("\n\t Enter name: ");
                    scanf("%s", A.name);
                    printf("\n\t Enter card number: ");
                    scanf("%s", A.card);
                    printf("\n\t Enter the account number: ");
                    scanf("%d", &accNo);
                    printf("\n\t Enter the amount to deposit: ");
                    scanf("%d", &dAmount);
                    A.a = dAmount; 
                    fprintf(fpAppend, "%s %d %s %d\n", A.name, accNo, A.card, A.a);
                    fclose(fpAppend);
                    printf("\n\t New account created successfully with balance: %d", A.a);
                }
                break; 
            case 2:
                printf("\n\t Enter the account number: ");
                scanf("%d", &accNo);
                printf("\n\t Enter the amount to deposit: ");
                scanf("%d", &dAmount);

                while (fscanf(fp, "%s %d %s %d", A.name, &A.accountNo, A.card, &A.a) != EOF) 
                {
                    if (A.accountNo == accNo) 
                    {
                        found = 1;
                        A.a =A.a+dAmount;
                        printf("\n\t Amount added successfully !");
                        printf("\n\t Now your balance is %d",A.a);
                    }
                    fprintf(temp, "%s %d %s %d\n", A.name, A.accountNo, A.card, A.a);
                }
                fclose(fp);
                fclose(temp);
                remove("ATM.txt");
                rename("Temp.txt", "ATM.txt");
                break;
            case 3:
                exit(0);
                break;
            default :
                printf("\n\t Invaild Choice");
                break;
        }
        printf("\n\t Do you want to continue (Y/N) :");
        scanf("%s",&ch);
    }while(ch=='y'||ch=='Y');    
}

void display()
{
    int count=0;
    struct ATM A;
    FILE *fp;
    fp=fopen("ATM.txt","r");
    if(fp==NULL)
    {
        printf("\n\t ATM.txt File open error");
    }
    else
    {
        printf("\n\t -------------------------------------------");
        printf("\n\t Name \t\t Account no \t Card no \t Amount");
        printf("\n\t ------------------------------------------");
        while(fscanf(fp,"%s %d  %s %d",&A.name,&A.accountNo,&A.card,&A.a)!=EOF)
        {
            count++;
            printf("\n\t %s \t %d \t %s \t %d",A.name,A.accountNo,A.card,A.a);
        }
        fclose(fp);
        if(count==0)
        {
            printf("\n\t No Record Found !");
        }
    }
}

void withdrawal()
{
    int accNo, am, found = 0;
    struct ATM A;
    FILE *fp = fopen("ATM.txt", "r");
    FILE *temp = fopen("Temp.txt", "w");

    if (fp == NULL || temp == NULL) 
    {
        printf("\n\t File open error!");
        return;
    }

    printf("\n\t Enter the account number: ");
    scanf("%d", &accNo);
    printf("\n\t Enter the amount to withdraw: ");
    scanf("%d", &am);

    while (fscanf(fp, "%s %d %s %d", A.name, &A.accountNo, A.card, &A.a) != EOF) 
    {
        if (A.accountNo == accNo) 
        {
            found = 1;
            if (am % 100 == 0 && am <= A.a) 
            {
                A.a =A.a-am;
                printf("\n\t Withdrawal successful! Remaining Balance: %d", A.a);
            } 
            else 
            {
                printf("\n\t Invalid amount! Must be a multiple of 100 and within balance.");
            }
        }
        fprintf(temp, "%s %d %s %d\n", A.name, A.accountNo, A.card, A.a);
    }
    fclose(fp);
    fclose(temp);
    remove("ATM.txt");
    rename("Temp.txt", "ATM.txt");

    if (!found) 
    {
        printf("\n\t Account not found!");
    }
}
int main()
{
    char ch;
    int choice,x;
    char pin[6];
    do
    {
        system("cls");
        printf("\n\t ---------------------------------");
        printf("\n\t          ATM DashBord            ");
        printf("\n\t ---------------------------------");
        printf("\n\t 1.Deposit Money");
        printf("\n\t 2.Check Balance");
        printf("\n\t 3.Whithdrawal Money");
        printf("\n\t 4.Exit");
        printf("\n\t ----------------------------------");
        printf("\n\t Enter your choice (1-4) :");
        scanf("%d",&choice);
        switch(choice)
        {
            case 1:
                printf("\n\t Enter the pin :");
                scanf("%s",&pin);
                x=checkPin(pin,"Pin.txt");
                if(x==1)
                {
                    addBalance();
                }
                else
                {
                    printf("\n\t Invaid Pin");
                }
                break;
            case 2:
                display();
                break;
            case 3:
                withdrawal();
                break;  
            case 4:
                exit(0);
                break;
            default:
                printf("\n\t Invaild Choice");
                break;
        }
        printf("\n\t DO you want to continue (Y/N):");
        scanf("%s",&ch);
    }while(ch=='Y'||ch=='y');
    return 0;
}