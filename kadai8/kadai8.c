#include <stdio.h>
#include <stdlib.h>

#define C 5 // ナップサックの容量
#define N 4

static const int weight[N] = {2, 1, 4, 5};
static const int value[N]  = {2000, 3000, 3000, 4000};
static int z[N];
static double x[N] = {0};

static int compare(const void *a, const void *b)
{
  return *(int *)b - *(int *)a;
}

int main(void)
{
  for (int i = 0; i < N; i++) {
    z[i] = value[i] / weight[i];
  }

  qsort(z, N, sizeof(int), compare);

  for (int j = 0, sum = 0; sum < C; j++) {
    int k;
    for (k = 0; z[j] != value[k] / weight[k]; k++);

    if (weight[k] <= C - sum) {
      x[k] = 1.0;
      sum += weight[k];
    } else {
      x[k] = (double)(C - sum) / weight[k];
      sum = C;
    }
  }

  for (int i = 0; i < N; i++) {
    printf("値段 %d円 重さ %dkg の荷物を %.1f個(%.1fkg)¥n", value[i], weight[i], x[i], x[i] * weight[i]);
  }
  return 0;
}

