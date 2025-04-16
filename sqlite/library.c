// i have taken AI help
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <stdbool.h>

#define MAX 100

// Genrates file name for the users libary
void getLibraryFileName(const char *username, char *filename) {
    sprintf(filename, "%s_library.txt", username);
}

// Return a unique movie ID for each movie added
int getMovieID() {
    static int id = 1; // Static to keep track of last ID
    return id++; // Return current id and increament for next movie
}

// Gets movie name from the user
void getMovieName(char *name) {
    printf("Enter Movie Name: ");
    fgets(name, MAX, stdin);
    name[strcspn(name, "\n")] = '\0'; // Remov newline character
}

// Gets genre of movie from user
void getMovieGenre(char *genre) {
    printf("Enter Movie Genre: ");
    fgets(genre, MAX, stdin);
    genre[strcspn(genre, "\n")] = '\0'; // Remov newline character
}

// Gets movie mood from the user
void getMovieMood(char *mood) {
    printf("Enter Movie Mood: ");
    fgets(mood, MAX, stdin);
    mood[strcspn(mood, "\n")] = '\0'; // Remov newline character
}

// Gets the rating of the movie from user
float getMovieRating() {
    float rating;
    printf("Enter Movie Rating (0.0 to 10.0): ");
    scanf("%f", &rating);
    getchar(); // Clear leftover newline character
    return rating;
}

// Adds a movie to the users movie libary
void addMovieToLibrary(const char *username) {
    char filename[MAX];
    getLibraryFileName(username, filename);
    
    FILE *fp = fopen(filename, "a");
    if (!fp) {
        printf("Error opening file.\n");
        return;
    }

    int id = getMovieID();
    char name[MAX], genre[MAX], mood[MAX];
    float rating;

    getMovieName(name);
    getMovieGenre(genre);
    getMovieMood(mood);
    rating = getMovieRating();

    fprintf(fp, "ID: %d\nName: %s\nGenre: %s\nMood: %s\nRating: %.1f\n--------------------\n", 
            id, name, genre, mood, rating);
    fclose(fp);

    printf("Movie added succesfully!\n");
}

// Views movies from library based on genre or mood
void viewMoviesByCriteria(const char *username) {
    char filename[MAX];
    getLibraryFileName(username, filename);

    FILE *fp = fopen(filename, "r");
    if (!fp) {
        printf("No libary found for user %s.\n", username);
        return;
    }

    int choice;
    char searchTerm[MAX];
    printf("\nSearch movies by:\n");
    printf("1. Genre\n");
    printf("2. Mood\n");
    printf("Enter your choce: ");
    scanf("%d", &choice);
    getchar();  // Clear the newline character after choice input

    if (choice == 1) {
        printf("Enter Genre to search: ");
        fgets(searchTerm, MAX, stdin);
        searchTerm[strcspn(searchTerm, "\n")] = '\0'; // Remov newline character
    } else if (choice == 2) {
        printf("Enter Mood to search: ");
        fgets(searchTerm, MAX, stdin);
        searchTerm[strcspn(searchTerm, "\n")] = '\0'; // Remov newline character
    } else {
        printf("Invalid choice!\n");
        fclose(fp);
        return;
    }

    char line[MAX];
    int matchFound = 0;
    while (fgets(line, MAX, fp)) {
        if ((choice == 1 && strstr(line, searchTerm)) || (choice == 2 && strstr(line, searchTerm))) {
            matchFound = 1;
            printf("%s", line); // Print matchng line
        }
    }

    if (!matchFound) {
        printf("No movies found matching your search.\n");
    }

    fclose(fp);
}

// View whole library of user
void viewLibrary(const char *username) {
    char filename[MAX];
    getLibraryFileName(username, filename);

    FILE *fp = fopen(filename, "r");
    if (!fp) {
        printf("No libary found for user %s.\n", username);
        return;
    }

    char ch;
    while ((ch = fgetc(fp)) != EOF) {
        putchar(ch);
    }
    fclose(fp);
}

// Count number of users' libaries
void countUserLibraries() {
    struct dirent *entry;
    DIR *dp = opendir(".");
    if (dp == NULL) {
        printf("Unable to open current directory.\n");
        return;
    }

    int count = 0;
    while ((entry = readdir(dp)) != NULL) {
        if (strstr(entry->d_name, "_library.txt")) {
            count++;
        }
    }

    closedir(dp);
    printf("There are %d user libraries.\n", count);
}

// Count number of movies for each user in thier library
void countUserLibraryOccurrences() {
    struct dirent *entry;
    DIR *dp = opendir(".");
    if (dp == NULL) {
        printf("Unable to open current directory.\n");
        return;
    }

    char username[MAX];
    int count;
    printf("Username\tCount\n");

    while ((entry = readdir(dp)) != NULL) {
        if (strstr(entry->d_name, "_library.txt")) {
            // Extract username from the filename
            sscanf(entry->d_name, "%99[^_]", username);

            FILE *fp = fopen(entry->d_name, "r");
            if (!fp) continue;

            // Count occurrences of this username in the file
            count = 0;
            char line[MAX];
            while (fgets(line, sizeof(line), fp)) {
                if (strstr(line, "Name:")) {
                    count++;
                }
            }

            fclose(fp);

            // Print username and movie count
            printf("%s\t\t%d\n", username, count);
        }
    }

    closedir(dp);
}

// Updates movie in library for a user
void updateMovieInLibrary(const char *username) {
    char filename[MAX];
    getLibraryFileName(username, filename);

    FILE *fp = fopen(filename, "r+");
    if (!fp) {
        printf("No libary found for user %s.\n", username);
        return;
    }

    int idToUpdate;
    printf("Enter the ID of the movie you want to update: ");
    scanf("%d", &idToUpdate);
    getchar(); // Clear newline character from the input buffer

    char line[MAX];
    int movieFound = 0;
    long position;
    while ((position = ftell(fp)) != -1 && fgets(line, MAX, fp)) {
        if (strstr(line, "ID:") && atoi(line + 4) == idToUpdate) {
            movieFound = 1;
            break;
        }
    }

    if (!movieFound) {
        printf("Movie with ID %d not found.\n", idToUpdate);
        fclose(fp);
        return;
    }

    printf("Updating movie details for ID %d...\n", idToUpdate);
    char name[MAX], genre[MAX], mood[MAX];
    float rating;
    
    getMovieName(name);
    getMovieGenre(genre);
    getMovieMood(mood);
    rating = getMovieRating();

    // Now we write back the updated data
    fseek(fp, position, SEEK_SET);  // Move to correct position of the movie
    fprintf(fp, "ID: %d\nName: %s\nGenre: %s\nMood: %s\nRating: %.1f\n--------------------\n",
            idToUpdate, name, genre, mood, rating);
    
    fclose(fp);
    printf("Movie updated succesfully!\n");
}

// Removes movie from user library
void deleteMovieFromLibrary(const char *username) {
    char filename[MAX];
    getLibraryFileName(username, filename);

    FILE *fp = fopen(filename, "r");
    if (!fp) {
        printf("No libary found for user %s.\n", username);
        return;
    }

    FILE *tempFile = fopen("temp.txt", "w");
    if (!tempFile) {
        printf("Error opening temporary file.\n");
        fclose(fp);
        return;
    }

    int idToRemove;
    printf("Enter the ID of the movie you want to remove: ");
    scanf("%d", &idToRemove);
    getchar();    // Clear newline character from the input buffer

    char line[MAX];
    int movieFound = 0;
    while (fgets(line, MAX, fp)) {
        if (strstr(line, "ID:") && atoi(line + 4) == idToRemove) {
            movieFound = 1;
            continue;         // Skip this movie from the temp file
        }
        fputs(line, tempFile);        // Write rest to temp file
    }

    fclose(fp);
    fclose(tempFile);

    if (movieFound) {
        remove(filename);       // Delete original file
        rename("temp.txt", filename);      // Rename temp file to original file
        printf("Movie with ID %d removed succesfully!\n", idToRemove);
    } else {
        printf("Movie with ID %d not found.\n", idToRemove);
        remove("temp.txt");    // Delete temp file if no movie removed
    }
}