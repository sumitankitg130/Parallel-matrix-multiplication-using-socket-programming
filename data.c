#include <stdio.h>
#include<time.h>
#include<string.h>
#include<stdlib.h>
int main()
{

    int mt[4],i,j,k;
    char filename[100];

    printf("Enter order of matrix :");
    scanf("%d %d", &mt[0], &mt[1]);
    printf("Enter filename:");
    scanf("%s",filename);
    int lower=1,upper=100;

        FILE *file3;
        file3 = fopen(filename, "w");

        for (i = 0; i < mt[0]; i++)
        {
            for (j = 0; j < mt[1]; j++)
            {
                int num = (rand() % (upper - lower + 1)) + lower;
                if (!fprintf(file3, "%d ", num))
                    break;
            }
            fprintf(file3, "\n");
        }
        fclose(file3);

        printf("Done");
    
}