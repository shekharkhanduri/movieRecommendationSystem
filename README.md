# Console-Based Movie Suggester

## About This Project
The Console-Based Movie Suggester is a command-line application that allows users to search for movies based on genres and view details such as ratings, summaries, and durations. The application also provides a personal movie library feature where users can store and manage their favorite movies.

## Features
- **Movie Search:** Users can search for movies based on predefined column names.
- **Movie Details:** Provides information like rating, summary, and duration.
- **Personal Movie Library:** Users can create and manage their own movie library using file handling.
- **Library Count:** Displays the number of movies currently in the user's personal library.
- **User Authentication:** Allows new users to register and existing users to log in using a username and password.
- **CRUD Operations:** Supports Create, Read, Update, and Delete operations on personal movie libraries.
- **Database Management:** The movie database (`movies.db`) is updated manually by replacing the existing database file.
- **SQLite Integration:** The project includes SQLite support for storing and managing movie data efficiently.

---

## Development Progress

### Latest Updates
- **[Date]** - Implemented `authentication.c`
  - Added support for user registration with username and password.
  - Allows registered users to log in and access their personal libraries.

- **[Date]** - Implemented `library.c`
  - Enables creation of personal movie libraries for users.
  - Supports full CRUD operations.
  - Displays the number of movies in the user's library.

- **[Date]** - Integrated SQLite3 for movie database management.
  - Included `sqlite3.c` and `sqlite3.h` for handling database operations.
  - Developed an Excel sheet to collect movie data, converted it to `.csv`, and then into `movies.db` using SQLite operations.
  - Added `movies.db` to the repository.

- **[Date]** - Developed a basic CLI in `main.c` for user interaction.
  - Users can navigate and perform various tasks.

- **[Date]** - Updated `MakeFile` to include SQLite-related dependencies.
  - Ensured compatibility with the new movie database structure.

---

## Next Steps
- Create `database.c` to retrieve data from `movies.db` based on user search (by genre, ID, name, mood, etc.).
- Implement movie recommendations based on user preferences.
- Improve the user interface for better readability.
- Enhance error handling and data validation.
- Add a feature to export the personal movie library to a text file.
- Optimize SQL queries for better performance.

_(This section will be continuously updated as development progresses.)_

