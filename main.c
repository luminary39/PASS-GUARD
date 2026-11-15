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
int from_leaked_passwords = 0; // global flag variable value


/*
==================================================================
================== Password Checker Functions ====================
==================================================================
*/

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

// declaring function for -- 10k most common password checker

int ten_thousand_most_common_password(char pass[]){

    FILE *fp;
    char word[1024];

    fp = fopen("Common Passwords/10k-most-common.txt", "r");

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

// declaring function for -- 100k-most-used-passwords-NCSC

int hundred_thousand_most_common_password(char pass[]){

    FILE *fp;
    char word[1024];

    fp = fopen("Common Passwords/100k-most-used-passwords-NCSC.txt", "r");

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

// declaring function for -- twentieth_century_dates_1900_2020

int twentieth_century_dates_1900_2020(char pass[]){

    FILE *fp;
    char word[1024];

    fp = fopen("Common Passwords/twentieth_century_dates_1900_2020.txt", "r");

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


// declaring function for -- 2020-200_most_used_passwords

int load2020Top200Passwords(char pass[]){

    FILE *fp;
    char word[1024];

    fp = fopen("Common Passwords/2020-200_most_used_passwords.txt", "r");

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


// declaring function for -- 2023-200_most_used_passwords

int load2023Top200Passwords(char pass[]){

    FILE *fp;
    char word[1024];

    fp = fopen("Common Passwords/2023-200_most_used_passwords.txt", "r");

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








/*
==================================================================
================== Passwords Strength Checker ====================
==================================================================
*/


// declaring function for -- password strength cheaker
void pass_strength(char pass[]){
    upper = lower = numbers = special = spaces = 0; // resetting values to 0

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

// int main(){

//     // resetting global flag variable value
//     from_leaked_passwords = 0;

//     printf("Enter Your Password(enter 0 to close): ");
//     scanf("%99s", pass);
//     int total_characters = strlen(pass);

//     // programe quitting feature
//     if (strcmp(pass, "0") == 0){
//         printf("Program Closed.\n");
//         return 0;
//     }

//     if(total_characters >=4){
//         if (check_common_passwords(pass) == 1){
//             printf("Your Giver Password Is Vulnerable! Found In Our \"Top 20 Common SSH Passwords\" Database, \nTry Again ...\n");
//             from_leaked_passwords++;
//             main();
//         }

//         if (ten_thousand_most_common_password(pass) == 1) 
//         {
//             printf("Your Giver Password Is Vulnerable! Found In Our \"10K Most Common Password Database\", \nTry Again ...\n");
//             from_leaked_passwords++;
//             main();
//         }

//         if (hundred_thousand_most_common_password(pass) == 1) 
//         {
//             printf("Your Giver Password Is Vulnerable! Found In Our \"100k-most-used-passwords-NCSC Database\", \nTry Again ...\n");
//             from_leaked_passwords++;
//             main();
//         }

//         if (twentieth_century_dates_1900_2020(pass) == 1) 
//         {
//             printf("Your Giver Password Is Vulnerable! Found In Our \"twentieth_century_dates_1900_2020 Database\", \nTry Again ...\n");
//             from_leaked_passwords++;
//             main();
//         }

//         if(load2020Top200Passwords(pass) == 1)
//         {
//             printf("Your Giver Password Is Vulnerable! Found In Our \"2020-200_most_used_passwords Database\", \nTry Again ...\n");
//             from_leaked_passwords++;
//             main();
//         }

//         if(load2023Top200Passwords(pass) == 1)
//         {
//             printf("Your Giver Password Is Vulnerable! Found In Our \"2023-200_most_used_passwords Database\", \nTry Again ...\n");
//             from_leaked_passwords++;
//             main();
//         }


        

//         else{
//             pass_strength(pass);
//         }

//         /*
//         There's a bug while repeating until password is strongt
//         */

        
//     }

//     else{
//         printf("Password Need to be at least 4 character long!\n\n");
//         main();
//     }
// }

int main(){

    while (1){

        // resetting global flag variable value
        from_leaked_passwords = 0;

        printf("Enter Your Password(enter 0 to close): ");
        scanf("%99s", pass);
        int total_characters = strlen(pass);

        // programe quitting feature
        if (strcmp(pass, "0") == 0){
            printf("Program Closed.\n");
            return 0;
        }

        if (total_characters < 4){
            printf("Password Need to be at least 4 character long!\n\n");
            continue;
        }

        // check ALL databases, report every one that matches
        printf("\n");

        if (check_common_passwords(pass) == 1){
            printf("Found In: \"Top 20 Common SSH Passwords\"\n");
            from_leaked_passwords++;
        }

        if (ten_thousand_most_common_password(pass) == 1){
            printf("Found In: \"10K Most Common Password Database\"\n");
            from_leaked_passwords++;
        }

        if (hundred_thousand_most_common_password(pass) == 1){
            printf("Found In: \"100k-most-used-passwords-NCSC Database\"\n");
            from_leaked_passwords++;
        }

        if (twentieth_century_dates_1900_2020(pass) == 1){
            printf("Found In: \"twentieth_century_dates_1900_2020 Database\"\n");
            from_leaked_passwords++;
        }

        if (load2020Top200Passwords(pass) == 1){
            printf("Found In: \"2020-200_most_used_passwords Database\"\n");
            from_leaked_passwords++;
        }

        if (load2023Top200Passwords(pass) == 1){
            printf("Found In: \"2023-200_most_used_passwords Database\"\n");
            from_leaked_passwords++;
        }

        // verdict
        if (from_leaked_passwords > 0){
            printf("\nYour Password Is Vulnerable! Found In %d Database(s). Try Again ...\n\n", from_leaked_passwords);
            continue;
        }

        pass_strength(pass);

        // stop only when the password is strong, otherwise ask again
        if (upper && lower && numbers && special){
            break;
        }
        printf("\n\n");
    }

    return 0;
}