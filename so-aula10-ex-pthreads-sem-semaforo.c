/*
  Programa que cria duas threads. Cada thread soma um valor
  a uma variável global compartilhada.

  Autor: Avelino Zorzo
  Data: 02.04.2012

  Quais os valores impressos? E na segunda vez que o programa executa? 
  Por quê?

*/

#include <stdio.h>
#include <pthread.h>
pthread_t tid1,tid2;  /* Descritores para as threas */int a = 0;            /* Variável global que será compartilhada entre as threads */

    
/* Rotina a ser executada por uma das threads */
void * p1 () {  int i ;
  
  for(i=0; i<1000000; i++) {       a = a + 2 ;
  }}
/* Rotina a ser executada por uma das threads */
void * p2 () {    int i;  
  for (i=0; i<1000000; i++) {       a = a + 5 ;   
  }}

int main() {  int result ;
  result = pthread_create(&tid1, NULL, p1, NULL);  result = pthread_create(&tid2, NULL, p2, NULL);
  pthread_join(tid1,NULL);  printf("Thread 1 finished: %d\n", a);

  pthread_join(tid2,NULL);  printf("Thread 2 finished: %d\n", a);

  return 0;
}