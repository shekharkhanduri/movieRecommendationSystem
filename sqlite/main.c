#include <stdio.h>
#include <stdlib.h>
#include "library.h"
#include "authentication.h"
#ifdef _WIN32
    #include <windows.h>
    #define SLEEP(ms) Sleep(ms)
#else
    #include <unistd.h>
    #define SLEEP(ms) usleep((ms) * 1000)
#endif

#define RESET   "\033[0m"
#define GREEN   "\033[32m"
#define CYAN    "\033[36m"
#define YELLOW  "\033[33m"
#define RED     "\033[31m"
#define BOLD    "\033[1m"

void clearScreen() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

void maximizeWindow() {
    #ifdef _WIN32
        system("mode con: cols=120 lines=30");  // Expands terminal width
        HWND console = GetConsoleWindow();
        ShowWindow(console, SW_MAXIMIZE);  // Maximizes terminal
    #endif
}
void showLoading(const char *message) {
    printf("%s", message);
    for (int i = 0; i < 3; i++) {
        printf(".");
        fflush(stdout);
        SLEEP(500);
    }
    printf("\n");
}

void printHeader(const char *title) {
    printf(GREEN "============================================================\n" RESET);
    printf(BOLD CYAN "                   %s                   \n" RESET, title);
    printf(GREEN "============================================================\n" RESET);
}

void mainMenu() {
    clearScreen();
    printHeader("WELCOME TO VOID COLLECTION 🎬");

    printf(BOLD YELLOW "\n📌 Choose an option:\n" RESET);
    printf(CYAN "  [1] 🔍 Search The Movie\n");
    printf("  [2] 📚 My Library\n");
    printf("  [3] 🚪 Exit\n");
    printf("------------------------------------------------------------\n");
    printf("  👉 Enter your choice: " RESET);
}

void searchMenu() {
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

void libraryMenu() {
    clearScreen();
    printHeader("MY LIBRARY 📚");

    printf(BOLD YELLOW "\n🔐 Library Options:\n" RESET);
    printf(CYAN "  [1] 🔑 Login\n");
    printf("  [2] 📝 Register\n");
    printf("  [3] 🔙 Back to Main Menu\n");
    printf("------------------------------------------------------------\n");
    printf("  👉 Enter your choice: " RESET);
}
void manageLibrary(const char *username) {
    int choice;
    while (1) {
        clearScreen();
        printHeader("LIBRARY MANAGEMENT 📂");

        printf(BOLD YELLOW "\n📌 Choose an option:\n" RESET);
        printf(CYAN "  [1] ➕ Add Movie to Library\n");
        printf("  [2] 📜 View My Library\n");
        printf("  [3] 🎭 Search Movies by Genre or Mood\n");
        printf("  [4] 📊 View Number of User Libraries\n");
        printf("  [5] ✏️ Update Movie in Library\n");
        printf("  [6] ❌ Remove Movie from Library\n");
        printf("  [7] 🔢 Count Libraries & Their Occurrences\n");
        printf("  [8] 🚪 Exit\n");
        printf("------------------------------------------------------------\n");
        printf("  👉 Enter your choice: " RESET);
        

        scanf("%d", &choice);
        getchar(); // Clear buffer

        switch (choice) {
            case 1:
                addMovieToLibrary(username);
                break;
            case 2:
                viewLibrary(username);
                break;
            case 3:
                viewMoviesByCriteria(username);
                break;
            case 4:
                countUserLibraries();
                break;
            case 5:
                updateMovieInLibrary(username);
                break;
            case 6:
                deleteMovieFromLibrary(username);
                break;
            case 7:
                countUserLibraryOccurrences();
                break;
            case 8:
                printf(GREEN "👋 Goodbye, %s!\n" RESET, username);
                exit(0);
            default:
                printf(RED "❌ Invalid choice! Try again.\n" RESET);
        }
        printf("\nPress Enter to continue...");
        getchar();
    }
}


void handleLibrary() {
    while (1) {
        libraryMenu();
        int op;
        scanf("%d", &op);

        switch (op) {
            char username[50];
            case 1: {
                showLoading("🔑 Logging in");

                int authStatus = authenticateUser(username);  // Pass username buffer

                if (authStatus) {
                    printf("\n✅ Login Successful! Welcome, %s!\n", username);
                    manageLibrary(username);  // Now you can use the same username
                } else {
                    printf("❌ Authentication failed. Returning to Library Menu.\n");
                }
                break;
            }
            case 2:
                showLoading("📝 Registering");
                while (getchar() != '\n');
                registerUser(username);
                manageLibrary(username);
                break;
            case 3:
                return; // Exit library menu
            default:
                printf(RED "❌ Invalid choice! Try again.\n" RESET);
        }
    }
}
int main() {
    int choice;
    SetConsoleOutputCP(65001);
    maximizeWindow();  // Maximize terminal on launch

    while (1) {
        mainMenu();
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                while (1) {
                    searchMenu();
                    int search;
                    scanf("%d", &search);
                    
                    switch (search) {
                        case 1: showLoading("🔍 Searching by Genre"); break;
                        case 2: showLoading("🔍 Searching by Name"); break;
                        case 3: showLoading("🔍 Searching by Year"); break;
                        case 4: showLoading("🔍 Searching by Mood"); break;
                        case 5: showLoading("🔍 Searching by ID"); break;
                        case 6: goto mainMenuLabel;
                        default: printf(RED "❌ Invalid option! Try again.\n" RESET);
                    }
                    printf("\nPress Enter to continue...");
                    getchar(); getchar();
                }
            case 2:
                handleLibrary();
                break;
            case 3:
                printf("\n🎬 Goodbye! See you again. 🚀\n");
                return 0;
            default:
                printf(RED "❌ Invalid choice! Please select 1, 2, or 3.\n" RESET);
                printf("\nPress Enter to try again...");
                getchar(); getchar();
        }

    mainMenuLabel:; 
    }
    return 0;
}
