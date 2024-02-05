#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "billing.h"

void main()
{
    int i, u, num;
    double ph;
    FILE *ptr;
    char name[1000];
    printf("\nEnter 1 to add the details of the purchased items and 2 to generate bill slip.\n");
    while (1)
    {
        printf("\nEnter response: ");
        scanf("%d", &u);

        switch (u)
        {
        case 1:
            fflush(stdin);
            printf("\nEnter customers name: ");
            fgets(name, 1000, stdin);
            printf("Enter customers phone number: ");
            scanf("%lf", &ph);
            printf("Enter the number of items purchased: ");
            scanf("%d", &num);
            struct Items *list = (struct Items *)malloc(num * sizeof(struct Items));
            printf("\nEnter the items purchased their price and quantity:\n");
            for (i = 0; i < num; i++)
            {
                fflush(stdin);
                printf("\nEnter item: ");
                fgets(list[i].item, 100, stdin);

                printf("Enter price of the item: ");
                scanf("%d", &list[i].price);

                printf("Enter quantity of the item purchased: ");
                scanf("%d", &list[i].quantity);
            }

            billGenerator(name, ph, list, num);
            break;

        case 2:
            exit(0);

        default:
            printf("\nInvalid Input");
            break;
        }
    }
}