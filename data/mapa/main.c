#include <stdio.h>

int main() {
    // Dimensiones del mapa
    int w_tile = 50;    // Ancho del tile
    int h_tile = 50;    // Alto del tile
    int filas = 480/w_tile;     // Número de filas
    int columnas = 640/h_tile;  // Número de columnas

    // Crear un arreglo 2D inicializado con ceros
    int mapa[13][13] = {0};

    // Abrir el archivo en modo escritura
    FILE *archivo = fopen("mapa.txt", "w");
    if (!archivo) {
        printf("Error: No se pudo crear el archivo.\n");
        return 1;
    }

    // Escribir los valores iniciales de w_tile, h_tile, filas y columnas
    fprintf(archivo, "%d %d %d %d\n", w_tile, h_tile, filas, columnas);

    // Escribir el arreglo 2D (13x13) al archivo
    for (int i = 0; i < filas; i++) {
        for (int j = 0; j < columnas; j++) {
            fprintf(archivo, "%d ", mapa[i][j]);
        }
        fprintf(archivo, "\n"); // Salto de línea al final de cada fila
    }

    // Cerrar el archivo
    fclose(archivo);

    printf("Archivo 'mapa.txt' creado exitosamente.\n");
    return 0;
}