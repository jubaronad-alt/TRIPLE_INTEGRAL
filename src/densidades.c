#include <math.h>
#include "densidades.h"

// Densidad constante: ρ(x,y,z) = 1
// Representa un cuerpo homogéneo donde la masa se distribuye uniformemente
double densidad_constante(double x, double y, double z) {
    return 1.0;
}

// Densidad lineal: ρ(x,y,z) = ax + by + cz
// Modela materiales cuya densidad varía linealmente en el espacio
double densidad_lineal(double x, double y, double z, double a, double b, double c) {
    return a*x + b*y + c*z;
}

// Densidad gaussiana: ρ(x,y,z) = e^(-(x²+y²+z²))
// Describe distribuciones de probabilidad o concentraciones que decaen exponencialmente
double densidad_gaussiana(double x, double y, double z) {
    return exp(-(x*x + y*y + z*z));
}
