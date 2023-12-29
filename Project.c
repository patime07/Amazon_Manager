#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>


char readtempenter;// (!) : this variable is temporary for reading the NULL character that follows the input read by "scanf" 
char email[250][80];
char fname[250][80];
char lname[250][80];
char password[250][80];
char bankNumb[250][80];
char secretQues[250][80];
char Answer[250][80];
int Balance[250];
int SelectedUserIndex;//the (array-logic) index (starting from 0) of the selected user
int NbOfUsers=0;

void fillFromFile();
void MainPage();
void Login();
void CheckPassword(char* password, char* inputPassword, int SelectedUserIndex); 
int  check_two_inverted(char *str1, char *str2);
void secret_question(int SelectedUserIndex);
void SignUp();
void Logout(); // logout function can be called only when the login is successful 
void swap(char *a, char *b);
void PersonalPage(int SelectedUserIndex); 
void CompleteOrder(int SelectedUserIndex, int TotalPrice);
void MakeAnOrder(int SelectedUserIndex);
void deleteAccount(int SelectedUserIndex);
void ChangePersonalInfo(int SelectedUserIndex);


int main(){

    fillFromFile();
    MainPage();
  
    return 0;
}


// a function that fill the arrays with the data from the file
void fillFromFile(){
    FILE *fptr;
    fptr = fopen("database.txt", "r");
    char line[100];
    int i = 0;
    do{
        fscanf(fptr, "%s %s %s %s %s %d %s %s", &email[i], &fname[i], &lname[i], &password[i], &bankNumb[i], &Balance[i], &secretQues[i], &Answer[i] );
        i++;

    }while(fgets(line, 100, fptr) != NULL);
    NbOfUsers=i;
    fclose(fptr);
    
}

// This function prints the main menu to login or signup or exit
void MainPage(){
    int choice;
    printf("Please SignUp or Login\n");
    printf("1. SignUp\n");
    printf("2. Login\n");
    printf("3. Exit\n");
    scanf("%d",&choice);

    switch (choice) {
        case 1:
            SignUp();
            break;
        case 2:
            Login();
            break;
        case 3:
            exit(0);
            break;
        default:
            printf("Invalid Input\n");
            MainPage();
            break;
    }
}



void Login(){

    // Ask for email and password
    printf("> Enter your email : ");
    char inputEmail[100];
    scanf("%s",inputEmail);

    char inputPassword[100];


    //Check if the email exists in the file and save the password in the file
    int IsUserExist = 0;

    for(int i = 0; i < NbOfUsers; i++){
        if(strcmp(email[i], inputEmail) == 0){    // if the email exists in the file
            printf("(!) : User Already Exists\n\n");        // Exists
            IsUserExist=1;
            SelectedUserIndex=i;
            break;

        
    }
} 


// check if the password is correct if the user eixsts
if(IsUserExist){
    printf("> Enter your password: ");
    scanf("%s",inputPassword);
    CheckPassword(password[SelectedUserIndex], inputPassword, SelectedUserIndex);//Exist-> Check Password

}

else{
    printf("(!) : User does not exist\n\n"); // NotExists-> Signup
    printf("Please SignUp\n\n");
    SignUp();
}

    
}
 
 
// a function that checks if the password is correct or mistyped or wrong
void CheckPassword(char* password, char* inputPassword, int SelectedUserIndex){
    if(strcmp(password, inputPassword) == 0){ //Same -> Succes 
        printf("(!) : Login Successful\n");
        PersonalPage(SelectedUserIndex);
    }
    else{
        if(check_two_inverted(password, inputPassword) == 1){
            printf("\n(!) : Password Mistyped\n");     //Inverted -> Secret Question
            secret_question(SelectedUserIndex);
        }
        else{
            printf("(!) : Incorrect Password\n");
            printf("Please Login again\n");    //Wrong -> Re-Login
            Login();
        }
       
    }
}


// a function that check if two caracters are inverted in two strings
int check_two_inverted(char *str1, char *str2){
    int i;
    int counter_inverted = 0;
    for(i=0; i<strlen(str1); i++){
        if(str1[i] != str2[i]){ //Not equal
            if( str1[i] == str2[i-1] && str1[i-1] == str2[i]){ // if the two caracters are inverted
                counter_inverted++;
                
            }
        }
    }

    if(counter_inverted == 1){ //inverted one time
    return 1; 
    }

    else{   //not inverted at all or inverted more than one time
    return 0;
    }

}


// a function that asks the user a secret question
void secret_question(int SelectedUserIndex){
    printf("Please enter answer for your secret question\n");
    printf("Hint : %s\n", secretQues[SelectedUserIndex]);
    char inputAnswer[100];
    gets(inputAnswer);

    if(strcmp(Answer[SelectedUserIndex], inputAnswer) == 0){ //SecretQuestion -> Success
        printf("\nSecret Question is Correct\n");
        
        printf("(!) Login Successful\n");
        PersonalPage(SelectedUserIndex);

    }
    else{
        printf("\n(!) : Incorrect Answer\n");   //SecretQuestion -> Re-Login
        printf("Please Login Again\n");
        Login();
    }
    
    }


// a function that asks the user to signup
void SignUp(){

    printf("\n######################## SIGNING UP ########################\n\n");
    char InputEmail[100];
    char InputBankNumb[100];
    printf("Please enter your email\n");
    scanf("%s", InputEmail);
    printf("Please enter your bank number\n");
    scanf("%s", InputBankNumb);

    for (int i = 0; i <NbOfUsers; i++)
    {
        if(strcmp(InputEmail, email[i]) == 0){ // if the email is already in the file
            printf("Email already exists\n");
            printf("Please try again\n");
            SignUp();
            break;
        }
    

         if(strcmp(InputBankNumb, bankNumb[i]) == 0){// if the bank number is already in the file
            printf("Bank Number already exists\n");
            printf("Please try again\n");
            SignUp();
            break;
        }
    }
    
    NbOfUsers++; //increase the number of users
    int i=NbOfUsers-1;

    strcpy(email[i], InputEmail);
    strcpy(bankNumb[i], InputBankNumb);

    printf("Please enter your balance\n");
    scanf("%d", &Balance[i]);

    scanf("%c", &readtempenter);


    printf("Please enter your first name\n");
    gets(fname[i]);                                    
    printf("Please enter your last name\n");
    gets(lname[i]);
    printf("Please enter your password\n");
    scanf("%s", &password[i]);
    scanf("%c", &readtempenter);

    printf("Please enter hint for your secret question\n");
    gets(secretQues[i]);
    printf("Please enter your answer for your secret question\n");
    gets(Answer[i]);
    printf("(!) : Account created succesfully, Please Login\n");
    Login();
}



char* StringtoLower(char* str){
    int i;
    for(i=0; i<strlen(str); i++){
        str[i] = tolower(str[i]);
    }
    return str;
}


// Logout function
void Logout(){
    //sort the fname alphabetically
    for(int i = 0; i < NbOfUsers; i++){
        for(int j = 0; j < NbOfUsers; j++){
            if(strcmp(StringtoLower(lname[i]), StringtoLower(lname[j])) < 0){

                // swap the arrays (strings)
                swap(fname[i], fname[j]);
                swap(lname[i], lname[j]);
                swap(email[i], email[j]);
                swap(bankNumb[i], bankNumb[j]);
                swap(password[i], password[j]);
                swap(secretQues[i], secretQues[j]);
                swap(Answer[i], Answer[j]);
               // swap the arrays (numbers)

                int temp = Balance[i];
                Balance[i] = Balance[j];
                Balance[j] = temp;

            }
        }
    }
    
    // print the sorted array in a new file named "output.txt"
    FILE *fptr;
    fptr = fopen("output.txt", "w");

    for(int i = 0; i < NbOfUsers; i++){
        fprintf(fptr, "%s %s %s %s %s %d %s %s\n", email[i], fname[i], lname[i], password[i], bankNumb[i], Balance[i], secretQues[i], Answer[i]);
    }
    fclose(fptr);

    printf("Logout Successful\n");
    exit(0);
}

//a function that swaps two strings
void swap(char* a, char* b){
    char temp[100];
    strcpy(temp, a);
    strcpy(a, b);
    strcpy(b, temp);
}

////////////////////

// a function that shows the personal page
void PersonalPage(int SelectedUserIndex){
    printf("\n######################## PERSONAL PAGE ########################\n\n");
    printf("Welcome %s %s\n", fname[SelectedUserIndex], lname[SelectedUserIndex]);
   
    printf("1. Change Personal Information\n");
    printf("2. Make an Order\n");
    printf("3. Delete Account\n");
    printf("4. Logout\n");             
     printf("\n###############################################################\n\n");
    
    int choice;
    scanf("%d", &choice);
    switch(choice){
        case 1:

            ChangePersonalInfo(SelectedUserIndex);
            break;

        case 2:
            MakeAnOrder(SelectedUserIndex);
            break;
        case 3:
            printf("%d\n", SelectedUserIndex);
            deleteAccount(SelectedUserIndex);
            
            printf("You Will Logout \n");
            Logout();
            break;
        case 4:
            Logout();
            break;

        default:
            printf("Invalid Choice\n");
            PersonalPage(SelectedUserIndex);
            break;
    }
}

// Change Personal Information function
void ChangePersonalInfo(int SelectedUserIndex){
    
    printf("Enter your password to change your personal information\n");
    char inputPassword[100];
    char inputEmail[100];

    scanf("%s", inputPassword);
    if(strcmp(inputPassword, password[SelectedUserIndex]) == 0){
        printf("\n######################## CHANGE PERSONAL INFORMATION ########################\n\n");
        printf("1. Change First Name\n");
        printf("2. Change Last Name\n");
        printf("3. Change Email\n");
        printf("4. Change Password\n");
        printf("5. Change Bank Number\n");
        printf("6. Go Back\n");
        printf("\n###############################################################\n\n");

        int choice;
  
        do{
            printf("Please enter your choice\n");
            scanf("%d", &choice);
            scanf("%c", &readtempenter);

            switch(choice){
                case 1:
                    printf("Please enter your new first name\n");
                    gets(fname[SelectedUserIndex]);    //Problem : Ask lHana : why gets() read nothing
                    printf("First Name Changed\n");
                    break;

                case 2:
                    printf("Please enter your new last name\n");
                    gets(lname[SelectedUserIndex]);         
                    printf("Last Name Changed\n");
                    break;

                case 3: // we need to check if the email is already in the email array
                    printf("Please enter your new email\n");
                    scanf("%s", &inputEmail);

                    int isemailexists = 0;
                    for(int i = 0; i < NbOfUsers; i++){
                        if(strcmp(inputEmail, email[i]) == 0){
                            printf("[x] : Email already exists\n");
                            printf("Please try again\n");
                            isemailexists = 1;
                            break;
                        }
                    }

                    if(isemailexists == 0){
                        strcpy(email[SelectedUserIndex], inputEmail);
                        printf("(!) : Email Changed\n");
                    }

                    break;

                case 4:
                    printf("Please enter your new password\n");
                    scanf("%s", &password[SelectedUserIndex]);
                    printf("(!) : Password Changed\n");
                    break;

                case 5:
                    // we need to check if the bank number is already in the bankNumb array
                    printf("Please enter your new bank number\n");
                    char inputBankNumb[100];
                    scanf("%s", &inputBankNumb);
                  
                    int isbanknumbexists = 0;
                    for(int i = 0; i < NbOfUsers; i++){
                        if(strcmp(inputBankNumb, bankNumb[i]) == 0){
                            printf("[x] : Bank Number already exists\n");
                            printf("Please try again\n");
                            isbanknumbexists = 1;
                            break;
                        }
                    }

                    if(isbanknumbexists == 0){
                        strcpy(bankNumb[SelectedUserIndex], inputBankNumb);
                        printf("Please enter the balance for the account No:  %s\n", bankNumb[SelectedUserIndex]);
                        scanf("%d", &Balance[SelectedUserIndex]);
                        printf("(!) : Bank Number and Balance Changed\n");

                        

                    }

                   break;

                default:
                    printf("You Will Be Redirected to Your Personal Page\n");
                    PersonalPage(SelectedUserIndex);
                    break;
            }

            }while(choice != 6);  




    }
    else{
        printf("(!) : Incorrect Password, you will redirected to your Personal Page\n");
        PersonalPage(SelectedUserIndex);
    }

    
}

// Make an Order function
void MakeAnOrder(int SelectedUserIndex){
    int NbItemsAllTyps[5] = {0,0,0,0,0};
    int IsWantToBuyMore;
    int TotalPrice=0;
    printf("\n######################## MAKE AN ORDER ########################\n\n");
   
   do{
    printf("1. Buy a Book -- 200 MAD\n");
    printf("2. Buy a Skin Care -- 700 MAD\n");
    printf("3. Buy a Watch -- 1000 MAD\n");
    printf("4. Buy a Desk -- 4000 MAD\n");
    printf("5. Buy a Laptop -- 6000 MAD\n");
    printf("Please Enter Your Choice\n");
    int choice;
    scanf("%d", &choice);

    // read the quantity of the item
    printf("Please Enter The Quantity\n");
    int quantity;
    scanf("%d", &quantity);
    NbItemsAllTyps[choice-1] += quantity;
   
    // If he wants to buy more items
    printf("Do You Want To Buy More Items?\n");
    printf("1. Yes\n");
    printf("2. No\n");
    scanf("%d", &IsWantToBuyMore);

    }while(IsWantToBuyMore == 1);   

    TotalPrice = 200 * NbItemsAllTyps[0] + 700 * NbItemsAllTyps[1] + 1000 * NbItemsAllTyps[2] + 4000 * NbItemsAllTyps[3] + 6000 * NbItemsAllTyps[4];
    
    CompleteOrder(SelectedUserIndex, TotalPrice);

}
   
// Complete Order function that checks if the user has enough money to buy the items 
void CompleteOrder(int SelectedUserIndex, int TotalPrice){
    
    int RepeatedUpdateBankAccount = 1; // this goes with each order 
    int inputBalance;
    char inputBankNumb[100];

    
    printf("\n######################## COMPLETE ORDER ########################\n\n");
    printf("This order will cost you %d MAD\n", TotalPrice);
    if(Balance[SelectedUserIndex] >= TotalPrice){ //enough money
        printf("Your Order Has Been Placed Successfully\n");
        printf("Your Balance Is %d\n", Balance[SelectedUserIndex]);
        Balance[SelectedUserIndex] -= TotalPrice;
        printf("Your New Balance Is %d\n", Balance[SelectedUserIndex]);
        PersonalPage(SelectedUserIndex);
    
        }
    else{   //not enough money
        do{
            printf("You Do Not Have Enough Money To Buy This Order\n");
            printf(" > Enter a new bank number\n");
            scanf("%s", inputBankNumb);
            
            int isbanknumbexists = 0;
            //check if the bank number is already in the bankNumb array
            for(int i = 0; i < NbOfUsers; i++){
                if(strcmp(inputBankNumb, bankNumb[i]) == 0){ 
                    isbanknumbexists = 1;
                    break;
                }
            }

            if(isbanknumbexists ==1){
                RepeatedUpdateBankAccount++;
                printf("[x] : Bank Number already exists\n");
                printf("Please try again\n");

            }    

            else{
               
               
                printf("Enter your new balance for the account No:  %s\n", inputBankNumb);
                scanf("%d", &inputBalance);
                //check if balance is enough

                    if(inputBalance<TotalPrice){
                        printf("[x]: Your Balance Is Not Enough, Try again with a new bank account\n");
                        RepeatedUpdateBankAccount++;
                    }

                    else{
                         Balance[SelectedUserIndex] = inputBalance;
                         strcpy(bankNumb[SelectedUserIndex], inputBankNumb);
                        printf("Your Balance Is %d\n", Balance[SelectedUserIndex]);
                        Balance[SelectedUserIndex] -= TotalPrice;
                        printf("Your New Balance Is %d\n", Balance[SelectedUserIndex]);
                        PersonalPage(SelectedUserIndex);

                    }



            }
            
           
            
            

            
        }while(RepeatedUpdateBankAccount <=3); 


        if(RepeatedUpdateBankAccount > 3){
            printf("You Have Exceeded The Number Of Attempts\n");
            printf("Your order has been canceled\n");
            TotalPrice=0;
            PersonalPage(SelectedUserIndex);
        }
    }


}

void deleteAccount(int SelectedUserIndex){
    printf("\n######################## DELETE ACCOUNT ########################\n\n");
    printf("1. Delete Account\n");
    printf("2. Go Back\n");
    printf("\n###############################################################\n\n");
    
    int choice;
    scanf("%d", &choice);
    switch(choice){
        case 1:
        // delete the account
            strcpy(fname[SelectedUserIndex], "\0");
            strcpy(lname[SelectedUserIndex], "\0");
            strcpy(email[SelectedUserIndex], "\0");
            strcpy(password[SelectedUserIndex], "\0");
            strcpy(bankNumb[SelectedUserIndex], "\0");
            strcpy(secretQues[SelectedUserIndex], "\0");
            strcpy(Answer[SelectedUserIndex], "\0");
            Balance[SelectedUserIndex] = 0;
            
            NbOfUsers--;
            //move the other users
            for(int i = SelectedUserIndex; i < NbOfUsers; i++){
                swap(fname[i], fname[i+1]);
                swap(lname[i], lname[i+1]);
                swap(email[i], email[i+1]);
                swap(password[i], password[i+1]);
                swap(bankNumb[i], bankNumb[i+1]);
                swap(secretQues[i], secretQues[i+1]);
                swap(Answer[i], Answer[i+1]);
                 // swap the balance
                 int temp = Balance[i];
                Balance[i] = Balance[i+1];
                Balance[i+1] = temp;

            }

            printf("Your Account Has Been Deleted\n");




        break;
            
        default:
            printf("You Will Be Redirected to the User Page \n");
            PersonalPage(SelectedUserIndex);
            break;
    }
}


