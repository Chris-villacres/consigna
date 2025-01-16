#ifndef FUNCIONES_H
#define FUNCIONES_H

#define DIAS_HISTORICOS 30
#define LIMITE_CO2 1000.0
#define LIMITE_SO2 500.0
#define LIMITE_NO2 200.0
#define LIMITE_PM25 25.0

typedef struct {
    char nombre[50];
    float niveles[DIAS_HISTORICOS];
    float nivel_actual;
} Zona;

void cargar_zonas_desde_archivo(Zona zonas[], int *num_zonas, const char *archivo);
void guardar_datos_a_archivo(Zona zonas[], int num_zonas, const char *archivo);
void calcular_promedios(Zona zonas[], int num_zonas, float promedios[]);
void predecir_niveles(Zona zonas[], int num_zonas, float predicciones[]);
void emitir_alertas_y_recomendaciones(Zona zonas[], int num_zonas, float predicciones[]);
void modificar_datos_en_archivo(Zona zonas[], int num_zonas, const char *archivo);

#endif


