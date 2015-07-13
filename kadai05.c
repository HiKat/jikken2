#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 9999
#define MIN 1
#define MAXELE 10

/*構造体の宣言。*/
typedef struct list{
  int data;
  struct list *next;
}LIST;

////////////////////////////////////////////////////////////////////////
/*リストの先頭要素のポインタを渡すとリストを出力する関数。*/
void print_list(LIST *p) {
  if(p == NULL) {
    printf("リストは空です。");
  }
  else {
    while (p != NULL) {
      printf("%d ",p->data);
      p = p->next;
    }
  }
  printf("\n");
 }
/////////////////////////////////////////////////////////////////////////
/*リストの先頭のポインタを渡されるとそのリストのメモリ領域を全て解放する関数*/
void free_list(LIST *top){
  while (top != NULL) {
    LIST *p;
    p = top->next;
    free(top);
    top = p;
  }
}
////////////////////////////////////////////////////////////////////////
/*挿入ソートのソーティングの本体となる関数。第一引数にリストの先頭のポインタ、第二引数に挿入する（m+1番目の要素）数値をとる。*/
LIST *insert_soating(LIST *top,int n){
  /*配列の最初から挿入する場所を探していく。先頭からnよりも大きな要素に当たるまで探す。*/
  /*実際はnと等しい要素、もしくはnよりも大きな要素を発見すればその直前にnを挿入するようにしても問題はなく、わずかながらもそのほうが探査の数が少なくて済む場合があるためこのように実装した。*/
  /*探査部分*/
  /*先頭要素がn以上の数である場合。先頭にnを追加する。*/
  if((top->data) >= n){
    LIST *new_top;
    new_top = (LIST *)malloc(sizeof(LIST));
    new_top->next = NULL;
    new_top->data = n;
    new_top->next = top;
    top = new_top;
  }
  /*先頭要素がn以上の数でない場合。*/
  else{
    LIST *l;
    l = top;
    if(l->next != NULL){
      while(((l->next)->data) < n){
	l = l->next;
	if(l->next == NULL){
	  break;
	}
      }
    }
    /*lが指す要素の次の要素が新しい要素が入る位置。つなぎ替えを行う。*/
    LIST *new_p;
    new_p = (LIST *)malloc(sizeof(LIST));
    new_p->next = NULL;
    new_p->data = n;
    new_p->next = l->next;
    l->next = new_p;
  }
  return top;
}
////////////////////////////////////////////////////////////////////////
int main(void) {   
  LIST *top;
  int dat;
  int input_list[MAXELE];
  int count = 1; /*キーボードから入力された適切な自然数の個数。これがリストに入る最大個数MAXELEに達すると数値の取得が終了する。*/
  char str[MAX];
  printf("%d個の%d以上%d以下の自然数からなる数値リストの取得を開始します。\n",MAXELE,MIN,MAX);
  while(count <= MAXELE){
    printf("%d個目の数字を半角数字で入力してください。",count);
    fgets(str,sizeof(str),stdin);
    if (atoi(str) < MIN || MAX < atoi(str)){
      fprintf(stderr,"入力された値は無効です。%d以上%d以下の自然数を半角で入力してください。\n",MIN,MAX);
    }
    else {
      dat = atoi(str);
      input_list[count-1] = atoi(str);;
      /*入力した数値が1番目の要素の時。*/
      if(count == 1){
	LIST *p;
	p = (LIST *)malloc(sizeof(LIST));
	p->next = NULL;
	p->data = dat; 
	top = p;
      }
      /*そうでない時。*/
      else{
	top = insert_soating(top,dat);
      }
      count++;
    }
  }
  printf("計10個の自然数の取得が完了しました。取得した数値のリストは以下のようになりました。\n");
  int i;
  for(i = 0;i < MAXELE;i++){
    printf("%d ",input_list[i]);
  }
  printf("\nこれをソートした結果は以下のようになりました。\n");     
  print_list(top);
  free_list(top);
  printf("使用していたメモリ領域を全て解放しました。\n");
  printf("すべての操作が終了しました。プログラムを正常に終了します。\n");
  return 0;
}
