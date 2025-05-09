#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LEN 50

void userinfo(char *user, char *pass) {
    int ch;
    while ((ch = getchar()) != '\n' && ch != EOF);  // flush buffer

    printf("Enter username: ");
    fgets(user, MAX_LEN, stdin);
    printf("Enter password: ");
    fgets(pass, MAX_LEN, stdin);

    user[strcspn(user, "\n")] = '\0';  
    pass[strcspn(pass, "\n")] = '\0';
}


void registerUser(char *registeredUser) {
    char user[MAX_LEN], pass[MAX_LEN];
    userinfo(user, pass);

    FILE *file = fopen("data/records.txt", "ab");
    if (!file) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }

    fprintf(file, "%s %s\n", user, pass);
    fclose(file);

    // Copy back the username to return it to the caller
    strcpy(registeredUser, user);
}


// ✨ Modified to return username via parameter
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
