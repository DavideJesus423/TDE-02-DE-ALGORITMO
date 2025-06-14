#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h> // para sqrt()

void extrair_coeficientes(char *entrada, int *a, int *b, int *c) {
    *a = *b = *c = 0;

    // Divide a equa��o no '='
    char *igual = strchr(entrada, '=');
    if (!igual) return;

    *igual = '\0';
    char *lados[2] = { entrada, igual + 1 };

    // L� lado esquerdo (sinal +) e direito (sinal -)
    for (int lado = 0; lado < 2; lado++) {
        char *ptr = lados[lado];
        int sinal_base = (lado == 0) ? 1 : -1;

        while (*ptr) {
            int s = sinal_base;
            if (*ptr == '+') ptr++;
            else if (*ptr == '-') { s *= -1; ptr++; }

            while (*ptr == ' ') ptr++;

            int valor = 0, tem_num = 0;
            while (isdigit(*ptr)) {
                valor = valor * 10 + (*ptr - '0');
                ptr++; tem_num = 1;
            }

            if (*ptr == 'x') {
                ptr++;
                if (*ptr == '^' && *(ptr + 1) == '2') {
                    ptr += 2;
                    *a += s * (tem_num ? valor : 1);
                } else {
                    *b += s * (tem_num ? valor : 1);
                }
            } else {
                if (tem_num) *c += s * valor;
            }

            while (*ptr == ' ') ptr++;
        }
    }
}

int main() {
    char entrada[100];
    int a, b, c;

    printf("Digite a equacao no formato: ax^2 + bx + c = d\n");
    fgets(entrada, sizeof(entrada), stdin);
    entrada[strcspn(entrada, "\n")] = '\0'; // remove o '\n'

    extrair_coeficientes(entrada, &a, &b, &c);

    // Caso sem inc�gnitas
    if (a == 0 && b == 0) {
        printf("Grau: indeterminado | Possui Solucao Real: Nao | Solucao: x=N.A.\n");
        system("pause");
        return 0;
    }

    // 1� grau
    if (a == 0) {
        printf("Grau: 1o grau | ");
        if (b != 0)
            printf("Possui Solucao Real: Sim | Solucao: x=%.2f\n", -((float)c) / b);
        else
            printf("Possui Solucao Real: Nao | Solucao: x=N.A.\n");
    }

    // 2� grau
    else {
        double delta = b * b - 4 * a * c;
        printf("Grau: 2o grau | ");
        if (delta < 0)
            printf("Possui Solucao Real: Nao | Solucao: x=N.A.\n");
        else {
            double raiz = sqrt(delta);
            double x1 = (-b - raiz) / (2.0 * a);
            double x2 = (-b + raiz) / (2.0 * a);
            printf("Possui Solucao Real: Sim | ");
            if (fabs(x1 - x2) < 1e-6)
                printf("Solucao: x=%.2f\n", x1); // raiz �nica
            else
                printf("Solucao: x=%.2f, x=%.2f\n", x1, x2); // duas ra�zes
        }
    }

    system("pause");
    return 0;
}
