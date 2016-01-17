#include <stdio.h>

void swap(int *a, int *b)
{
  int tmp = *a;
  *a = *b;
  *b = tmp;
}

void sort(int base[], size_t num)
{
  size_t l = 0;
  size_t r = 0;
  for (size_t i = 0; i < num - 1; i++) {
    size_t j;
    for (j = l; j < num - r - 1; j++) {
      if (j % 2 == 0) {
	if (base[j] > base[j + 1]) {
	  swap(&base[j], &base[j + 1]);
	}
      } else {
	if (base[j] < base[j + 1]) {
	  swap(&base[j], &base[j + 1]);
	}
      }
      if (j % 2 == 0) {
	r++;
      } else {
	l++;
      }
    }
  }
}

int main(void)
{
  int data[] = {17, 39, 1, 9, 5, 24, 2, 11, 23, 6};
  const size_t data_num = sizeof(data) / sizeof(data[0]);

  printf("入力: ");
  for (size_t i = 0; i < data_num; i++) {
    printf("%3d", data[i]);
  }
  printf("¥n");

  sort(data, data_num);

  printf("出力: ");
  for (size_t i = 0; i < data_num; i++) {
    printf("%3d", data[i]);
  }
  printf("¥n");

  return 0;
}

