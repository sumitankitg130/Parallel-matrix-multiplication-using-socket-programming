#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/types.h>

#include <arpa/inet.h>
#include <errno.h>
#include <stdlib.h>

#define SERV_PORT 5576
int main(int argc, char **argv)
{
  int i, j, k;
  ssize_t n;
  char filename[80], recvline[80];
  struct sockaddr_in servaddr;
  int sockfd;
  sockfd = socket(AF_INET, SOCK_STREAM, 0);
  bzero(&servaddr, sizeof(servaddr));
  servaddr.sin_family = AF_INET;
  servaddr.sin_port = htons(SERV_PORT);
  inet_pton(AF_INET, argv[1], &servaddr.sin_addr);
  if (connect(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr)) < 0)
  {
    puts("connect error...\n");
    return 0;
  }

  int rows1;
  int valread;


  valread = read(sockfd, &rows1, sizeof(rows1));
  printf("Your number of rows: %d\n", rows1);
  if(rows1==0){
    return 0;
  }
  int sizes[4];
  valread = recv(sockfd, &sizes, sizeof(sizes), 0);
  printf("Sizes:%dx%d, %dx%d\n", sizes[0], sizes[1], sizes[2], sizes[3]);
  //static int a[rows1][sizes[1]],b[sizes[2]][sizes[3]],c[rows1][sizes[3]];
  static int a[9000][9000], b[9000][9000], c[9000][9000];
  memset(a, 0, sizeof(a));
  memset(b, 0, sizeof(b));
  memset(c, 0, sizeof(c));


  for (i = 0; i < rows1; i++)
  {
    if (read(sockfd, &a[i], sizeof(int) * sizes[1]) < 0)
      printf("receiving matrix 1 failed:%d", errno);
  }

  printf("Received matrix 1\n");

  for (i = 0; i < sizes[2]; i++)
  {
    if (read(sockfd, &b[i], sizeof(int) * sizes[3]) < 0)
      printf("receiving matrix 1 failed:%d", errno);
  }

  printf("\nReceived matrix 2\n");

  printf("Multiplying...\n");
  long sum = 0;
  for (i = 0; i < rows1; i++)
  {
    for (j = 0; j < sizes[3]; j++)
    {
      for (k = 0; k < sizes[2]; k++)
      {
        sum = sum + a[i][k] * b[k][j];
      }

      c[i][j] = sum;
      sum = 0;
    }
    if ((i + 1) % 100 == 0)
      printf("%d %% completed\n", (i + 1) * 100 / rows1);
  }
  for (i = 0; i < rows1; i++)
    send(sockfd, &c[i], sizeof(int) * sizes[3], 0);
  printf("Multiplied matrix sent...");
}
