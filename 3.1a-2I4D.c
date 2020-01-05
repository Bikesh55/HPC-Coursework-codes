
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <crypt.h>
#include <mpi.h>

/*****************************************************************************
The variable names and the function names of this program is same as provided by the university.
The added variable and function are the only changes made to this program.
  

To compile:
     mpicc -o 3.1a-2I4D 3.1a-2I4D.c -lcrypt
     
  To run 3 processes on this computer:
    mpirun -n 3 ./mr.py ./3.1a-2I4D | grep Time
*****************************************************************************/


int n_passwords = 4;

char *passwords_enc[] = {
"$6$KB$aFJ.B9OwE7S.ouqqP9IcmoTjL2lBggrJgnK40p.Q.KWWJ6a.eD9oqlFSECfqRu5b.oWW5BBBk6dXSOVZp7.pD.",

"$6$KB$iBCwS/0SYkcytqyJZgNXIP5dpsklila4zd867yOhyhXdE.r466t/V4Tz.q4KtzfEt7AKXWL7H.lBc4zpuxZtr/",

"$6$KB$MtcQ0by1Wos/FjkJLQRa.QcctBA58Z8.vPQ6fdG5XQ222FQrB6onMcb03Lumj26CQ9NFY/tvQ/yqMei8xyFWe/",

"$6$KB$0cKJ/232Os568Dko9TzQg.YUDKEjff/EC8Msb.YuwhEhJ1pZD8WQE1WRsvYxfgP0y8qAH.WIDwfUc6QevfsHS0"
};
/**
 Required by lack of standard function in C.  
*/

void substr(char *dest, char *src, int start, int length){
  memcpy(dest, src + start, length);
  *(dest + length) = '\0';
}

void function_1(char *salt_and_encrypted){
  int p,a, t;    
  char salt[7];
  char plain[7];
  char *enc;
  int count = 0;

  substr(salt, salt_and_encrypted, 0, 6);

  for(p='A';p<='M'; p++){
    for(a='A'; a<='Z'; a++){
     
for(t=0; t<=9999; t++){

//printf("Instance 1:");
        sprintf(plain, "%c%c%04d", p,a,t);
        enc = (char *) crypt(plain, salt);
        count++;
        if(strcmp(salt_and_encrypted, enc) == 0){
          printf("#%-8d%s %s\n", count, plain, enc);
        }

      }
    }
  }


  printf("%d solutions explored\n", count);
}

void function_2(char *salt_and_encrypted){
  int p, a, t, m;
  char salt[7];
  char plain[7];
  char *enc;
  int count = 0;

  substr(salt, salt_and_encrypted, 0, 6);

  for(p='N';p<='Z'; p++){
    for(a='A'; a<='Z'; a++){
      for(t=0; t<=9999; t++){

//printf("Instance 1:");
        sprintf(plain, "%c%c%04d", p,a,t);
        enc = (char *) crypt(plain, salt);
        count++;
        if(strcmp(salt_and_encrypted, enc) == 0){
          printf("#%-8d%s %s\n", count, plain, enc);
        }

      }
    }
  }

  printf("%d solutions explored\n", count);
}

int time_difference(struct timespec *start, struct timespec *finish,
                    long long int *difference) {
  long long int ds =  finish->tv_sec - start->tv_sec;
  long long int dn =  finish->tv_nsec - start->tv_nsec;

  if(dn < 0 ) {
    ds--;
    dn += 1000000000;
  }
  *difference = ds * 1000000000 + dn;
  return !(*difference > 0);
}

int main() {

  struct timespec start, finish;  
  long long int time_elapsed;

  clock_gettime(CLOCK_MONOTONIC, &start);

  int size, rank;
  int i;

  MPI_Init(NULL, NULL);
  MPI_Comm_size(MPI_COMM_WORLD, &size);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  if(size != 3){
    if (rank ==0){
printf("this program needs to run on exactly 3 process to run\n ");
}
}else{
 if(rank == 0){

int r;
MPI_Send(&r, 1, MPI_INT, 1, 0, MPI_COMM_WORLD);
MPI_Send(&r, 1, MPI_INT, 2, 0, MPI_COMM_WORLD);

}else if(rank==1){
 int num;
 MPI_Recv(&num, 1, MPI_INT, 0, 0, MPI_COMM_WORLD,MPI_STATUS_IGNORE);
  for(i=0; i<n_passwords; i<i++){
    function_1(passwords_enc[i]);
   }
  } else{
    int num;
    MPI_Recv(&num, 1, MPI_INT, 0, 0, MPI_COMM_WORLD,MPI_STATUS_IGNORE);
for(i=0; i<n_passwords; i<i++){
          function_2(passwords_enc[i]);
   }
  }
}
 MPI_Finalize();
  clock_gettime(CLOCK_MONOTONIC, &finish);
  time_difference(&start, &finish, &time_elapsed);
 



if (rank ==0){

printf("Time elapsed was %lldns or %0.9lfs\n", time_elapsed,
         (time_elapsed/1.0e9));

}
  return 0;
}
