#include <stdio.h>
#include <stdlib.h>
#include <string.h>



struct Persona {
    char nombre[40];
    char apellido[40];
    char dni[9];
} ;

void ingresarDatos() {
    FILE *archivo = fopen("datos.txt", "a"); 
    if (archivo == NULL) {
        printf("Error al abrir el archivo.\n");
        return;
    }

    Persona persona;

    printf("\nIngrese nombre: ");
    scanf(" %s", persona.nombre);
    printf("Ingrese apellido: ");
    scanf(" %s", persona.apellido);
    printf("Ingrese DNI: ");
    scanf(" %s", persona.dni);
    printf("\n");

    fprintf(archivo, "%s;%s;%s\n", persona.nombre, persona.apellido, persona.dni);
    fclose(archivo);

    printf("Datos guardados correctamente.\n");
}

void buscarPorDNI() {
    FILE *archivo = fopen("datos.txt", "r");
    if (archivo == NULL) {
        printf("No se pudo abrir el archivo.\n");
        return;
    }

    char dniBusqueda[9];
    char linea[300];
    Persona persona;
    int encontrado = 0;

    printf("\nIngrese el DNI a buscar: ");
    scanf(" %s", dniBusqueda);

    while (fgets(linea, sizeof(linea), archivo)) {
        sscanf(linea, "%[^;];%[^;];%[^\n]", persona.nombre, persona.apellido, persona.dni);

        if (strcmp(persona.dni, dniBusqueda) == 0) {
            printf("\nNombre: %s\n", persona.nombre);
            printf("Apellido: %s\n\n", persona.apellido);
            encontrado = 1;
            
        }
    }

    if (!encontrado) {
        printf("\nDNI no encontrado.\n");
    }

    fclose(archivo);
}

int main() {
    int opcion;

    do {
        
        
        
        printf("1. Ingresar datos\n");
        printf("2. Buscar por DNI\n");
        printf("3. Salir\n");
        printf("Seleccione una opcion: ");
        scanf("%d", &opcion);
       

        switch (opcion) {
            case 1:
                ingresarDatos();
                break;
            case 2:
                buscarPorDNI();
                break;
            case 3:
                printf("\nSaliendo del programa\n");
                break;
            default:
                printf("Opcion no valida.\n");
        }
    } while (opcion != 3);

    return 0;
}

