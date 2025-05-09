#include <stdio.h>
#include <stdlib.h>
#include "sqlite3.h"
#include <string.h>

#define DB_NAME "data/mydatabase.db"

// Callback function for displaying search results
int display_callback(void *flag, int argc, char **argv, char **col_name) {
    int *found = (int *)flag;
    *found = 1; // Mark result as found

    printf("\n=============================\n");
    for (int i = 0; i < argc; i++) {
        printf("\n[%s]: %s\n", col_name[i], argv[i] ? argv[i] : "NULL");
    }
    return 0;
}


// Open database connection
sqlite3* open_database() {
    sqlite3 *db;
    int rc = sqlite3_open(DB_NAME, &db);

    if (rc) {
        fprintf(stderr, "❌ Cannot open database: %s\n", sqlite3_errmsg(db));
        return NULL;
    }
    return db;
}

// Search by numeric column
void search_by_column_num(const char *column, const char value) {
    sqlite3 *db = open_database();
    if (!db) return;

    char query[512];
    snprintf(query, sizeof(query),
             "SELECT * FROM movies WHERE %s = %d;", column, value);

    int result_found = 0;
    char *err_msg = NULL;

    // ✅ Use the new callback that updates result_found
    int rc = sqlite3_exec(db, query, display_callback, &result_found, &err_msg);

    if (rc != SQLITE_OK) {
        fprintf(stderr, "❌ SQL error: %s\n", err_msg);
        sqlite3_free(err_msg);
    } else if (!result_found) {
        printf("\n⚠️  No matches found for '%d' in '%s'.\n", value, column);
    }

    sqlite3_close(db);
}

// General search by column
void search_by_column_text(const char *column, const char *value) {
    sqlite3 *db = open_database();
    if (!db) return;

    char query[512];
    snprintf(query, sizeof(query),
             "SELECT * FROM movies WHERE %s LIKE '%%%s%%';", column, value);

    int result_found = 0;
    char *err_msg = NULL;

    // ✅ Use the new callback that updates result_found
    int rc = sqlite3_exec(db, query, display_callback, &result_found, &err_msg);

    if (rc != SQLITE_OK) {
        fprintf(stderr, "❌ SQL error: %s\n", err_msg);
        sqlite3_free(err_msg);
    } else if (!result_found) {
        printf("\n⚠️  No matches found for '%s' in '%s'.\n", value, column);
    }

    sqlite3_close(db);
}
