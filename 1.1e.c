#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <crypt.h>
#include <time.h>
#include <ctype.h>
#include <errno.h>
#include <sys/stat.h>
#include <math.h>
#include <pthread.h>

/***********************************************************************
*******
  Compile with:
    cc -o 1.1e 1.1e.c -lcrypt -pthread

 
  Run with:
    ./1.1e> results.txt

  
************************************************************************
******/
int n_passwords = 4;

char *encrypted_passwords[] = {

"$6$KB$5B3KGhhav2/OsufUGxdicHWDBJM7ojVt0DvSVVwcpHL2OiiiBnq.b6hHZ/uYsi9PETZ6XDOW9/xOOrcbIXcfE/",

"$6$KB$kwebHrK29hjigYG8zvp87N2VpoQE51HML2nZsPyUYIRTcdOpbfCWgjr5wfdXEgNJFOMyt1weZuyTr8AmTZZ8d/",

"$6$KB$dzMbKiZard0rTfPtzDNxInzgsgYk.xYdOMGPWk1ZH0u30ySyP7XaQWhcX/MkoLXjRsJrAAqY3GqB7xPOnboJc.",

"$6$KB$EboVTynH7cHCTdC3B.gP2Tq4yF/rJhziZlrhoUCq.TWT/3spujem0kTzlktwP6WJB/sx5DsbMeKzabWAEAsx1/"
};

/**
 Required by lack of standard function in C.   
*/

void substr(char *dest, char *src, int start, int length){
  memcpy(dest, src + start, length);
  *(dest + length) = '\0';
}


void crack(){
    pthread_t t1, t2;
int i;
  

    void *first_block();
    void *second_block();
    for(i=0; i<n_passwords; i<i++){


    pthread_create(&t1, NULL, first_block, encrypted_passwords[i]);
    pthread_create(&t2, NULL, second_block, encrypted_passwords[i]);

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);
 
}
}
void *first_block(char *salt_and_encrypted){
    int x, y ,z;
    char salt[7];    // String used in hahttps://www.youtube.com/watch?v=L8yJjIGleMwshing the password. Need space
    char plain[7];   // The combination of letters currently being checked
    char *enc;       // Pointer to the encrypted password
    int count = 0;   // The number of combinations explored so far

   substr(salt, salt_and_encrypted, 0, 6);

    for(x='A'; x<='M'; x++){
        for(y='A'; y<='Z'; y++){
            for(z=0; z<=99; z++){
                sprintf(plain, "%c%c%02d", x, y, z);
                enc = (char *) crypt(plain, salt);
                count++;
                if(strcmp(salt_and_encrypted, enc) == 0){
                    printf("#%-8d%s %s\n", count, plain, enc);
                    } else {
                        printf(" %-8d%s %s\n", count, plain, enc);}
                    }
            }
        }
printf("%d solutions explored\n", count);
}

void *second_block(char *salt_and_encrypted){
     int a,b,c;
    char salt[7];    // String used in hahttps://www.youtube.com/watch?v=L8yJjIGleMwshing the password. Need space
    char plain[7];   // The combination of letters currently being checked
    char *enc;       // Pointer to the encrypted password
    int count = 0;   // The number of combinations explored so far

   substr(salt, salt_and_encrypted, 0, 6);

    for(a='N'; a<='Z'; a++){
        for(b='A'; b<='Z'; b++){
            for(c=0; c<=99; c++){
                sprintf(plain, "%c%c%02d", a,b,c);
                enc = (char *) crypt(plain, salt);
                count++;
                if(strcmp(salt_and_encrypted, enc) == 0){
                    printf("#%-8d%s %s\n", count, plain, enc);
                    } else {
                        printf(" %-8d%s %s\n", count, plain, enc);}
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
