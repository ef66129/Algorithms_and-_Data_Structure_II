#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define D_NUM 10000
#define D_MAX 20000
#define K_NUM 5
#define HASH_NUM 15000

/**
 * @brief ハッシュ関数
 */
int hash_func(int value)
{
  return value % HASH_NUM;
}

int main(void)
{
  int D[D_NUM];              //!< データ
  int K[K_NUM];              //!< 探索するデータ
  int *Hash[HASH_NUM] = {0}; //!< ハッシュ
  int sum_count       = 0;   //!< 探索回数の合計
  
  // 変数の初期化
  srand((unsigned)time(NULL));
  for (int i = 0; i < D_NUM; i++) {
    D[i] = rand() % D_MAX;
  }
  for (int i = 0; i < K_NUM; i++) {
    K[i] = rand() % D_MAX;
  }
  
  // ハッシュの作成
  // ハッシュ関数の結果から格納場所を決める
  // すでにデータがある(!=NULL)場合は1つずらす
  for (int i = 0; i < D_NUM; i++) {
    int k;
    for (k = hash_func(D[i]); Hash[k]; k++) {
      k = hash_func(k);
    }
    Hash[k] = &D[i];
  }

  // データの探索
  for (int i = 0; i < K_NUM; i++) {
    int k;
    int count = 0;
    // ハッシュ関数からデータの場所を決める
    // データが見つかるかNULLに当たるまで探索を実行する
    for (k = hash_func(K[i]); Hash[k]; k++) {
      count++;
      if (K[i] == *Hash[k]) {
	break;
      }
    }
    printf("%d回目の探索\n", i + 1);
    printf("探索データ: %d\n", K[i]);
    if (Hash[k]) {
      printf("データ番号: %d\n", k);
    } else {
      printf("データは見つかりませんでした。\n");
    }
    putchar('\n');
    sum_count += count;
  }

  printf("探索回数の平均: %f\n", (double)sum_count / K_NUM);

  return 0;
}
