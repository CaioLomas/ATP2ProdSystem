#include<stdio.h>
#include<string.h>
#include<windows.h>
#include<stdlib.h>
#include<conio2.h>

#define TF 3
/* 6 structs Produtos, Fornecedores, Clientes, Vendas, VendaProd, Data */

/*borda(1,1,80,25)*/

char menu ()
{
	gotoxy(51,12);
	printf("[A] Cadastrar produto:");
	gotoxy(51,13);
	printf("[B] Cadastrar fornecedor:");
	return toupper(getch());
}

void borda (int CI, int LI, int CF, int LF, int cor)
{
	int i;
	
		textcolor(cor);
		gotoxy(CI,LI);
	printf("%c",201);
		gotoxy(CF,LI);
	printf("%c",187);
		gotoxy(CI,LF);
	printf("%c",200);
		gotoxy(CF,LF);
	printf("%c",188);
	
	for(i=CI+1;i<CF;i++)
	{
		gotoxy(i,LI);
		printf("%c",205);
		gotoxy(i,LF);
		printf("%c",205);
	}
	for(i=LI+1;i<LF;i++)
	{
		gotoxy(CI,i);
		printf("%c",186);
		gotoxy(CF,i);
		printf("%c",186);
	}
	getch();
}

void msgEstatica ()
{
	textcolor(10);
	gotoxy(33,3);
	printf("***MENSAGEM***");
	textcolor(1);
	gotoxy(60,9);
	printf("***MENU***");
	getch();
}

void limpar ()
{	
	int i,j;
	
	//Menu
	gotoxy(51,10);
	for(i=51;i<79;i++)
	 for(j=10;j<24;j++)
	   printf("%c",32);
	
	//Código
	gotoxy(2,8);
	for(i=2;i<49;i++)
	 for(j=8;j<24;j++)
	   printf("%c",32);
	
	//Mensagem
	gotoxy(4,5);
	for(i=4;i<80;i++)
	 for(j=5;j<6;j++)
	   printf("%c",32);
}

int main (void)
{
	int CI,LI,CF,LF,cor;
	
	/*BORDA PRINCIPAL*/
	
	cor=12;
	CI=1,LI=1,CF=80,LF=25;
	borda(CI,LI,CF,LF,cor);
	
	
	/*
	MENSAGENS PARA O USUÁRIO DEVEM
	ESTAR ENTRE:
	CI 4 a 33 / 48 a 78
	LI 4 
	CF 78 
	LF 6
	*/
	
	cor=10;
	CI=2,LI=2,CF=79,LF=7;
	borda(CI,LI,CF,LF,cor);
	
	/* 
	MENU DEVE ESTAR ENTRE:
	CI 51 a 60 / 70 a 79
	LI 9
	CF 79
	LF 23
	*/
	
	cor=1;
	CI=50,LI=8,CF=78,LF=24;
	borda(CI,LI,CF,LF,cor);
	
	//BORDA CÓDIGO
	
	cor=15;
	CI=2,LI=8,CF=49,LF=24;
	borda(CI,LI,CF,LF,cor);
	
	//***MENSAGEM*** E ***MENU***
	
	msgEstatica();
	
	menu();
	
	printf("\n\n\n\n\n");
		
	return 0;
} 
