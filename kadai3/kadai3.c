/*
Copyright (c) 2015 EF66_129
Released under the MIT license
http://opensource.org/licenses/mit-license.php
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define D_NUM 10000
#define D_MAX 20000
#define HASH_NUM (D_NUM * 2)
#define OUTPUT_FILENAME "hash.txt"

int hash_func(int value)
{
  return value % HASH_NUM;
}

int main(void)
{
  int D[D_NUM];
  int *Hash[HASH_NUM] = {0};
  FILE *fp;
  
  srand((unsigned)time(NULL));
  for (int i = 0; i < D_NUM; i++) {
    D[i] = rand() % D_MAX;
  }
  
  for (int i = 0; i < D_NUM; i++) {
    int k;
    for (k = hash_func(D[i]); Hash[k]; k++) {
      k = k % HASH_NUM;
    }
    Hash[k] = &D[i];
  }
#ifdef _MSC_VER
  if (fopen_s(&fp, OUTPUT_FILENAME, "w") == 0) {
#else
  if ((fp = fopen(OUTPUT_FILENAME, "w"))) {
#endif
    for (int i = 0; i < HASH_NUM; i++) {
      if (Hash[i]) {
	fprintf(fp, "%d\n", *Hash[i]);
      } else {
	fprintf(fp, "NULL\n");
      }
    }
    printf("結果を" OUTPUT_FILENAME "に書き込みました。\n");
  } else {
    printf("ファイルに結果を書き込めませんでした。\n");
    return -1;
  }

  return 0;    
  
}
