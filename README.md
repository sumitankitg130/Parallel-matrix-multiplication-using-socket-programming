# Parallelization of Matrix Multiplication in a Distributed Environment


**_Abstract_—This paper describes the procedure and results of measuring speeds of multiplication of in a distributed system using socket programming. One server and two or more clients are run to do the task and the speeds are compared to situations with zero or one client.  The server distributes the blocks of rows and columns on the registered clients. The clients return their product blocks to a server, which calculate the final product of matrix multiplication.**

_ **Keywords—socket programming, matrix multiplication, parallelization, Load balancing** _

# I.Introduction

Matrix multiplication (MM) is an important linear algebra operation. A number of scientific and engineering applications include this operation as a building block.Due to its importance many parallel algorithms have been developed to perform MM efficiently. This paper tries to perform MM by parallelizing the process with help of socket programming. Socket programming is a technique used for communication between server and client on LAN. It is known that clusters of computers offer more performance than an ordinary computer. This knowledge has been used in this paper to improve the speed of calculation of product of matrices.

## A.Problem Statement

Implementing an efficient parallel algorithm for matrix multiplication which can work in a distributed environment and dividing the tasks efficiently to different clients by load balancing.

## B.Objectives

1. Compare speedup in multiplication of matrices in a distributed environment and on a single computer.
2. Divide tasks equally and efficiently.
3. Design in a way such that load balancing is done based on number of clients available.

# II.Literature Survey

## A.Parallelization of array operations by using socket programming in .NET

- Ersin and his team in [2] successfully showed the time difference between one, two and three clients.
- Advantages:Clearly shows time taken in all three cases.
- Disadvantages: The operation performed could be more complex to get results closer to real life situations.

## B.Implementation of Distributed Application using RMI Java threads

- Arabi and his team in [3] worked on multiplication of matrices in distributed environment using RMI (Remote Method Invocation) in java.
- Advantages:Shows method of multiplication of matrices in a distributed environment.
- Disadvantages: Load balancing could also be considered.

# III.Matrix Multiplication techniques

There are many different methods for multiplication of matrices. Two of those methods has been shown below. This paper has implemented the master slave algorithm in a distributed environment.

## A.Iterative Algorithm[1]

- Input: matrices A and B
- Let C be a new matrix of the appropriate size
- For i from 1 to n:
  - For j from 1 to p:
    - Let sum = 0
    - For k from 1 to m:
      - Set sum ← sum + Aik× Bkj
    - Set Cij ← sum
- Return C

The above algorithm is an iterative algorithm. It has a time complexity of O(n3).

## B.Master Slave Algorithm

- The master process for each job, which sends the first matrix from the pair of matrices multiplication joined with a certain number of rows of the other matrix depending on the number of slaves.
- Each Slave process receives one entire matrix and a certain number of rows of the other matrix based on the number of slaves. Thus it computes the rows of the resulting matrix and sends it back to the master.
- The master process collects the rows of resulting matrix from the slaves.

# IV.Design And Implementation

In our proposed model, the server determines the distributed numbers of rows from the first matrix and the corresponding columns of the second matrix depending on the balance of workload on registered clients. For example, when size of first matrix is 1000 x 1000 and size of second matrix is also 1000 x 1000, if the registered clients number is 3 then server distribute the 1000 rows on that distributed clients, which mean each client multiply 333 rows with its corresponding columns and return its product to the server. In case if rows cannot be distributed equally some clients will get one extra row in order to complete the multiplication. One server and &quot;n&quot; clients are used to perform matrix multiplication as shown in Fig,1.

If the size of matrices is less than 500x500 then the server will process the result locally instead of using the clients. And if the number of clients is very high then the server will decide how many clients to actually use to perform the operation efficiently and will disregard other clients. This is how load balancing is implemented.

![1](https://user-images.githubusercontent.com/50589688/88675481-9ea86100-d108-11ea-83df-6102efb3211c.png)


Fig.1

Implementation algorithm is (depicted in Fig.2) as follows;

1. Client discovery; Client will register itself with the server to take a task from it
2. Generate Matrices; Server generates two matrices randomly or getting them as inputs
3. If size of matrices is very low then instead of using client, server itself will process the result, otherwise if number of clients is very high then it will use only some of the clients and discard others. This makes the process more efficient.
4. Data distribution Server will distribute number of rows from first matrix and whole second matrix on clients that it has registered.
5. Sever waits for result; Server will wait for results from clients and append it in result matrix
6. Results collecting; Server will collect the results that sent by each client and compute the time that taken by each client and compute all time taken in this process
7. Shutdown; Finally, server will send shutdown to all clients.


![2](https://user-images.githubusercontent.com/50589688/88675629-bbdd2f80-d108-11ea-9947-909da7d74bb2.jpg)
Fig.2

# V.Results And Discussion

Time taken to compute the resultant matrix is compared with different scenarios such as computing it locally, or with different number of clients.

Decrease in computation time increases as number of clients increases. Although decrease in execution time is very less for small matrices, it is very observable for larger matrices. This performance boost is very reasonable in terms of its cost, as clusters of some moderately performing computers is more readily available than a very powerful computer. The below table (Fig. 3)shows the results of our experiment in different cases.

| Matrix Size\No. of clients | One | Two | Three | Four |
| --- | --- | --- | --- | --- |
| 256 x 256 | 0.0540 seconds | 0.0520 seconds | 0.0521 seconds | 0.0527 seconds |
| 512 x 512 | 0.4269 seconds | 0.4508 seconds | 0.8459 seconds | 0.5874 seconds |
| 1000 x 1000 | 3.5989 seconds | 2.3749 seconds | 2.4802 seconds | 2.3799 seconds |
| 2000 x 2000 | 45.6737 seconds | 25.8680 seconds | 18.5406 seconds | 15.1859 seconds |
| 5000 x 5000 | 836 seconds | 430.7300 seconds | 296.3526 seconds | 265.5593 seconds |

Fig. 3

The below graph (Fig. 4) shows our results in graphical form for easy comparison purpose.

![4](https://user-images.githubusercontent.com/50589688/88675652-c4ce0100-d108-11ea-87af-f20b961dcadd.jpg)

Fig.4

# VI.How to Use

1. Compile "fileserver.c" on the server machine and execute it.
2. Enter number of clients to be connected.
3. Compile "fileclient.c" on the different client machines and execute it.
4. Enter input filename and start execution.

"matmul.c" can be used to time multiplication time on a single machine.

"data.c" can be used to generate random matrices of different sizes.

# VII.Conclusion

In this paper we implemented and analyzed the parallel matrix multiplication on distributed systems. Our mechanism will make it easier to automatic migrate the computation load to client. Future work will apply this implementation on any practical application like weather prediction, databases systems, data compression and others with increasing the numbers of clients.

##### References

1. Matrix Multiplication Algorithm. Available: [https://en.wikipedia.org/wiki/Matrix\_multiplication\_algorithm](https://en.wikipedia.org/wiki/Matrix_multiplication_algorithm)
2. Parallelization of array operations by using socket programming in .NET. Available:[https://ieeexplore.ieee.org/document/6240938](https://ieeexplore.ieee.org/document/6240938)
3. Implementation of Distributed Application using RMI Java threads. Available:[https://ieeexplore.ieee.org/document/4458214](https://ieeexplore.ieee.org/document/4458214)
