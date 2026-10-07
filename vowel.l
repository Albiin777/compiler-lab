%{
#include<stdio.h>
#include<stdlib.h>
int conso =0;
int vowe=0;
%}
%%
[aeiouAEIOU]		{vowe++;}//ee rule true ayillenkile next rule-lek povullu
[a-zA-Z]		    {conso++;}
[ \t\n]			    {}
.			          ;
%%
int main(){
	printf("Enter a string: ");
	yylex();
	printf("Consonants: %d\n",conso);
	printf("Vowels: %d\n",vowe); //String enter cheythit ctrl+d cheythale out kanan pattu
	return 0;
}
int yywrap(){return 1;}
