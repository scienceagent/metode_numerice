#include <stdio.h>

float x[11], y[11], ym[11], rk[11], h = 0.1, a = 0; 
float y0 = 0.5; 

void InitXY() {
    int i;
    y[0] = y0;  
    ym[0] = y0; 
    rk[0] = y0; 
    x[0] = a; 
    for (i = 1; i < 11; i++) {
        x[i] = x[i - 1] + h;
    }
}

float f(float p1, float p2) {
    return p1 * p2 + 0.1 * p2 * p2;
}

void Euler() {
    int i;
    for (i = 1; i < 11; i++) {
        y[i] = y[i - 1] + h * f(x[i - 1], y[i - 1]);
    }
}

void EulerM() {
    int i;
    for (i = 1; i < 11; i++) {
        float y_predict = y[i - 1] + h * f(x[i - 1], y[i - 1]); 
        ym[i] = y[i - 1] + h * (f(x[i - 1], y[i - 1]) + f(x[i], y_predict)) / 2; 
    }
}

void RungeKutta() {
    int i;
    for (i = 1; i < 11; i++) {
        float k1 = h * f(x[i - 1], rk[i - 1]);
        float k2 = h * f(x[i - 1] + h / 2, rk[i - 1] + k1 / 2);
        float k3 = h * f(x[i - 1] + h / 2, rk[i - 1] + k2 / 2);
        float k4 = h * f(x[i - 1] + h, rk[i - 1] + k3);
        rk[i] = rk[i - 1] + (k1 + 2 * k2 + 2 * k3 + k4) / 6;
    }
}

int main() {
    int i;

    InitXY();

    Euler();
    EulerM();
    RungeKutta();

    printf("============================================================================================================\n");
    printf("|   x   |");
    for (i = 0; i < 11; i++) {
        printf("  %.1f   |", x[i]);
    }
    printf("\n============================================================================================================\n");
    printf("| Euler |");
    for (i = 0; i < 11; i++) {
        printf(" %.5f |", y[i]);
    }
    printf("\n|EulerM |");
    for (i = 0; i < 11; i++) {
        printf(" %.5f |", ym[i]);
    }
    printf("\n|RungeK |");
    for (i = 0; i < 11; i++) {
        printf(" %.5f |", rk[i]);
    }
    printf("\n============================================================================================================\n");

    return 0;
}
