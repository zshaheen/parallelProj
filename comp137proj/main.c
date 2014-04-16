/* pth_main.c
 *
 * A simple Pthread program to test Code::Blocks
 * configuration on Windows.
 * This program is taken from Pacheco Chapter 2.
 */
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

const int MAX_THREADS = 64;

/* Global variable:  accessible to all threads */
int thread_count;

void Usage(char* prog_name);
void* Hello(void* rank);  /* Thread function */

/*--------------------------------------------------------------------*/
int main(int argc, char* argv[]) {
   long       thread;
   pthread_t* thread_handles;

   /* Get number of threads from command line */
   if (argc != 2) Usage(argv[0]);
   thread_count = strtol(argv[1], NULL, 10);
   if (thread_count <= 0 || thread_count > MAX_THREADS) Usage(argv[0]);

   /* create an array of thread handles */
   thread_handles = malloc (thread_count*sizeof(pthread_t));

   /* start the threads, giving each a unique rank */
   for (thread = 0; thread < thread_count; thread++)
      pthread_create(&thread_handles[thread], NULL,
          Hello, (void*) thread);

   /* print a message from the main thread */
   printf("Hello from the main thread\n");

   /* wait for all threads to complete */
   for (thread = 0; thread < thread_count; thread++)
      pthread_join(thread_handles[thread], NULL);

   /* delete the dynamically allocated array of thread handles */
   free(thread_handles);
   return 0;
}

/*-------------------------------------------------------------------*/
void* Hello(void* rank) {
   long my_rank = (long) rank;

   printf("Hello from thread %ld of %d\n", my_rank, thread_count);

   return NULL;
}

/*-------------------------------------------------------------------*/
void Usage(char* prog_name) {
   fprintf(stderr, "usage: %s <number of threads>\n", prog_name);
   fprintf(stderr, "0 < number of threads <= %d\n", MAX_THREADS);
   exit(0);
}
