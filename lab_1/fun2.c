#include <stdio.h>
#include <math.h>

#define epsilon 0.0001

int numar_iteratii = 0;

double functie(double x)
{
    return pow(x, 3) + 7 * x - 2;
}

double derivata_functie(double x)
{
    return 3 * pow(x, 3) + 7;
}

double metoda_injumatatirii(double a, double b)
{
    double c;
    if (functie(a) * functie(b) < 0)
    {
        while (fabs(b - a) > epsilon)
        {
            c = (a + b) / 2;
            numar_iteratii++;
            printf("Pasul %d: a = %f, b = %f, c = %f\n", numar_iteratii, a, b, c);
            if (functie(a) * functie(c) < 0)
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

double metoda_newton(double a)
{
    double x = a, x1;
    do
    {
        x1 = x - functie(x) / derivata_functie(x);
        numar_iteratii++;
        printf("Pasul %d: x = %f, x1 = %f\n", numar_iteratii, x, x1);
        if (fabs(x1 - x) <= epsilon)
            break;
        x = x1;
    } while (1);
    return x1;
}

double metoda_secantelor(double x0, double x1)
{
    double x2;
    do
    {
        x2 = x1 - (functie(x1) * (x1 - x0)) / (functie(x1) - functie(x0));
        numar_iteratii++;
        printf("Pasul %d: x0 = %f, x1 = %f, x2 = %f\n", numar_iteratii, x0, x1, x2);
        if (fabs(x2 - x1) <= epsilon)
            break;
        x0 = x1;
        x1 = x2;
    } while (1);
    return x2;
}

int main()
{
    double a = -1, b = 1;
    
    printf("Metoda injumatatirii intervalului:\n");
    double radacina_injumatatire = metoda_injumatatirii(a, b);
    if (radacina_injumatatire != -1)
    {
        printf("Rădăcina: (%f, 0)\n", radacina_injumatatire);
    }
    else
    {
        printf("Metoda injumatatirii nu a reusit.\n");
    }
    printf("Numar iteratii: %d\n", numar_iteratii);
    numar_iteratii = 0;

    printf("Metoda Newton:\n");
    printf("Rădăcina: %f\n", metoda_newton(a));
    printf("Numar iteratii: %d\n", numar_iteratii);
    numar_iteratii = 0;

    printf("Metoda secantelor:\n");
    printf("Rădăcina: %f\n", metoda_secantelor(a, b));
    printf("Numar iteratii: %d\n", numar_iteratii);

    return 0;
}
