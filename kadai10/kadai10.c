#include <stdio.h>
#include <string.h>

#define FALSE 0
#define TRUE (!FALSE)
#define L_NUM 256

static int strmatch(const char *T, const char *P, size_t *index)
{
  int i, j;
  int L[L_NUM];
  size_t n = strlen(T);
  size_t m = strlen(P);

  for (i = 0; i < L_NUM; i++) {
    L[i] = -1;
  }
  
  for (i = 0; i < m; i++) {
    L[(unsigned char)T[i]] = i;
  }

  i = 0;
  while (i < n - m + 1) {
    for (j = m - 1; T[i + j] == P[j] && j >= 0; j--);
    if (j == -1) {
      if (index) *index = (size_t)i;
      return TRUE;
    } else if (L[(unsigned char)T[i + j]] < j) {
      i += j - L[(unsigned char)T[i + j]];
    } else {
      i++;
    }
  }

  return FALSE;
}

int main(void)
{
  const char *string = "she sells sea shells ";
  const char *pattern = "sea";
  size_t index;

  if (strmatch(string, pattern, &index)) {
    printf("%d文字目に一致しました。\n", (int)(index + 1));
  } else {
    puts("一致しませんでした。");
  }

  return 0;
}
