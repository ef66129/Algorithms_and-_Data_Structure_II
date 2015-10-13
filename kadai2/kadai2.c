/*
Copyright (c) 2015 EF66_129
Released under the MIT license
http://opensource.org/licenses/mit-license.php
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#ifdef _MSC_VER
#  define PRIdPTRD "Id"
#else
#  define PRIdPTRD "td"
#endif

#define D_NUM 10000 // データの数
#define D_MAX 20000 // データの最大値
#define K_NUM 5     // 検索する回数

void swap(int *a, int *b)
{
  int w = *a;
  *a = *b;
  *b = w;
}

/**
 * 概要:  クイックソートを行う関数
 * first: 配列の最も前のアドレス
 * last:  配列の最も後ろのアドレス
 */
void sort(int *first, int *last)
{
  int *f = first;
  int *l = last;
  int p = *(first + (last - first) / 2);
  
  if (first > last) return;
  for (;;) {
    while(*f < p) f++;
    while(p < *l) l--;
    if (f >= l) break;
    swap(f++,l--);
  }
  sort(first,f- 1);
  sort(l + 1,last);
}
  

/**
 * 概要:  二分探索を行う関数
 * value: 検索する値
 * first: 検索対象の配列のうち、もっとも先頭のアドレス
 * last:  検索対象の配列のうち、もっとも後ろのアドレス
 * count: 回数をカウントする変数へのポインタ
 * 戻り値: 配列の中で値があるアドレス、見つからなかったらNULL
 */
int *find(int value, const int *first, const int *last, int *count)
{
  const int *mid = first + ((last - first) / 2);

  (*count)++;
  
  if (first <= last) {
    if (*mid == value) {
      return (int *)mid;
    } else if (*mid > value) {
      return find(value, first, mid - 1, count);
    } else {
      return find(value, mid + 1, last, count);
    }
  } else {
    return NULL;
  }
}

int main(void)
{
  int D[D_NUM];
  int k[K_NUM];
  int count_sum = 0;

  srand((unsigned)time(NULL));

  for (int i = 0; i < D_NUM; i++) {
    D[i] = rand() % D_MAX;
  }
  sort(&D[0], &D[D_NUM - 1]);

  for (int i = 0; i < K_NUM; i++) {
    k[i] = rand() % D_MAX;
  }

  for (int i = 0; i < K_NUM; i++) {
    int count = 0;
    int *result;

    printf("%d回目: %dを探索します。\n", i + 1, k[i]);
    result = find(k[i], &D[0], &D[D_NUM - 1], &count);
    if (result) {
      printf("データが見つかりました。\n");
      printf("探索回数: %d\n", count);
      printf("探索データのあったデータ番号: %" PRIdPTRD "\n", result - D);
    } else {
      printf("データが見つかりませんでした。\n");
      printf("探索回数: %d\n", count);
    }
    putchar('\n');
    count_sum += count;
  }

  printf("探索が終了するまでの平均回数: %f\n", (double)count_sum / K_NUM);

  return 0;
}
