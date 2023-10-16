#include<stdio.h>
#include<string.h>
#include<windows.h>
#include<stdlib.h>
#include<conio2.h>


#define TF 4

/* 
	Sistema de vendas simples em C - Caio Lomas - UNOESTE FIPP BSI 2º TERMO 

	NESTE TRABALHO EU PREZEI POR DEIXAR PELO MENOS AS CHAVES PRIMÁRIAS COM BOAS VERIFICAÇÕES
	IMPEDINDO QUE SEJAM DIGITADOS CARACTERES E REPETINDO VERIFICAÇÕES
	
	NÃO HÁ INSERÇÃO DE DADOS AUTOMÁTICA, BOM QUE TESTA AS VERIFICAÇÕES

	O CÓDIGO ESTÁ SEPARADO POR COMENTÁRIOS DIVIDINDO AS FUNÇÕES DE BUSCA, CADASTRO, MENUS, BORDA, ETC.
	
Lacunas a serem preenchidas no código: 
1 - Ao usar scanf ou gets para o usuário dar entrada
em algum dado, não consigo verificar as colunas a cada dígito que ele coloca no buffer sem inserir diretamente, logo
não consigo impedir ele de quebrar a borda caso digite um número ou nome maior que os limites da borda. 

2 - Terminar de validar entradas de números inteiros com char no caso de preço, estoque e validade. Por enquanto fiz
só com código que é chave primária. ISSO VALE PARA CADASTRO E VENDA!

3 - Verificar se o código do fornecedor existe na hora de cadastrar os produtos. (FUNÇÃO PRA ISSO)

4 - A verificação de números inteiros ocorre bem, no entanto se pressionar ENTER, o código avança, mas 
ENTER não é 13 na tabela ASCII? Isso seria <'0' que é uma condição da minha transformação. Estranho.

5 - FAZER MENU PARA ESCOLHER O QUE VISUALIZAR, O QUE EXCLUIR, O QUE ATUALIZAR

6 - Depois eu simplifico as vendas com funções mais compactas

7 - MELHORAR A EXIBIÇÃO DA NOTA FISCAL

8 - EU TO PASSANDO COISA ERRADA NO ESTOQUE EM "Vendendo", existecod não é o indice de onde vai estar aquele código, mas sim o TLP

/* 6 structs Produtos, Fornecedores, Clientes, Vendas, VendaProd, Data */



/*Declaração das structs*/
	struct Datav 
	{
    	int dia;
    	int mes;
    	int ano;
	};


	struct Fornecedor
	{
		int codF;
		char nomeF[35];
		char Cidade[35];	
	};
	
	struct Produtos
	{
		int codP,Estoque;
		char nomeP[35];	
		float preco;
		struct Datav DTV;
		int codF;
	};
	
	struct Cliente
	{
		char CPF[15];
		char nomeC[35];
		int qtdC;
		float valor;	
	};
	
	struct Vendas
	{
		int codV;
		char CPF[35];
		struct Datav DTV;
		float total;
	};
	
	struct VendasProd
	{
		int codV;
		int codP;
		int qtde;
		float valorU;	
	};
	
/*Funções de limpeza*/	
void limparMenu ()
{
	int c,l;
	
	//Menu
	for(c=51;c<78;c++)
	 for(l=10;l<24;l++)
	 {
	  gotoxy(c,l);
	  printf("%c",32);
	 }	
}

void limparTela (int &linhaC)
{	
	int c,l;
	
	//Código
	if(linhaC>=23)
	{
		linhaC=12;
		for(c=3;c<48;c++)
	 	 for(l=10;l<23;l++)
	   		{
	   		gotoxy(c,l);
	   		printf("%c",32);
	   		}
	}
}

void limparMsg ()
{
	int c=5,l=5;
	
		 //Mensagem
	 	 for(c=5;c<77;c++)
	   		{
	   		gotoxy(c,l);
	   		printf("%c",32);
	   		}
}

void limparTelaAnyway ()
{
	int c,l;
	
	//Código COMPLETO
	for(c=3;c<48;c++)
	 	 for(l=9;l<23;l++)
	   		{
	   		gotoxy(c,l);
	   		printf("%c",32);
	   		}
}

/*Menus*/
char menu ()
{	
	char tecla;
	
	limparMenu();
	textcolor(1);
	gotoxy(51,11);
	printf("[A] Cadastrar fornecedor:");
	gotoxy(51,13);
	printf("[B] Cadastrar produto:");
	gotoxy(51,15);
	printf("[C] Cadastrar cliente:");
	gotoxy(51,17);
	printf("[D] Visualizar:");
	gotoxy(51,19);
	printf("[E] Realizar vendas:");
	gotoxy(51,21);
	printf("[ESC] Sair:");
	gotoxy(51,23);
	printf("%c			    %c",17,16);
	
	tecla=toupper(getch());
	if(tecla==-32)
		{
		tecla=getch();	
			if(tecla==77)
			{
			limparMenu();	
			gotoxy(51,11);
			printf("[F] Atualizar:");
			gotoxy(51,13);
			printf("[G] Excluir:");
			gotoxy(51,15);
			printf("[H] Relatorio geral:");
			tecla=toupper(getch());	
			if(tecla>=72&&tecla<=75)
				return tecla;
			}	
		}	
	
	return tecla;
}

char menu2 ()
{
	char tecla;
	
	limparMenu();
	textcolor(1);
	gotoxy(51,11);
	printf("[1] Mostrar fornecedores:");
	gotoxy(51,13);
	printf("[2] Mostrar produtos:");
	gotoxy(51,15);
	printf("[3] Mostrar clientes:");

	tecla=getch();
	
	return tecla;
}

char menu3 ()
{
	char tecla;
	
	limparMenu();
	textcolor(1);
	gotoxy(51,11);
	printf("[1] Atualizar fornecedores:");
	gotoxy(51,13);
	printf("[2] Atualizar produtos:");
	gotoxy(51,15);
	printf("[3] Atualizar clientes:");
	gotoxy(51,17);
	printf("[ESC] Voltar:");

	tecla=getch();
	
	return tecla;
}

char menu4 ()
{
	char tecla;
	
	limparMenu();
	textcolor(1);
	gotoxy(51,11);
	printf("[1] Excluir fornecedores:");
	gotoxy(51,13);
	printf("[2] Excluir produtos:");
	gotoxy(51,15);
	printf("[3] Excluir clientes:");
	gotoxy(51,17);
	printf("[4] Excluir vendas:");

	tecla=getch();
	
	return tecla;
}

char menu5 ()
{
	char tecla;
	
	limparMenu();
	textcolor(1);
	gotoxy(51,11);
	printf("[1] Alterar codigo:");
	gotoxy(51,13);
	printf("[2] Alterar nome:");
	gotoxy(51,15);
	printf("[3] Alterar estoque:");
	gotoxy(51,17);
	printf("[4] Alterar preco:");
	gotoxy(51,19);
	printf("[5] Alterar validade:");
	gotoxy(51,21);
	printf("[6] Alterar codigo fornecedor:");

	tecla=getch();
	
	return tecla;
}

char menu6 ()
{
	char tecla;
	
	limparMenu();
	textcolor(1);
	gotoxy(51,11);
	printf("[A] Alterar codigo:");
	gotoxy(51,13);
	printf("[B] Alterar nome:");
	gotoxy(51,15);
	printf("[C] Alterar cidade:");

	tecla=toupper(getch());	
	
	return tecla;
}

char menu7 ()
{
	char tecla;
	
	limparMenu();
	textcolor(1);
	gotoxy(51,11);
	printf("[A] Alterar CPF:");
	gotoxy(51,13);
	printf("[B] Alterar nome:");
	gotoxy(51,15);
	printf("[C] Alterar qtd compras:");
	gotoxy(51,17);
	printf("[D] Alterar valor comprado:");
	
	tecla=toupper(getch());
	
	return tecla;
}

/*Buscas*/
int BuscaCodF(struct Fornecedor F[TF], int TL,int cod)
{
	int i=0;
	
	while(i<TL && cod!=F[i].codF)
	i++;
	if(i<TL)
	 return i;
	else
	 return -1;
}

int BuscaCodP(struct Produtos P[TF], int TLP,int cod)
{
	int i=0;
	
	while(i<TLP && cod!=P[i].codP)
	i++;
	
	if(i<TLP)
	 return i;
	 
	else
	 return -1;
}

int BuscaCPF(struct Cliente C[TF], int TLC, char aux[35]) 
{
    int i;
    
    for (i = 0; i < TLC; i++) 
	{
        if (strcmp(C[i].CPF, aux) == 0)
		 {
            return i; 
         }
    }
    
    return -1;
}

int BuscaEstoque(struct Produtos P[TF],int indice)
{
	int i,qtd;
	
	if(P[indice].Estoque==0)
		return -1;
		
	else
		{
			qtd=P[indice].Estoque;
			return qtd;
		}	
}

int BuscaIndiceCPF(struct Cliente C[TF], int TLC,char aux[35])
{
	int i;
    
    for (i = 0; i < TLC; i++) 
	{
        if (strcmp(C[i].CPF, aux) == 0)
		 {
            return i; 
         }
    }
}

/*Verifica e transforma char em int*/
int verificaINT (char aux[35])
{
	int i,check=0,numero=0;
	
	for(i=0;i<strlen(aux);i++)
		if(aux[i]<'0'||aux[i]>'9')
		   check++;
			
		if(check>0)
		return -1;
		
		else if(strlen(aux)>1)
		{
		numero = atoi(aux);	
		return numero;	
		}
		else 
		{
		numero = aux[0] - '0';
		return  numero; 
		}
}

float verificaFLOAT (char aux[35])
{
    int i, pontos = 0;  
    float numero = 0.0;

    for (i = 0; i < strlen(aux); i++) 
	{
        if (aux[i] == '.') 
		{
            pontos++;  
            
            if (pontos > 1) 
			return -1.0;  
            
        } 
		else if (aux[i] < '0' || aux[i] > '9') 
            return -1.0;
        
    }

    if (pontos == 0) 
	{
        return -1.0;  
    }

    numero = atof(aux);  
    return numero;
}

/*Repete as verificações em caso de usuário teimoso*/
int RepeteVerifica (int &linhaC,char aux[35])
{
	int num;
		
	limparMsg ();
	gotoxy(24,5);
	textcolor(10);
	printf("ERRO: Insira um numero inteiro");
	textcolor(15);
	linhaC++;
	gotoxy(8,linhaC);
	gets(aux);
	num = verificaINT(aux);
	limparTela(linhaC);
	
	return num;
}

int RepeteExisteF (int &linhaC,char aux[35],int &cod, struct Fornecedor F[TF],int TLF)
{
	int existe;
	
		limparMsg ();
		limparTela(linhaC);
		gotoxy(24,5);
		textcolor(10);
		printf("ERRO: Codigo ja existente, insira outro");
		textcolor(15);
		gotoxy(8,linhaC);
		gets(aux);
		cod = verificaINT(aux);
		while(cod==0)
	 	{
	  		cod = RepeteVerifica(linhaC,aux);	
	 	}
		existe = BuscaCodF(F,TLF,cod);
		linhaC++;
		
		return existe;	
}

int retornaCOD (int &linhaC,int codprod,struct Produtos P[TF],int TLP)
{
	int pos,existe;
	char aux[35];
	
		limparMsg ();
		limparTela(linhaC);
		gotoxy(24,5);
		textcolor(10);
		printf("ERRO: Codigo ja existente, insira outro");
		textcolor(15);
		gotoxy(8,linhaC);
		gets(aux);
		codprod = verificaINT(aux);
		while(codprod==-1)
	 	{
	  		codprod = RepeteVerifica(linhaC,aux);	
	 	}
		existe = BuscaCodP(P,TLP,codprod);
		linhaC++;
		
		return codprod;	
}

int RepeteExisteP (int &linhaC,int &codprod,struct Produtos P[TF],int TLP)
{
	int pos,existe;
	char aux[35];
	
		limparMsg ();
		limparTela(linhaC);
		gotoxy(24,5);
		textcolor(10);
		printf("ERRO: Codigo nao existente, insira outro");
		textcolor(15);
		gotoxy(8,linhaC);
		gets(aux);
		codprod = verificaINT(aux);
		while(codprod==-1)
	 	{
	  		codprod = RepeteVerifica(linhaC,aux);	
	 	}
		existe = BuscaCodP(P,TLP,codprod);
		linhaC++;
		
		return existe;	
}


/*Validação CPF*/
void formataCPF (char CPF[35])
{
	char cpfFormatado[15];
	int i,j;
	
	for (i = 0, j = 0; i < strlen(CPF) - 2; i++) 
	{
        if (i == 3 || i == 6) 
            cpfFormatado[j++] = '.';
        
        	cpfFormatado[j++] = CPF[i];
    }

    cpfFormatado[j++] = '-';
    
    for (i = strlen(CPF) - 2; i < strlen(CPF); i++, j++) 
        cpfFormatado[j] = CPF[i];

	strcpy(CPF, cpfFormatado);
}

int verificaDigitosCPF(char CPF[35]) 
{
    int cpf[11],i,soma=0,resto;

    for (i = 0; i < 11; i++) 
        cpf[i] = CPF[i] - '0';
    
    for (i = 0; i < 9; i++) 
        soma += cpf[i] * (10 - i);
    
    resto = soma % 11;
    
    int digito1 = (resto < 2) ? 0 : (11 - resto);

    if (cpf[9] != digito1) 
        return -1;  
        
    soma = 0;
    for (i = 0; i < 10; i++) 
        soma += cpf[i] * (11 - i);
    
    resto = soma % 11;
    
    int digito2 = (resto < 2) ? 0 : (11 - resto);

    if (cpf[10] != digito2) 
        return -1;  


    return 1; 
}

int validaCPF (char aux[35])
{
	int i,ok;
	char CPF[35];
	
	if (strlen(aux) != 11) 
        return -1;
    
    for (i = 0; i < strlen(aux); i++) 
		if (aux[i] < '0' || aux[i] > '9') 
            return -1;  
	
	strcpy(CPF,aux);
	ok=verificaDigitosCPF(CPF);
	
	if(ok==1)
    return 1;
    else
    return -1;
}

/*Visualização dos cadastros*/
void VisuForn(struct Fornecedor F[TF], int TLF) 
{
    int i, linhaC = 11;
    int larguraMaxima = 20; 

    textcolor(15);

    for (i = 0; i < TLF; i++) 
	{
        gotoxy(8, linhaC);
        printf("Codigo: %d", F[i].codF);
        linhaC++;
        gotoxy(8, linhaC);
        printf("Nome: %-*s", larguraMaxima, F[i].nomeF);
        linhaC++;
        gotoxy(8, linhaC);
        printf("Cidade: %-*s", larguraMaxima, F[i].Cidade);
        linhaC += 2;  
        if (linhaC >= 23) 
		{
			fflush(stdin);
            getch();
            limparTela(linhaC);
        }
    }
    fflush(stdin);
    getch();
    limparTelaAnyway();
}

void VisuFP(struct Fornecedor F[TF], int TLF)
{
	 int i, linhaC = 11;
    int larguraMaxima = 20; 

    textcolor(15);

    for (i = 0; i < TLF; i++) 
	{
        gotoxy(8, linhaC);
        printf("Codigo: %d", F[i].codF);
        linhaC++;
        gotoxy(8, linhaC);
        printf("Nome: %-*s", larguraMaxima, F[i].nomeF);
        linhaC += 2;  
        if (linhaC >= 23) 
		{
            getch();
            limparTela(linhaC);
        }
    }
    getch();
    limparTelaAnyway();
}

void VisuProd(struct Produtos P[TF],int TLP)
{
	int i, linhaC = 11;
    int larguraMaxima = 20; 

    textcolor(15);

    for (i = 0; i < TLP; i++) 
	{
        gotoxy(8, linhaC);
        printf("Codigo: %d", P[i].codP);
        linhaC++;
        gotoxy(8, linhaC);
        printf("Nome: %-*s", larguraMaxima, P[i].nomeP);
        linhaC++; 
        gotoxy(8, linhaC);
        printf("Estoque: %d", P[i].Estoque);
        linhaC++;
        gotoxy(8, linhaC);
        printf("Preco: R$%.2f", P[i].preco);
        linhaC++;
        gotoxy(8, linhaC);
        printf("Data de validade: %d/%d/%d", P[i].DTV.dia,P[i].DTV.mes,P[i].DTV.ano);
        getch();
        
        linhaC += 2;
        limparTela(linhaC);
    }
    fflush(stdin);
    limparTelaAnyway();	
}

void VisuCli(struct Cliente C[TF], int TLC)
{
	int i, linhaC = 11;
    int larguraMaxima = 20; 

    textcolor(15);

    for (i = 0; i < TLC; i++) 
	{
        gotoxy(8, linhaC);
        printf("CPF: %s", C[i].CPF);
        linhaC++;
        gotoxy(8, linhaC);
        printf("Nome: %-*s", larguraMaxima, C[i].nomeC);
        linhaC++; 
        gotoxy(8, linhaC);
        printf("Qtd compras: %d", C[i].qtdC);
        linhaC++;
        gotoxy(8, linhaC);
        printf("Total comprado: R$%.2f", C[i].valor);
        getch();
        
        linhaC += 2;
        limparTela(linhaC);
    }
    limparTelaAnyway();	
}

void VisuVenda(struct Vendas V[TF], int TLV) 
{
	limparTelaAnyway();
    int linhaC = 11;
    
   	gotoxy(8, linhaC);
	printf("CPF: %s", V[TLV].CPF);
	linhaC++;


    gotoxy(8, linhaC);
    printf("Data de venda: %d/%d/%d", V[TLV].DTV.dia, V[TLV].DTV.mes, V[TLV].DTV.ano);
    linhaC++;

    gotoxy(8, linhaC);
    printf("Total vendido: R$%.2f", V[TLV].total);
    linhaC++;
    
    gotoxy(8, linhaC);
    printf("Codigo: %d",V[TLV].codV);
    linhaC++;

    fflush(stdin);
    getch();
}

void relatorio (struct Vendas V[],struct Produtos P[],struct Fornecedor F[],struct VendasProd VP[],int TLV,int TLP,int TLF,int TLVP)
{
	int i, linhaC = 11;

    textcolor(15);

    for (i = 0; i < TLV; i++) 
	{
        gotoxy(8, linhaC);
        printf("Cod:%d", V[i].CPF);
        linhaC++;
        gotoxy(8, linhaC);
        printf("Nome: %-*s", larguraMaxima, C[i].nomeC);
        linhaC++; 
        gotoxy(8, linhaC);
        printf("Qtd compras: %d", C[i].qtdC);
        linhaC++;
        gotoxy(8, linhaC);
        printf("Total comprado: R$%.2f", C[i].valor);
        getch();
        
        linhaC += 2;
        limparTela(linhaC);
    }
    
    limparTelaAnyway();	
}

/*Bordas*/
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
}

void msgEstatica ()
{
	textcolor(10);
	gotoxy(33,3);
	printf("***MENSAGEM***");
	textcolor(1);
	gotoxy(60,9);
	printf("***MENU***");
}

/*Cadastros*/
void cad_Fornecedor (struct Fornecedor F[TF], int &TLF)
{
	int i,linhaC=11,existe,qtd,cod;
	char aux[35];
	
	limparMsg ();
	gotoxy(24,5);
	textcolor(10);
	printf("Quantos fornecedores deseja cadastrar?");
	textcolor(15);
	gotoxy(8,linhaC);
	fflush(stdin);
	gets(aux);
	qtd = verificaINT(aux);
	
	while(qtd==-1)
	 {
	 	fflush(stdin);
	 	qtd = RepeteVerifica(linhaC,aux);
	 	limparTela(linhaC);	
	 }
	if(qtd==0)
	 return;
	 
	linhaC++;
	
	for(i=0;i<qtd;i++)
	{
		limparMsg ();
		gotoxy(24,5);
		textcolor(10);
		printf("Informe o codigo do fornecedor");
		textcolor(15);
		gotoxy(8,linhaC);
		fflush(stdin);
		gets(aux);
		cod = verificaINT(aux); 
		while(cod==-1)
	 	{
	 		fflush(stdin);
	  		cod = RepeteVerifica(linhaC,aux);
	  		limparTela(linhaC);	
	 	}
	 	
		linhaC++;
		
			existe = BuscaCodF(F,TLF,cod);
			if(existe==-1)
				F[TLF].codF=cod;
			else
			{
				while(existe!=-1)
				{
					fflush(stdin);
					existe=RepeteExisteF(linhaC,aux,cod,F,TLF);	
					limparTela(linhaC);	
				}
				F[TLF].codF=cod;
			}
			
			limparTela(linhaC);
		limparMsg ();	
		gotoxy(24,5);
		textcolor(10);
		printf("Informe o nome do fornecedor");
		textcolor(15);
		gotoxy(8,linhaC);
			fflush(stdin);
			gets(F[TLF].nomeF);
			linhaC++;
			limparTela(linhaC);
		limparMsg ();	
		gotoxy(24,5);
		textcolor(10);
		printf("Informe a cidade do fornecedor");
		textcolor(15);
		gotoxy(8,linhaC);
			fflush(stdin);
			gets(F[TLF].Cidade);
			linhaC++;
			limparTela(linhaC);
			TLF++;
	}
	
		limparMsg ();	
		gotoxy(24,5);
		textcolor(10);
		printf("Fornecedor cadastrado com sucesso!");
		getch();
		
		limparTelaAnyway ();
}

void cad_Produtos (struct Produtos P[], int &TLP,struct Fornecedor F[], int TLF)
{
	int i,linhaC=11,existe,qtd,codprod,codFP;
	char aux[35];
	
	if(TLF==0)
	{
		limparMsg ();
		gotoxy(24,5);
		textcolor(10);
		printf("ERRO: Nao ha fornecedores cadastrados!");
		getch();
		return;
	}
	
	limparMsg ();
	gotoxy(24,5);
	textcolor(10);
	printf("Quantos produtos deseja cadastrar?");
	textcolor(15);
	gotoxy(8,linhaC);
	fflush(stdin);
	gets(aux);
	qtd = verificaINT(aux);
	
	while(qtd==-1)
	 {
	 	fflush(stdin);
	 	qtd = RepeteVerifica(linhaC,aux);
	 	limparTela(linhaC);	
	 }
	if(qtd==0)
	 return;
	
	linhaC++;
	
	for(i=0;i<qtd;i++)
	{
		limparMsg ();
		gotoxy(24,5);
		textcolor(10);
		printf("Informe o codigo do produto");
		textcolor(15);
		gotoxy(8,linhaC);
		fflush(stdin);
		gets(aux);
		codprod = verificaINT(aux);
		while(codprod==-1)
	 	{
	 		fflush(stdin);
	  		codprod = RepeteVerifica(linhaC,aux);
	  		limparTela(linhaC);	
	 	}
	 	
		linhaC++;
		
		existe = BuscaCodP(P,TLP,codprod);
	
		while(existe!=-1)
		{
			fflush(stdin);
			existe=retornaCOD(linhaC,codprod,P,TLP);	
			limparTela(linhaC);	
		}
		
		P[TLP].codP=codprod;
			
			
			limparTela(linhaC);
			limparMsg ();	
			gotoxy(24,5);
			textcolor(10);
			printf("Informe o nome do produto");
			textcolor(15);
			gotoxy(8,linhaC);
			fflush(stdin);
			gets(P[TLP].nomeP);
			linhaC++;
			
			limparTela(linhaC);                      
			limparMsg ();	
			gotoxy(24,5);
			textcolor(10);
			printf("Informe a quantidade para estoque");
			textcolor(15);
			gotoxy(8,linhaC);
			scanf("%d",&P[TLP].Estoque);
			linhaC++;
			
			limparTela(linhaC);
			limparMsg ();	
			gotoxy(24,5);
			textcolor(10);
			printf("Informe o preco deste produto");
			textcolor(15);
			gotoxy(8,linhaC);
			scanf("%f",&P[TLP].preco);
			linhaC++;
			
			limparTela(linhaC);
			limparMsg ();	
			gotoxy(24,5);
			textcolor(10);
			printf("Informe a data de validade deste produto");
			textcolor(15);
			gotoxy(8,linhaC);
			scanf("%d %d %d",&P[TLP].DTV.dia,&P[TLP].DTV.mes,&P[TLP].DTV.ano);
			linhaC++;
			
			limparTela(linhaC);
			limparMsg ();	
			gotoxy(24,5);
			textcolor(10);
			printf("Informe o codigo do fornecedor deste produto");
			limparTelaAnyway ();
			VisuFP(F,TLF);
			textcolor(15);
			gotoxy(8,linhaC);
			fflush(stdin);
			gets(aux);
			codFP = verificaINT(aux);
	
			while(codFP==-1)
	 		{
	 			fflush(stdin);
	 			codFP = RepeteVerifica(linhaC,aux);
	 			limparTela(linhaC);	
	 		}
	 		
	 		
	 		
	 		P[TLP].codF=codFP;
	
			linhaC++;
			limparTela(linhaC);
			
			TLP++;
	}
	
		limparMsg ();	
		gotoxy(24,5);
		textcolor(10);
		printf("Produto cadastrado com sucesso!");
		getch();
		
		limparTelaAnyway ();	
}

void cad_Cliente (struct Cliente C[TF], int &TLC, int TLP)
{
	int i,linhaC=11,valido,existe,qtd,compra;
	float valor;
	char aux[35];
	
	if(TLP==0)
	{
		limparMsg ();
		gotoxy(24,5);
		textcolor(10);
		printf("ERRO: Nao ha produtos cadastrados!");
		getch();
		return;
	}
	
	limparMsg ();
	gotoxy(24,5);
	textcolor(10);
	printf("Quantos clientes deseja cadastrar?");
	textcolor(15);
	gotoxy(8,linhaC);
	fflush(stdin);
	gets(aux);
	qtd = verificaINT(aux);
	
	while(qtd==-1)
	 {
	 	fflush(stdin);
	 	qtd = RepeteVerifica(linhaC,aux);
	 	limparTela(linhaC);	
	 }
	if(qtd==0)
	 return;
	
	linhaC++;
	
	for(i=0;i<qtd;i++)
	{
		limparMsg ();
		gotoxy(24,5);
		textcolor(10);
		printf("Informe o CPF do cliente - apenas numeros");
		textcolor(15);
		gotoxy(8,linhaC);
		fflush(stdin);
		gets(aux);	
		valido = validaCPF(aux);
		
		while(valido==-1)
	 	{
	 		limparMsg ();
			gotoxy(24,5);
			textcolor(10);
			printf("ERRO: CPF invalido");
			linhaC++;
			textcolor(15);
			gotoxy(8,linhaC);
	 		fflush(stdin);
	 		gets(aux);
	  		valido = validaCPF(aux);
	  		limparTela(linhaC);	
	 	}
	 		
	 		formataCPF(aux);
	 		existe = BuscaCPF(C,TLC,aux);
	 		if(existe==-1)
	 			strcpy(C[TLC].CPF,aux);
	 		else	
	 		{
			 while(existe!=-1)
				{
					limparMsg ();
					gotoxy(24,5);
					textcolor(10);
					printf("ERRO: CPF ja cadastrado");
					linhaC++;
					textcolor(15);
					gotoxy(8,linhaC);
	 				fflush(stdin);
	 				gets(aux);
	  				valido = validaCPF(aux);
					formataCPF(aux);
	 				existe = BuscaCPF(C,TLC,aux);
					limparTela(linhaC);	
				}
				strcpy(C[TLC].CPF,aux);
	 		}
	 	
			linhaC++;
			
			limparMsg ();	
			gotoxy(24,5);
			textcolor(10);
			printf("Informe o nome do cliente");
			textcolor(15);
			gotoxy(8,linhaC);
			fflush(stdin);
			gets(C[TLC].nomeC);
			linhaC++;
			limparTela(linhaC);  
			
			C[TLC].qtdC=0;
			C[TLC].valor=0;
			
			TLC++;
	}
	
		limparMsg ();	
		gotoxy(24,5);
		textcolor(10);
		printf("Cliente cadastrado com sucesso!");
		getch();
		
		limparTelaAnyway ();
}

/*Realizando as vendas*/ 

void Vendendo (struct Vendas V[],struct VendasProd VP[],struct Cliente C[],struct Produtos P[],int &TLV,int &TLVP,int TLC, int TLP,int TLF)
{
	int i,linhaC=11,valido,existecpf,qtd,codprd,existecod,qtd2;
	char aux[30],res;
	float valortot,VU;
		
	if(TLP==0)
	{
		limparMsg ();
		gotoxy(24,5);
		textcolor(10);
		printf("ERRO: Nao ha produtos cadastrados!");
		getch();
		return;
	}
	
		limparMsg ();
		gotoxy(24,5);
		textcolor(10);
		printf("Informe o CPF do cliente - apenas numeros");
		textcolor(15);
		gotoxy(8,linhaC);
		fflush(stdin);
		gets(aux);	
		valido = validaCPF(aux);
		
			while(valido==-1)
	 	{
	 		limparMsg ();
			gotoxy(24,5);
			textcolor(10);
			printf("ERRO: CPF invalido");
			linhaC++;
			textcolor(15);
			gotoxy(8,linhaC);
	 		fflush(stdin);
	 		gets(aux);
	  		valido = validaCPF(aux);
	  		limparTela(linhaC);	
	 	}
	 		
	 	formataCPF(aux);
	 		
		existecpf = BuscaCPF(C,TLC,aux); 
				
				while(existecpf==-1)
				{
					limparMsg ();
					gotoxy(24,5);
					textcolor(10);
					printf("ERRO: CPF nao cadastrado");
					linhaC++;
					textcolor(15);
					gotoxy(8,linhaC);
	 				fflush(stdin);
	 				gets(aux);
	  				valido = validaCPF(aux);
					formataCPF(aux);
	 				existecpf = BuscaCPF(C,TLC,aux);
					limparTela(linhaC);	
				}
		
	 		strcpy(V[TLV].CPF,aux);
	 	
			linhaC++;
			
			limparTela(linhaC);
			limparMsg ();	
			gotoxy(24,5);
			textcolor(10);
			printf("Informe a data dessa venda");
			textcolor(15);
			gotoxy(8,linhaC);
			scanf("%d %d %d",&V[TLV].DTV.dia,&V[TLV].DTV.mes,&V[TLV].DTV.ano);
		
			
			limparMsg ();
			gotoxy(24,5);
			textcolor(10);
			printf("Informe a quantidade de cada produto diferente");
			linhaC++;
			textcolor(15);
			gotoxy(8,linhaC);
			fflush(stdin);
			gets(aux);
			qtd = verificaINT(aux);
			
			while(qtd==-1)
	 		{
	 			fflush(stdin);
	  			qtd = RepeteVerifica(linhaC,aux);
	  			limparTela(linhaC);	
	 		}
	 	
			valortot=0;
			
			for(i=0;i<qtd;i++)
			{
				limparMsg ();
				gotoxy(24,5);
				textcolor(10);
				printf("Informe o codigo do produto");
				linhaC++;
				textcolor(15);
				gotoxy(8,linhaC);
				fflush(stdin);
				gets(aux);
				codprd = verificaINT(aux); 
				while(codprd==-1)
	 			{
	 				fflush(stdin);
	  				codprd = RepeteVerifica(linhaC,aux);
	  				limparTela(linhaC);	
	 			}
				
				existecod = BuscaCodP(P,TLP,codprd); 
				
				while(existecod==-1)
				{
					fflush(stdin);
					existecod=RepeteExisteP(linhaC,codprd,P,TLP);	
					limparTela(linhaC);	
				}
			
				VP[TLVP].codP=codprd;
				VU=P[existecod].preco;
				limparTela(linhaC);
				
				    limparMsg();
				    gotoxy(24, 5);
				    textcolor(10);
				    printf("Informe a quantidade a ser vendida  disponivel [%d]: ", P[existecod].Estoque);
				    linhaC++;
				    textcolor(15);
				    gotoxy(8, linhaC);
				    fflush(stdin);
				    gets(aux);
				    qtd2 = verificaINT(aux);

				    if (qtd2 > 0 && qtd2 <= P[existecod].Estoque) 
					{
				        P[existecod].Estoque -= qtd2;
				        valortot += qtd2 * P[existecod].preco;
    				} 
    				
					else
					{
				        limparMsg();
				        gotoxy(24, 5);
				        textcolor(10);
				        printf("ERRO: Quantidade invalida ou estoque insuficiente.");
				        textcolor(15);
				        fflush(stdin);
				        getch();
    				}
	 			
				linhaC++;
				
				VP[TLVP].qtde=qtd2;
				VP[TLVP].valorU=VU;
				
				TLVP++;
			}
	
	C[existecpf].qtdC++;
   	C[existecpf].valor += valortot;		
	
			
	V[TLV].total=valortot;
	V[TLV].codV=TLV+1;
		
	limparMsg ();	
	gotoxy(24,5);
	textcolor(10);
	printf("Venda realizada com sucesso!");
	fflush(stdin);
	getch();
		
	limparMsg ();
	limparTela(linhaC);
	gotoxy(24,5);
	textcolor(10);
	printf("Deseja imprimir a nota fiscal? S/N");
	textcolor(15);
	gotoxy(8,linhaC);
	fflush(stdin);
	res=toupper(getch());
	if(res=='S')
	{
		VisuVenda(V,TLV);	
	}	
		
	TLV++;
	
	limparTelaAnyway ();
}

/*Atualizar cadastros*/
void AtualizaForn(struct Fornecedor F[TF],int TLF)
{
	int linhaC=11,cod,existe,indice;
	char aux[35],op;
	
		limparMsg ();
		gotoxy(24,5);
		textcolor(10);
		printf("Informe o codigo do fornecedor");
		textcolor(15);
		gotoxy(8,linhaC);
		fflush(stdin);
		gets(aux);
		cod = verificaINT(aux); 
		while(cod==-1)
	 	{
	 		fflush(stdin);
	  		cod = RepeteVerifica(linhaC,aux);
	  		limparTela(linhaC);	
	 	}
	 	
		linhaC++;
		
		existe = BuscaCodF(F,TLF,cod);
		
		if(existe==-1)
		{
			limparMsg ();
			gotoxy(24,5);
			textcolor(10);
			printf("ERRO: Fornecedor nao cadastrado!");
			getch();
			return;
		}
			
		else
		{
			op=menu6();
			
			switch(op)
			{
				case'A':limparMsg ();
				gotoxy(24,5);
				textcolor(10);
				printf("Informe o codigo do fornecedor");
				textcolor(15);
				gotoxy(8,linhaC);
				fflush(stdin);
				gets(aux);
				cod = verificaINT(aux); 
				while(cod==-1)
			 	{
			 		fflush(stdin);
			  		cod = RepeteVerifica(linhaC,aux);
			  		limparTela(linhaC);	
			 	}
			 	
				linhaC++;
				
				indice = BuscaCodF(F,TLF,cod);
				
				if(indice!=-1)
				 	{
					 	limparMsg ();
						gotoxy(24,5);
						textcolor(10);
						printf("ERRO: Codigo ja esta sendo utilizado!");
						getch();
						return;
				 	}			
					else
					{
						F[existe].codF=cod;
						limparMsg ();	
						gotoxy(24,5);
						textcolor(10);
						printf("Codigo atualizado com sucesso!");
						getch();
					}
				break;
				
				case'B':limparMsg ();	
				gotoxy(24,5);
				textcolor(10);
				printf("Informe o novo nome");
				linhaC++;
				textcolor(15);
				gotoxy(8,linhaC);
				fflush(stdin);
				gets(F[existe].nomeF);
				linhaC++;
				limparTela(linhaC); 
				limparMsg ();	
				gotoxy(24,5);
				textcolor(10);
				printf("Nome atualizado com sucesso!");
				getch();
					
				break;
				
				case'C':limparMsg ();	
				gotoxy(24,5);
				textcolor(10);
				printf("Informe a nova cidade");
				linhaC++;
				textcolor(15);
				gotoxy(8,linhaC);
				fflush(stdin);
				gets(F[existe].Cidade);
				linhaC++;
				limparTela(linhaC); 
				limparMsg ();	
				gotoxy(24,5);
				textcolor(10);
				printf("Cidade atualizada com sucesso!");
				getch();
					
				break;
			}
		}
	
		limparMsg ();	
		gotoxy(24,5);
		textcolor(10);
		printf("Atualizacao feita com sucesso!");
		getch();
		
		limparTelaAnyway ();
		
}

void AtualizaProd (struct Produtos P[TF],int TLP)
{
	int linhaC=11,cod,existe,indice;
	char aux[35],op;
	
		limparMsg ();
		gotoxy(24,5);
		textcolor(10);
		printf("Informe o codigo do produto");
		textcolor(15);
		gotoxy(8,linhaC);
		fflush(stdin);
		gets(aux);
		cod = verificaINT(aux); 
		while(cod==-1)
	 	{
	 		fflush(stdin);
	  		cod = RepeteVerifica(linhaC,aux);
	  		limparTela(linhaC);	
	 	}
	 	
		linhaC++;
		
		existe = BuscaCodP(P,TLP,cod);
		
		if(existe==-1)
		{
			limparMsg ();
			gotoxy(24,5);
			textcolor(10);
			printf("ERRO: Produto nao cadastrado!");
			getch();
			return;
		}
			
		else
		{
			op=menu5();
			
			switch(op)
			{
				case'A':limparMsg ();
				gotoxy(24,5);
				textcolor(10);
				printf("Informe o codigo do produto");
				textcolor(15);
				gotoxy(8,linhaC);
				fflush(stdin);
				gets(aux);
				cod = verificaINT(aux); 
				while(cod==-1)
			 	{
			 		fflush(stdin);
			  		cod = RepeteVerifica(linhaC,aux);
			  		limparTela(linhaC);	
			 	}
			 	
				linhaC++;
				
				indice = BuscaCodP(P,TLP,cod);
				
				if(indice!=-1)
				 	{
					 	limparMsg ();
						gotoxy(24,5);
						textcolor(10);
						printf("ERRO: Codigo ja esta sendo utilizado!");
						getch();
						return;
				 	}			
					else
					{
						P[existe].codP=cod;
						limparMsg ();	
						gotoxy(24,5);
						textcolor(10);
						printf("Codigo atualizado com sucesso!");
						getch();
					}
				break;
				
				case'B':limparMsg ();	
				gotoxy(24,5);
				textcolor(10);
				printf("Informe o novo nome");
				linhaC++;
				textcolor(15);
				gotoxy(8,linhaC);
				fflush(stdin);
				gets(P[existe].nomeP);
				linhaC++;
				limparTela(linhaC); 
				limparMsg ();	
				gotoxy(24,5);
				textcolor(10);
				printf("Nome atualizado com sucesso!");
				getch();
					
				break;
				
				case'C':limparMsg ();	
				gotoxy(24,5);
				textcolor(10);
				printf("Informe o novo estoque");
				linhaC++;
				textcolor(15);
				gotoxy(8,linhaC);
				scanf("%d",P[existe].Estoque);
				linhaC++;
				limparTela(linhaC); 
				limparMsg ();	
				gotoxy(24,5);
				textcolor(10);
				printf("Estoque atualizado com sucesso!");
				getch();
					
				break;
				
				case'D':limparMsg ();	
				gotoxy(24,5);
				textcolor(10);
				printf("Informe o novo preco");
				linhaC++;
				textcolor(15);
				gotoxy(8,linhaC);
				scanf("%f",P[existe].preco);
				linhaC++;
				limparTela(linhaC); 
				limparMsg ();	
				gotoxy(24,5);
				textcolor(10);
				printf("Preco atualizado com sucesso!");
				getch();
				
				break;
				
				case'E':limparMsg ();	
				gotoxy(24,5);
				textcolor(10);
				printf("Informe a nova data de validade");
				linhaC++;
				textcolor(15);
				gotoxy(8,linhaC);
				scanf("%d%d%d",P[existe].DTV.dia,P[existe].DTV.mes,P[existe].DTV.ano);
				linhaC++;
				limparTela(linhaC); 
				limparMsg ();	
				gotoxy(24,5);
				textcolor(10);
				printf("Data atualizada com sucesso!");
				getch();
				
				break;
				
				case'F':limparMsg ();	
				gotoxy(24,5);
				textcolor(10);
				printf("Informe o novo codigo do fornecedor");
				linhaC++;
				textcolor(15);
				gotoxy(8,linhaC);
				scanf("%d",P[existe].codF);
				linhaC++;
				limparTela(linhaC); 
				limparMsg ();	
				gotoxy(24,5);
				textcolor(10);
				printf("Codigo do fornecedor atualizado com sucesso!");
				getch();
					
				break;
			}
		}
	
		limparMsg ();	
		gotoxy(24,5);
		textcolor(10);
		printf("Atualizacao feita com sucesso!");
		getch();
		
		limparTelaAnyway ();
}

void AtualizaCliente (struct Cliente C[TF],int TLC)
{
	int linhaC=11,valido,existe,indice;
	char aux[15],op;
	
	if(TLC==0)
	{
		limparMsg ();
		gotoxy(24,5);
		textcolor(10);
		printf("ERRO: Nao ha clientes cadastrados!");
		getch();
		return;
	}
	
		limparMsg ();
		gotoxy(24,5);
		textcolor(10);
		printf("Informe o CPF do cliente - apenas numeros");
		textcolor(15);
		gotoxy(8,linhaC);
		fflush(stdin);
		gets(aux);	
		valido = validaCPF(aux);
		
		while(valido==-1)
	 	{
	 		limparMsg ();
			gotoxy(24,5);
			textcolor(10);
			printf("ERRO: CPF invalido");
			linhaC++;
			textcolor(15);
			gotoxy(8,linhaC);
	 		fflush(stdin);
	 		gets(aux);
	  		valido = validaCPF(aux);
	  		limparTela(linhaC);	
	 	}
	 		
	 		formataCPF(aux);
	 		existe = BuscaCPF(C,TLC,aux);
	 		if(existe==-1)
	 		{
	 				limparMsg ();
					gotoxy(24,5);
					textcolor(10);
					printf("ERRO: Cliente nao cadastrado!");
					getch();
					return;
	 		}
	 		else	
	 		{
			 	op=menu7();
				 
				switch(op)
				{
					case'A': limparMsg ();
					gotoxy(24,5);
					textcolor(10);
					printf("Digite o novo CPF");
					linhaC++;
					textcolor(15);
					gotoxy(8,linhaC);
					fflush(stdin);
					gets(aux);	
					valido = validaCPF(aux);
					
					while(valido==-1)
				 	{
				 		limparMsg ();
						gotoxy(24,5);
						textcolor(10);
						printf("ERRO: CPF invalido");
						linhaC++;
						textcolor(15);
						gotoxy(8,linhaC);
				 		fflush(stdin);
				 		gets(aux);
				  		valido = validaCPF(aux);
				  		limparTela(linhaC);	
				 	}
				 		
				 		formataCPF(aux);
				 		indice = BuscaCPF(C,TLC,aux);
				 		
					if(indice!=-1)
				 	{
					 	limparMsg ();
						gotoxy(24,5);
						textcolor(10);
						printf("ERRO: CPF ja esta sendo utilizado!");
						getch();
						return;
				 	}			
					else
					{
						strcpy(C[existe].CPF,aux);
						limparMsg ();	
						gotoxy(24,5);
						textcolor(10);
						printf("CPF atualizado com sucesso!");
						getch();
					}

					break;
					
					case'B':limparMsg ();	
					gotoxy(24,5);
					textcolor(10);
					printf("Informe o novo nome");
					linhaC++;
					textcolor(15);
					gotoxy(8,linhaC);
					fflush(stdin);
					gets(C[existe].nomeC);
					linhaC++;
					limparTela(linhaC); 
					limparMsg ();	
					gotoxy(24,5);
					textcolor(10);
					printf("Nome atualizado com sucesso!");
					getch();
					break;
					
					case'C':limparMsg ();	
					gotoxy(24,5);
					textcolor(10);
					printf("Informe a nova quantia");
					linhaC++;
					textcolor(15);
					gotoxy(8,linhaC);
					scanf("%d",&C[existe].qtdC);
					linhaC++;
					limparTela(linhaC); 
					limparMsg ();	
					gotoxy(24,5);
					textcolor(10);
					printf("Compras atualizadas com sucesso!");
					getch();
					break;
					
					case'D':limparMsg ();	
					gotoxy(24,5);
					textcolor(10);
					printf("Informe o novo valor");
					linhaC++;
					textcolor(15);
					gotoxy(8,linhaC);
					scanf("%f",&C[existe].valor);
					linhaC++;
					limparTela(linhaC); 
					limparMsg ();	
					gotoxy(24,5);
					textcolor(10);
					printf("Valor atualizado com sucesso!");
					getch();
					break;
					
				}	
	 		}

		limparMsg ();	
		gotoxy(24,5);
		textcolor(10);
		printf("Atualizacao feita com sucesso!");
		getch();
		
		limparTelaAnyway ();		
}

void Executar ()
{
	char op,opR;
	struct Fornecedor F[TF];
	struct Produtos P[TF];
	struct Cliente C[TF];
	struct Datav DTV;
	struct Vendas V[TF];
	struct VendasProd VP[TF];
	
	int TLF=0,TLP=0,TLC=0,TLV=0,TLVP=0;
	
	do
	
	{
		limparMsg();
		limparTelaAnyway();
		op=menu();
		
		switch(op)
		{
			case 'A': textcolor(15);
			gotoxy(14,9);
			printf("Cadastro do Fornecedor.");
			cad_Fornecedor(F,TLF);
			break;
			
			case 'B':textcolor(15);
			gotoxy(14,9);
			printf("Cadastro do Produto.");
			cad_Produtos(P,TLP,F,TLF);
			break;
			
			case 'C':textcolor(15);
			gotoxy(14,9);
			printf("Cadastro do Cliente.");
			cad_Cliente(C,TLC,TLP);
			break;
			
			case 'D':limparMsg ();	
			gotoxy(24,5);
			textcolor(10);
			printf("Relatorio Simples.");
		
			opR=menu2();
			
				if(opR=='1')
					VisuForn(F,TLF);
				
				else if(opR=='2')
					VisuProd(P,TLP);
				
				else if(opR=='3')
					VisuCli(C,TLC);			
				break;
			 
			case 'E':limparMsg ();	
			gotoxy(24,5);
			textcolor(10);
			printf("Venda de produtos.");
			Vendendo(V,VP,C,P,TLV,TLVP,TLC,TLP,TLF);
			break;
			
			case 'F':limparMsg ();	
			gotoxy(24,5);
			textcolor(10);
			printf("Atualizar dados.");
			
			opR=menu3();	
			
			do
			{
			
				if(opR=='1')
					AtualizaForn(F,TLF);
				
				else if(opR=='2')
					VisuProd(P,TLP);
				
				else if(opR=='3')
					AtualizaCliente(C,TLC);	
					
				opR=menu3();	
					
			}while(opR!=27);		
			break;
			
			case 'H':limparMsg ();	
			gotoxy(24,5);
			textcolor(10);
			printf("Relatorio geral.");
			relatorio(V,P,F,VP,TLV,TLP,TLF,TLVP);
			break;
		}
		
	}while(op!=27);
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
	
	Executar();
	
	printf("\n\n\n\n\n\n\n\n\n\n\n");
		
	return 0;
} 
