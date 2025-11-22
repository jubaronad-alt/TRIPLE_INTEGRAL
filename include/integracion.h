#ifndef INTEGRATION_H
#define INTEGRATION_H

typedef struct {
    double masa;
    double x_bar;
    double y_bar;
    double z_bar;
} Resultado;

// Método de Riemann
Resultado integrar_riemann(
    double (*densidad)(double, double, double),
    double x_min, double x_max, int nx,
    double y_min, double y_max, int ny,
    double z_min, double z_max, int nz,
    double a, double b, double c  // parámetros para densidad lineal
);

// Método de Monte Carlo
Resultado integrar_monte_carlo(
    double (*densidad)(double, double, double),
    double x_min, double x_max,
    double y_min, double y_max,
    double z_min, double z_max,
    int muestras,
    double a, double b, double c  // parámetros para densidad lineal
);

#endif
