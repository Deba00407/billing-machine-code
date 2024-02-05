#include <stdlib.h>
#include <string.h>
#include <time.h>

struct Items
{
    char item[100];
    int price;
    int quantity;
};

float calculateDiscount(float a)
{
    float x = a;
    if (x >= 5000 && x < 10000)
        x = (0.05 * x);

    else if (x >= 10000 && x < 20000)
        x = (0.10 * x);

    else if (x >= 20000)
        x = (0.20 * x);
    return x;
}

void billGenerator(char name[1000], double ph, struct Items *list, int num)
{
    FILE *ptr = fopen("D:/Customer.txt", "w");
    FILE *p = fopen("D:/bill template.txt", "r");
    float bill_amount = 0;
    srand(time(0));
    int i, j, m, n;
    for (i = 0; i < num; i++)
        bill_amount += (list[i].price * list[i].quantity);

    while (!feof(p))
    {
        char ch = (char)fgetc(p);
        char *c = (char *)malloc(5 * sizeof(char));
        if (ch == '#')
        {
            fgets(c, 5, p);
            if (strcmp(c, "00xf") == 0)
                fprintf(ptr, "%d", rand() % 101);
            else if (strcmp(c, "01xf") == 0)
            {
                fprintf(ptr, "%s", name);
                printf("%d", ftell(ptr));
                continue;
            }

            else if (strcmp(c, "02xf") == 0)
            {
                fprintf(ptr, "%0.0lf", ph);
                continue;
            }

            else if (strcmp(c, "03xf") == 0)
            {
                // fprintf(ptr, "\n", NULL);
                for (i = 0; i < num; i++)
                {
                    fprintf(ptr, "%s\t\t\t", list[i].item);
                    fprintf(ptr, "%d\t\t\t  %d\t\t\t  %d\n", list[i].quantity, list[i].price, list[i].price * list[i].quantity);
                    continue;
                }
            }

            else if (strcmp(c, "04xf") == 0)
            {
                fprintf(ptr, "%0.0f", bill_amount);
                continue;
            }

            else if (strcmp(c, "05xf") == 0)
                fprintf(ptr, "%0.3f", calculateDiscount(bill_amount));

            else if (strcmp(c, "06xf") == 0)
            {
                fprintf(ptr, "%0.3f", (bill_amount - calculateDiscount(bill_amount)) + (0.36 * bill_amount));
                continue;
            }
            free(c);
        }

        else
            putc(ch, ptr);
    }

    fclose(p);
    fclose(ptr);

    free(list);
}