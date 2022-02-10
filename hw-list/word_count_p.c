/*
 * Implementation of the word_count interface using Pintos lists and pthreads.
 *
 * You may modify this file, and are expected to modify it.
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

#ifndef PINTOS_LIST
#error "PINTOS_LIST must be #define'd when compiling word_count_lp.c"
#endif

#ifndef PTHREADS
#error "PTHREADS must be #define'd when compiling word_count_lp.c"
#endif

#include "word_count.h"

void init_words(word_count_list_t* wclist) { 
  list_init(&wclist->lst);
  pthread_mutex_init(&wclist->lock, NULL);
  /* TODO */
}

size_t len_words(word_count_list_t* wclist) {
  /* TODO */
  size_t len = 0;
  struct list_elem *e;
  for (e = list_begin(&wclist->lst); e != list_end(&wclist->lst); e = list_next(e)) {
    len++;
  }
  return len;
}

word_count_t* find_word(word_count_list_t* wclist, char* word) {
  /* TODO */
  struct list_elem *e;
  struct word_count *wc;
  for (e = list_begin(&wclist->lst); e != list_end(&wclist->lst); e = list_next(e)) {
    wc = list_entry(e, struct word_count, elem);
    if (strcmp(wc->word, word) == 0) {
      //printf("equal");
      return wc;
    }
  }
  return NULL;
}

word_count_t* add_word(word_count_list_t* wclist, char* word) {
  /* TODO */
  pthread_mutex_lock(&wclist->lock);
  word_count_t *wc = find_word(wclist, word);
  if (wc != NULL) {
    wc->count++;
  } else {
    wc = malloc(sizeof(word_count_t));
    if (wc == NULL) { 
      return wc;
    }
    wc->word = word;
    wc->count = 1;
    //printf("%d %s\n", wc->count, wc->word);
    
    struct list_elem *e = list_begin(&wclist->lst);
    list_insert(e, &wc->elem);
  }
  pthread_mutex_unlock(&wclist->lock);
  return wc;
}

void fprint_words(word_count_list_t* wclist, FILE* outfile) { 
  struct list_elem *e;
  struct word_count *wc;
  for (e = list_begin(&wclist->lst); e != list_end(&wclist->lst); e = list_next(e)) {
    wc = list_entry(e, struct word_count, elem);
    fprintf(outfile, "%d %s\n", wc->count, wc->word);
  }
  /* TODO */
}

void wordcount_sort(word_count_list_t* wclist,
                    bool less(const word_count_t*, const word_count_t*)) {
  /* TODO */
}
