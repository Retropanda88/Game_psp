#include <stdio.h>
#include <stdlib.h>

struct Mapa {
    int w_tile;
    int h_tile;
    int columnas;
    int filas;
    int *data;
};

void save_mapa(const char *fn) {
    FILE *fd = fopen(fn, "wb");
    if (!fd) {
        printf("Error al abrir el archivo para escribir\n");
        return;
    }

    struct Mapa m;
    m.w_tile = 32;
    m.h_tile = 32;
    m.columnas = 3;
    m.filas = 3;
    
    // Asignar datos del mapa (un ejemplo simple)
    m.data = (int *)malloc(sizeof(int) * m.filas * m.columnas);
    if (!m.data) {
        printf("Error de memoria\n");
        fclose(fd);
        return;
    }

    int contador = 1;
    for (int i = 0; i < m.filas; ++i) {
        for (int j = 0; j < m.columnas; ++j) {
            m.data[i * m.columnas + j] = contador++;
        }
    }

    // Escribir los datos en el archivo binario
    fwrite(&m.w_tile, sizeof(int), 1, fd);
    fwrite(&m.h_tile, sizeof(int), 1, fd);
    fwrite(&m.columnas, sizeof(int), 1, fd);
    fwrite(&m.filas, sizeof(int), 1, fd);
    fwrite(m.data, sizeof(int), m.filas * m.columnas, fd);

    // Liberar memoria y cerrar el archivo
    free(m.data);
    fclose(fd);

    printf("Archivo guardado exitosamente.\n");
}

int main() {
    save_mapa("mapa.dat");
    return 0;
}