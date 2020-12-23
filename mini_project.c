#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include<conio.h>

void delay(int number_of_seconds);
void LoginPage();

typedef struct {
    char itemName[20];
    int costPrice;
    int MRP;
    int quantityLeft;
} product;

product stock[10];

void init_stock()
{
    strcpy(stock[0].itemName,"Product-1");
    stock[0].costPrice=10;
    stock[0].MRP=12;

    strcpy(stock[1].itemName,"Product-2");
    stock[1].costPrice=50;
    stock[1].MRP=56;

    strcpy(stock[2].itemName,"Product-3");
    stock[2].costPrice=70;
    stock[2].MRP=78;

    strcpy(stock[3].itemName,"Product-4");
    stock[3].costPrice=100;
    stock[3].MRP=120;

    strcpy(stock[4].itemName,"Product-5");
    stock[4].costPrice=110;
    stock[4].MRP=116;

    strcpy(stock[5].itemName,"Product-6");
    stock[5].costPrice=60;
    stock[5].MRP=64;

    strcpy(stock[6].itemName,"Product-7");
    stock[6].costPrice=200;
    stock[6].MRP=220;

    strcpy(stock[7].itemName,"Product-8");
    stock[7].costPrice=150;
    stock[7].MRP=161;

    strcpy(stock[8].itemName,"Product-9");
    stock[8].costPrice=170;
    stock[8].MRP=162;

    strcpy(stock[9].itemName,"Product-10");
    stock[9].costPrice=250;
    stock[9].MRP=275;

    for(int i=0;i<10;i++) stock[i].quantityLeft=100;
}

void checkStock()
{
    printf("+==============+============+===========+===============+===============+\n");
    printf("| PRODUCT NAME | COST PRICE |    MRP    | QUANTITY LEFT |    STATUS     |\n");
    printf("+==============+============+===========+===============+===============+\n");
    for(int i=0;i<10;i++)
    {
        printf("| %-10s   |     %3d    |    %3d    |      %3d      |",stock[i].itemName,stock[i].costPrice,stock[i].MRP,stock[i].quantityLeft);
        if(stock[i].quantityLeft==0) printf("  UNAVAILABLE  |\n");
        else if(stock[i].quantityLeft<20) printf("  LESS STOCK   |\n");
        else if(stock[i].quantityLeft<60) printf("  SUFFICIENT   |\n");
        else printf("    PERFECT    |\n");
    }
    printf("+==============+============+===========+===============+===============+\n");
}

typedef struct 
{
    int Id;
    char name[20];
    char password[20];
} cashier;

struct bill
{
    char customerName[20];
    char PhNo[10];
    int items[10];
    char feedback[50];
    int totalSP;
    int totalCP;
    int discountPercent;
    float PorL;    //percentage Profit or Loss ; + if profit ; - if Loss ;
    int modeOfPayment;     //'1' Online,'2' Card,'3' Cash
    int paid;
    struct bill* next;
};
typedef struct bill bill;

bill* newBill()
{
    bill* temp;
    temp=(bill*)malloc(sizeof(bill));
    for(int i=0;i<10;i++) temp->items[i]=0;
    temp->totalSP=0;
    temp->totalCP=0;
    temp->next=NULL;
    return temp;
}

//root=head;

void showMenu()
{
    printf("+=================+============================+=================+\n");
    printf("|  Product Index  |         Product Name       |       MRP       |\n");
    printf("+=================+============================+=================+\n");
    for (int i=0; i<10; i++) {
        printf("| %11d     |         %-10s         | %14d  |\n", i+1,stock[i].itemName,stock[i].MRP);
    }        
    printf("+=================+============================+=================+\n");
}

void printBill(bill* head)
{
    printf("Customer Name : %s\n",head->customerName);
    
    printf("Phone Number  : %s\n",head->PhNo);
    printf("+======+==================+=================+===============+=================+\n");
    printf("| S.No |   Product Name   |  Price of Each  |  No.of Items  |   Total price   |\n");
    printf("+======+==================+=================+===============+=================+\n");
    int count=1;
    for(int i=0;i<10;i++){
        if(head->items[i]){
            printf("| %4d |   Product-%2d     |       %3d       |       %2d      |       %4d      |\n",count,i+1,stock[i].MRP,head->items[i],stock[i].MRP*head->items[i]);
            count++;
        }
    }
    printf("+======+==================+=================+===============+=================+\n");
    printf("TOTAL      = %d\n",head->totalSP);
    printf("GST        = 9%%\n");
    printf("TOTAL(+GST)= %.2f\n",(float)head->totalSP*1.09);
    float multiFactor=1+(0.01)*(9-head->discountPercent);
    if(head->discountPercent) printf("Discount   = %d%%\n\n",head->discountPercent);
    printf("FINAL COST = %.2f /-\n",(float)head->totalSP*multiFactor);
}

//Passwords
char APass[]="Admin@123";
char OPass[]="Owner@123";
cashier cashiers[4];
void init_Cashiers()
{
    char pass[20];
    printf("Admin, Enter your Password: ");
    scanf("%s",pass);
    int i=2;
    while(strcmp(pass,APass))
    {
        if(i==0) {
            printf("You have exceeded maximum number of tries.\n           Exiting Program.");
            delay(1); printf("."); delay(1); printf("."); delay(1); printf("\n");
            exit(-1);
        }
        printf("User does not exist.You have %d more %s left\nEnter your password again: ",i,(i==1)?"try":"tries");
        scanf("%s",pass);
        i--;
    }
    printf("Successfully Logged in :)\n");
    printf("Enter the names of four Cashiers \n");
    for(int i=1;i<=4;i++)
    {
        printf("Cashier-%d: ",i); scanf("%s",cashiers[i-1].name);
        cashiers[i-1].Id=i;
        printf("Set Cashier-%d Password : ",i); scanf("%s",cashiers[i-1].password);
    }
    printf("\nUsernames and passwords of the Cashiers are set.\n"); delay(1);
    printf("Redirecting to Login Page."); delay(1); printf("."); delay(1); printf("."); delay(1); printf("\n\n");
}

char* getCashierPassword(char* username)
{
    for(int i=0;i<4;i++)
        if(strcmp(username,cashiers[i].name)==0) return cashiers[i].password;
    return NULL;                     //returns null if the username doesnot exist
}

int AdminPage(bill** head,bill** root)                 //returns 4-digit security code if required, else returns -1
{
    printf("**********ADMIN'S PAGE**********\n");
    char pass[20];
    printf("Enter your Password: ");
    scanf("%s",pass);
    int i=2;
    while(strcmp(pass,APass))
    {
        if(i==0) {
            printf("You have exceeded maximum number of tries.\n           Exiting Program.");
            delay(1); printf("."); delay(1); printf("."); delay(1); printf("\n");
            exit(-1);
        }
        printf("ERROR: Incorrect Password.\nYou have %d more %s left\nEnter your password again: ",i,(i==1)?"try":"tries");
        scanf("%s",pass);
        i--;
    }
    printf("Successfully Logged in as Admin :)\n");
    printf("Select an option:\n");
    printf("1.Details of Cashiers\n2.Generate a Security Code\n3.Reset Bills\n Enter '0' to go back to login Page\n");
    int option;
    scanf("%d",&option);
    if(option==0)
    {
        LoginPage(head,root);
        return -1;
    }
    else if(option==1)
    {
        printf("Details of Cashiers: \n");
        printf("Id  Name            Password\n");
        for(int i=0;i<4;i++)
        {
            printf(" %d  %s              %s\n",cashiers[i].Id,cashiers[i].name,cashiers[i].password);
        }
        delay(5);
        printf("Redirecting to Login Page."); delay(1); printf("."); delay(1); printf("."); delay(1); printf("\n");
        LoginPage(head,root);
        return -1;
    }
    else if(option==2)
    {
        printf("Generating a Security Code."); delay(1); printf("."); delay(1); printf("."); delay(1); printf("\n");
        srand(time(0));
        int code=rand()%9000+1000;
        return code;
    }
    else if(option==3)
    {
        free(*root);
        free(*head);
        *head=newBill();
        *root=*head;
        printf("Deleting all bills."); delay(1); printf("."); delay(1); printf("."); delay(1); printf("\n");
        printf("Succussfully deleted all Bills\n");
        printf("Redirecting to Login Page."); delay(1); printf("."); delay(1); printf("."); delay(1); printf("\n");
        LoginPage(head,root);
        return -1;
    }
}

void CashierPage(bill** head,bill** root)
{
    printf("**********CASHIER'S PAGE**********\n");
    char username[20],pass[20];
    printf("Enter your name: ");
    scanf("%s",username);
    int i=2;
    while(getCashierPassword(username)==NULL)
    {
        if(i==0) {
            printf("You have exceeded maximum number of tries.\n           Exiting Program.");
            delay(1); printf("."); delay(1); printf("."); delay(1); printf("\n");
            exit(-1);
        }
        printf("User does not exist.You have %d more %s left\nEnter your name again: ",i,(i==1)?"try":"tries");
        scanf("%s",username);
        i--;
    }
    printf("Enter your Password: ");
    char *correctPass=getCashierPassword(username);
    scanf("%s",pass);
    if(strcmp(pass,correctPass))
    {
        fprintf(stderr,"ERROR: Incorrect Password\n");
        printf("Select an option : \n1.Try again\n2.Contact Admin for security Code\n3.Go back to Login Page\n4.Exit\n");
        int option;
        scanf("%d",&option);
        if(option==1){
            int i=2;
            while(option==1 && strcmp(pass,correctPass))
            {
                for(int i=0;i<strlen(pass);i++) pass[i]='\0';
                printf("Enter your Password again: "); scanf("%s",pass);
                if(strcmp(pass,correctPass)==0) break;
                fprintf(stderr,"ERROR: Incorrect Password\n"); i--;
                if(i==0) {
                    option=2;
                    break;
                }
                printf("Select an option : \n1.Try again (%d %s left)\n2.Contact Admin for security Code\n3.exit\n",i,(i==1)?"try":"tries");
                scanf("%d",&option);
            }
        }
        if(option==2)
        {
            printf("Redirecting to Admin's Page to generate security code.");
            delay(1); printf("."); delay(1); printf("."); delay(1); printf("\n");
            printf("Contacting Admin: (Once entered Admin Page, select 'Security Code')\n\n");
            int code;
            if((code=AdminPage(head,root))!=-1){
                int newPass;
                printf("The newly generated code for %s is %d\n",username,code);
                printf("Enter the same code as password to login as %s : \n",username);
                scanf("%d",&newPass);
                if(newPass!=code)
                {
                    printf("You have entered invalid Code :(\n");
                    printf("\nExiting Program.");
                    delay(1); printf("."); delay(1); printf("."); delay(1); printf("\n");
                    exit(-1);
                } 
            }
        }
        else if(option==3)
        {
            printf("Redirecting to Login Page."); delay(1); printf("."); delay(1); printf("."); delay(1); printf("\n\n");
            LoginPage(head,root);
        }
        else if(option==4)
        {
            printf("\nExiting Program.");
            delay(1); printf("."); delay(1); printf("."); delay(1); printf("\n");
            exit(-1);
        }
    }

    printf("Successfully Logged in as Cashier(%s) :)\n",username);
    printf("Select an option:\n");
    printf("Queries : \n");
    printf("'y' to add bill of new customer\n'x' to stop adding new customers\n");
    char q1;
    scanf(" %c",&q1);
    while(q1=='y')
    {
        system("cls");
        printf("**********MENU***********\n");
        showMenu();
        printf("\nAsk the Customer to enter their name and phone number\n");
        printf("Customer Name : "); scanf("%s",(*head)->customerName);
        printf("Phone Number : "); scanf("%s",(*head)->PhNo);
        printf("Queries :\n");
        printf("'+' <product index> <number of items of that product> to add a product\n'-' <product name> <number of items of that product> to delete the product\n'0' to stop billing of that customer\n");
        printf("NOTE : Enter Product index ranging from '1' to '10' in place of <product index>\n");
        char q2;
        scanf(" %c",&q2);
        while(1){
            if(q2=='+'){
                int p_index;
                int noOfitems;
                scanf("%d %d",&p_index,&noOfitems);
                if(p_index>10 || p_index<1) {
                    printf("ERROR : product index is not Valid.It must be in the range 1 to 10\n");
                    printf("Enter New query (+,-,0):\n");
                    scanf(" %c",&q2);
                    continue;
                }
                if(noOfitems>stock[p_index-1].quantityLeft)
                {
                    printf("STOCK NOT SUFFICIENT\n");
                    printf("Rather you can buy %d items of %s\n",stock[p_index-1].quantityLeft,stock[p_index-1].itemName);
                    printf("Enter 'y' if agreed,'n' if you dont want this product\n");
                    char agree;
                    scanf(" %c",&agree);
                    if(agree=='y'){
                        noOfitems=stock[p_index-1].quantityLeft;
                        printf("Added + %d %d insted of + %d %d\n",p_index,noOfitems,p_index,stock[p_index-1].quantityLeft);
                    }
                    else{
                        printf("Enter New query (+,-,0):\n");
                        scanf(" %c",&q2);
                        continue;
                    }
                }
                (*head)->items[p_index-1]+=noOfitems;
                (*head)->totalCP+=stock[p_index-1].costPrice*noOfitems;
                (*head)->totalSP+=stock[p_index-1].MRP*noOfitems;
                stock[p_index-1].quantityLeft-=noOfitems;
            }
            else if(q2=='-'){
                int p_index;
                int noOfitems;
                scanf("%d %d",&p_index,&noOfitems);
                noOfitems=(noOfitems<(*head)->items[p_index-1])?noOfitems:(*head)->items[p_index-1];
                (*head)->items[p_index-1]-=noOfitems;
                (*head)->totalCP-=stock[p_index-1].costPrice*noOfitems;
                (*head)->totalSP-=stock[p_index-1].MRP*noOfitems;
                stock[p_index-1].quantityLeft+=noOfitems;
            }
            else if(q2=='0'){
                if((*head)->totalSP<1000) (*head)->discountPercent=0;
                else if((*head)->totalSP>=1000 && (*head)->totalSP<2500) (*head)->discountPercent=5;
                else if((*head)->totalSP>=2500) (*head)->discountPercent=10;
                printf("You have finished entering all your required products\n");
                printf("Here is your Bill :\n");
                printf("********YOUR BILL*********\n\n");
                printBill(*head);
                printf("Enter any key to continue...\n"); getch();
                printf("\nAsk the customer for mode of payment. Select an option below:\n");
                printf("1.Online Banking (including paytm/Gpay/PhonePe)\n2.Card\n3.Cash\nMode of Payment : ");
                scanf(" %d",&(*head)->modeOfPayment);
                printf("\nAsk the Customer for Feedback (at most 5 words)\nFEEDBACK : ");
                scanf("%[^\n]s",(*head)->feedback);
                (*head)->paid=((*head)->totalSP*(100+9-(*head)->discountPercent))/100;
                (*head)->PorL=(float)((float)((*head)->paid-(*head)->totalCP)/(*head)->totalCP)*100;
                (*head)->next=newBill();
                (*head)=(*head)->next;
                printf("\n*****THANK YOU*****\n****VISIT AGAIN****\n\n");
                break;
            }
            scanf(" %c",&q2);
        }
        printf("Enter any key to continue...\n"); getch();
        printf("Select an option:\n");
        printf("'y' to add bill of new customer\n'x' to stop adding new customers\n");
        scanf(" %c",&q1);
    }
    printf("Redirecting to Login Page."); delay(1); printf("."); delay(1); printf("."); delay(1); printf("\n\n");
    LoginPage(head,root);
}

void OwnerPage(bill** head,bill** root)
{
    printf("**********OWNER'S PAGE**********\n");
    char pass[20];
    printf("Enter your Password: ");
    scanf("%s",pass);
    int i=2;
    while(strcmp(pass,OPass))
    {
        if(i==0) {
            printf("You have exceeded maximum number of tries.\n           Exiting Program.");
            delay(1); printf("."); delay(1); printf("."); delay(1); printf("\n");
            exit(-1);
        }
        printf("ERROR: Incorrect Password.\nYou have %d more %s left\nEnter your password again: ",i,(i==1)?"try":"tries");
        scanf("%s",pass);
        i--;
    }
    printf("Successfully Logged in as Owner :)\n");
    int option=10;
    while(option!=7){
        printf("Select an option:\n");
        printf("1.Show All Bills\n2.Read Feedbacks\n3.Check Stock\n4.Update Prices\n5.Add Stock\n6.Overall Profit or Loss\n7.Return to Login Page\n");
        scanf(" %d",&option);
        if(option==1)
        {
            system("cls");
            printf("\n***************BILLS***************\n\n");
            int count=1;
            bill* curr=*root;
            if(curr->next==NULL)
            {
                printf("NO BILLS FOUND\n");
                getch();
                printf("Redirecting to Login Page."); delay(1); printf("."); delay(1); printf("."); delay(1); printf("\n\n");
                LoginPage(head,root);
                return;
            }
            while(curr->next!=NULL)
            {
                printf("*********************BILL-%d********************\n",count);
                printBill(curr);
                curr->PorL>=0?printf("Profit%% = %.2f\n",curr->PorL):printf("Loss%% = %.2f\n",-1*curr->PorL);
                printf("Payment Option Chosen : ");
                if(curr->modeOfPayment==1) printf("Net Banking\n");
                else if(curr->modeOfPayment==2) printf("Card\n");
                else if(curr->modeOfPayment==3) printf("Cash\n");
                printf("\nFEEDBACK : %s\n\n",curr->feedback);
                curr=curr->next;
                count++;
                printf("\nPress any key to display Next Bill...\n"); getch();
            }
            printf("\n\nEND OF BILLS\n\n");
        }
        else if(option==2)
        {
            system("cls");
            printf("\n***************FEEDBACKS***************\n\n");
            int count=1;
            bill* curr=*root;
            while(curr->next!=NULL)
            {
                printf("%d) %s\n",count,curr->feedback);
                curr=curr->next;
                count++;
            }
        }
        else if(option==3)
        {
            checkStock();
        }
        else if(option==4)
        {
            printf("Enter the Product Index(1-10) for which you wish to update Price : ");
            int p_index;
            scanf(" %d",&p_index);
            printf("Product-%d\n",p_index);
            printf("OLD PRICE : %d\n",stock[p_index-1].MRP);
            printf("Enter NEW PRICE : "); scanf(" %d",&stock[p_index-1].MRP);
            printf("Successfully updated MRP of Product-%d to %d\n",p_index,stock[p_index-1].MRP);
        }
        else if(option==5)
        {
            printf("Enter the Product Index(1-10) for which you wish to add stock : ");
            int p_index;
            scanf(" %d",&p_index);
            printf("Product-%d\n",p_index);
            printf("STOCK AVAILABLE = %d",stock[p_index-1].quantityLeft);
            int addStock;
            printf("Enter the quantity of Product-%d you wish to Add to : ",p_index);
            scanf(" %d",&addStock);
            stock[p_index-1].quantityLeft+=addStock;
            printf("Successfully add stock to Product-%d\n Now Quantity of Product-%d left is %d\n",p_index,p_index,stock[p_index-1].quantityLeft);
        }
        else if(option==6)
        {
            system("cls");
            printf("**************PROFIT/LOSS***************\n");
            printf("\nBill-index     Profit/Loss      Percentage\n");
            float sum=0;
            int count=1;
            bill* curr=*root;
            while(curr->next!=NULL)
            {
                printf("Bill-%d        ",count);
                if(curr->PorL>0)
                {
                    printf("\033[0;32m"); printf("   PROFIT         %.2f\n",curr->PorL); printf("\033[0m");
                }
                else if(curr->PorL<0)
                {
                    printf("\033[0;31m"); printf("   LOSS         %.2f\n",-1*curr->PorL); printf("\033[0m");
                }
                else printf("NO LOSS NO GAIN");
                sum+=curr->PorL;
                curr=curr->next;
                count++;
            }
        }
        printf("Press any key to continue...\n\n");
        getch();
    }
    printf("Redirecting to Login Page."); delay(1); printf("."); delay(1); printf("."); delay(1); printf("\n\n");
    LoginPage(head,root);
}

void LoginPage(bill** head,bill** root)
{
    printf("**********LOGIN PAGE**********\n");
    printf("Enter your JobId \n'1' for Cashier \n'2' for Admin \n'3' for Owner \n'0' if you want to Exit\n");
    int jobId;
    scanf("%d",&jobId);
    if(jobId==0)
    {
        printf("\nExiting Program.");
        delay(1); printf("."); delay(1); printf("."); delay(1); printf("\n");
        exit(-1);
    }
    else if(jobId==1)
    {
        system("cls");
        CashierPage(head,root);
    }
    else if(jobId==2)
    {
        system("cls");
        AdminPage(head,root);
    }
    else if(jobId==3)
    {
        system("cls");
        OwnerPage(head,root);
    }
}

void delay(int number_of_seconds) 
{ 
    int milli_seconds = 1000 * number_of_seconds; 
    clock_t start_time = clock(); 
    while (clock() < start_time + milli_seconds) ; 
} 



int main()
{
    system("cls");
    printf("***********WELCOME************\n");
    printf("Press any key to continue...\n");
    getch();
    printf("Configuring details of Cashiers by the Admin."); 
    delay(1); printf("."); delay(1); printf("."); delay(1); printf("\n");
    init_Cashiers();
    init_stock();
    bill* head;
    head=newBill();
    bill* root;
    root=head;
    system("cls");
    LoginPage(&head,&root);
    return 0;
}
