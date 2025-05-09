#ifndef LIBRARY_H
#define LIBRARY_H

#include <stdio.h>

// Function declarations

// Personal Library Management
void addMovieToLibrary(const char* username);
void viewLibrary(const char* username);
void updateMovieInLibrary(const char* username);
void deleteMovieFromLibrary(const char* username);

// Search and Analysis
void viewMoviesByCriteria(const char* username); // e.g., by genre or mood
void countUserLibraries();                       // total number of user libraries
void countUserLibraryOccurrences();              // counts how many libraries exist and their frequency

#endif // LIBRARY_H
