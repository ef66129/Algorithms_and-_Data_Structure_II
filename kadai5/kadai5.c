#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* 各種マクロ */
#define PARENT(n) ((n + 1) / 2 - 1)
#define LEFT_CHILD(n) ((n + 1) * 2 - 1)
#define RIGHT_CHILD(n) (LEFT_CHILD(n) + 1)

/* 比較関数のtypedef */
typedef int (*heap_sort_compare)(void *a, void *b);

/* プロトタイプ宣言 */
void swap(void *a, void *b, size_t size);
void push_heap(void *base, void *ptr, size_t count, size_t size, heap_sort_compare cmp);
void delete_maximum(void *base, size_t count, size_t size, heap_sort_compare cmp);
void heap_sort(void *base, size_t count, size_t size, heap_sort_compare cmp);
int compare(void *a, void *b);

/* 2つの値を入れ替える関数 */
void swap(void *a, void *b, size_t size)
{
#if __STDC_VERSION__ >= 199901L
  /* variable length array (VLA) */
  char tmp[size];
#else
  char *tmp = malloc(size);
#endif
  memcpy(tmp, a,   size);
  memcpy(a,   b,   size);
  memcpy(b,   tmp, size);
#if __STDC_VERSION__ < 199901L
  free(tmp);
#endif
}

void push_heap(void *base, void *ptr, size_t count, size_t size, heap_sort_compare cmp)
{
  for (;count > PARENT(count)
	 && cmp((char *)base + size * count, (char *)base + size * PARENT(count)) > 0;
       count = PARENT(count)) {
    swap((char *)base + size * count, (char *)base + size * PARENT(count), size);
  }
}

void delete_maximum(void *base, size_t count, size_t size, heap_sort_compare cmp)
{
  size_t i;
  
  swap(base, (char *)base + size * (count - 1), size);
  count--;

  for (i = 0; i < count; i++) {
    size_t l_ch = LEFT_CHILD(i);
    size_t r_ch = RIGHT_CHILD(i);
    size_t target = i;

    if (l_ch >= count) return;                                         /* 子を持つかどうかを判定 */
    if (cmp((char *)base + size * l_ch, (char *)base + size * i) > 0)  /* 親子の値をを比較 */
      target = l_ch;
    if (r_ch < count                                                   /* 子が2つの場合 */
	&& cmp((char *)base + size * r_ch, (char *)base + size * target) > 0)
      target = r_ch;
    if (target == i) return;
    swap((char *)base + size * i, (char *)base + size * target, size); /* 親子の値を交換 */
  }
}

void heap_sort(void *base, size_t count, size_t size, heap_sort_compare cmp)
{
  size_t i;

  /* データをヒープに並べる */
  for (i = 1; i < count; i++) {
    push_heap(base, (char *)base + size * i, i, size, cmp);
  }
  /* ヒープからデータを取り出し、末尾に並べていく */
  for (i = 0; i < count; i++) {
    delete_maximum(base, count - i, size, cmp);
  }
}

/* 
 * 比較関数
 * a > b  : >0
 * a == b : 0
 * a < b  : <0
 */
int compare(void *a, void *b)
{
  return *(int *)a - *(int *)b;
}

int main(void)
{
  int data[] = {17, 39, 1, 9, 5, 24, 2, 11, 23, 6};
  size_t data_count = sizeof(data) / sizeof(data[0]);
  size_t i;

  heap_sort(data, data_count, sizeof(data[0]), compare);

  for (i = 0; i < data_count - 1; i++) {
    printf("%2d, ", data[i]);
  }
  printf("%2d\n", data[i]);

  return EXIT_SUCCESS;
}
