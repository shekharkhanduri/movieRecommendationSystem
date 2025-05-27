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

// Define arrays for genres and moods from the movie database
const char *genres[] = {
    "Action", "Adventure", "Animation", "Anthology", "Biography", "Comedy",
    "Crime", "Drama", "Family", "Fantasy", "History", "Horror", "Music",
    "Musical", "Mystery", "Romance", "Sci-fi", "Sports", "Thriller", "War",
    "Western"
};
const int num_genres = 21;

const char *moods[] = {
    "Action-packed", "Adventurous", "Ambitious", "Audacious", "Beautiful",
    "Bittersweet", "Chaotic", "Charming", "Chilling", "Colorful", "Dark",
    "Disturbing", "Dystopian", "Edgy", "Eerie", "Emotional", "Empowering",
    "Enchanting", "Energetic", "Epic", "Exhilarating", "Family-oriented",
    "Feel-good", "Futuristic", "Grand", "Gritty", "Gripping", "Heartwarming",
    "Heroic", "Hopeful", "Humorous", "Iconic", "Imaginative", "Innovative",
    "Inspiring", "Intense", "Intriguing", "Irreverent", "Laid-back", "Lavish",
    "Lighthearted", "Mind-bending", "Moody", "Motivational", "Mysterious",
    "Non-linear", "Nostalgic", "Patriotic", "Poignant", "Provocative", "Quirky",
    "Reflective", "Relatable", "Romantic", "Satirical", "Socially-conscious",
    "Somber", "Stylish", "Surreal", "Suspenseful", "Tense", "Terrifying",
    "Thought-provoking", "Timeless", "Tragic", "Triumphant", "Uplifting",
    "Visually-stunning", "Visionary", "Whimsical", "Witty"
};
const int num_moods = 68;

void clearScreen()
{
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void showLoading(const char *message) {
    printf("%s", message);
    for (int i = 0; i < 3; i++) {
        printf(".");
        fflush(stdout);
        SLEEP(400);
    }
    printf("\n\n");
}

void printDivider() {
    printf(GREEN "------------------------------------------------------------\n" RESET);
}


void printHeader(const char *title)
{
    printf(GREEN "============================================================\n" RESET);
    printf(BOLD CYAN "                   %s                   \n" RESET, title);
    printf(GREEN "============================================================\n" RESET);
}
void printListInColumns(const char *title, const char **items, int count, int col_width, int columns) {
    int rows = (count + columns - 1) / columns;
    printf(BOLD YELLOW "\n%s:\n\n" RESET, title);

    for (int r = 0; r < rows; r++) {
        for (int c = 0; c < columns; c++) {
            int idx = r + c * rows;
            if (idx < count) {
                printf(CYAN "  - %-*s" RESET, col_width, items[idx]);
            } else {
                for (int i = 0; i < col_width + 4; i++) printf(" ");
            }
        }
        printf("\n");
    }
}

void mainMenu() {
    clearScreen();
    printHeader("VOID COLLECTION 🎬");

    printf(BOLD YELLOW "\n📌 What would you like to do?\n\n" RESET);
    printf(CYAN "   [1] 🔍  Search for a Movie\n");
    printf("   [2] 📚  Access My Library\n");
    printf("   [3] 🚪  Exit the Program\n");
    printDivider();
    printf("   👉 Enter your choice: " RESET);
}


void searchMenu() {
    clearScreen();
    printHeader("MOVIE SEARCH 🔎");

    printf(BOLD YELLOW "\n📂 Search by:\n\n" RESET);
    printf(CYAN "   [1] 🎭  Genre           [2] 🎬  Name\n");
    printf("   [3] 📅  Year            [4] 😃  Mood\n");
    printf("   [5] 🔢  ID              [6] 🔙  Back to Main Menu\n");
    printDivider();
    printf("   👉 Enter your choice: " RESET);
}

void printGenres() {
    printListInColumns("Available Genres", genres, num_genres, 16, 3);
}

void printMoods() {
    printListInColumns("Available Moods", moods, num_moods, 22, 3);
}
void handleSearchMovie()
{
    int search, num;
    char column[20];
    char text[100];

    while (1) {
        searchMenu();
        scanf("%d", &search);
        getchar(); // Flush newline left by scanf

        switch (search) {
            case 1: { // Genre
                strcpy(column, "genre");
                printGenres();
                printf("\n🎭 Enter genre: ");
                scanf("%s", text);
                showLoading("\n🔍 Searching by Genre");
                search_by_column_text(column, text);
                getchar();
                break;
            }

            case 2: { // Title
                strcpy(column, "title");
                printf("\n🎬 Enter Title: ");
                fgets(text, sizeof(text), stdin);
                text[strcspn(text, "\n")] = 0; // Trim newline
                showLoading("\n🔍 Searching by Name");
                search_by_column_text(column, text);
                break;
            }

            case 3: { // Year
                strcpy(column, "year");
                printf("\n📅 Enter Year: ");
                scanf("%d", &num);
                getchar(); // Flush newline
                showLoading("\n🔍 Searching by Year");
                search_by_column_num(column, num);
                break;
            }

            case 4: { // Mood
                strcpy(column, "mood");
                printMoods();
                printf("\n😃 Enter mood: ");
                scanf("%s", text);
                showLoading("\n🔍 Searching by Mood");
                search_by_column_text(column, text);
                getchar();
                break;
            }

            case 5: { // ID
                strcpy(column, "ID");
                printf("\n🔢 Enter ID: ");
                scanf("%d", &num);
                getchar(); // Flush newline
                showLoading("\n🔍 Searching by ID");
                search_by_column_num(column, num);
                break;
            }

            case 6:
                return; // Back to main menu

            default:
                printf(RED "\n❌ Invalid option! Try again.\n" RESET);
        }

        printf("\nPress Enter to continue...");
        getchar(); // Pause
    }
}


void libraryMenu() {
    clearScreen();
    printHeader("MY PERSONAL LIBRARY 📚");

    printf(BOLD YELLOW "\n🔐 Choose a Library Option:\n\n" RESET);
    printf(CYAN "   [1] 🔑  Login to Library\n");
    printf("   [2] 📝  Register New Account\n");
    printf("   [3] 🔙  Return to Main Menu\n");
    printDivider();
    printf("   👉 Enter your choice: " RESET);
}

void manageLibrary(const char *username)
{
    int choice;
    while (1)
    {
        clearScreen();
        printHeader(BOLD YELLOW "\n📂 Your Library Options:\n" RESET);
        printf(CYAN "   [1] ➕  Add a Movie\n");
        printf("   [2] 📜  View My Library\n");
        printf("   [3] ❌  Remove a Movie\n");
        printf("   [4] 🔙  Logout\n");
        printDivider();
        printf("   👉 Enter your choice: " RESET);


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
                printf(GREEN "\n✅ Login Successful! Welcome, %s!\n" RESET, username);
                manageLibrary(username); // Now you can use the same username
            }
            else
            {
                printf(RED "\n❌ Authentication failed. Please try again.\n" RESET);
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
           clearScreen();
            printHeader("VOID COLLECTION 🎬");
            printf(GREEN "\n🎬 Thank you for using Void Collection!\n🚀 See you again soon!\n\n" RESET);
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