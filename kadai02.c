#include <stdio.h>
#include <stdlib.h>/*exitを使用するためのヘッダファイル*/
#include <string.h>



int main(void)
  
{
  
  /*講義の曜日時限を引数に格納する*/
  char *timelist[] = {"Mo4", "Mo3", "Tu3", "We1", "Th3", "Fr1"};  

  FILE *ip,*op;
  
  /*読み込み用にmylecture.txtを開く*/
  ip = fopen("mylecture.txt","r");
  if(ip == NULL){
  fprintf(stderr, "mylecture.txtを開くことが出来ませんでした。異常を検出したためプログラムを強制終了しました。\n");
    exit(1);/*異常終了*/
  }
  
  /*書き込み用にmylecture.dataを開き、なければ新しく作成する。*/
  op = fopen("mylecture.data","w");
  if(op == NULL){
  fprintf(stderr, "mylecture.dataを開く、もしくは作成することが出来ませんでした。異常を検出したためプログラムを強制終了しました。\n");
    exit(1);/*異常終了*/
  }
  
  
  /*mylecture.txtから講義名を読み込んで引数に格納する*/
  char lecture[256];
  
  int i;
  int j;
  int numoflectures; 
  char k[256];
 
  /*mylecture.txtに記述されている講義数を行数から読み取るためのfor文。行数（講義数）はj*/
  for(j = 0; fgets(k, 256, ip) != NULL; j++){
    ;
  }

  numoflectures = j;
  rewind(ip);/*直前のfgetを使ったループでファイルの読み込み位置がEOFの位置になっている。したがってこれをrewindでもとに戻す。*/

  for(i = 0; i < numoflectures; i++){
    fgets(lecture, 256, ip);
    fprintf(op,"%s\t",timelist[i]);
    fprintf(op,"%s",lecture);
  }
	
  
  
  fclose(ip);
  fclose(op);
  printf("mylecture.dataの作成が終了しました。\n");
 
}
 

