#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sqlite3.h"
#include "database.h"  

#define MAX 255

typedef struct {
    int id;
    char name[MAX];
    char genre[MAX];
    char mood[MAX];
    float rating;
} Movie;

void getLibraryFileName(const char *username, char *filename) {
    sprintf(filename, "data/%s_library.txt", username);
}

void close_database(sqlite3 *db) {
    if (db) {
        sqlite3_close(db); 
    }
}

int get_movie_by_id(int id, Movie *movie_details) {
    sqlite3 *db;
    sqlite3_stmt *stmt;
    char query[MAX];

    db = open_database();
    if (!db) {
        printf("Failed to connect to the database.\n");
        return 0;
    }

    snprintf(query, MAX, "SELECT title, genre, mood, rating FROM movies WHERE id = %d;", id);
    int rc = sqlite3_prepare_v2(db, query, -1, &stmt, 0);
    if (rc != SQLITE_OK) {
        printf("Failed to prepare SQL query: %s\n", sqlite3_errmsg(db));
        sqlite3_finalize(stmt);
        close_database(db);
        return 0;
    }

    rc = sqlite3_step(stmt);
    if (rc == SQLITE_ROW) {
        strncpy(movie_details->name, (const char *)sqlite3_column_text(stmt, 0), MAX);
        strncpy(movie_details->genre, (const char *)sqlite3_column_text(stmt, 1), MAX);
        strncpy(movie_details->mood, (const char *)sqlite3_column_text(stmt, 2), MAX);
        movie_details->rating = (float)sqlite3_column_double(stmt, 3);
        movie_details->id = id;

        sqlite3_finalize(stmt);
        close_database(db);
        return 1;
    } else {
        sqlite3_finalize(stmt);
        close_database(db);
        return 0; 
    }
}


void addMovieToLibrary(const char *username) {
    char filename[MAX];
    getLibraryFileName(username, filename);

    FILE *fp = fopen(filename, "a");
    if (!fp) {
        printf("Error opening file.\n");
        return;
    }

    int id;
    printf("\nEnter movie ID to add to your library: ");
    scanf("%d", &id);
    getchar(); 

    Movie movie_details;
    if (!get_movie_by_id(id, &movie_details)) {
        printf("Movie not found with ID %d.\n", id);
        fclose(fp);
        return;
    }

    fprintf(fp, "ID: %d\nName: %s\nGenre: %s\nMood: %s\nRating: %.1f\n--------------------\n", 
            movie_details.id, movie_details.name, movie_details.genre, movie_details.mood, movie_details.rating);

    fclose(fp);
    printf("Movie added successfully!\n");
}

void viewLibrary(const char *username) {
    char filename[MAX];
    getLibraryFileName(username, filename);

    FILE *fp = fopen(filename, "r");
    if (!fp) {
        printf("No library found for user %s.\n", username);
        return;
    }

    char line[MAX];
    while (fgets(line, MAX, fp)) {
        printf("%s", line);
    }

    fclose(fp);
}

void deleteMovieFromLibrary(const char *username) {
    char filename[MAX];
    getLibraryFileName(username, filename);

    FILE *fp = fopen(filename, "r");
    if (!fp) {
        printf("No library found for user %s.\n", username);
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
    getchar();

    char line[MAX];
    int movieFound = 0;
    int skipEntry = 0;

    while (fgets(line, MAX, fp)) {
        if (strncmp(line, "ID:", 3) == 0) {
            int currentId;
            sscanf(line + 3, "%d", &currentId); 

            if (currentId == idToRemove) {
                skipEntry = 1; 
                movieFound = 1;
                continue;
            } else {
                skipEntry = 0; 
            }
        }

        if (!skipEntry) {
            fputs(line, tempFile); 
        }
    }

    fclose(fp);
    fclose(tempFile);

    if (movieFound) {
        remove(filename);
        rename("temp.txt", filename);
        printf("Movie with ID %d removed successfully!\n", idToRemove);
    } else {
        printf("Movie with ID %d not found.\n", idToRemove);
        remove("temp.txt");
    }
}