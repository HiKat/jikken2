#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXELEMENT 50 
/*ソートに使用できる数値のリストの最大要素数をMAXELEMENTとしてマクロに定義する。*/
#define MIN 1
#define MAX 9999 
/*ソートに使用する数値リストの各要素の最大、最小値。*/


/*///////////////////////////////////////////////////*/
/*ソート対象となる数値のリストを作成*/
/*作成した数値のリストの要素数をnumoflistとして大域変数を作成する。*/
int getlist(int newlist[])
{
  int list[MAXELEMENT];
  char str[MAX];
  int val;
  int i=0,j=0,n=0;
  char *p = "end\n";

  fprintf(stderr,"ソーティングする数値のリストを作成します。数値の入力を開始します。ただし入力可能なリストの要素は%d個以下、1以上9999以下の自然数（半角数字）とします。\n入力を終了する際はendを入力してください。\n",MAXELEMENT);

  do {
    fprintf(stderr,"数値を入力してください。");
    fgets(str, sizeof(str), stdin);
    if (strcmp(p, str) == 0){
      break;
    }
    else {
      if (atoi(str)<MIN || MAX<atoi(str)){
	fprintf(stderr,"%d以上%d以下の自然数を半角で入力してください。",MIN,MAX);
      }
      else {
	val = atoi(str);
	list[i] = val;
	i++;
      }
    }   
  } while(i < MAXELEMENT);
  
  n = i;

  for(j = 0; j < n; j++) {
    newlist[j] = list[j];
  }

  printf("リスト(%d個)の取得が完了しました。\n",i);
  printf("取得したリストは{\n");
  
  for (i = 0 ; i < n ; i++) {
    if (i==0){
      printf("%4d ",newlist[0]);
    }
    else {
      if (i%10){
	printf("%4d ", newlist[i]);
      }
      else {
	printf("\n%4d ", newlist[i]);
      }
    }
  }
  printf("\n}です。\n");
  return n;
}


/*/////////////////////////////////////////////////////*/
/*ソーティング本体*/
/*ソート済みの数値リストとして配列soatedlistを作成する。*/
/*バブルソート本体。データ列を X1, ... ,Xn として、X1 > X2が真ならばそれらを入れ換える。これを繰り返す。ソート後は X1<X2<...<Xn となる。*/
/*listは入力された数値リストを入れた配列。*/
/*newlistはソート済みの数値リストを入れる配列。*/
void soating(int list[],int numoflist) 
{
  int i,j;
  int copy1,copy2;

  for (i = 0; i < numoflist; i++){
    for (j = 0; j < (numoflist-i-1); j++){ 
      if (list[j] > list[j+1]){
	copy1 = list[j];
	copy2 = list[j+1];
	list[j] = copy2;
	list[j+1] = copy1;
      }
    }
  }
}

/*//////////////////////////////////////////////////////*/
/*リストの出力*/
/*指定があるため要素は10個おきに改行して表示する。*/
void print_list(int list[],int numoflist)
{
  int i;

  printf("生成されたリストは{\n");
  for (i = 0 ; i < numoflist ; i++){
    if (i==0){
      printf("%4d ",list[0]);
    }
    else {
      if (i%10){
	printf("%4d ", list[i]);
      }
      else {
	printf("\n%4d ", list[i]);
      }
    }
  }
  printf("\n}です。\n");
}

/*//////////////////////////////////////////////////////*/
/*実行*/
int main(void)
{
  int inputlist[MAXELEMENT];
  /*ソーティングに用いる数値リストを格納する配列をinpulistとして定義。*/

  int numoflist = getlist(inputlist);
  /*getlistの実行と同時にソーティングに用いる数値のリストの要素数をnumoflistとして定義、初期化。*/
  /*numoflistはinpulistやsoatedlistとは違って配列ではないため値が関数の中で書き換えられても書き換えられたものは、いわばnumoflistのコピーのようなもので、関数の外を出ると元のコピー元の値が参照されてしまう。そのため関数getlistの戻り値をnumoflistの値にしてこのように初期化する必要がある。*/

  soating(inputlist,numoflist);
  print_list(inputlist,numoflist);
  return 0;
}
