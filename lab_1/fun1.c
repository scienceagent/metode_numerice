#include <stdio.h>
#include <math.h>

#define epsilon 0.0001

int count = 0;

double f(double x)
{
    return log10(2 * x + 3) + 2 * x - 1;
}

double fi(double x)
{
    return (log10(2 * x + 3) - 1) / -2;
}

double fD(double x)
{
    return 2 + 2 / (2 * x + 3);
}

double fDD(double x)
{
    return -2 / pow(2 * x + 3, 2);
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
        return -1;
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
    double a = -1, b = 1;
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
