# YouTube Data Management System

## Overview
This project is designed to manage YouTube data, including users, videos, and other related information. It allows extracting data from text files and managing it through various operations. The project is implemented in C++ and makes use of object-oriented programming concepts. The build process is automated using a `Makefile`, which simplifies compilation and cleanup tasks.

## Features
- **User Management:** Extract user data from a text file and process it within the program.
- **Video Management:** Manage video-related data, including statistics like views, ratings, etc.
- **Data Extraction:** The program reads from text files (e.g., `fake_youtube_data_updated.txt` and `users.txt`) to load user and video information into the system.
- **Makefile:** The project can be easily compiled and cleaned using `make` commands.

## File Structure
- **main.cpp:** The main entry point for the program.
- **Creator.cpp / Creator.h:** These files handle YouTube content creators and their data.
- **DataManager.cpp:** Manages the extraction and organization of data from the text files.
- **Person.cpp / User.cpp:** Manages user-related functionality, such as account management.
- **Video.cpp:** Manages the videos uploaded by creators, including statistics and other metadata.
- **fake_youtube_data_updated.txt:** A text file that contains fake YouTube data, such as user IDs and video information.
- **users.txt:** A file containing user information such as user IDs, names, and related statistics.

## How to Use

### Compilation
The project uses a `Makefile` to simplify the build process. To compile the project, run:

```bash
make
```
This command will generate the executable file using the object files for the different source files.

## Cleaning the Project
To remove the generated object files and executable, you can use the make clean command:
```bash
make clean
```
## YouTube Data Extraction
The program reads data from fake_youtube_data_updated.txt and users.txt. These files store user information, statistics, and video-related data.

## Future Enhancements
Implement additional functionality for more advanced user and video management.
Improve data handling by adding a database or persistent storage mechanism.
Add a graphical user interface (GUI) for easier interaction with the YouTube data.
