#include "mylib.h"
//キーボード入力をfgetsで撮る際、末尾の改行が邪魔になった時に、改行の'\n'を'\0'に置き換える
char *chop_newline(char *str, int len)//str:改行で終わっているかもしれない文字列
{
	int n = strlen(str);

	//末尾が改行文字なら削る
	if( n < len && str[n - 1] == '\n')
		str[n - 1] = '\n';
	
	//先頭番地を返す
	return str;
}