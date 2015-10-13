# kadai2
二分探索

## ソート
ソートはクイックソートで行った。
中身はポインタを使うこと以外は教科書のものと大体同じ。
```
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
```

## 二分探索
これも教科書と一緒。
違うのは再帰を使っているところ、ポインタを使っているところ、探索範囲が1個になった時の挙動くらい。
戻り値は配列の要素に対するポインタで、見つからなければNULLになるので、NULLかどうかを調べれば見つかったかが分かる。

回数のカウントはポインタを渡して値を増やしていくことでカウントしていく。

```
int *find(int value, const int *first, const int *last, int *count)
{
  const int *mid = first + ((last - first) / 2);

  if (count) (*count)++;
  
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
```

## 結果の出力
データ番号は配列の先頭ポインタと`find()`の引き算で分かる。
型は`ptrdiff_t`となるので`%td`で出力する。  
MSVC++は`%td`が使えないので`%Id`になる。
使い分けは`_MSC_VER`マクロが定義されているかどうかの判別をすれば可能。

```
#ifdef _MSC_VER
#  define PRIdPTRD "Id"
#else
#  define PRIdPTRD "td"
#endif
```

```
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
```