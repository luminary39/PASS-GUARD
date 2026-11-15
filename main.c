#include <stdio.h>
#include <string.h>
#include <ctype.h>


//declarations
int i; 
int upper = 0; 
int lower = 0; 
int numbers = 0; 
int special = 0; 
int spaces =0;
char pass[100];
int total_characters;

// declaring function for -- common 20 password checker

int check_common_passwords(char pass[]){

    FILE *fp;
    char word[1024];

    fp = fopen("Common Passwords/top-20-common-SSH-passwords.txt", "r");

    if (fp == NULL){
        printf("Error! Password Dataset Not Found!\n");
        return -1;
    }

    while(fgets(word, sizeof(word), fp)){

        // remove newline character
        word[strcspn(word, "\n\r")] = '\0';

        // compare user password with dataset
        if (strcmp(pass, word) == 0){
            fclose(fp);
            return 1; // common password found
        }

        
    }
    fclose(fp);
    return 0; // password not found


}


// declaring function for -- password strength cheaker
void pass_strength(char pass[]){

// programe starts here

for (i = 0; i < strlen(pass); i++){
    if (isupper(pass[i])){
        upper++;
    } else if (islower(pass[i])){
        lower++;
    } else if (isdigit(pass[i])){
        numbers++;
    } else if(isspace(pass[i])){
        spaces++;
    } else{
        special++;
    }
}

    

// printing verdict
printf("\n\n========== PASSWORD Verdict ==========\n\n");
if (upper && lower && numbers && special){
    printf("\nYour Password Is Strong!");
}
else{
    printf("\nYour Password Needs To Have Minimum 1 Uppercase, 1 Lowercase, 1 Digit and 1 Special Character!");
}

// Printing Data
printf("\n\n========== PASSWORD ANALYSIS ==========\n\n");
printf("Total Uppercase: %d\n", upper);
printf("Total lowercase: %d\n", lower);
printf("Total Digits: %d\n", numbers);
printf("Total Special Characters: %d\n", special);
printf("Total Spaces: %d\n", spaces);
}

int main(){

    printf("Enter Your Password(enter 0 to close): ");
    scanf("%99s", pass);
    int total_characters = strlen(pass);

    // programe quitting feature
    if (strcmp(pass, "0") == 0){
        printf("Program Closed.\n");
        return 0;
    }

    if(total_characters >=8){
        if (check_common_passwords(pass) == 1){
            printf("Your Giver Password Is Vulnerable! Found In Our Common Password Database, \nTry Again ...\n\n");
            main();
        }

        else{
            pass_strength(pass);
        }

        /*
        There's a bug while repeating until password is strongt
        */

        
    }

    else{
        printf("Password Need to be at least 8 character long!\n\n");
        main();
    }
}