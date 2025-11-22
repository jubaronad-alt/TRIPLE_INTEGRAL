#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "densidades.h"
#include "integracion.h"

void escribir_resultado_csv(const char* metodo, const char* densidad, 
                           int nx, int ny, int nz, Resultado res, double tiempo) {
    FILE* archivo = fopen("resultados.csv", "a");
    if (archivo == NULL) {
        printf("Error al abrir el archivo CSV\n");
        return;
    }
    
    fprintf(archivo, "%s,%s,%d,%d,%d,%.6f,%.6f,%.6f,%.6f,%.6f\n",
            metodo, densidad, nx, ny, nz, res.masa, 
            res.x_bar, res.y_bar, res.z_bar, tiempo);
    
    fclose(archivo);
    printf("Resultados guardados en resultados.csv\n");
}

int main() {
    int opcion_metodo, opcion_densidad, nx, ny, nz, muestras;
    double x_min, x_max, y_min, y_max, z_min, z_max;
    double a = 0, b = 0, c = 0;  // Parámetros para densidad lineal
    clock_t start, end;
    double tiempo;
    Resultado res;
    
    printf("=== CALCULO DE MASA Y CENTRO DE MASA ===\n\n");
    
    // Entrada de límites de integración
    printf("Ingrese límites de integración:\n");
    printf("x_min: "); scanf("%lf", &x_min);
    printf("x_max: "); scanf("%lf", &x_max);
    printf("y_min: "); scanf("%lf", &y_min);
    printf("y_max: "); scanf("%lf", &y_max);
    printf("z_min: "); scanf("%lf", &z_min);
    printf("z_max: "); scanf("%lf", &z_max);
    
    // Selección de método
    printf("\nSeleccione método de integración:\n");
    printf("1. Riemann\n");
    printf("2. Monte Carlo\n");
    printf("Opción: "); scanf("%d", &opcion_metodo);
    
    // Selección de densidad
    printf("\nSeleccione función de densidad:\n");
    printf("1. Constante\n");
    printf("2. Lineal\n");
    printf("3. Gaussiana\n");
    printf("Opción: "); scanf("%d", &opcion_densidad);
    
    // Parámetros adicionales para densidad lineal
    if (opcion_densidad == 2) {
        printf("Ingrese parámetros a,b,c para densidad lineal: ");
        scanf("%lf %lf %lf", &a, &b, &c);
    }
    
    // Configuración del método
    if (opcion_metodo == 1) {
        printf("Ingrese número de subdivisiones (nx ny nz): ");
        scanf("%d %d %d", &nx, &ny, &nz);
        muestras = 0;
    } else {
        printf("Ingrese número de muestras: ");
        scanf("%d", &muestras);
        nx = ny = nz = 0;
    }
    
    // Ejecutar cálculo
    start = clock();
    
    switch(opcion_metodo) {
        case 1:  // Riemann
            switch(opcion_densidad) {
                case 1: res = integrar_riemann(densidad_constante, x_min, x_max, nx, y_min, y_max, ny, z_min, z_max, nz, 0, 0, 0); break;
                case 2: res = integrar_riemann(densidad_lineal, x_min, x_max, nx, y_min, y_max, ny, z_min, z_max, nz, a, b, c); break;
                case 3: res = integrar_riemann(densidad_gaussiana, x_min, x_max, nx, y_min, y_max, ny, z_min, z_max, nz, 0, 0, 0); break;
            }
            break;
            
        case 2:  // Monte Carlo
            switch(opcion_densidad) {
                case 1: res = integrar_monte_carlo(densidad_constante, x_min, x_max, y_min, y_max, z_min, z_max, muestras, 0, 0, 0); break;
                case 2: res = integrar_monte_carlo(densidad_lineal, x_min, x_max, y_min, y_max, z_min, z_max, muestras, a, b, c); break;
                case 3: res = integrar_monte_carlo(densidad_gaussiana, x_min, x_max, y_min, y_max, z_min, z_max, muestras, 0, 0, 0); break;
            }
            break;
    }
    
    end = clock();
    tiempo = (double)(end - start) / CLOCKS_PER_SEC;
    
    // Mostrar resultados
    printf("\n=== RESULTADOS ===\n");
    printf("Masa total: %.6f\n", res.masa);
    printf("Centro de masa: (%.6f, %.6f, %.6f)\n", res.x_bar, res.y_bar, res.z_bar);
    printf("Tiempo de cálculo: %.6f segundos\n", tiempo);
    
    // Guardar en CSV
    const char* nombres_metodos[] = {"", "Riemann", "MonteCarlo"};
    const char* nombres_densidades[] = {"", "Constante", "Lineal", "Gaussiana"};
    
    if (opcion_metodo == 2) { nx = ny = nz = muestras; }  // Para formato CSV
    
    escribir_resultado_csv(nombres_metodos[opcion_metodo], 
                          nombres_densidades[opcion_densidad],
                          nx, ny, nz, res, tiempo);
    
    return 0;
}
