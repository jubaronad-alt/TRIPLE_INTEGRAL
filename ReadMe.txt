=== CÁLCULO DE MASA Y CENTRO DE MASA - INTEGRACIÓN TRIPLE ===

DESCRIPCIÓN:
Programa en C para calcular la masa total y centro de masa de cuerpos 
tridimensionales mediante integración triple numérica
CARACTERÍSTICAS PRINCIPALES:
- Tres funciones de densidad: Constante, Lineal, Gaussiana
- Dos métodos de integración: Riemann y Monte Carlo
- Cálculo de masa total y centro de masa (x̄, ȳ, z̄)
- Exportación automática de resultados a CSV
- Medición de tiempo de ejecución
- Proyecto modular con Makefile

ESTRUCTURA DEL PROYECTO:
triple_integral/
├── src/
│   ├── main.c              # Programa principal
│   ├── integration.c       # Métodos de integración
│   └── densidades.c        # Funciones de densidad
├── include/
│   ├── integration.h       # Headers de integración
│   └── densidades.h        # Headers de densidades
├── Makefile               # Sistema de compilación
└── README.md              # Documentación

COMPILACIÓN Y EJECUCIÓN:

1. Compilar el programa:
   make

2. Ejecutar:
   ./bin/triple_integral

3. Limpiar archivos compilados:
   make clean

FUNCIONES DE DENSIDAD:

1. CONSTANTE: ρ(x,y,z) = 1
   - Cuerpos homogéneos
   - Verificación de métodos

2. LINEAL: ρ(x,y,z) = a·x + b·y + c·z
   - Materiales con gradientes
   - Parámetros: a, b, c

3. GAUSSIANA: ρ(x,y,z) = e^(-(x²+y²+z²))
   - Distribuciones de probabilidad
   - Decaimiento exponencial

MÉTODOS DE INTEGRACIÓN:

1. RIEMANN:
   - Divisiones regulares del volumen
   - Evaluación en puntos medios
   - Configuración: nx, ny, nz (subdivisiones)

2. MONTE CARLO:
   - Puntos aleatorios dentro del volumen
   - Estimación estadística
   - Configuración: número de muestras

EJEMPLOS DE USO:

Ejemplo 1 - Cubo homogéneo:
Límites: [0,1] en x, y, z
Método: Riemann
Densidad: Constante
Subdivisiones: 20 20 20
Resultado: Masa=1.0, Centro=(0.5,0.5,0.5)

Ejemplo 2 - Esfera gaussiana:
Límites: [-2,2] en x, y, z
Método: Monte Carlo
Densidad: Gaussiana
Muestras: 100000
Resultado: Masa≈5.568, Centro≈(0,0,0)

FORMATO DE SALIDA:

Archivo resultados.csv:
Metodo, Densidad, Nx, Ny, Nz, M, x_bar, y_bar, z_bar, Tiempo

Ejemplo:
Riemann, Lineal, 30, 30, 30, 38400.000000, 1.166667, 1.100000, 1.066667, 0.045000

REQUISITOS:
- Sistema Linux
- Compilador GCC
- Herramienta Make

INSTRUCCIONES DETALLADAS:

1. Al ejecutar el programa, seguir los pasos:
   a) Ingresar límites de integración (x_min, x_max, etc.)
   b) Seleccionar método (1: Riemann, 2: Monte Carlo)
   c) Elegir densidad (1: Constante, 2: Lineal, 3: Gaussiana)
   d) Configurar parámetros específicos del método

2. Los resultados se muestran en pantalla y se guardan en resultados.csv

3. Para densidad lineal, ingresar parámetros a, b, c cuando se soliciten

CONCEPTOS MATEMÁTICOS:

Masa total: M = ∭ ρ(x,y,z) dV

Centro de masa: 
x̄ = (1/M) ∭ x·ρ(x,y,z) dV
ȳ = (1/M) ∭ y·ρ(x,y,z) dV
z̄ = (1/M) ∭ z·ρ(x,y,z) dV

Método Riemann: División del volumen en subceldas
Método Monte Carlo: Estimación mediante promedios estadísticos