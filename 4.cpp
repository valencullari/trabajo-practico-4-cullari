#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct Persona {
    char nombre[30];
    char apellido[30];
    int dni;
};

int cargar(struct Persona personas[]) {
    FILE *archivo = fopen("cuentas.txt", "r");
    if (archivo == NULL) {
        printf("No se pudo abrir el archivo. Lista vacía.\n");
        return 0;
    }

    int i = 0;
    while (fscanf(archivo, "Nombre: %s\n", personas[i].nombre) != EOF) {
        fscanf(archivo, "Apellido: %s\n", personas[i].apellido);
        fscanf(archivo, "DNI: %d\n", &personas[i].dni);
        fscanf(archivo, "\n");
        i++;
        if (i >= 100) {
            printf("Limite de personas alcanzado.\n");
            break;
        }
    }

    fclose(archivo);
    return i;
}

void guardar(struct Persona personas[], int total) {
    FILE *archivo = fopen("cuentas.txt", "w");
    if (archivo == NULL) {
        printf("No se pudo guardar el archivo.\n");
        return;
    }

    for (int i = 0; i < total; i++) {
        fprintf(archivo, "Nombre: %s\n", personas[i].nombre);
        fprintf(archivo, "Apellido: %s\n", personas[i].apellido);
        fprintf(archivo, "DNI: %d\n\n", personas[i].dni);
    }

    fclose(archivo);
    printf("Datos guardados correctamente.\n");
}

int agregar(struct Persona personas[], int *total) {
    if (*total >= 100) {
        printf("No se pueden agregar mas personas.\n");
        return 0;
    }

    int nuevoDNI;
    char nuevoNombre[30], nuevoApellido[30];

    printf("Nombre: ");
    scanf("%s", nuevoNombre);
    printf("Apellido: ");
    scanf("%s", nuevoApellido);
    printf("DNI: ");
    scanf("%d", &nuevoDNI);

    for (int i = 0; i < *total; i++) {
        if (personas[i].dni == nuevoDNI) {
            printf("DNI ya existente. No se puede agregar.\n");
            return 0;
        }
    }

    strcpy(personas[*total].nombre, nuevoNombre);
    strcpy(personas[*total].apellido, nuevoApellido);
    personas[*total].dni = nuevoDNI;

    printf("Agregado: %s %s (DNI %d)\n", nuevoNombre, nuevoApellido, nuevoDNI);
    (*total)++;
    return 1;
}

void buscarDNI(struct Persona personas[], int total, int dni) {
    for (int i = 0; i < total; i++) {
        if (personas[i].dni == dni) {
            printf("Nombre: %s\n", personas[i].nombre);
            printf("Apellido: %s\n", personas[i].apellido);
            printf("DNI: %d\n", personas[i].dni);
            return;
        }
    }
    printf("DNI no encontrado.\n");
}

void buscarNombreApellido(struct Persona personas[], int total, char nombre[], char apellido[]) {
    int encontrado = 0;
    for (int i = 0; i < total; i++) {
        if (strcmp(personas[i].nombre, nombre) == 0 && strcmp(personas[i].apellido, apellido) == 0) {
            printf("Nombre: %s\n", personas[i].nombre);
            printf("Apellido: %s\n", personas[i].apellido);
            printf("DNI: %d\n", personas[i].dni);
            encontrado = 1;
        }
    }

    if (!encontrado) {
        printf("No se encontro esa persona por nombre y apellido.\n");
    }
}

int ordenarPorDNI(const void *a, const void *b) {
    struct Persona *p1 = (struct Persona *)a;
    struct Persona *p2 = (struct Persona *)b;
    return p1->dni - p2->dni;
}

int ordenarPorNombreApellido(const void *a, const void *b) {
    struct Persona *p1 = (struct Persona *)a;
    struct Persona *p2 = (struct Persona *)b;

    int compNombre = strcmp(p1->nombre, p2->nombre);
    if (compNombre != 0) return compNombre;

    return strcmp(p1->apellido, p2->apellido);
}

void mostrarOrdenadas(struct Persona personas[], int total) {
    if (total == 0) {
        printf("No hay personas cargadas.\n");
        return;
    }

    int tipo;
    printf("Ordenar por:\n");
    printf("1. DNI\n");
    printf("2. Nombre y apellido\n");
    printf("Opción: ");
    scanf("%d", &tipo);

    struct Persona copia[100];
    memcpy(copia, personas, sizeof(struct Persona) * total);

    if (tipo == 1) {
        qsort(copia, total, sizeof(struct Persona), ordenarPorDNI);
    } else if (tipo == 2) {
        qsort(copia, total, sizeof(struct Persona), ordenarPorNombreApellido);
    } else {
        printf("Opcion de orden no valida.\n");
        return;
    }

    printf("\nPersonas ordenadas:\n");
    for (int i = 0; i < total; i++) {
        printf("Nombre: %s\n", copia[i].nombre);
        printf("Apellido: %s\n", copia[i].apellido);
        printf("DNI: %d\n\n", copia[i].dni);
    }
}

int main() {
    struct Persona personas[100];
    int total = cargar(personas);
    int opcion;
    int dni;
    char nombre[30], apellido[30];

    do {
        printf("1. Agregar persona\n");
        printf("2. Buscar por DNI\n");
        printf("3. Buscar por nombre y apellido\n");
        printf("4. Mostrar ordenadas\n");
        printf("5. Salir\n");
        printf("Opción: ");
        scanf("%d", &opcion);

        if (opcion == 1) {
            if (agregar(personas, &total)) {
                guardar(personas, total);
            }
        } else if (opcion == 2) {
            printf("DNI a buscar: ");
            scanf("%d", &dni);
            buscarDNI(personas, total, dni);
        } else if (opcion == 3) {
            printf("Nombre: ");
            scanf("%s", nombre);
            printf("Apellido: ");
            scanf("%s", apellido);
            buscarNombreApellido(personas, total, nombre, apellido);
        } else if (opcion == 4) {
            mostrarOrdenadas(personas, total);
        } else if (opcion == 5) {
            printf("Saliendo del programa\n");
        } else {
            printf("Opcion no valida.\n");
        }

    } while (opcion != 5);

    return 0;
}

