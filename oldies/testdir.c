#include <stdio.h>
#include <dirent.h>
#include"../src/parse.h"


int main() 
{
    DIR *dir;
    struct dirent *entry;
    // Abre el directorio actual (".")
    dir = opendir(".");

	entry = readdir(dir);
    while (entry != NULL) 
    {
        printf("Nombre de archivo o directorio: %s\n", entry->d_name);
        entry = readdir(dir);
    }

    closedir(dir);

    

    return 0;
}
