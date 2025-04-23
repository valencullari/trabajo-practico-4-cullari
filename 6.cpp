#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Jugador {
    char nombre[50];
    int puntaje;
};

int cargar(struct Jugador lista[], int *cantidad) {
    FILE *archivo = fopen("jugadores.txt", "r");
    if (archivo == NULL) {
        printf("no se encontró el archivo, se creara uno nuevo al guardar\n");
        *cantidad = 0;
        return 0;
    }

    *cantidad = 0;
    while (fscanf(archivo, "Nombre: %[^\n]\n", lista[*cantidad].nombre) != EOF) {
        fscanf(archivo, "Puntaje: %d\n", &lista[*cantidad].puntaje);
        fscanf(archivo, "\n");
        (*cantidad)++;

        if (*cantidad >= 100) {
            printf("se llego al limite de jugadores\n");
            break;
        }
    }

    fclose(archivo);
    return 1;
}

void guardar(struct Jugador lista[], int cantidad) {
    FILE *archivo = fopen("jugadores.txt", "w");
    if (archivo == NULL) {
        printf("no se pudo guardar el archivo\n");
        return;
    }

    for (int i = 0; i < cantidad; i++) {
        fprintf(archivo, "Nombre:\t%s\n", lista[i].nombre);
        fprintf(archivo, "Puntaje:\t%d\n\n", lista[i].puntaje);
    }

    fclose(archivo);
    printf("datos guardados correctamente\n");
}

void agregar(struct Jugador lista[], int *cantidad) {
    if (*cantidad >= 100) {
        printf("no se pueden agregar mas jugadores\n");
        return;
    }

    printf("nombre del jugador: ");
    scanf(" %[^\n]", lista[*cantidad].nombre);
    printf("puntaje: ");
    scanf("%d", &lista[*cantidad].puntaje);

    (*cantidad)++;
    guardar(lista, *cantidad);
}

void mostrarTop10(struct Jugador lista[], int cantidad) {
    if (cantidad == 0) {
        printf("no hay jugadores cargados\n");
        return;
    }

    for (int i = 0; i < cantidad - 1; i++) {
        for (int j = i + 1; j < cantidad; j++) {
            if (lista[j].puntaje > lista[i].puntaje) {
                struct Jugador aux = lista[i];
                lista[i] = lista[j];
                lista[j] = aux;
            }
        }
    }

    int max = cantidad < 10 ? cantidad : 10;
   
    for (int i = 0; i < max; i++) {
    	printf("\ntop %d\n", i+1);
        printf("nombre: %s\n", lista[i].nombre);
        printf("puntaje: %d\n\n", lista[i].puntaje);
    }
}

void buscar(struct Jugador lista[], int cantidad) {
    char nombreBuscado[50];
    int encontrado = 0;

    printf("nombre del jugador a buscar: ");
    scanf(" %[^\n]", nombreBuscado);

    for (int i = 0; i < cantidad; i++) {
        if (strcmp(lista[i].nombre, nombreBuscado) == 0) {
            printf("\njugador encontrado:\n");
            printf("nombre: %s\n", lista[i].nombre);
            printf("puntaje: %d\n", lista[i].puntaje);
            encontrado = 1;
        }
    }

    if (!encontrado) {
        printf("no se encontro el jugador\n");
    }
}

int main() {
    struct Jugador jugadores[100];
    int total = 0;
    cargar(jugadores, &total);

    int opcion;

    do {
        printf("1) agregar jugador\n");
        printf("2) mostrar top 10\n");
        printf("3) buscar jugador\n");
        printf("4) salir\n");
        printf("opción: ");
        scanf("%d", &opcion);

        if (opcion == 1) {
            agregar(jugadores, &total);
        } else if (opcion == 2) {
            mostrarTop10(jugadores, total);
        } else if (opcion == 3) {
            buscar(jugadores, total);
        } else if (opcion == 4) {
            printf("saliendo del programa\n");
        } else {
            printf("opción no válida\n");
        }

    } while (opcion != 4);

    return 0;
}

