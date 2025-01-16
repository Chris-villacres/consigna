#include <stdio.h>
#include "funciones.h"

int main() {
    int num_zonas;
    Zona zonas[5];

    cargar_zonas_desde_archivo(zonas, &num_zonas, "niveles.txt");

    int opcion;
    float promedios[num_zonas];
    float predicciones[num_zonas];

    do {
        printf("\n*** Menú de Opciones ***\n");
        printf("1. Calcular promedios de contaminación\n");
        printf("2. Predecir niveles de contaminación\n");
        printf("3. Emitir alertas y recomendaciones\n");
        printf("4. Guardar datos en archivo\n");
        printf("5. Modificar datos en archivo\n");
        printf("6. Salir\n");
        printf("Seleccione una opción: ");
        scanf("%d", &opcion);

        switch (opcion) {
            case 1:
                calcular_promedios(zonas, num_zonas, promedios);
                break;
            case 2:
                predecir_niveles(zonas, num_zonas, predicciones);
                break;
            case 3:
                emitir_alertas_y_recomendaciones(zonas, num_zonas, predicciones);
                break;
            case 4:
                guardar_datos_a_archivo(zonas, num_zonas, "niveles_actualizados.txt");
                break;
            case 5:
                modificar_datos_en_archivo(zonas, num_zonas, "niveles.txt");
                break;
            case 6:
                printf("Saliendo del programa.\n");
                break;
            default:
                printf("Opción inválida. Intente de nuevo.\n");
        }
    } while (opcion != 6);

    return 0;
}
