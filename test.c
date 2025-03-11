#include <stdio.h>
#include <sqlite3.h>

// Callback function to process each row of the result
static int callback(void *data, int argc, char **argv, char **azColName) {
    // Print table row with ASCII art borders
    printf("| %-3s | %-5s | %-3s |\n", argv[0], argv[1], argv[2]);
    return 0;
}

int main() {
    sqlite3 *db;
    char *err_msg = 0;

    // Open or create a database
    int rc = sqlite3_open("test.db", &db);

    if (rc != SQLITE_OK) {
        fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return 1;
    } else {
        printf("Database opened successfully\n");
    }

    // Create a table
    const char *sql = "CREATE TABLE IF NOT EXISTS Users ("
                      "ID INTEGER PRIMARY KEY AUTOINCREMENT, "
                      "Name TEXT NOT NULL, "
                      "Age INTEGER NOT NULL);";

    rc = sqlite3_exec(db, sql, 0, 0, &err_msg);

    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", err_msg);
        sqlite3_free(err_msg);
    } else {
        fprintf(stdout, "Table created successfully\n");
    }

    // Insert data
    sql = "INSERT INTO Users (Name, Age) VALUES ('Alice', 25);"
          "INSERT INTO Users (Name, Age) VALUES ('Bob', 30);";

    rc = sqlite3_exec(db, sql, 0, 0, &err_msg);

    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", err_msg);
        sqlite3_free(err_msg);
    } else {
        fprintf(stdout, "Data inserted successfully\n");
    }

    // Query and display the table with ASCII art
    printf("\n+----+-------+-----+");
    printf("\n| ID | Name  | Age |");
    printf("\n+----+-------+-----+");

    sql = "SELECT * FROM Users;";
    rc = sqlite3_exec(db, sql, callback, 0, &err_msg);

    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", err_msg);
        sqlite3_free(err_msg);
    } else {
        printf("\n+----+-------+-----+\n");
    }

    // Close the database
    sqlite3_close(db);

    return 0;
}