/*#include <stdio.h>
#include <dirent.h>
#include"../src/parse.h"


int main() 
{
    DIR *dir;
    struct dirent *entry;
    // Abre el directorio actual (".")
    dir = opendir(".");
    memset(&entry, 0, sizeof(struct dirent));
    while (entry != NULL) 
    {
        entry = readdir(dir);
        printf("Nombre de archivo o directorio: %s\n", entry->d_name);
    }
    closedir(dir);


    return 0;
}
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>

int coincideConPatron(const char *nombre, const char *patron) {
    // Comprueba si el nombre del archivo coincide con el patrón
    int longitudNombre = strlen(nombre);
    int longitudPatron = strlen(patron);

    if (longitudPatron == 0) {
        return 1; // Si el patrón está vacío, cualquier nombre coincide
    }

    if (longitudNombre < longitudPatron) {
        return 0; // El nombre es más corto que el patrón, no coincide
    }

    if (patron[longitudPatron - 1] == '*') {
        return strncmp(nombre, patron, longitudPatron - 1) == 0; // Comodín al final
    }

    return strcmp(nombre, patron) == 0; // Sin comodín
}

int main() {
    DIR *dir;
    struct dirent *entry;
    const char *patron = "*.c"; // Patrón para archivos "prueba*"

    dir = opendir(".");

    if (dir) {
        while ((entry = readdir(dir)) != NULL) {
            if (entry->d_type == DT_REG) { // Comprueba si es un archivo regular
                if (coincideConPatron(entry->d_name, patron)) {
                    printf("Nombre de archivo: %s\n", entry->d_name);
                }
            }
        }
        closedir(dir);
    }

    return 0;
}
