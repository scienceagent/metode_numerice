#include <stdio.h>
#include <math.h>

#define epsilon 0.0001

int count = 0;

// f(x) = x^3 + 7x - 2
double f(double x)
{
    return pow(x, 3) + 7 * x - 2;
}

// g(x) = (x^3 - 2) / -7 (Modified as an iterative function approximation)
double fi(double x)
{
    return (pow(x, 3) - 2) / -7;
}

// f'(x) = 3x^2 + 7
double fD(double x)
{
    return 3 * pow(x, 2) + 7;
}

// f''(x) = 6x
double fDD(double x)
{
    return 6 * x;
}

double injumatatire(double a, double b)
{
    double c;
    if (f(a) * f(b) < 0)
    {
        while (fabs(b - a) > epsilon)
        {
            c = (a + b) / 2;
            count++;
            if (f(a) * f(c) < 0)
                b = c;
            else
                a = c;
        }
        return c;
    }
    else
    {
        return -1; // Return -1 if the method fails
    }
}

double aproximare(double a)
{
    double x = a, y;
    do
    {
        y = fi(x);
        count++;
        if (fabs(y - x) <= epsilon)
            break;
        x = y;
    } while (1);
    return x;
}

double newton(double a)
{
    double x = a, x1;
    do
    {
        x1 = x - f(x) / fD(x);
        count++;
        if (fabs(x1 - x) <= epsilon)
            break;
        x = x1;
    } while (1);
    return x1;
}

int main()
{
    double a = -2, b = 2; // Adjusting the range to include the root
    printf("Metoda injumatatirii intervalului:\n");
    double rootInj = injumatatire(a, b);
    if (rootInj != -1)
    {
        printf("(%f, 0)\n", rootInj);
    }
    else
    {
        printf("Metoda injumatatirii nu a reusit.\n");
    }
    printf("Numar iteratii: %d\n", count);
    count = 0;

    printf("Metoda aproximarilor succesive:\n");
    printf("%f\n", aproximare(a));
    printf("Numar iteratii: %d\n", count);
    count = 0;

    printf("Metoda Newton:\n");
    printf("%f\n", newton(a));
    printf("Numar iteratii: %d\n", count);

    return 0;
}
