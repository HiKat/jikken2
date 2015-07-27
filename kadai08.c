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
  int temp_array;/*要素を入れ替える際に必要となる空間*/
  int piv;
  piv = array[start];/*ピボットの選択*/
  int left_i = start;
  int left_need_to_change = 0;
  int right_i = end;
  int right_need_to_change = 0;
  /*配列の要素数が1個の時*/
  if(end == start){
    ;
  }
  /*配列の要素数が２個以上の時*/
  else{
    /*left_iを左から動かしてピボットとなる数以上の要素を探していく。見つかれば今度は左端からright_iを動かしてピボットとなる数未満の要素を探していく。２つともが見つかりペアができればそれらを交換してそこから再びペアを探し始める。*/
    /*以降のソーティングでポイントとなっているのはleft_iとright_iが隣り合った位置に来るまで交換可能なペアを探査していくのだが、２つが隣り合う位置に来た時に各ループを脱出するような仕様にしているのでループを脱出した辞典で再びleft_iとright_iが指す要素が交換可能かどうかを調べる必要がある。*/
    /*そうやって確認した結果、また新たに交換可能なペアが出来る場合は交換すれば良い。しかし更に複雑なのは、left_iもしくはright_i番の要素は最初に探査を行った時の条件に適する要素であるにもかかわらずもう一方がそうでない場合である。これらの場合については別個に考える必要が有るため一番外側のwhile文を抜けた"<--------------"で示す場所で考慮してある。*/
    /*ただしこのwhile文はソートする配列の要素数が２個の時はスキップされる。*/
    while(left_i+1<right_i){
      /*見つかった場合*/
      if(piv <= array[left_i]){
	while(left_i+1<right_i){
	  if(piv > array[right_i]){
	    /*交換するペアが見つかった場合*/
	    temp_array = array[left_i];
	    array[left_i] = array[right_i];
	    array[right_i] = temp_array;
	    break; 
	  }
	  else{
	    right_i--;
	  }
	}
      }
      /*見つからなかった場合*/
      else{
	if(left_i+1 == right_i){
	  break;
	}
	else{
	  left_i++;
	}
      }
    }
    //   <--------------    この関数の暴徒のコメントで述べたのがここからのコードである。
    /*left_i、right_i番の要素を要素をそれぞれピボットと照らし合わせる。条件に適する場合は用意した0-1変数、left_need_to_change、right_need_to_changeの値が1になる。*/
    /*array[left_i]を確認*/
    if(piv <= array[left_i]){
      left_need_to_change = 1;
    }
    /*array[right_i]を確認*/ 
    if(piv > array[right_i]){
      right_need_to_change = 1;
    }
    if(left_need_to_change == 1 && right_need_to_change == 1){
      temp_array = array[left_i];
      array[left_i] = array[right_i];
      array[right_i] = temp_array;
    }
    /*ソートする配列の要素数が２個の時はここで終了。*/
    if(start+1 < end){
      if(left_need_to_change == 1 && right_need_to_change == 0){
	if(left_i == start){//left_iはstart異常でなければならないので
	  ;
	}
	else{
	  left_i--;
	  right_i--;
	}
      }
      if(left_need_to_change == 0 && right_need_to_change == 1){
	if(right_i == end){//right_iはend以下でなければならないので
	  left_i++;
	  right_i++;
	}
	else{
	  ;
	}
      }
      /* 左右にわかれた配列のそれぞれで同様のアルゴリズムを再帰的に適用する*/
      soating(array,start,left_i);
      soating(array,right_i,end);
    }
    else{
      ;
    }
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
  printf("この配列に昇順のクイックソートを適用します。\n");
  soating(array,0,arraysize-1);
  print_list(array,arraysize);
  return 0;
}
