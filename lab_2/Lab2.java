import java.util.*;
import java.io.*;
import java.math.BigDecimal;

public class Lab2 {
    final static int lung = 4; // Updated to match the problem size (4x4 matrix)

    public static void main(String[] args) throws IOException {
        float[][] a = {
            {15.1f, -0.9f, 1.2f, 0.4f},
            {-0.9f, 14.6f, 0.8f, 0.7f},
            {1.2f, 0.8f, 17.6f, -0.6f},
            {0.4f, 0.7f, -0.6f, 21.3f}
        };
        
        float[] b = {9.2f, 8.7f, -10.6f, 9.7f};

        System.out.println("\nMatrix A:");
        for (float[] row : a) {
            for (float value : row) {
                System.out.print(value + "\t");
            }
            System.out.println();
        }

        System.out.println("\nVector b:");
        for (float value : b) {
            System.out.println(value);
        }
        
        GaussSeidel gaussSeidel = new GaussSeidel();
        Jacobi jacobi = new Jacobi();
        Cholesky cholesky = new Cholesky();
        float[][] l = new float[lung][lung]; // Initialize matrix l for Cholesky

        System.out.println("\nResults using Cholesky Method:");
        cholesky.cholesky(lung, b, l, a);

        System.out.println("\nResults using Jacobi Method (Error = 0.001):");
        jacobi.jacobi(lung, 0.001, a, b);

        System.out.println("\nResults using Gauss-Seidel Method (Error = 0.001):");
        gaussSeidel.gaussSeidel(lung, 0.001, a, b);

        System.out.println("\nResults using Gauss-Seidel Method (Error = 0.00001):");
        gaussSeidel.gaussSeidel(lung, 0.00001, a, b);

        // Menu-driven approach
        Scanner sc = new Scanner(System.in); // Scanner initialized here for menu input
        int menu;

        while (true) {
            System.out.println("1 - Metoda lui Cholesky");
            System.out.println("2 - Metoda Jacobi");
            System.out.println("3 - Metoda Gauss-Seidel");
            System.out.println("0 - Exit");
            System.out.print(">>> ");
            menu = sc.nextInt();

            try {
                switch (menu) {
                    case 1:
                        System.out.println("Rezultatele:");
                        System.out.println("\nMetoda Cholesky:\n");
                        cholesky.cholesky(lung, b, l, a);
                        System.out.print("\nIntroduceți orice caracter pentru a continua:\n>>> ");
                        System.in.read();
                        break;
                    case 2:
                        System.out.println("Rezultatele:");
                        System.out.println("\nMetoda Jacobi (Eroarea = 0.001):");
                        jacobi.jacobi(lung, 0.001, a, b);
                        System.out.print("\nIntroduceți orice caracter pentru a continua:\n>>> ");
                        System.in.read();
                        break;
                    case 3:
                        System.out.println("Rezultatele");
                        System.out.println("\nMetoda Gauss-Seidel (Eroarea = 0.001)");
                        gaussSeidel.gaussSeidel(lung, 0.001, a, b);
                        System.out.println("\nMetoda Gauss-Seidel (Eroarea = 0.00001)");
                        gaussSeidel.gaussSeidel(lung, 0.00001, a, b);
                        System.out.print("\nIntroduceți orice caracter pentru a continua:\n>>> ");
                        System.in.read();
                        break;
                    case 0:
                        System.out.println("Exiting the program.");
                        System.exit(0);
                    default:
                        System.out.println("Opțiune greșită!");
                        break;
                }
            } catch (IOException e) {
                System.out.println("An error occurred: " + e.getMessage());
            }
            System.out.println("\n\n\n");
        }
    }
}

class DiagonalaDominanta {
    protected int DiagDom(float[][] a, int lung) {
        float s;
        for (int i = 0; i < lung; i++) {
            s = 0;
            for (int j = 0; j < lung; j++) {
                if (i != j) {
                    s += a[i][j];
                }
            }
            if (a[i][i] < s) {
                return 0;
            } else if (a[i][i] == 0) {
                return 0;
            }
        }
        return 1;
    }
}

class GaussSeidel extends DiagonalaDominanta {
    public void gaussSeidel(int lung, double Eps, float[][] a, float[] b) throws IOException {
        float[] x = new float[20], x1 = new float[20], d = new float[20];
        float[][] q = new float[20][20];
        float t, max;
        int ni = 0;
        for (int i = 0; i < lung; i++) {
            for (int j = 0; j < lung; j++) {
                if (i != j) {
                    q[i][j] = -(a[i][j] / a[i][i]);
                } else {
                    q[i][j] = 0;
                }
            }
            if (DiagDom(a, lung) != 1) {
                System.out.println("Aceasta matricea nu este diagonal dominata");
                return;
            }
            d[i] = b[i] / a[i][i];
            x[i] = d[i];
        }
        
        do {
            for (int i = 0; i < lung; i++) {
                x1[i] = x[i];
            }
            for (int i = 0; i < lung; i++) {
                t = 0;
                for (int j = 0; j < lung; j++) {
                    t += (q[i][j] * x[j]);
                }
                x[i] = ((float)t + d[i]);
            }
            max = (float) Math.abs(x[0] - x1[0]);
            for (int i = 1; i < lung; i++) {
                if ((float) Math.abs(x[i] - x1[i]) > max) {
                    max = (float) Math.abs(x[i] - x1[i]);
                }
            }
            ni++;
        } while (max > Eps);
        
        System.out.println("\nRezultatele x:");
        for (int i = 0; i < lung; i++) {
            System.out.println("x" + (i + 1) + " = " + BigDecimal.valueOf(x[i]));
        }
        System.out.println("\nNumarul iteratiilor = " + ni);
    }
}

class Jacobi extends DiagonalaDominanta {
    public void jacobi(int lung, double Eps, float[][] a, float[] b) throws IOException {
        float[] x = new float[20], x1 = new float[20], d = new float[20];
        float[][] q = new float[20][20];
        float t, max;
        int ni = 0;

        for (int i = 0; i < lung; i++) {
            for (int j = 0; j < lung; j++) {
                if (i != j) {
                    q[i][j] = -(a[i][j] / a[i][i]);
                } else {
                    q[i][j] = 0;
                }
            }
        }

        if (DiagDom(a, lung) != 1) {
            System.out.println("Aceasta matricea nu este diagonal dominata");
            return;
        }

        for (int i = 0; i < lung; i++) {
            d[i] = b[i] / a[i][i];
            x[i] = d[i];
        }

        do {
            for (int i = 0; i < lung; i++) {
                x1[i] = x[i];
            }
            for (int i = 0; i < lung; i++) {
                t = 0;
                for (int j = 0; j < lung; j++) {
                    t += q[i][j] * x1[j];
                }
                x[i] = t + d[i];
            }
            max = (float) Math.abs(x[0] - x1[0]);
            for (int i = 1; i < lung; i++) {
                if ((float) Math.abs(x[i] - x1[i]) > max) {
                    max = (float) Math.abs(x[i] - x1[i]);
                }
            }
            ni++;
        } while (max > Eps);

        System.out.println("\nRezultatele x:");
        for (int i = 0; i < lung; i++) {
            System.out.println("x" + (i + 1) + " = " + BigDecimal.valueOf(x[i]));
        }
        System.out.println("\nNumarul iteratiilor = " + ni);
    }
}

class Cholesky {
    public void cholesky(int lung, float[] b, float[][] l, float[][] a) throws IOException {
        if (Pozitiv(lung, a) == 0) {
            System.out.println("\nAceasta matricea nu este pozitiv definita!");
            return;
        } else if (Simetric(lung, a) == 0) {
            System.out.println("\nAceasta matricea nu este simetrica!");
            return;
        }
        determinare(lung, b, l, a);
    }

    private void determinare(int lung, float[] b, float[][] l, float[][] a) {
        factor(lung, l, a); // Perform Cholesky decomposition to fill the L matrix
        float[] y = new float[lung]; // Intermediate result after forward substitution
        float[] x = new float[lung]; // Final solution after backward substitution
        float t;
    
        // Forward substitution to find y
        y[0] = b[0] / l[0][0];
        for (int i = 1; i < lung; i++) {
            t = 0;
            for (int j = 0; j < i; j++) {
                t += l[i][j] * y[j];
            }
            y[i] = (b[i] - t) / l[i][i];
        }
    
        // Display intermediate y values
        System.out.println("\nIntermediate results (y):");
        for (int i = 0; i < lung; i++) {
            System.out.printf("y%d = %.4f\n", i + 1, y[i]); // Format y values to 4 decimal places
        }
    
        // Backward substitution to find x
        x[lung - 1] = y[lung - 1] / l[lung - 1][lung - 1];
        for (int i = lung - 2; i >= 0; i--) {
            t = 0;
            for (int j = lung - 1; j > i; j--) {
                t += l[j][i] * x[j];
            }
            x[i] = (y[i] - t) / l[i][i];
        }
    
        // Display final x values
        System.out.println("\nFinal results (x):");
        for (int i = 0; i < lung; i++) {
            System.out.printf("x%d = %.4f\n", i + 1, x[i]); // Format x values to 4 decimal places
        }
    }
    

    private void factor(int lung, float[][] l, float[][] a) {
        float s;
        for (int i = 0; i < lung; i++) {
            for (int j = 0; j < i; j++) {
                s = 0;
                for (int k = 0; k < j; k++) {
                    s += l[i][k] * l[j][k];
                }
                l[i][j] = (a[i][j] - s) / l[j][j];
            }
            s = 0;
            for (int k = 0; k < i; k++) {
                s += l[i][k] * l[i][k];
            }
            l[i][i] = (float) Math.sqrt(a[i][i] - s);
        }
    }

    private int Pozitiv(int lung, float[][] a) {
        float d;
        for (int i = 0; i < lung; i++) {
            d = a[i][i];
            if (d <= 0) {
                return 0;
            }
        }
        return 1;
    }

    private int Simetric(int lung, float[][] a) {
        for (int i = 0; i < lung; i++) {
            for (int j = 0; j < lung; j++) {
                if (a[i][j] != a[j][i]) {
                    return 0;
                }
            }
        }
        return 1;
    }
}
