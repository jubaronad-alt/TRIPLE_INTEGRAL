#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "integracion.h"

Resultado integrar_riemann(
    double (*densidad)(double, double, double),
    double x_min, double x_max, int nx,
    double y_min, double y_max, int ny,
    double z_min, double z_max, int nz,
    double a, double b, double c) {
    
    Resultado res = {0, 0, 0, 0};
    double dx = (x_max - x_min) / nx;
    double dy = (y_max - y_min) / ny;
    double dz = (z_max - z_min) / nz;
    double dV = dx * dy * dz;
    
    for (int i = 0; i < nx; i++) {
        double x = x_min + (i + 0.5) * dx;  // Punto medio
        for (int j = 0; j < ny; j++) {
            double y = y_min + (j + 0.5) * dy;
            for (int k = 0; k < nz; k++) {
                double z = z_min + (k + 0.5) * dz;
                
                double rho = densidad(x, y, z);
                if (a != 0 || b != 0 || c != 0) {  // Para densidad lineal
                    rho = densidad(x, y, z) * (a*x + b*y + c*z);
                }
                
                res.masa += rho * dV;
                res.x_bar += x * rho * dV;
                res.y_bar += y * rho * dV;
                res.z_bar += z * rho * dV;
            }
        }
    }
    
    if (res.masa != 0) {
        res.x_bar /= res.masa;
        res.y_bar /= res.masa;
        res.z_bar /= res.masa;
    }
    
    return res;
}

Resultado integrar_monte_carlo(
    double (*densidad)(double, double, double),
    double x_min, double x_max,
    double y_min, double y_max,
    double z_min, double z_max,
    int muestras,
    double a, double b, double c) {
    
    Resultado res = {0, 0, 0, 0};
    double volumen = (x_max - x_min) * (y_max - y_min) * (z_max - z_min);
    
    // Semilla para números aleatorios
    srand(time(NULL));
    
    for (int i = 0; i < muestras; i++) {
        double x = x_min + (double)rand() / RAND_MAX * (x_max - x_min);
        double y = y_min + (double)rand() / RAND_MAX * (y_max - y_min);
        double z = z_min + (double)rand() / RAND_MAX * (z_max - z_min);
        
        double rho = densidad(x, y, z);
        if (a != 0 || b != 0 || c != 0) {  // Para densidad lineal
            rho = densidad(x, y, z) * (a*x + b*y + c*z);
        }
        
        res.masa += rho;
        res.x_bar += x * rho;
        res.y_bar += y * rho;
        res.z_bar += z * rho;
    }
    
    // Escalar por volumen y número de muestras
    double factor = volumen / muestras;
    res.masa *= factor;
    res.x_bar *= factor;
    res.y_bar *= factor;
    res.z_bar *= factor;
    
    if (res.masa != 0) {
        res.x_bar /= res.masa;
        res.y_bar /= res.masa;
        res.z_bar /= res.masa;
    }
    
    return res;
}
