#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h> 

#define MAX_LEN 50

int isUsernameTaken(const char *username) {
    FILE *file = fopen("data/records.txt", "rb");
    if (!file) return 0;  

    char fileUser[MAX_LEN], filePass[MAX_LEN];
    while (fscanf(file, "%s %s", fileUser, filePass) != EOF) {
        if (strcmp(username, fileUser) == 0) {
            fclose(file);
            return 1;
        }
    }

    fclose(file);
    return 0;
}

int isWeakPassword(const char *password) {
    int hasUpper = 0, hasLower = 0, hasDigit = 0, hasSpecial = 0;
    size_t len = strlen(password);
    if (len < 8) return 1; 

    for (size_t i = 0; i < len; i++) {
        if (isupper(password[i])) hasUpper = 1;
        else if (islower(password[i])) hasLower = 1;
        else if (isdigit(password[i])) hasDigit = 1;
        else if (ispunct(password[i])) hasSpecial = 1;
    }

    return !(hasUpper && hasLower && hasDigit && hasSpecial);
}


void userinfo(char *user, char *pass) {
    int ch;
    while ((ch = getchar()) != '\n' && ch != EOF);  

    printf("\nEnter username: ");
    fgets(user, MAX_LEN, stdin);
    printf("\nEnter password: ");
    fgets(pass, MAX_LEN, stdin);

    user[strcspn(user, "\n")] = '\0';  
    pass[strcspn(pass, "\n")] = '\0';
}

void registerUser(char *registeredUser) {
    char user[MAX_LEN], pass[MAX_LEN];

    while (1) {
        userinfo(user, pass);

        if (isUsernameTaken(user)) {
            printf("\n❌ Username '%s' is already taken. Try another.", user);
            continue;
        }

        if (isWeakPassword(pass)) {
            printf("\n❌ Weak password. Must contain:\n");
            printf("   - Minimum 8 characters\n");
            printf("   - At least one uppercase, one lowercase, one digit, one special character");
            continue;
        }

        break; 
    }

    FILE *file = fopen("data/records.txt", "ab");
    if (!file) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }

    fprintf(file, "%s %s\n", user, pass);
    fclose(file);

    strcpy(registeredUser, user);
    printf("✅ User '%s' registered successfully.\n", user);
}



int authenticateUser(char *authenticatedUser) {
    char inputUser[MAX_LEN], inputPass[MAX_LEN];
    userinfo(inputUser, inputPass);

    FILE *file = fopen("data/records.txt", "rb");
    if (!file) {
        printf("No user records found. Register first.\n");
        return 0;
    }

    char fileUser[MAX_LEN], filePass[MAX_LEN];
    while (fscanf(file, "%s %s", fileUser, filePass) != EOF) {
        if (strcmp(inputUser, fileUser) == 0 && strcmp(inputPass, filePass) == 0) {
            fclose(file);
            strcpy(authenticatedUser, inputUser);  // ✅ Send username back to main
            return 1;
        }
    }

    fclose(file);
    printf("Invalid username or password.\n");
    return 0;
}
