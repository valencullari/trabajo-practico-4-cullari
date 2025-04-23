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
    if (archivo == NULL) return 0;

    int i = 0;
    while (fscanf(archivo, "Nombre: %s\n", personas[i].nombre) != EOF) {
        fscanf(archivo, "Apellido: %s\n", personas[i].apellido);
        fscanf(archivo, "DNI: %d\n", &personas[i].dni);
        fscanf(archivo, "\n");
        i++;
    }

    fclose(archivo);
    return i;
}

void guardar(const char *nombre_archivo, struct Persona personas[], int total) {
    FILE *archivo = fopen(nombre_archivo, "w");
    if (archivo == NULL) {
        printf("no se pudo guardar en %s\n", nombre_archivo);
        return;
    }

    for (int i = 0; i < total; i++) {
        fprintf(archivo, "Nombre: %s\n", personas[i].nombre);
        fprintf(archivo, "Apellido: %s\n", personas[i].apellido);
        fprintf(archivo, "DNI: %d\n\n", personas[i].dni);
    }

    fclose(archivo);
}

int buscarPorDNI(struct Persona personas[], int total, int dni) {
    for (int i = 0; i < total; i++) {
        if (personas[i].dni == dni) return i;
    }
    return -1;
}

void mostrar(struct Persona p) {
    printf("nombre: %s\n", p.nombre);
    printf("apellido: %s\n", p.apellido);
    printf("dni: %d\n", p.dni);
}

int ordenarDNI(const void *a, const void *b) {
    struct Persona *p1 = (struct Persona *)a;
    struct Persona *p2 = (struct Persona *)b;
    return p1->dni - p2->dni;
}

int ordenarNombreApellido(const void *a, const void *b) {
    struct Persona *p1 = (struct Persona *)a;
    struct Persona *p2 = (struct Persona *)b;
    int nombre_cmp = strcmp(p1->nombre, p2->nombre);
    if (nombre_cmp == 0)
        return strcmp(p1->apellido, p2->apellido);
    return nombre_cmp;
}

void verOrdenadas(struct Persona personas[], int total) {
    int tipo;
    printf("ordenar por:\n1. dni\n2. nombre y apellido\nopcion: ");
    scanf("%d", &tipo);

    if (tipo != 1 && tipo != 2) {
        printf("opcion no valida\n");
        return;
    }

    qsort(personas, total, sizeof(struct Persona),
          tipo == 1 ? ordenarDNI : ordenarNombreApellido);

    for (int i = 0; i < total; i++) {
        mostrar(personas[i]);
        printf("\n");
    }
}

void editarCopia(struct Persona personas[], int total) {
    int dni, pos;
    printf("dni a modificar: ");
    scanf("%d", &dni);

    pos = buscarPorDNI(personas, total, dni);
    if (pos == -1) {
        printf("no encontrado\n");
        return;
    }

    struct Persona copia[100];
    memcpy(copia, personas, sizeof(struct Persona) * total);

    printf("datos actuales:\n");
    mostrar(copia[pos]);

    int cambio;
    printf("que quiere cambiar?\n1. nombre\n2. apellido\n3. dni\nopcion: ");
    scanf("%d", &cambio);

    if (cambio == 1) {
        printf("nuevo nombre: ");
        scanf("%s", copia[pos].nombre);
    } else if (cambio == 2) {
        printf("nuevo apellido: ");
        scanf("%s", copia[pos].apellido);
    } else if (cambio == 3) {
        printf("nuevo dni: ");
        scanf("%d", &copia[pos].dni);
    } else {
        printf("opcion no valida\n");
        return;
    }

    guardar("copiasCuenta.txt", copia, total);
    printf("copia modificada:\n");
    mostrar(copia[pos]);

    printf("aplicar cambio a archivo original? (1. si, 2. no): ");
    int aplicar;
    scanf("%d", &aplicar);

    if (aplicar == 1) {
        personas[pos] = copia[pos];
        guardar("cuentas.txt", personas, total);
        printf("cambio aplicado\n");
    } else {
        printf("solo se guardo en copia\n");
    }
}

int agregar(struct Persona personas[], int *total) {
    if (*total >= 100) {
        printf("limite alcanzado\n");
        return 0;
    }

    int dni;
    char nombre[30], apellido[30];
    printf("nombre: ");
    scanf("%s", nombre);
    printf("apellido: ");
    scanf("%s", apellido);
    printf("dni: ");
    scanf("%d", &dni);

    for (int i = 0; i < *total; i++) {
        if (personas[i].dni == dni) {
            printf("dni ya registrado\n");
            return 0;
        }
    }

    strcpy(personas[*total].nombre, nombre);
    strcpy(personas[*total].apellido, apellido);
    personas[*total].dni = dni;

    (*total)++;
    guardar("cuentas.txt", personas, *total);
    printf("persona agregada\n");
    return 1;
}

int main() {
    struct Persona personas[100];
    int total = cargar(personas);
    int opcion;

    do {
        printf("1. agregar persona\n");
        printf("2. buscar por dni\n");
        printf("3. ver personas ordenadas\n");
        printf("4. modificar en copia\n");
        printf("5. salir\nopcion: ");
        scanf("%d", &opcion);

        if (opcion == 1) {
            agregar(personas, &total);
        } else if (opcion == 2) {
            int dni;
            printf("dni a buscar: ");
            scanf("%d", &dni);
            int i = buscarPorDNI(personas, total, dni);
            if (i != -1) mostrar(personas[i]);
            else printf("no encontrado\n");
        } else if (opcion == 3) {
            verOrdenadas(personas, total);
        } else if (opcion == 4) {
            editarCopia(personas, total);
        } else if (opcion == 5) {
            printf("saliendo del programa\n");
        } else {
            printf("opcion no valida\n");
        }
    } while (opcion != 5);

    return 0;
}

