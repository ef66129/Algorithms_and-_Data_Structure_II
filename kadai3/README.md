# kadai3
ハッシュ

## 前準備
まず、ハッシュの大きさを決める。  
とりあえず、データの個数の２倍とした。
`#define HASH_NUM (D_NUM * 2)`

また、ハッシュの中身をファイルに出力するので、ファイル名も定義しておいた。
`#define OUTPUT_FILENAME "hash.txt"`

## ハッシュ関数
ハッシュ関数はハッシュの個数で割った余りとした。
```
int hash_func(int value)
{
  return value % HASH_NUM;
}
```

## ハッシュ
ハッシュはポインタの配列とした。
`int *Hash[HASH_NUM] = {0};`
ハッシュにはアドレスを入れていき、何もなければ`NULL`になる。

## 格納
ハッシュ関数の結果を基ににして入れていく。
既に入っている場合は１つずつずらしていく。

```
  for (int i = 0; i < D_NUM; i++) {
    int k;
    for (k = hash_func(D[i]); Hash[k]; k++) {
      k = k % HASH_NUM;
    }
    Hash[k] = &D[i];
  }
```

## 結果の出力
ファイルに出力する。
`fopen_s`関数はC99ではMSVC++の独自拡張なので`#ifdef`を使っている。
```
#ifdef _MSC_VER
  if (fopen_s(&fp, OUTPUT_FILENAME, "w") == 0) {
#else
  if ((fp = fopen(OUTPUT_FILENAME, "w"))) {
#endif
    for (int i = 0; i < HASH_NUM; i++) {
      if (Hash[i]) {
	fprintf(fp, "%d¥n", *Hash[i]);
      } else {
	fprintf(fp, "NULL¥n");
      }
    }
    printf("結果を" OUTPUT_FILENAME "に書き込みました。¥n");
  } else {
    printf("ファイルに結果を書き込めませんでした。¥n");
    return -1;
  }
```