#include <stdio.h>
#include <stdlib.h>/*exitを使用するためのヘッダファイル*/
#include <string.h>
#define MAXOFARRAYSIZE 20000
#define FILENAME "sorting.data"/*数値データの入ったファイル名*/
#define MAX 32767
#define SOATING0 "クイックソート"
#define SOATING0_FUNC quick_soating
#define SOATING1 "バブルソート"
#define SOATING1_FUNC bubble_soating

typedef void(*ARRAY_FUNC)(long array[],int x,int y);//関数ポインタを要素に持つ配列の宣言を簡略化するため


///////////////////////////////////////
int make_array(FILE *ip,long array[]){
  if(ip == NULL){ 
    fprintf(stderr, "%sを正常に開くことが出来ませんでした。異常を検出したためプログラムを強制終了しました。\n",FILENAME);
    exit(1);/*異常終了*/
  } 
  printf("%sの数値を読み込みます。\n",FILENAME);
  char buf[MAX];
  char *tp;/*strtokで文字列bufを処理するための文字列の先頭のポインタ。ここでbufは例えば「3198 4399 2962 1572 2704 395 2537 46 672 0」というような数値が空白で区切られたもの。*/
  char *buf_p;
  int i = 0;
  while(1){
    if(fgets(buf,sizeof(buf),ip) == NULL){
      break;
    }
    else{
      /*strtokでbufから数値列を空白で分解していく*/
      buf_p = buf;
      tp = strtok(buf_p," ");
      array[i] = atoi(tp);
      while(tp != NULL){
	tp = strtok(NULL," ");
	i++;
	if(tp != NULL){
	  array[i] = atoi(tp);
	}
      }
    }
  }
  fclose(ip);
  printf("%sからの数値の読み込みが完了しました。\n",FILENAME);
  return i;
}
//////////////////////////////////////
void print_array(long array[],int arraysize){
  int i;
  printf("生成された配列の要素は順に{\n");
  for (i = 0;i < arraysize;i++){
    if (i == 0){
      printf("%4ld ",array[0]);
    }
    else {
      if (i%10){
	printf("%4ld ",array[i]);
      }
      else {	
	printf("\n%4ld ",array[i]);
      }
    }
  }
  printf("\n}です。\n");
}
//////////////////////////////////////
void quick_soating(long array[],int start,int end_plus_one){
  int end = end_plus_one-1;
  int temp_array;
  int piv;
  piv = array[start];
  int left_i = start;
  int left_need_to_change = 0;
  int right_i = end;
  int right_need_to_change = 0;
  if(end == start){
    ;
  }
  else{
    while(left_i+1 < right_i){
      if(piv <= array[left_i]){
	while(left_i+1 < right_i){
	  if(piv > array[right_i]){
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
      else{
	if(left_i+1 == right_i){
	  break;
	}
	else{
	  left_i++;
	}
      }
    }
    if(piv <= array[left_i]){
      left_need_to_change = 1;
    }
    if(piv > array[right_i]){
      right_need_to_change = 1;
    }
    if(left_need_to_change == 1 && right_need_to_change == 1){
      temp_array = array[left_i];
      array[left_i] = array[right_i];
      array[right_i] = temp_array;
    }
    if(start+1 < end){
      if(left_need_to_change == 1 && right_need_to_change == 0){
	if(left_i == start){
	  ;
	}
	else{
	  left_i--;
	  right_i--;
	}
      }
      if(left_need_to_change == 0 && right_need_to_change == 1){
	if(right_i == end){
	  left_i++;
	  right_i++;
	}
	else{
	  ;
	}
      }
      quick_soating(array,start,left_i+1);
      quick_soating(array,right_i,end+1);
    }
    else{
      ;
    }
  }
}
//////////////////////////////////////
void bubble_soating(long array[],int a,int arraysize) {
  int i,j;
  int temp;
  for (i = 0; i < arraysize; i++){
    for (j = 0; j < (arraysize-i-1); j++){ 
      if (array[j] > array[j+1]){
	temp = array[j];
	array[j] = array[j+1];
	array[j+1] = temp;
      }
    }
  }
}
//////////////////////////////////////
int main(void){  
  /*読み込み用にmylecture.txtを開く*/
  char *fname = FILENAME;
  FILE *ip;
  ip = fopen(fname,"r");
  long array[MAXOFARRAYSIZE];
  int arraysize = make_array(ip,array);
  char com[256];
  int input_number;/*入力されたコマンドの数字*/
  print_array(array,arraysize);
  while(1){
    printf("コマンドを入力してください。%sを行う場合は%dを入力、%sを行う場合は%dを入力してください。コマンドに応じたソーティングが取得された数値配列に対して実行されます。\n",SOATING0,0,SOATING1,1);
    fgets(com,sizeof(com),stdin);
    if(atoi(com) != 0 && atoi(com) != 1){
      
fprintf(stderr,"入力されたコマンドは無効です。入力をやり直してください。\n");
    }
    else{
      input_number = atoi(com);
      break;
    }
  }
  /*関数ポインタの宣言*/
  ARRAY_FUNC array_func[] = {
    SOATING0_FUNC,
    SOATING1_FUNC
  };
  printf("ソートを開始します。\n");
  (*array_func[input_number])(array,0,arraysize);
  printf("ソートが完了しました。\n");
  printf("結果を出力します。\n");
  print_array(array,arraysize);
  printf("すべての操作が完了しました。\n");
}
//////////////////////////////////
