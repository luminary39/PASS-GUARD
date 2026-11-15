#include <stdio.h>
#include <string.h>
#include <ctype.h>


//declarations
int i;
int upper = 0;
int lower = 0;
int numbers = 0;
int special = 0;
int spaces = 0;
char pass[100];
int from_leaked_passwords = 0; // counts how many databases contain the password


/*
==================================================================
================== Password Database List ========================
==================================================================
*/

// add new database files here
const char *files[] = {
    "Common Passwords/top-passwords-shortlist.txt",
    "Common Passwords/top-20-common-SSH-passwords.txt",
    "Common Passwords/worst-passwords-2017-top100-slashdata.txt",
    "Common Passwords/10k-most-common.txt",
    "Common Passwords/100k-most-used-passwords-NCSC.txt",
    "Common Passwords/twentieth_century_dates_1900_2020.txt",
    "Common Passwords/2020-200_most_used_passwords.txt",
    "Common Passwords/2023-200_most_used_passwords.txt",
    "Common Passwords/2024-197_most_used_passwords.txt",
    "Common Passwords/2025-199_most_used_passwords.txt",
    "Common Passwords/500-worst-passwords.txt",
    "Common Passwords/Pwdb_top-1000.txt",
    "Common Passwords/Pwdb_top-10000.txt",
    "Common Passwords/Pwdb_top-100000.txt",
    "Common Passwords/Pwdb_top-1000000.txt",
    "Common Passwords/Pwdb_top-10000000.txt",
    "Common Passwords/darkweb2017_top-10.txt",
    "Common Passwords/darkweb2017_top-100.txt",
    "Common Passwords/darkweb2017_top-1000.txt",
    "Common Passwords/darkweb2017_top-10000.txt",
    "Common Passwords/medical-devices.txt",
    "Common Passwords/probable-v2_top-12000.txt",
    "Common Passwords/probable-v2_top-1575.txt",
    "Common Passwords/probable-v2_top-207.txt",
    "Common Passwords/xato-net-10-million-passwords-10.txt",
    "Common Passwords/xato-net-10-million-passwords-100.txt",
    "Common Passwords/xato-net-10-million-passwords-1000.txt",
    "Common Passwords/xato-net-10-million-passwords-10000.txt",
    "Common Passwords/xato-net-10-million-passwords-100000.txt",
    "Common Passwords/xato-net-10-million-passwords-1000000.txt",


};

// number of files, updates automatically
int file_count = sizeof(files) / sizeof(files[0]);


/*
==================================================================
================== Password Checker Function =====================
==================================================================
*/

// returns 1 if found, 0 if not found, -1 if file missing
int check_file(const char *path, char pass[]){

    FILE *fp = fopen(path, "r");
    char word[1024];

    if (fp == NULL){
        printf("[!] Could not open: %s\n", path);
        return -1;
    }

    while (fgets(word, sizeof(word), fp)){
        char *s = word;

        // skip UTF-8 BOM if present
        if ((unsigned char)s[0] == 0xEF && (unsigned char)s[1] == 0xBB && (unsigned char)s[2] == 0xBF)
            s += 3;

        // trim trailing newline / spaces / tabs
        int len = strlen(s);
        while (len > 0 && (s[len-1] == '\n' || s[len-1] == '\r' || s[len-1] == ' ' || s[len-1] == '\t'))
            s[--len] = '\0';

        // 1) exact whole-line match
        if (strcmp(pass, s) == 0){
            fclose(fp);
            return 1;
        }

        // 2) match any piece of the line (handles "rank,password" / "password,count")
        char copy[1024];
        strcpy(copy, s);
        char *tok = strtok(copy, ",;\t \"");
        while (tok != NULL){
            if (strcmp(pass, tok) == 0){
                fclose(fp);
                return 1;
            }
            tok = strtok(NULL, ",;\t \"");
        }
    }

    fclose(fp);
    return 0;
}


/*
==================================================================
================== Passwords Strength Checker ====================
==================================================================
*/

// declaring function for -- password strength checker
void pass_strength(char pass[]){
    upper = lower = numbers = special = spaces = 0; // resetting values to 0

    for (i = 0; i < strlen(pass); i++){
        if (isupper(pass[i])){
            upper++;
        } else if (islower(pass[i])){
            lower++;
        } else if (isdigit(pass[i])){
            numbers++;
        } else if (isspace(pass[i])){
            spaces++;
        } else {
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

    while (1){

        // resetting counter
        from_leaked_passwords = 0;

        printf("Enter Your Password(enter 0 to close): ");
        if (scanf("%99s", pass) != 1){
            return 0; // input closed
        }
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

        for (int k = 0; k < file_count; k++){
            if (check_file(files[k], pass) == 1){
                printf("Found In: \"%s\"\n", files[k]);
                from_leaked_passwords++;
            }
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