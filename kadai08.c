#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdlib.h>

#define MAXELEMENT 50 
#define MIN 1
#define MAX 9999 
/*ソートに使用する数値リストの各要素の最大、最小値。*/
/*///////////////////////////////////////////////////*/
/*ソート対象となる数値のリストを作成。引数として与えられた配列にキーボードから入力した数値を格納する。引数として配列の要素数を返す。*/
int getlist(int list[]){
  char str[MAX];
  int val;
  int i = 1,n = 0;
  char *p = "end\n";

  fprintf(stderr,"ソーティングする数値のリストを作成します。数値の入力を開始します。ただし入力可能なリストの要素は%d個以下、1以上9999以下の自然数（半角数字）とします。\n入力を終了する際はendを入力してください。\n",MAXELEMENT);
  while(i <= MAXELEMENT){
    printf("%d個目の要素を取得します。数値もしくはendを入力してください。",i);
    fgets(str, sizeof(str), stdin);
    if(strcmp(p, str) == 0){
      break;
    }
    else{
      if(atoi(str) < MIN || MAX < atoi(str)){
	fprintf(stderr,"入力された数は無効です。%d以上%d以下の自然数を半角で入力してください。",MIN,MAX);
      }
      else {
	val = atoi(str);
	list[i-1] = val;
	i++;
      }
    }   
  }
  printf("リスト(%d個)の取得が完了しました。\n",i-1);
  n = i-1;
  /*以下で取得した要素を全て列挙して確認する。*/
  printf("取得したリストは{\n");
  for (i = 0 ; i < n ; i++) {
    if (i == 0){
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
  return n;
}
/*/////////////////////////////////////////////////////*/
/*ソーティング本体*/
/*引数として配列と2つの整数startとendをとる。与えられた配列のstart番の要素からend番の要素の間に挿入ソートを適用する。*/
void soating(int array[],int start,int end){
  if(start == end){
    ;
  }
  else{
    int piv;
    piv = array[0];/*ピボットの選択*/
    int left_i = start;
    int left_change = start;
    int right_i = end;
    int right_change = end;
    int temp_array;/*要素を入れ替える際に必要となる空間*/
    while(left_i < right_i){
      /*１ ピボット以上の数値を配列先頭から検索*/
      while(left_i <= end+1){
	if(piv <= array[left_i]){
	  left_change = left_i;
	  break;
	}
	else{
	left_i++;
	}
      }
      /*２ ピボット未満の数値を配列末尾から検索*/
      while(right_i <= end+1){
	if(piv > array[right_i]){
	right_change = right_i;
	break;
	}
	else{
	  right_i--;
	}
      }
    if(left_i >= right_i){
      break;
    }
    /*３ それぞれを交換する*/
    temp_array = array[left_change];
    array[left_change] = array[right_change];
    array[right_change] = temp_array;
    /*インクリメント、デクリメント*/
    left_i++;
    right_i--;
    }
    soating(array,start,left_change);
    soating(array,left_change+1,end);
  }
}
/*//////////////////////////////////////////////////////*/
/*リストの出力*/
/*指定があるため要素は10個おきに改行して表示する。*/
/*numoflistは引数としてとった配列の要素数*/
void print_list(int list[],int numoflist){
  int i;
  printf("生成されたリストは{\n");
  for (i = 0 ; i < numoflist ; i++){
    if (i==0){
      printf("%4d ",list[0]);
    }
    else {
      if (i%10){
	printf("%4d ",list[i]);
      }
      else {	
	printf("\n%4d ",list[i]);
      }
    }
  }
  printf("\n}です。\n");
}
/*//////////////////////////////////////////////////////*/
/*実行*/
int main(void)
{
  int array[MAXELEMENT];
  int arraysize = getlist(array);
  print_list(array,arraysize);
  printf("この配列にクイックソートを適用します。");
  soating(array,0,arraysize-1);
  print_list(array,arraysize);
  return 0;
}
