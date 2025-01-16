#include "funciones.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void cargar_zonas_desde_archivo(Zona zonas[], int *num_zonas, const char *archivo) {
    const char *zonas_disponibles[] = {"Cumbaya", "Lumbisi", "Valle_de_los_Chillos", "Norte", "Sur"};
    int total_zonas = 5;

    printf("Zonas disponibles:\n");
    for (int i = 0; i < total_zonas; i++) {
        printf("%d. %s\n", i + 1, zonas_disponibles[i]);
    }

    printf("Ingrese el número de zonas que desea analizar (máximo 5): ");
    scanf("%d", num_zonas);
    if (*num_zonas > 5) {
        printf("El número máximo de zonas es 5. Ajustando a 5.\n");
        *num_zonas = 5;
    }

    printf("Seleccione las zonas a analizar ingresando sus números separados por espacios (termine con -1):\n");
    int indices[5];
    int count = 0;
    while (count < *num_zonas) {
        int idx;
        scanf("%d", &idx);
        if (idx == -1 || count >= *num_zonas) break;
        if (idx < 1 || idx > total_zonas) {
            printf("Índice fuera de rango. Intente de nuevo.\n");
        } else {
            indices[count++] = idx - 1;
        }
    }

    for (int i = 0; i < count; i++) {
        strcpy(zonas[i].nombre, zonas_disponibles[indices[i]]);
        printf("Ingrese el nivel actual de contaminación para %s: ", zonas[i].nombre);
        scanf("%f", &zonas[i].nivel_actual);

        for (int j = 0; j < DIAS_HISTORICOS; j++) {
            zonas[i].niveles[j] = 20.0 + rand() % 40;  // Valores generados aleatoriamente para simulación
        }
    }
}

void calcular_promedios(Zona zonas[], int num_zonas, float promedios[]) {
    for (int i = 0; i < num_zonas; i++) {
        float suma = 0.0;
        for (int j = 0; j < DIAS_HISTORICOS; j++) {
            suma += zonas[i].niveles[j];
        }
        promedios[i] = suma / DIAS_HISTORICOS;
        printf("Promedio de contaminación en %s: %.2f µg/m³\n", zonas[i].nombre, promedios[i]);
    }
}

void predecir_niveles(Zona zonas[], int num_zonas, float predicciones[]) {
    for (int i = 0; i < num_zonas; i++) {
        float suma = 0.0;
        float pesos = 0.0;

        for (int j = 0; j < DIAS_HISTORICOS; j++) {
            int peso = (j >= DIAS_HISTORICOS - 10) ? 2 : 1;
            suma += zonas[i].niveles[j] * peso;
            pesos += peso;
        }
        predicciones[i] = suma / pesos;
        printf("Predicción de contaminación en %s para las próximas 24 horas: %.2f µg/m³\n", zonas[i].nombre, predicciones[i]);
    }
}

void emitir_alertas_y_recomendaciones(Zona zonas[], int num_zonas, float predicciones[]) {
    for (int i = 0; i < num_zonas; i++) {
        if (predicciones[i] > 30) {
            printf("ALERTA: Los niveles de contaminación en %s son peligrosos.\n", zonas[i].nombre);
            printf("Recomendaciones para %s:\n", zonas[i].nombre);
            printf("- Reducir el tráfico vehicular.\n");
            printf("- Cerrar temporalmente industrias.\n");
            printf("- Suspender actividades al aire libre.\n");
        } else {
            printf("Niveles de contaminación en %s no peligrosos.\n", zonas[i].nombre);
        }
    }
}

#include "funciones.h"
#include <stdio.h>

void guardar_datos_a_archivo(Zona zonas[], int num_zonas, const char *archivo) {
    FILE *fp = fopen(archivo, "w");
    if (fp == NULL) {
        printf("No se pudo abrir el archivo %s para guardar.\n", archivo);
        return;
    }

    for (int i = 0; i < num_zonas; i++) {
        // Guardamos el nombre de la zona
        fprintf(fp, "%s\n", zonas[i].nombre);
        
        // Guardamos el promedio de contaminación
        float suma = 0.0;
        for (int j = 0; j < DIAS_HISTORICOS; j++) {
            suma += zonas[i].niveles[j];
        }
        float promedio = suma / DIAS_HISTORICOS;
        fprintf(fp, "Promedio de contaminación: %.2f µg/m³\n", promedio);
        
        // Guardamos el nivel actual
        fprintf(fp, "Nivel actual de contaminación: %.2f µg/m³\n", zonas[i].nivel_actual);
        
        // Predicción del día siguiente
        float prediccion = 0.0;
        float suma_prediccion = 0.0;
        float pesos = 0.0;
        for (int j = 0; j < DIAS_HISTORICOS; j++) {
            int peso = (j >= DIAS_HISTORICOS - 10) ? 2 : 1;
            suma_prediccion += zonas[i].niveles[j] * peso;
            pesos += peso;
        }
        prediccion = suma_prediccion / pesos;
        fprintf(fp, "Predicción para el día siguiente: %.2f µg/m³\n", prediccion);
        
        fprintf(fp, "\n"); // Espacio entre zonas
    }

    fclose(fp);
    printf("Datos guardados correctamente en %s\n", archivo);
}
void modificar_datos_en_archivo(Zona zonas[], int num_zonas, const char *archivo) {
    FILE *fp = fopen(archivo, "r+");
    if (fp == NULL) {
        printf("No se pudo abrir el archivo %s para modificar.\n", archivo);
        return;
    }

    char nombre_zona[50];
    printf("Ingrese el nombre de la zona que desea modificar: ");
    scanf(" %[^\n]", nombre_zona);  // Leer con espacios

    int zona_encontrada = 0;
    while (fscanf(fp, "%s", zonas[0].nombre) != EOF) { // Recorremos todas las zonas
        if (strcmp(zonas[0].nombre, nombre_zona) == 0) {
            zona_encontrada = 1;
            break;
        }
    }

    if (zona_encontrada) {
        // Si encontramos la zona, preguntamos qué valor modificar
        int opcion_modificar;
        printf("¿Qué valor desea modificar?\n");
        printf("1. Nivel actual de contaminación\n");
        printf("2. Datos históricos de contaminación\n");
        printf("Seleccione una opción: ");
        scanf("%d", &opcion_modificar);

        if (opcion_modificar == 1) {
            printf("Ingrese el nuevo nivel actual de contaminación para %s: ", zonas[0].nombre);
            scanf("%f", &zonas[0].nivel_actual);
        } else if (opcion_modificar == 2) {
            printf("Ingrese los nuevos valores históricos de contaminación para %s (30 valores):\n", zonas[0].nombre);
            for (int i = 0; i < DIAS_HISTORICOS; i++) {
                printf("Día %d: ", i + 1);
                scanf("%f", &zonas[0].niveles[i]);
            }
        }

        // Guardar los cambios en el archivo
        FILE *fp_temp = fopen("temp.txt", "w");
        if (fp_temp == NULL) {
            printf("Error al crear archivo temporal.\n");
            fclose(fp);
            return;
        }

        // Reescribir el archivo con los cambios
        rewind(fp);
        while (fscanf(fp, "%s", zonas[0].nombre) != EOF) {
            if (strcmp(zonas[0].nombre, nombre_zona) == 0) {
                fprintf(fp_temp, "%s\n", zonas[0].nombre);
                fprintf(fp_temp, "%.2f\n", zonas[0].nivel_actual);
                for (int i = 0; i < DIAS_HISTORICOS; i++) {
                    fprintf(fp_temp, "%.2f\n", zonas[0].niveles[i]);
                }
            } else {
                // Copiar los datos sin cambios
                fprintf(fp_temp, "%s\n", zonas[0].nombre);
                fscanf(fp, "%f", &zonas[0].nivel_actual);
                fprintf(fp_temp, "%.2f\n", zonas[0].nivel_actual);
                for (int i = 0; i < DIAS_HISTORICOS; i++) {
                    fscanf(fp, "%f", &zonas[0].niveles[i]);
                    fprintf(fp_temp, "%.2f\n", zonas[0].niveles[i]);
                }
            }
        }

        fclose(fp);
        fclose(fp_temp);

        // Reemplazar el archivo original con el archivo temporal
        remove(archivo);
        rename("temp.txt", archivo);

        printf("Datos modificados correctamente.\n");
    } else {
        printf("Zona no encontrada.\n");
    }
}
