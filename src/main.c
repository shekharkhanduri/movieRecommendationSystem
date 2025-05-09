#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "library.h"
#include "authentication.h"
#include "database.h"
#ifdef _WIN32
#include <windows.h>
#define SLEEP(ms) Sleep(ms)
#else
#include <unistd.h>
#define SLEEP(ms) usleep((ms) * 1000)
#endif

#define RESET "\033[0m"
#define GREEN "\033[32m"
#define CYAN "\033[36m"
#define YELLOW "\033[33m"
#define RED "\033[31m"
#define BOLD "\033[1m"

void clearScreen()
{
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void showLoading(const char *message)
{
    printf("%s", message);
    for (int i = 0; i < 3; i++)
    {
        printf(".");
        fflush(stdout);
        SLEEP(500);
    }
    printf("\n");
}

void printHeader(const char *title)
{
    printf(GREEN "============================================================\n" RESET);
    printf(BOLD CYAN "                   %s                   \n" RESET, title);
    printf(GREEN "============================================================\n" RESET);
}

void mainMenu()
{
    clearScreen();
    printHeader("WELCOME TO VOID COLLECTION 🎬");

    printf(BOLD YELLOW "\n📌 Choose an option:\n" RESET);
    printf(CYAN "  [1] 🔍 Search The Movie\n");
    printf("  [2] 📚 My Library\n");
    printf("  [3] 🚪 Exit\n");
    printf("------------------------------------------------------------\n");
    printf("  👉 Enter your choice: " RESET);
}

void searchMenu()
{
    clearScreen();
    printHeader("SEARCH MOVIES 🔎");

    printf(BOLD YELLOW "\n📝 Search by:\n" RESET);
    printf(CYAN "  [1] 🎭 Genre\n");
    printf("  [2] 🎬 Name\n");
    printf("  [3] 📅 Year\n");
    printf("  [4] 😃 Mood\n");
    printf("  [5] 🔢 ID\n");
    printf("  [6] 🔙 Back to Main Menu\n");
    printf("------------------------------------------------------------\n");
    printf("  👉 Enter your choice: " RESET);
}

void handleSearchMovie()
{
    int search, num;
    char column[20];
    char text[100];

    while (1)
    {
        searchMenu();
        scanf("%d", &search);
        getchar(); // To consume newline

        switch (search)
        {
        case 1:
            strcpy(column, "genre");
            printf("\n 🎭 Enter genre: ");
            scanf("%s", text);
            showLoading("\n🔍 Searching by Genre");
            search_by_column_text(column, text);
            break;
        case 2:
            strcpy(column, "title");
            printf("Enter Title: ");
            scanf("%s", text);
            showLoading("🔍 Searching by Name");
            search_by_column_text(column, text);
            break;
        case 3:
            strcpy(column, "year");
            printf("Enter Year: ");
            scanf("%d", &num);
            showLoading("🔍 Searching by Year");
            search_by_column_num(column, num);
            break;
        case 4:
            strcpy(column, "mood");
            printf("Enter mood: ");
            scanf("%s", text);
            showLoading("🔍 Searching by Mood");
            search_by_column_text(column, text);
            break;
        case 5:
            strcpy(column, "ID");
            printf("Enter ID: ");
            scanf("%d", &num);
            showLoading("🔍 Searching by ID");
            search_by_column_num(column, num);
            break;
        case 6:
            return; // Return to main menu
        default:
            printf(RED "❌ Invalid option! Try again.\n" RESET);
        }

        getchar(); // consume leftover newline
        printf("\nPress Enter to continue...");
        getchar();
    }
}


void libraryMenu()
{
    clearScreen();
    printHeader("MY LIBRARY 📚");

    printf(BOLD YELLOW "\n🔐 Library Options:\n" RESET);
    printf(CYAN "  [1] 🔑 Login\n");
    printf("  [2] 📝 Register\n");
    printf("  [3] 🔙 Back to Main Menu\n");
    printf("------------------------------------------------------------\n");
    printf("  👉 Enter your choice: " RESET);
}
void manageLibrary(const char *username)
{
    int choice;
    while (1)
    {
        clearScreen();
        printHeader("LIBRARY MANAGEMENT 📂");

        printf(BOLD YELLOW "\n📌 Choose an option:\n" RESET);
        printf(CYAN "  [1] ➕ Add Movie to Library\n");
        printf("  [2] 📜 View My Library\n");
        printf("  [3] ❌ Remove Movie from Library\n");
        printf("  [4] 🚪 Exit\n");
        printf("------------------------------------------------------------\n");
        printf("  👉 Enter your choice: " RESET);

        scanf("%d", &choice);
        getchar(); // Clear buffer

        switch (choice)
        {
        case 1:
            addMovieToLibrary(username);
            break;
        case 2:
            clearScreen();
            printHeader("Your Movie Library:");
            viewLibrary(username);
            break;
        case 3:
            deleteMovieFromLibrary(username);
            break;
        case 4:
            printf(GREEN "👋 Goodbye, %s!\n" RESET, username);
            return;
        default:
            printf(RED "❌ Invalid choice! Try again.\n" RESET);
        }
        printf("\nPress Enter to continue...");
        getchar();
    }
}

void handleLibrary()
{
    while (1)
    {
        libraryMenu();
        int op;
        scanf("%d", &op);

        switch (op)
        {
            char username[50];
        case 1:
        {
            int authStatus = authenticateUser(username); // Pass username buffer
            showLoading("🔑 Logging in");
            if (authStatus)
            {
                printf("\n✅ Login Successful! Welcome, %s!\n", username);
                manageLibrary(username); // Now you can use the same username
            }
            else
            {
                printf("❌ Authentication failed. Returning to Library Menu.\n");
            }
            break;
        }
        case 2:
            registerUser(username);
            showLoading("📝 Registering");
            manageLibrary(username);
            break;
        case 3:
            return; // Exit library menu
        default:
            printf(RED "❌ Invalid choice! Try again.\n" RESET);
        }
    }
}
int main()
{
    int choice;
    SetConsoleOutputCP(65001);

    while (1)
    {
        mainMenu();
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            handleSearchMovie();
            break;
        case 2:
            handleLibrary();
            break;
        case 3:
            printf("\n🎬 Goodbye! See you again. 🚀\n");
            return 0;
        default:
            printf(RED "❌ Invalid choice! Please select 1, 2, or 3.\n" RESET);
            printf("\nPress Enter to try again...");
            getchar();
            getchar();
        }
    }
    return 0;
}
