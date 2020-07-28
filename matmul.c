#include <stdio.h>
#include<sys/time.h>
#include<string.h>
int main()
{
    static int a[10000][10000], b[10000][10000], c[10000][10000];
    int mt[4],i,j,k;
    memset(a, 0, sizeof(a));
    memset(b, 0, sizeof(b));
    memset(c, 0, sizeof(c));
    printf("Enter order of matrix 1:");
    scanf("%d %d", &mt[0], &mt[1]);
    printf("Enter order of matrix 2:");
    scanf("%d %d", &mt[2], &mt[3]);

    if (mt[1] != mt[2])
        printf("Matrices cannot be multiplied");
    else
    {

        FILE *file2;
        char filename[100];
        printf("Enter filename for first matrix:");
        scanf("%s", filename);
        file2 = fopen(filename, "r");

        for (i = 0; i < mt[0]; i++)
        {
            for (j = 0; j < mt[1]; j++)
            {
                if (!fscanf(file2, "%d", &a[i][j]))
                    break;
            }
        }
        fclose(file2);

        printf("matrix 1\n");

        FILE *file;
        printf("Enter filename for second matrix:");
        scanf("%s", filename);
        file = fopen(filename, "r");

        for (i = 0; i < mt[2]; i++)
        {
            for (j = 0; j < mt[3]; j++)
            {
                if (!fscanf(file, "%d", &b[i][j]))
                    break;
            }
        }
        fclose(file);

        printf("matrix 2 read\n");
        struct timeval  tv1, tv2;               /////////////////////////STARTING TIMER
        gettimeofday(&tv1, NULL);

        long sum = 0;
        for (i = 0; i < mt[0]; i++)
        {
            for (j = 0; j < mt[3]; j++)
            {
                for (k = 0; k < mt[2]; k++)
                {
                    sum = sum + a[i][k] * b[k][j];
                }

                c[i][j] = sum;
                sum = 0;
            }
            if((i+1)%100==0)
                printf("%d %% completed\n",(i+1)*100/mt[0]);
        }

        gettimeofday(&tv2, NULL);                               ///////////////////////////////ENDING TIMER
        printf ("Done in %f seconds\n",
         (double) (tv2.tv_usec - tv1.tv_usec) / 1000000 +
         (double) (tv2.tv_sec - tv1.tv_sec));

        FILE *file3;
        file3 = fopen("OutputSin.txt", "w");

        for (i = 0; i < mt[2]; i++)
        {
            for (j = 0; j < mt[3]; j++)
            {
                if (!fprintf(file3, "%d ", c[i][j]))
                    break;
            }
            fprintf(file3, "\n");
        }
        fclose(file3);

        
    }
}