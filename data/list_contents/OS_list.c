#include <stdio.h>

#ifdef WIN32

#include <windows.h>
#include <string.h>

/*
 * Prints every file in /saves (ls command) (Windows only)
 */

void print_OS_dir_contents(const char* const dir) {
    WIN32_FIND_DATA file;
    HANDLE file_search_handle;
    const size_t dir_length = strlen(dir);
    char file_path[dir_length + 2]; // 1 for * and 1 for \0

    strcpy(file_path, dir);
    file_path[dir_length] = '*';
    file_path[dir_length + 1] = '\0';


    file_search_handle = FindFirstFile(file_path, &file);

    if(file_search_handle != INVALID_HANDLE_VALUE){ // In case directory isn't found
        FindNextFile(file_search_handle, &file); // Pass ..'s directory

        while(FindNextFile(file_search_handle, &file))
            puts(file.cFileName);

        FindClose(file_search_handle);

    }
    else
        puts("Didn't find any saved files\n");

}

#else

// alphasort() and scandir() are specified in POSIX.1-2008
// Considering that your OS is either WIN or included in POSIX.1-2008

#include <stdlib.h>
#include <dirent.h>

/*
 * Prints every file in /saves (ls command) (POSIX Only)
 */

void print_OS_dir_contents(const char* const dir) {
    struct dirent **contents_list;

    const int n = scandir(dir, &contents_list, NULL, alphasort);

    // First two files are the current and parent directory.
    // n == -1 (Error) -> For example no directory created yet
    if (n >= 3) {

        for (int i = 0; i < n; ++i) {

            if (i >= 2) // excluding . and .. directories
                puts(contents_list[i]->d_name);

            free(contents_list[i]);
        }

        free(contents_list);
    }
    else
        puts("Didn't find any saved files\n");
}

#endif