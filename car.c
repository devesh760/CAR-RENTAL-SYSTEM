#include<stdio.h>
#include<string.h>
#include<time.h>
#include<stdlib.h>
#include"conio2.h"
#include"car.h"
#include <windows.h>

void addAdmin()
{
    FILE *fp=fopen("admin.bin","rb");
    if(fp==NULL)
    {
        fp=fopen("admin.bin","wb");
        User u[2]={{"admin","abc","Ramesh"},{"aftab","abc","Md Aftab Ahmad"}};
        fwrite(u,sizeof(u),1 ,fp);
        fclose(fp);
        printf("File saved!");
        _getch();
    }
    else
    {
        fclose(fp);
    }
}
User* getInput()
{
    int i;
    clrscr();
    textcolor(YELLOW);
    gotoxy(32,1);
    printf("CAR RENTAL SYSTEM\n");
    for(i=0;i<=80;i++)
        printf("%c",2);
    gotoxy(32,5);
    printf("*LOGIN PANEL*");
    gotoxy(1,7);
    textcolor(LIGHTCYAN);
    for(i=0;i<80;i++)
        printf("%c",2);
    gotoxy(1,15);
    for(i=0;i<80;i++)
        printf("%c",2 );
    gotoxy(60,8);
    textcolor(WHITE);
    printf("Press 0 to exit");
    gotoxy(25,10);
    textcolor(LIGHTCYAN);
    printf("Enter user id:");
    fflush(stdin);
    textcolor(WHITE);
    static User usr;
    fgets(usr.userid,20,stdin);
    char *pos;
    pos=strchr(usr.userid,'\n');
    *pos='\0';
    if(strcmp(usr.userid,"0")==0)
    {
        textcolor(LIGHTRED);
        gotoxy(30,17);
        printf("Login Cancelled!");
        _getch();
        textcolor(YELLOW);
        return NULL;
    }
    gotoxy(25,11);
    textcolor(LIGHTCYAN);
    printf("Enter Password:");
    fflush(stdin);
    i=0;
    textcolor(WHITE);
    for(;;)
    {
        usr.pwd[i]=_getch();
        if(usr.pwd[i]==13)
            break;
        else if(usr.pwd[i]==8)
        {
            if(i!=0)
            {
            i--;
            printf("\b \b");
            }
        }
         else
         {
         printf("*");
         i++;
         }
    }
    usr.pwd[i]='\0';
    if(strcmp(usr.pwd,"0")==0)
    {
        textcolor(LIGHTRED);
        gotoxy(30,17);
        printf("Login cancelled!");
        _getch();
        textcolor(YELLOW);
        return NULL;
    }
    return &usr;
}
int checkUserExist(User u,char *usertype)
{
   if(strcmp(u.userid,"")==0||strcmp(u.pwd,"")==0)
   {
       gotoxy(28,20);
       textcolor(LIGHTRED);
       printf("BOTH FIELDS ARE MANDATORY" );
       _getch();
       gotoxy(28,20);
       printf("\t\t\t\t\t\t\t\t\t");
       gotoxy(39,10);
       return 0;
   }
   int found=0;
   if(!(strcmp(usertype,"admin")))
   {
       FILE *fp=fopen("admin.bin","rb");
       User user;
       while(fread(&user,sizeof(User),1,fp)==1)
       {
           if(strcmp(u.userid,user.userid)==0&&strcmp(u.pwd,user.pwd)==0)
           {
               found=1;
               break;
           }
       }
       if(!found)
       {
           gotoxy(27,20);
           textcolor(LIGHTRED);
           printf("INVALID USERID OR PASSWORD");
           _getch();
           fclose(fp);
           return 0;
       }
       fclose(fp);
       return 1;
   }
   else if(!(strcmp(usertype,"emp")))
   {
       FILE *fp=fopen("emp.bin","rb");
       User user;
       while(fread(&user,sizeof(User),1,fp)==1)
       {
           if(strcmp(u.userid,user.userid)==0&&strcmp(u.pwd,user.pwd)==0)
           {
               found=1;
               break;
           }
       }
       if(!found)
       {
           gotoxy(27,20);
           textcolor(LIGHTRED);
           printf("INVALID USERID OR PASSWORD");
           _getch();
           fclose(fp);
           return 0;
       }
       fclose(fp);
       return 1;
   }
   return 0;
}
int adminMenu()
{
    int choice,i;
    textcolor(LIGHTRED);
    gotoxy(32,2);
    printf("CAR RENTAL SYSTEM");
    textcolor(LIGHTGREEN);

    gotoxy(35,6);
    printf("ADMIN MENU\n");
    for(i=0;i<80;i++)
    {
        printf("*");
    }
    textcolor(YELLOW);
    gotoxy(32,8);
    printf("1. Add Employee");
    gotoxy(32,9);
    printf("2. Add Car Details");
    gotoxy(32,10);
    printf("3. Show Employees");
    gotoxy(32,11);
    printf("4. Show Car Details");
    gotoxy(32,12);
    printf("5. Delete Employee");
    gotoxy(32,13);
    printf("6. Delete Car Details");
    gotoxy(32,14);
    printf("7. Exit");
    gotoxy(32,16);
    printf("Enter your choice:");
    textcolor(WHITE);
    scanf("%d",&choice);
    return choice;
}
void addEmployee()
{
    FILE *fp=fopen("emp.bin","rb");
    int id;
    char uchoice;
    char emp[10]="Emp-";
    char empid[10];
    User u,ur;
    if(fp==NULL)
    {
        fp=fopen("emp.bin","ab");
        id=1;
        sprintf(empid,"%d",id);
        strcat(emp,empid);
        strcpy(u.userid,emp);
        strcpy(emp,"Emp-");
    }
    else
    {
         fp=fopen("emp.bin","ab+");
         fseek(fp,-60,SEEK_END);
         fread(&ur,sizeof(ur),1,fp);
         char sub[3];
         char str[20];
         strcpy(str,ur.userid);
         sub_str(str,sub,'-');
         id=atoi(sub);
         id++;
         sprintf(empid,"%d",id);
         strcat(emp,empid);
         strcpy(u.userid,emp);
         strcpy(emp,"Emp-");
    }
    do
    {
       clrscr();
       gotoxy(32,2);
       textcolor(LIGHTRED);
       printf("CAR RENTAL SYSTEM");
       textcolor(LIGHTGREEN);
       int i;
       gotoxy(1,3);
       for(i=0;i<80;i++)
       {
           printf("~");
       }
       textcolor(WHITE);
       gotoxy(25,5);
       printf("***** ADD EMPLOYEE DETAILS *****");
       gotoxy(1,8);
       textcolor(YELLOW);
       printf("Enter Employee Name:");
       fflush(stdin);
       textcolor(WHITE);
       fgets(u.name,20,stdin);
       char *pos;
       pos=strchr(u.name,'\n');
       *pos='\0';
       textcolor(YELLOW);
       printf("Enter Employee pwd:");
       fflush(stdin);
       textcolor(WHITE);
       fgets(u.pwd,20,stdin);
       pos=strchr(u.pwd,'\n');
       *pos='\0';
       textcolor(YELLOW);
       fseek(fp,0,SEEK_END);
       fwrite(&u,sizeof(User),1,fp);
       gotoxy(30,15);
       textcolor(LIGHTGREEN);
       printf("EMPLOYEE ADDED SUCCESSFULLY");
       printf("\n EMPLOYEE ID IS: %s",u.userid);
       _getch();
       gotoxy(1,20);
       textcolor(LIGHTRED);
       printf("DO YOU WANT TO ADD MORE EMPLOYEE(Y/N):");
       textcolor(WHITE);
       fflush(stdin);
       scanf("%c",&uchoice);
       id++;
       sprintf(empid,"%d",id);
       strcat(emp,empid);
       strcpy(u.userid,emp);
       strcpy(emp,"Emp-");
    }while(uchoice=='Y'||uchoice=='y');
    fclose(fp);
}
void viewEmployee()
{
    FILE *fp=fopen("emp.bin","rb");
    User ur;
    int i;
    textcolor(YELLOW);
    gotoxy(32,1);
    printf("CAR RENTAL SYSTEM\n ");
    for(i=0;i<80;i++)
    {
        printf("%c",247);
    }
    gotoxy(31,5);
    textcolor(YELLOW);
    printf("* EMPLOYEE DETAILS *");
    gotoxy(1,7);
    textcolor(LIGHTGREEN);
    for(i=0;i<80;i++)
        printf("%c",247);
    gotoxy(1,8);
    printf(" Employee ID\t\t\tName\t\t\tPassword");
    gotoxy(1,9);
    textcolor(LIGHTGREEN);
    for(i=0;i<80;i++)
        printf("%c",247);
    int x=10;
    textcolor(YELLOW);
    while(fread(&ur,sizeof(ur),1,fp)==1)
    {
        gotoxy(2,x);
        printf("%s",ur.userid);
        gotoxy(33,x);
        printf("%s",ur.name);
        gotoxy(57,x);
        printf("%s",ur.pwd);
        x++;
    }
    fclose(fp);
    _getch();
}
int deleteEmp()
{
    FILE *fp1=fopen("emp.bin","rb");
    char empid[10];
    int i;
    textcolor(YELLOW);
    gotoxy(32,1);
    printf("CAR RENTAL SYSTEM\n");
    for(i=1;i<80;i++)
        printf("%c",247);
    gotoxy(29,5);
    textcolor(YELLOW);
    printf("* DELETE EMPLOYEE RECORD *");
    gotoxy(1,7);
    textcolor(LIGHTGREEN);
    for(i=0;i<80;i++)
    printf("%c",247);
    gotoxy(1,12);
    for(i=1;i<80;i++)
      printf("%c",247);
    if(fp1==NULL)
    {
        textcolor(LIGHTRED);
        printf("\nNO Employee id to delete the record");
        return -1;
    }
        FILE *fp2=fopen("temp.bin","wb+");
        gotoxy(10,9);
        textcolor(YELLOW);
        printf("Enter Employee id to delete the record");
        textcolor(WHITE);
        scanf("%s",empid);
        User u;
        int found=0;

        while(fread(&u,sizeof(u),1,fp1)==1)
        {
            if(strcmp(u.userid,empid)!=0)
            {
                fwrite(&u,sizeof(u),1,fp2);
            }
            else
            {
                found=1;
            }
        }
        fclose(fp1);
        if(found==1)
        {
            rewind(fp2);
            fp1=fopen("emp.bin","wb");
            while(fread(&u,sizeof(u),1,fp2)==1)
            {
                fwrite(&u,sizeof(u),1,fp1);
            }
            fclose(fp1);
        }
        fclose(fp2);
        remove("temp.bin");
        return found;
}
void addCarDetails()
{
    FILE *fp=fopen("car.bin","rb ");
    int id,i;
    char choice;
    Car c,cr;
    if(fp==NULL)
    {
        fp=fopen("car.bin","ab");
        id=1;
        c.car_id=id;
    }
    else
    {
         fp=fopen("car.bin","ab+");
         fseek(fp,-sizeof(Car),SEEK_END);
         fread(&cr,sizeof(cr),1,fp);
         id=cr.car_id;
         id++;
         c.car_id=id;
    }
    do
    {
    clrscr();
    fseek(fp,0,SEEK_END);
    textcolor(RED);
    gotoxy(32,2);
    printf("CAR RENTAL SYSTEM");
    textcolor(CYAN);
    gotoxy(28,5);
    printf("*****Add Car Details*****\n");
    textcolor(YELLOW);
    for(i=0;i<80;i++)
        printf("%c",247);
    gotoxy(1,8);
    textcolor(YELLOW);
    printf("Enter Car Model:");
    fflush(stdin);
    textcolor(WHITE);
    fgets(c.car_name,50,stdin);
    char *pos=strchr(c.car_name,'\n');
    *pos='\0';
    fflush(stdin);
    textcolor(YELLOW);
    printf("Enter Car Count:");
    textcolor(WHITE);
    scanf("%d",&c.car_count);
    fflush(stdin);
    textcolor(YELLOW);
    printf("Enter car capacity:");
    textcolor(WHITE);
    scanf("%d",&c.capacity);
    textcolor(YELLOW);
    printf("Enter Car Price:");
    textcolor(WHITE);
    scanf("%d",&c.price);
    fwrite(&c,sizeof(c),1,fp);
    textcolor(GREEN);
    printf("\n\nCar added successfully\nCar id is:%d",c.car_id);
    _getch();
    textcolor(RED);
    printf("\n\n\n\n\nDo you want to add any more car details(y/n):");
    textcolor(WHITE);
    fflush(stdin);
    scanf("%c",&choice);
    id++;
    c.car_id=id;
    }while(choice == 'Y'||choice=='y');
    fclose(fp);
}
void showCarDetails()
{
    int i;
    FILE *fp=fopen("car.bin","rb");
    textcolor(RED);
    gotoxy(34,1);
    printf("CAR RENTAL SYSTEM\n");
    textcolor(YELLOW);
    for(i=0;i<=81;i++)
        printf("%c",247);
    gotoxy(33,5);
    printf("*ALL CAR DETAILS*\n");
    textcolor(GREEN);
    for(i=0;i<=81;i++)
        printf("%c",247);
    textcolor(WHITE);
    printf(" CAR ID      MODEL\t\tCAPICITY         AVAILABLE\t     PRICE/RATE\n");
    textcolor(GREEN);
    for(i=0;i<=81;i++)
        printf("%c",247);
    Car c;
    int x=9;
    textcolor(LIGHTCYAN);
    while(fread(&c,sizeof(c),1,fp)==1 )
    {
        gotoxy(2,x);
        printf("%d",c.car_id);
        gotoxy(14,x);
        printf("%s",c.car_name);
        gotoxy(37,x);
        printf("%d",c.capacity);
        gotoxy(54,x);
        printf("%d",c.car_count);
        gotoxy(70,x);
        printf("%d",c.price);
        x++;
    }
    _getch();
    fclose(fp);
}
int deleteCarModel()
{
    FILE *fp1=fopen("car.bin","rb");
    int i;
    textcolor(YELLOW);
    gotoxy(32,1);
    printf("CAR RENTAL SYSTEM\n");
    for(i=1;i<80;i++)
        printf("%c",247);
    gotoxy(29,5);
    textcolor(YELLOW);
    printf("* DELETE CAR RECORD *");
    gotoxy(1,7);
    textcolor(LIGHTGREEN);
    for(i=0;i<80;i++)
    printf("%c",247);
    gotoxy(1,12);
    for(i=1;i<80;i++)
      printf("%c",247);
    if(fp1==NULL)
    {
        textcolor(LIGHTRED);
        printf("\nNO Car to delete the record");
        return -1;
    }
    int id;
    FILE *fp2=fopen("temp.bin","wb+");
    gotoxy(10,9);
    textcolor(YELLOW);
    printf("Enter CAR ID to delete the record:");
    textcolor(WHITE);
    fflush(stdin);
    scanf("%d",&id);
    Car c;
    int found=0;

    while(fread(&c,sizeof(Car),1,fp1)==1)
    {
        if(c.car_id!=id)
        {
            fwrite(&c,sizeof(Car),1,fp2);
        }
        else
        {
            found=1;

        }
    }
    fclose(fp1);
    if(found==1)
    {
        fp1=fopen("car.bin","wb");
        rewind(fp2);
        while(fread(&c,sizeof(Car),1,fp2)==1)
        {
            fwrite(&c,sizeof(Car),1,fp1);
        }
        fclose(fp1);
    }
    fclose(fp2);
    remove("temp.bin");
    return found;

}
//start here car code
void sub_str(char *str,char *sub,char c)
{
     int i,f=0,j=0;
     for(i=0;str[i]!=c;i++)
     {
         f++;
     }
     for(i=++f;str[i]!='\0';i++)
     {
         sub[j]=str[i];
         j++;
     }
     sub[j]='\0';
}
int empMenu()
{
    int choice ,i;
    textcolor(LIGHTRED);
    gotoxy(32,2);
    printf("CAR RENTAL SYSTEM");
    textcolor(LIGHTGREEN);
    gotoxy(35,6);
    printf("EMPLOYEE MENU\n");
    for(i=0;i<80;i++)
        printf("*");
    textcolor(YELLOW);
    gotoxy(32,8);
    printf("1. Rent a car");
    gotoxy(32,9);
    printf("2. Booking Details");
    gotoxy(32,10);
    printf("3. Available Car Details");
    gotoxy(32,11);
    printf("4. Show Car Details");
    gotoxy(32,12);
    printf("5. Exit");
    gotoxy(32,15);
    printf("Enter choice:");
    textcolor(WHITE);
    scanf("%d",&choice);
    return choice;
}
int selectCarModel()
{
    int flag;
    FILE *fp=fopen("car.bin","rb");
    Car c;
    int choice,x=9;
    gotoxy(34,x);
    while(fread(&c,sizeof(c),1,fp)==1)
    {
        if(c.car_count>0)
        {
            printf("%d . %s",c.car_id,c.car_name);
            gotoxy(34,++x);
        }
    }
    gotoxy(34,x+2);
    printf("Enter your choice:");
    textcolor(WHITE);
    while(1)
    {
        flag = 0;
        scanf("%d",&choice);
        if(choice == 0)
        {
            fclose(fp);
            return choice;
        }
        rewind(fp);
        while(fread(&c,sizeof(c),1,fp)==1)
        {
            if(c.car_id==choice && c.car_count>0)
            {
                flag=1;
                break;
            }
        }
        if(flag==1)
        {
            fclose(fp);
            return choice;
        }
        else
        {
            gotoxy(37,x+4);
            textcolor(LIGHTRED);
            printf("Wrong input");
            _getch();
            gotoxy(35,x+4);
            printf("\t\t");
            gotoxy(52,x+2);
            printf("\t");
            gotoxy(52,x+2);
            textcolor(WHITE);
        }
    }
}
int isValidDate(struct tm dt)
{
    SYSTEMTIME time;
    GetSystemTime(&time);
    if(dt.tm_year>=time.wYear && dt.tm_year<=time.wYear+2)
    {
        if(dt.tm_mon>=time.wMonth && dt.tm_mon<=12)
        {
            if((dt.tm_mday>=time.wDay && dt.tm_mday<=31) && (dt.tm_mon==1 || dt.tm_mon==3 || dt.tm_mon==5 ||dt.tm_mon==7 || dt.tm_mon==8 || dt.tm_mon==10 || dt.tm_mon==12))
                return 1;
            else if((dt.tm_mday>=time.wDay &&dt.tm_mday<=30) && (dt.tm_mon==4 ||dt.tm_mon==6 || dt.tm_mon==9 || dt.tm_mon==11))
                return 1;
            else if((dt.tm_mday>=time.wDay && dt.tm_mday<=28) && (dt.tm_mon==2))
                return 1;
            else if(dt.tm_mon==29 && dt.tm_mon==2 && (dt.tm_year%400==0 ||(dt.tm_year%4==0 && dt.tm_year%100!=0)))
                return 1;
                else
                    return 0;
        }
        else
        {
            return 0;
        }
    }
    else
    {
        return 0;
    }
}
void updateCarCount(int C)
{
    FILE *fp=fopen("car.bin","rb+");
    Car c;
    while(fread(&c,sizeof(Car),1,fp)==1)
    {
        if(c.car_id==C)
        {
            c.car_count=c.car_count-1;
            fseek(fp,-sizeof(Car),SEEK_CUR);
            fwrite(&c,sizeof(Car),1,fp);
            break;
        }
    }
    fclose(fp);
}
char* getCarName(int car_id)
{
    FILE *fp=fopen("car.bin","rb+");
    static Car c;
    while(fread(&c,sizeof(c),1,fp)==1)
    {
        if(c.car_id==car_id)
        {
            break;
        }
    }
    fclose(fp);
    return c.car_name;
}
void bookedCarDetails()
{
    clrscr();
    FILE *fp=fopen("customer.bin","rb");
    Customer_Car_Details cc;
    int i;
    textcolor(YELLOW);
    gotoxy(32,1);
    printf("CAR RENTAL SYSTEM\n");
    for(i=0;i<80;i++)
        printf("%c",2);
    gotoxy(31,5);
    textcolor(YELLOW);
    printf("* Booked Car Details *");
    gotoxy(1,7);
    textcolor(LIGHTGREEN);
    for(i=0;i<80;i++)
        printf("%c",2);
    gotoxy(1,8);
    printf("Model\t   Cust Name\t  pick up\t  Drop\t\t S_Date\t     E_Date");
    gotoxy(1,9);
    textcolor(LIGHTGREEN);
    for(i=0;i<80;i++)
        printf("%c",2);
    int x=10;
    textcolor(YELLOW);

    while(fread(&cc,sizeof(Customer_Car_Details),1,fp)==1)
    {
        gotoxy(1,x);
        printf("%s",getCarName(cc.car_id));
        gotoxy(13,x);
        printf("%s",cc.cust_name);
        gotoxy(27,x);
        printf("%s",cc.pick);
        gotoxy(44,x);
        printf("%s",cc.drop);
        gotoxy(58,x);
        printf("%d-%d-%d",cc.sd.tm_mday,cc.sd.tm_mon,cc.sd.tm_year);
        gotoxy(70,x);
        printf("%d-%d-%d",cc.ed.tm_mday,cc.ed.tm_mon,cc.ed.tm_year);
        x++;
    }
    fclose(fp);
    _getch();
}
int rentCar()
{
    Customer_Car_Details cc;
    int c,i;
    textcolor(LIGHTRED);
    gotoxy(32,2);
    printf("CAR RENTAL SYSTEM");
    textcolor(LIGHTGREEN);
    gotoxy(35,6);
    printf("EMPLOYEE MENU\n");
    for(i=0;i<80;i++)
        printf("*");
    gotoxy(67,8);
    textcolor(WHITE);
    printf("Press 0 to exit");
    textcolor(YELLOW);
    gotoxy(32,8);
    c=selectCarModel();
    if(c == 0)
        return c;
    cc.car_id=c;
    clrscr();
    textcolor(LIGHTRED);
    gotoxy(32,2);
    printf("CAR RENTAL SYSTEM");
    textcolor(LIGHTGREEN);
    gotoxy(35,6);
    printf("EMPLOYEE MENU\n");
    for(i=0;i<80;i++)
        printf("*");
    gotoxy(1,17);
    for(i=0;i<80;i++)
        printf("*");
    textcolor(YELLOW);
    gotoxy(27,9);;
    printf("Enter Customer Name:");
    fflush(stdin);
    textcolor(WHITE);
    fgets(cc.cust_name,30,stdin);
    char *pos;
    pos=strchr(cc.cust_name,'\n');
    *pos='\0';
    gotoxy(27,10);
    textcolor(YELLOW);
    printf("Enter pickup point:");
    fflush(stdin);
    textcolor(WHITE);
    fgets(cc.pick,30,stdin);
    *pos='\0';
    gotoxy(27,11);
    textcolor(YELLOW);
    printf("Enter Drop Point:");
    fflush(stdin);
    textcolor(WHITE);
    fgets(cc.drop,30,stdin);
    pos=strchr(cc.drop,'\n');
    *pos='\0';
    gotoxy(27,12);
    textcolor(YELLOW);
    printf("Enter start date (dd/mm/yyyy):");
    textcolor(WHITE);
    do
    {
        scanf("%d/%d/%d",&cc.sd.tm_mday,&cc.sd.tm_mon,&cc.sd.tm_year);
        int dateValid=isValidDate(cc.sd);
        if(dateValid==0)
        {
                  gotoxy(27,18);
                  textcolor(LIGHTRED);
                  printf("Wrong Date");
                  _getch();
                  gotoxy(27,18);
                  printf("\t\t");
                  gotoxy(56,12);
                  printf("\t\t\t");
                  gotoxy(56,12);
                  textcolor(WHITE);
        }
        else
            break;

    }while(1);
    gotoxy(27,13);
    textcolor(YELLOW);
    printf("Enter end date (dd/mm/yyyy):");
    textcolor(WHITE);
    do
    {
        scanf("%d/%d/%d",&cc.ed.tm_mday,&cc.ed.tm_mon,&cc.ed.tm_year);
        int dateValid1=isValidDate(cc.ed);
        int dateValid2=VALIDdate(cc.sd,cc.ed);
        if(dateValid1 == 0 || dateValid2 == 0)
        {
                  gotoxy(27,18);
                  textcolor(LIGHTRED);
                  printf("Wrong Date");
                  _getch();
                  gotoxy(27,18);
                  printf("\t\t");
                  gotoxy(55,13);
                  printf("\t\t\t");
                  gotoxy(55,13);
                  textcolor(WHITE);
        }
        else
            break;
    }while(1);
    FILE *fp;
    fp=fopen("customer.bin","ab");
    fwrite(&cc,sizeof(Customer_Car_Details),1,fp);
    updateCarCount(c);
    printf("\nPress any key to continue...");
    _getch();
    fclose(fp);
    bookedCarDetails();
    return 1;
}
void showAvailableCarDetails()
{
    int i;
    FILE *fp=fopen("car.bin","rb");
    textcolor(RED);
    gotoxy(34,1);
    printf("CAR RENTAL SYSTEM\n");
    textcolor(YELLOW);
    for(i=0;i<=81;i++)
        printf("*");
    gotoxy(33,5);
    printf("*ALL CAR DETAILS*\n");
    textcolor(GREEN);
    for(i=0;i<=81;i++)
        printf("%c",2);
    textcolor(WHITE);
    printf(" CAR ID      MODEL\t\tCAPICITY         AVAILABLE\t     PRICE/RATE\n");
    textcolor(GREEN);
    for(i=0;i<=81;i++)
        printf("%c",2);
    Car c;
    int x=9;
    textcolor(LIGHTCYAN);
    while(fread(&c,sizeof(c),1,fp)==1 )
    {
        if(c.car_count<=0)
            continue;
        gotoxy(2,x);
        printf("%d",c.car_id);
        gotoxy(14,x);
        printf("%s",c.car_name);
        gotoxy(37,x);
        printf("%d",c.capacity);
        gotoxy(54,x);
        printf("%d",c.car_count);
        gotoxy(70,x);
        printf("%d",c.price);
        x++;
    }
    _getch();
    fclose(fp);
}
void showSelectedCarDetails()
{
    int i;
    FILE *fp=fopen("car.bin","rb");
    textcolor(RED);
    gotoxy(34,1);
    printf("CAR RENTAL SYSTEM\n");
    textcolor(YELLOW);
    for(i=0;i<=81;i++)
        printf("*");
    gotoxy(33,5);
    printf("*ALL CAR DETAILS*\n");
    textcolor(GREEN);
    for(i=0;i<=81;i++)
        printf("%c",2);
    textcolor(WHITE);
    printf(" CAR ID      MODEL\t\tCAPICITY         AVAILABLE\t     PRICE/RATE\n");
    textcolor(GREEN);
    for(i=0;i<=81;i++)
        printf("%c",2);
    Car c;
    int x=9;
    textcolor(LIGHTCYAN);
    while(fread(&c,sizeof(c),1,fp)==1 )
    {
        gotoxy(2,x);
        printf("%d",c.car_id);
        gotoxy(14,x);
        printf("%s",c.car_name);
        gotoxy(37,x);
        printf("%d",c.capacity);
        gotoxy(54,x);
        printf("%d",c.car_count);
        gotoxy(70,x);
        printf("%d",c.price);
        x++;
    }
    _getch();
    fclose(fp);
}
int VALIDdate(struct tm sd,struct tm ed)
{
    if(sd.tm_year==ed.tm_year)
    {
        if(sd.tm_mon==ed.tm_mon)
        {
            if(sd.tm_mday<=ed.tm_mday)
                return 1;
            else
             return 0;
        }
        else if(sd.tm_mon<ed.tm_mon)
        {
              return 1;
        }
        else
        return 0;

    }
    else if(sd.tm_year<ed.tm_year)
    {
        return 1;
    }
    else
        return 0;
}
