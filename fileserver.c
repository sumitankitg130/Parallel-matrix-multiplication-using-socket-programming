#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <time.h>
#include<sys/time.h>
#include <stdlib.h>
#include <errno.h>
#include<math.h>
#define SERV_PORT 5576
int main(int argc, char **argv)
{

  

  int i, j, k;
  ssize_t n;
  FILE *fp;
  char s[80], f[80];
  struct sockaddr_in servaddr, cliaddr;
  int listenfd, max_clients,origmax;
  unsigned clilen;
  listenfd = socket(AF_INET, SOCK_STREAM, 0);
  bzero(&servaddr, sizeof(servaddr));
  servaddr.sin_family = AF_INET;
  servaddr.sin_port = htons(SERV_PORT);
  bind(listenfd, (struct sockaddr *)&servaddr, sizeof(servaddr));
  listen(listenfd, 1);
  clilen = sizeof(cliaddr);

  printf("Enter number of clients:");
  scanf("%d", &max_clients);
  origmax=max_clients;
  int connfd[max_clients];
  memset(connfd, 0, sizeof(connfd));
  for (i = 0; i < max_clients; i++)
  {
    connfd[i] = accept(listenfd, (struct sockaddr *)&cliaddr, &clilen);
    if (connfd[i] < 0)
    {
      printf("accept error...");
      return 0;
    }
    else
      printf("\n client %d connected.\n", i + 1);
  }

  int sd, valread;
  int mt[4], each, extra, eachextra;

  printf("Enter order of matrix 1:");
  scanf("%d %d", &mt[0], &mt[1]);
  printf("Enter order of matrix 2:");
  scanf("%d %d", &mt[2], &mt[3]);

  static int a[10000][10000],b[10000][10000],c[10000][10000];
  memset(a,0,sizeof(a));
  memset(b,0,sizeof(b));
  memset(c,0,sizeof(c));

  if (mt[1] != mt[2])
    printf("Matrices cannot be multiplied");
  else
  {
    extra = mt[0] % max_clients;
    each = mt[0] / max_clients;

    if(max_clients>mt[0]/256+1){
      max_clients=mt[0]/256+1;
      extra = mt[0] % max_clients;
      each = mt[0] / max_clients;
    }
    //printf("Using %d clients.\n",max_clients);
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

    printf("matrix 1 read \n");


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

  }
  j = 0;
  int sendmsg;


  struct timeval  tv1, tv2;
  gettimeofday(&tv1, NULL);                             /////////////////////STARTING TIMER
   
  if(mt[0]<=500){
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
        for(i=0;i<max_clients;i++){
          close(connfd[i]);
        }
  }
  else{

  for (i = 0; i < max_clients; i++)
  {
    sd = connfd[i];

    if (i < extra)
    {
      sendmsg = each + 1;
    }
    else
    {
      sendmsg = each;
    }
    int val;
    if (send(sd, &sendmsg, sizeof(each), 0) < 0)
    {
      printf("Send Failed");
      return 0;
    }
    if (send(sd, &mt, sizeof(mt), 0) < 0)
    {
      puts("Send Failed");
      return 0;
    }
    for (int cnt = 0; cnt < sendmsg; cnt++, j++)
    {
      if ((val = send(sd, &a[j], sizeof(int) * mt[1], 0)) < 0)
        printf("Send a Failed... %d  %d\n", val, errno);
    }
    for(int cnt=0;cnt<mt[2];cnt++)
      if (send(sd, &b[cnt], sizeof(int) * mt[3], 0) < 0)
        puts("Send b failed...");
  }
  for(i;i<origmax;i++){
    sd=connfd[i];
    int inf=0;
    send(sd,&inf,sizeof(inf),0);
  }
  j = 0;
  for (i = 0; i < max_clients; i++)
  {
    sd = connfd[i];
    if (i < extra)
    {
      sendmsg = each + 1;
    }
    else
    {
      sendmsg = each;
    }
    for (int cnt = 0; cnt < sendmsg; cnt++, j++)
    {
      if (recv(sd, &c[j], sizeof(int) * mt[3], 0) < 0)
        puts("Recv c Failed...");
    }
  }
  
  printf("data sent and received.");
  printf("\nReceived multiplied matrix:\n");

  }



  gettimeofday(&tv2, NULL);                                         //////////////////////////ENDING TIMER
  printf ("Done in %f seconds\n",
         (double) (tv2.tv_usec - tv1.tv_usec) / 1000000 +
         (double) (tv2.tv_sec - tv1.tv_sec));


  FILE *file3;
    file3 = fopen("Output.txt", "w");

    for (i = 0; i < mt[2]; i++)
    {
      for (j = 0; j < mt[3]; j++)
      {
        if (!fprintf(file3, "%d ", c[i][j]))
          break;
      }
      fprintf(file3,"\n");
    }
    fclose(file3);

}
