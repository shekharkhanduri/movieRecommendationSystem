#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> // For sleep

#define RESET   "\033[0m"
#define GREEN   "\033[32m"
#define CYAN    "\033[36m"
#define YELLOW  "\033[33m"
#define RED     "\033[31m"
#define BOLD    "\033[1m"

#define SLEEP(ms) usleep((ms) * 1000)

void clearScreen() {
    system("clear");
}

void printHeader(const char *title) {
    printf(GREEN "============================================================\n" RESET);
    printf(BOLD CYAN "                   %s                   \n" RESET, title);
    printf(GREEN "============================================================\n" RESET);
}

void mainMenu() {
    clearScreen();
    printHeader("🎬 WELCOME TO VOID COLLECTION");

    printf(BOLD YELLOW "\n📌 Choose an option:\n" RESET);
    printf(CYAN "  [1] 🔍 Search The Movie\n");
    printf("  [2] 📚 My Library\n");
    printf("  [3] 🚪 Exit\n");
    printf("------------------------------------------------------------\n");
    printf("  👉 Enter your choice: " RESET);
}

void searchMenu() {
    clearScreen();
    printHeader("🔎 SEARCH MOVIES");

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
    printHeader("📚 MY LIBRARY");

    printf(BOLD YELLOW "\n🔐 Library Options:\n" RESET);
    printf(CYAN "  [1] 🔑 Login\n");
    printf("  [2] 📝 Register\n");
    printf("  [3] 🔙 Back to Main Menu\n");
    printf("------------------------------------------------------------\n");
    printf("  👉 Enter your choice: " RESET);
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

void waitForEnter() {
    printf("\nPress Enter to continue...");
    while (getchar() != '\n'); // Clear input buffer
    getchar();
}

int main() {
    int choice;

    while (1) {
        mainMenu();
        if (scanf("%d", &choice) != 1) {
            while (getchar() != '\n'); // Clear invalid input
            continue;
        }

        switch (choice) {
            case 1: {
                int search;
                while (1) {
                    searchMenu();
                    if (scanf("%d", &search) != 1) {
                        while (getchar() != '\n'); // Clear invalid input
                        continue;
                    }

                    switch (search) {
                        case 1: showLoading("🔍 Searching by Genre"); break;
                        case 2: showLoading("🔍 Searching by Name"); break;
                        case 3: showLoading("🔍 Searching by Year"); break;
                        case 4: showLoading("🔍 Searching by Mood"); break;
                        case 5: showLoading("🔍 Searching by ID"); break;
                        case 6: goto mainMenuLabel;
                        default: printf(RED "❌ Invalid option! Try again.\n" RESET);
                    }
                    waitForEnter();
                }
            }

            case 2: {
                int op;
                while (1) {
                    libraryMenu();
                    if (scanf("%d", &op) != 1) {
                        while (getchar() != '\n'); // Clear invalid input
                        continue;
                    }

                    switch (op) {
                        case 1: showLoading("🔑 Logging in"); break;
                        case 2: showLoading("📝 Registering"); break;
                        case 3: goto mainMenuLabel;
                        default: printf(RED "❌ Invalid choice! Try again.\n" RESET);
                    }
                    waitForEnter();
                }
            }

            case 3:
                printf("\n🎬 Goodbye! See you again. 🚀\n");
                return 0;

            default:
                printf(RED "❌ Invalid choice! Please select 1, 2, or 3.\n" RESET);
                waitForEnter();
        }

    mainMenuLabel:;
    }
}
