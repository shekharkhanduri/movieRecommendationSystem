#include <stdio.h>
#include <sqlite3.h>

int main() {
    sqlite3 *db;
    char *errMsg = 0;
    int rc;

    // Open or create a database file
    rc = sqlite3_open("movies.db", &db);

    if (rc) {
        printf("Cannot open database: %s\n", sqlite3_errmsg(db));
        return 1;
    } else {
        printf("Database opened successfully!\n");
    }

    // SQL statement to create a table
    char *sql = "CREATE TABLE IF NOT EXISTS Movies ("
                "ID INTEGER PRIMARY KEY AUTOINCREMENT, "
                "Title TEXT NOT NULL, "
                "Genre TEXT NOT NULL, "
                "Rating REAL);";

    rc = sqlite3_exec(db, sql, 0, 0, &errMsg);
    if (rc != SQLITE_OK) {
        printf("SQL error: %s\n", errMsg);
        sqlite3_free(errMsg);
    } else {
        printf("Table created successfully!\n");
    }

    // Insert sample data
    sql = "INSERT INTO Movies (Title, Genre, Rating) VALUES "
          "('Inception', 'Sci-Fi', 8.8), "
          "('Interstellar', 'Sci-Fi', 8.6), "
          "('The Dark Knight', 'Action', 9.0);";

    rc = sqlite3_exec(db, sql, 0, 0, &errMsg);
    if (rc != SQLITE_OK) {
        printf("SQL error: %s\n", errMsg);
        sqlite3_free(errMsg);
    } else {
        printf("Data inserted successfully!\n");
    }

    // Close the database
    sqlite3_close(db);
    return 0;
}
