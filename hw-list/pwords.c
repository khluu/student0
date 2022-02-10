/*
 * Word count application with one thread per input file.
 *
 * You may modify this file in any way you like, and are expected to modify it.
 * Your solution must read each input file from a separate thread. We encourage
 * you to make as few changes as necessary.
 */

/*
 * Copyright © 2021 University of California, Berkeley
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 * HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <pthread.h>

#include "word_count.h"
#include "word_helpers.h"

struct thread_param {
  char *name;
  word_count_list_t *wc;
};

void* readFile(void *args) {
  struct thread_param *thread_params = args;
  FILE *fp = fopen(thread_params->name, "r");
  printf("file: %s\n", thread_params->name);
  count_words(thread_params->wc, fp);
  
}

/*
 * main - handle command line, spawning one thread per file.
 */
int main(int argc, char* argv[]) {
  /* Create the empty data structure. */
  word_count_list_t word_counts;
  init_words(&word_counts);

  if (argc <= 1) {
    /* Process stdin in a single thread. */
    count_words(&word_counts, stdin);
  } else {
    int rc;
    int nthreads = argc - 1;
    struct thread_param *thread_params[nthreads];
    pthread_t threads[nthreads];

    //printf("num threads: %d", nthreads);

    for (int t = 0; t < nthreads; t++) {
      thread_params[t] = malloc(sizeof(struct thread_param));
      thread_params[t]->name = argv[t + 1];
      //printf("file name: %s", argv[t+1]);
      thread_params[t]->wc = &word_counts;
      //printf("thread %d\n", t);
      rc = pthread_create(&threads[t], NULL, &readFile, (void*) thread_params[t]);
      //if (rc) {
      //  printf("ERROR; return code from pthread_create() is %d\n", rc);
      //  exit(-1);
      //}
    }
    for (int t = 0; t < nthreads; t++) {
      pthread_join(threads[t], NULL);
    }
    """
    for(int t = 0; t < nthreads; t++) {
      printf("thread %d\n", t);
      printf("file: %s\n", thread_params[t]->name);
    }
    """
    /* TODO */
  }

  /* Output final result of all threads' work. */
  wordcount_sort(&word_counts, less_count);
  fprint_words(&word_counts, stdout);
  return 0;
}
