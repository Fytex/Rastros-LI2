#include <stdio.h>

#ifdef WIN32

#include <windows.h>

/*
 * Prints every file in /saves (ls command) (Windows only)
 */

void print_OS_dir_contents(const char *dir) {
    WIN32_FIND_DATA file;
    HANDLE fhandle;
    printf("%d", POSIX);
    fhandle = FindFirstFile(dir, &file);
    if(fhandle == INVALID_HANDLE_VALUE){ // In case directory isn't found
        printf("Invalid File Handle.\n");
        exit(1);
    }
    FindNextFile(fhandle, &file) // Pass ..

    while(FindNextFile(fhandle, &file)){
        puts(file.cFileName);
    }

}


#else

// alphasort() and scandir() are specified in POSIX.1-2008
// Considering that your OS is either WIN or included in POSIX.1-2008

#include <stdlib.h>
#include <dirent.h>

/*
 * Prints every file in /saves (ls command) (POSIX Only)
 */

void print_OS_dir_contents(const char *dir) {
    struct dirent **contents_list;

    int n = scandir(dir, &contents_list, NULL, alphasort);

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