#ifndef DATABASE_H
#define DATABASE_H
#include "sqlite3.h" 
void search_by_column_text(const char *column, const char *value);
void search_by_column_num(const char *column, const int value);
sqlite3* open_database();

#endif
