#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <crypt.h>
#include <time.h>

/***********************************************************************
*******

  Compile with:
    cc -o 1.1c 1.1c.c -lcrypt

 
  Run with:
    ./1.1c > results.txt

  
************************************************************************
******/
int n_passwords = 4;

char *encrypted_passwords[] = {

"$6$KB$XIt7PXVcgoQg9dthQcv.k4j3U9EwPy5G8QR9ELGoZ5NhsBQJQdYa4q.TFxD5b3tiB.sMFqUd5pOAjf8HatYMQ/",

"$6$KB$P9VhzBKxdHtTQ7rsh4suCMrHQ9IN.1VQGysmse2JpnOCesqhAzufptMXpDCoKgC02BAKaVwt5RKwX07t4xl7l1",

"$6$KB$sai/mLBZWnihibWqp7vfd353eRm8rP.OJbramtzNbnhFvqCQQsxdN9uWHASlcfmDEqfMS.mJ.PvQcGHWAMigY1",

"$6$KB$4E3YxT79l15HfehoazGTzhQxFNO/Dfyl9q67IkcWX0jvEnySPVSjlEaOL5G44ua671fYrUBNQ8N2NcMDg86Zl0"
};

/**
 Required by lack of standard function in C.   
*/

void substr(char *dest, char *src, int start, int length){
  memcpy(dest, src + start, length);
  *(dest + length) = '\0';
}

/**
 This function can crack the kind of password explained above. All
combinations
 that are tried are displayed and when the password is found, #, is put
at the
 start of the line. Note that one of the most time consuming operations
that
 it performs is the output of intermediate results, so performance
experiments
 for this kind of program should not include this. i.e. comment out the
printfs.
*/

void crack(char *salt_and_encrypted){
  int a, x, y, z;     // Loop counters
  char salt[7];    // String used in hahttps://www.youtube.com/watch?v=L8yJjIGleMwshing the password. Need space
  char plain[7];   // The combination of letters currently being checked
  char *enc;       // Pointer to the encrypted password
  int count = 0;   // The number of combinations explored so far

  substr(salt, salt_and_encrypted, 0, 6);

  for(x='A'; x<='Z'; x++){
    for(y='A'; y<='Z'; y++){
      for(a='A'; a<='Z'; a++){
      for(z=0; z<=99; z++){
        sprintf(plain, "%c%c%c%02d", x, y, a, z);
        enc = (char *) crypt(plain, salt);
        count++;
        if(strcmp(salt_and_encrypted, enc) == 0){
          printf("#%-8d%s %s\n", count, plain, enc);
        } else {
          printf(" %-8d%s %s\n", count, plain, enc);
        }
      }
      }
    }
  }
  printf("%d solutions explored\n", count);
}


//Calculating time

int time_difference(struct timespec *start, struct timespec *finish, long long int *difference)
 {
	  long long int ds =  finish->tv_sec - start->tv_sec; 
	  long long int dn =  finish->tv_nsec - start->tv_nsec; 

	  if(dn < 0 ) {
	    ds--;
	    dn += 1000000000; 
  } 
	  *difference = ds * 1000000000 + dn;
	  return !(*difference > 0);
}
int main(int argc, char *argv[])
{
  	int i;
	struct timespec start, finish;   
  	long long int time_elapsed;

  	clock_gettime(CLOCK_MONOTONIC, &start);

  	for(i=0;i<n_passwords;i<i++) 
	{
    		crack(encrypted_passwords[i]);
  	}
	clock_gettime(CLOCK_MONOTONIC, &finish);
	  time_difference(&start, &finish, &time_elapsed);
	  printf("Time elapsed was %lldns or %0.9lfs\n", time_elapsed,
		                                 (time_elapsed/1.0e9)); 
  return 0;
}
