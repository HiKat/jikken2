#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 9999
#define MIN 1
#define MAXELE 10

/*構造体の宣言。*/
struct list {
  int data;
  struct list *next;
};

////////////////////////////////////////////////////////////////////////
/*リストの先頭要素のポインタを渡すとリストを出力する関数。*/
void print_list(struct list *p) {
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
void free_list(struct list *top) {
  while (top != NULL) {
    struct list *p;
    p = top->next;
    free(top);
    top = p;
  }
}
/////////////////////////////////////////////////////////////////////////
/*リストの先頭要素のポインタと自然数を引数に取りリストにその自然数を挿入する関数insert。戻り値はinsert済みのリストの先頭要素のポインタ。*/
struct list *insert(struct list *l,int n) {
  /*リストの先頭要素がn以上の自然数であった場合。*/
  if(l->data >= n) {
    struct list *p;
    p = (struct list *)malloc(sizeof(struct list));
    p->next = NULL;
    p->data = n;
    p->next = l;
    l = p;
  }
  else {
    /*ポインタmを使って数値を挿入する位置を探査する。*/
    struct list *m;
    m = l;
    while(((m->next)->data) < n) {
      m = m->next;
      if(m->next == NULL) {
	break;
      }
    }
    /*m->next部分でポインタをつなぎ変えて挿入を行う。*/
    struct list *p1;
    p1 = (struct list *)malloc(sizeof(struct list));
    p1->next = NULL;
    p1->data = n;
    p1->next = m->next;
    m->next = p1;
  }
  return l;
}
////////////////////////////////////////////////////////////////////////
/*リストの先頭要素のポインタと自然数を引数にとりその自然数をリストの中から削除する関数delete。戻り値はdelete済みのリストの先頭要素のポインタ。*/
struct list *delete(struct list *top,int n) {
  /*先頭要素を指すポインタがNULL、すなわちリストが空の時。*/
  if(top == NULL) {
    return top;
  }
  else {
    /*先頭の要素がnと一致する場合。*/
    if(top->data == n){
      while(top->data == n) {
	struct list *p;
	p = top;
	top = top->next;
	free(p);
	if(top == NULL) {
	  break;
	}  
      }
      if(top != NULL) {
	delete(top,n);
      }
    }
    /*先頭の要素がnと一致しない場合。*/
    /*ポインタm1を先頭から１つずつずらしてnに一致する要素の手前の要素もしくは最後尾の要素で止める。*/
    else {
      /*ポインタmを使ってリスト中の自然数nと等しい要素を探査する。*/
      struct list *m1;
      m1 = top;
      while(m1->next != NULL) {
	/*m1が指す次の要素がnに一致する場合。*/
	if((m1->next)->data == n) {
	  struct list *m2;
	  m2 = m1;
	  /*ポインタm2を定義して、「m1が指す要素」と「m2が指す要素の次の要素」でnに一致する要素が挟まれるようにm2を移動させる。*/
	  while((m2->next)->data == n) {
	    m2 = m2->next;
	    if(m2->next == NULL) {
	      break;
	    }	      
	  }
	  /*間を取り除く。*/
	  struct list *p;
	  p = m1->next;
	  /*つなぎ替える。*/
	  m1->next = m2->next;
	  /*切り離す。*/
	  m2->next = NULL;
	  /*先頭がpで示され最後尾がm2で示されるリストのメモリ領域を解放する。*/
	  free_list(p);
	}
	/*一致しなければポインタを次にすすめる。*/
	else {
	  m1 = m1->next;
	}
      }
    }
    return top;
  }
}


////////////////////////////////////////////////////////////////////////
int main(void) {   
  struct list *top = NULL;
  struct list *end = NULL;
  struct list *p;
  int dat;
  int count = 1; /*キーボードから入力された適切な自然数の個数。これがリストに入る最大個数MAXELEに達すると数値の取得が終了する。*/
  char str[MAX];
  /*まず，MAXELE個の自然数をキーボードから入力し，それらを入力順に先頭から並べた リストを作り、画面に表示する．*/
  printf("%d個の%d以上%d以下の自然数からなる数値リストの取得を開始します。\n",MAXELE,MIN,MAX);
  do  {
    printf("%d個目の数字を半角数字で入力してください。",count);
    fgets(str,sizeof(str),stdin);
    if (atoi(str)<MIN || MAX<atoi(str)){
      fprintf(stderr,"入力された値は無効です。%d以上%d以下の自然数を半角で入力してください。\n",MIN,MAX);
    }
    else {
      dat = atoi(str);
      p = (struct list *)malloc(sizeof(struct list));
      p->next = NULL;
      p->data = dat;
      if(top == NULL){
	top = p;
      }
      else{
	end->next = p;
      }
      end = p;
      count++;
    }
  }while(count-1 < MAXELE);
  printf("計10個の自然数の取得が完了しました。取得した数値のリストは以下のようになりました。\n");
  print_list(top);
  /*自然数をキーボードから入力する度に，それを挿入した結果のリストを出力する．これを10回繰り返す．*/
  printf("これからリストに自然数を挿入する操作を10回行います。\n入力された自然数nがリスト中のn以上の自然数の中で一番先頭に近いものの直前に挿入されます。（nがリスト中のどの自然数よりも大きい場合は最後に挿入されます。) \n");
  int insertn;
  int count2 = 1;
  char str2[MAX]; 
  while(count2 < 11) {
    printf("%d回目の挿入操作を行います。%d以上%d以下の自然数を入力してください。",count2,MIN,MAX);
    fgets(str2,sizeof(str2),stdin);
    if (atoi(str2)<MIN || MAX<atoi(str2)){
      fprintf(stderr,"入力された値は無効です。%d以上%d以下の自然数を半角で入力してください。\n",MIN,MAX);
    }
    else {
      insertn = atoi(str2);
      /*insert(top,insertn);*/
      top = insert(top,insertn);
      print_list(top);	     
      count2++;
    }
  }
  printf("計10回の挿入操作が完了しました。\n");
  /*その後、自然数をキーボードから入力する度に，それを削除した結果のリストを出力する．これを10回繰り返す．*/
  printf("これからリストから自然数を削除する操作を10回行います。\n入力された自然数がリストの中から全て削除されます。\n");
  int deleten;
  int count3 = 1;
  char str3[MAX];
  while(count3 < 11) {
    printf("%d回目の削除操作を行います。%d以上%d以下の自然数を入力してください。",count3,MIN,MAX);
    fgets(str3,sizeof(str3),stdin);
    if (atoi(str3)<MIN || MAX<atoi(str3)){
      fprintf(stderr,"入力された値は無効です。%d以上%d以下の自然数を半角で入力してください。\n",MIN,MAX);
    }
    else {
      deleten = atoi(str3);
      top = delete(top,deleten);
      print_list(top);	     
      count3++;
    }
  }
  printf("計10回の削除操作が完了しました。\n");
  free_list(top);
  printf("使用していたメモリ領域を全て解放しました。\n");
  printf("すべての操作が終了しました。プログラムを正常に終了します。\n");
  return 0;
}
