#include <stdio.h>
#include <stdlib.h>
#include <string.h>


//Declaração da Struct
typedef struct elemento_pilha
{
    //int dado;
    char *nome;
    char *identidade;
    char *endereco;
    char *telefone;
    float valor;
    char *data;
    char *nomesuper;
    int identificador;
    struct elemento_pilha* prox; //estrutura que define os processos da pilha
} telemento_pilha;

typedef struct pilha
{
    telemento_pilha* inicio;
    telemento_pilha* final;      //estrutura que define a estrutura da pilha
} pilha;

int tamanho=0;

int VerificaPilhaVazia (pilha F);
void Criapilha(pilha *F);
int Empilha (pilha *F, char *Nome, char *Identidade, char *Endereco, char *Telefone, float Valor, char *Data, char *Nomesuper, int cont);
int DesEmpilha (pilha *F);
int RemoveFim (pilha *F);
int ImprimePilha(pilha *F);
int ConsultaElemento(pilha *F, int processo);
int Ordena(pilha *F ,int tamanho);
int Prioridade(pilha *F, int tamanho, char *nomesuper);
int RemoveMeio (pilha *F, int pos);
int RemoveFim (pilha *F);

//Verifica se a pilha de processos está vazia
int main(int argc, char *argv[])
{
    pilha no;
    //pilha *b;
    int cont;
    int opcao=1;
    int busca;
    float Valor;
    char *Nome, *Identidade, *Endereco, *Telefone, *Nomesuper, *Data;
    Criapilha(&no);

    Nome = (char*) malloc(20*sizeof(char));
    Identidade = (char*) malloc(10*sizeof(char));
    Endereco = (char*) malloc(100*sizeof(char));
    Telefone = (char*) malloc(9*sizeof(char));
    Nomesuper = (char*) malloc(20*sizeof(char));
    Data = (char*) malloc(10*sizeof(char));

    //srand(time(NULL));

    while(opcao != 0)
    {
        //system("clear"); //se for rodar no linux
        //system("cls"); // se for rodar no windows

        printf("==================== pilha ====================\n");
        printf("1 - Inserir processo na pilha\n");
        printf("2 - Remover processo da pilha\n");
        printf("3 - Listar todos os processos\n");
        printf("4 - Consultar processo\n");
        printf("5 - Colocar Supermercado na prioridade\n");
        printf("0 - Sair\n");
        scanf("%d",&opcao);

		switch(opcao) {
			case 1:
				printf("Digite o valor \n");
				scanf("%f",&Valor);
				printf("Digite a data (formato DD/MM/AAAA) \n");
				scanf("%s", Data); //adição do campo data do cheque que também é solicitado na especificação
				printf("Nome: \n");
				scanf("%s", Nome);
				printf("Identidade: \n");
				scanf("%s", Identidade);
				printf("Digite o endereço \n");
				scanf("%s",Endereco);
				printf("Digite o telefone \n");
				scanf("%s",Telefone);
				printf("Digite o nome do supermercado \n");
				scanf("%s", Nomesuper);
				cont= 000000000 + ( rand() % 99999999 );
				Empilha (&no , Nome, Identidade, Endereco, Telefone, Valor, Data, Nomesuper, cont);
				if(tamanho > 1)
				{
					Ordena(&no , tamanho);
				}
				printf("O processo foi colocado na pilha!\n\n\n");
			break;
			case 2:
				DesEmpilha(&no);
				//RemoveMeio(&no, 3);
				printf("O processo do topo foi retirado da pilha!\n\n\n");
			break;
			case 3:
				ImprimePilha(&no);
            break;
			case 4:
				printf("Qual o processo que deseja buscar na pilha?\n");
				scanf("%d",&busca);
				ConsultaElemento(&no,busca);
            break;
			case 5:
				printf("Qual o mercado deseja colocar como prioridade?\n");
				scanf("%s",Nomesuper);
				Prioridade(&no, tamanho,Nomesuper);
			break;
        }
    }

    getchar();
    
    return 0; 
   
}


int VerificaPilhaVazia (pilha F)
{
    if(F.inicio == NULL && F.final == NULL)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

void Criapilha(pilha *F)
{
    F->final=NULL;
    F->inicio=F->final;
}

//Insere Processo
int Empilha (pilha *F, char *Nome, char *Identidade, char *Endereco, char *Telefone, float Valor, char *Data, char *Nomesuper, int cont)
{
    telemento_pilha *novo;
    novo = (telemento_pilha*) malloc(sizeof(telemento_pilha));

    novo->nome = (char*) malloc(20*sizeof(char));
    novo->identidade = (char*) malloc(10*sizeof(char));
    novo->endereco = (char*) malloc(100*sizeof(char));
    novo->telefone = (char*) malloc(9*sizeof(char));
    novo->data = (char*) malloc(10*sizeof(char));
    novo->nomesuper = (char*) malloc(20*sizeof(char));

    if (novo == NULL)
    {
        return 0;
    }

    strcpy(novo->nome, Nome);
    strcpy(novo->identidade, Identidade);
    strcpy(novo->endereco, Endereco);
    strcpy(novo->telefone, Telefone);
    strcpy(novo->data, Data);
    strcpy(novo->nomesuper, Nomesuper);
    novo->valor = Valor;
    novo->identificador = cont;

    if (VerificaPilhaVazia(*F))
    {
        F->inicio = novo;
        F->final =  novo;
        novo->prox=NULL;
    }
    else
    {
        novo->prox = F->inicio;
        F->inicio = novo;
    }
    tamanho++;
    return 1;
}

//Remove Processo
int DesEmpilha (pilha *F)
{
    telemento_pilha *remov;
    if (VerificaPilhaVazia(*F))
    {
        return 0;
    }
    /*if (F->inicio == F->final)
    {
        F->final = NULL;
    }*/
    remov = F->inicio;
    F->inicio = F->inicio->prox;
    free(remov->nome);
    free(remov->endereco);
    free(remov->telefone);
    free(remov->data);
    free(remov->nomesuper);
    free(remov->identidade);
    free(remov);
    tamanho--;
    
    return 1;
}


//Imprime lista dos processos
int ImprimePilha(pilha *F)
{
    telemento_pilha *p;
    p=F->inicio;
    if (VerificaPilhaVazia(*F))
    {
        printf ("A pilha está vazia!\n\n\n");
        return 0;
    }
    while(p!=NULL)
    {
        printf("-------------------------------------------\n");
        printf("Nome: %s\n", p->nome);
        printf("Identidade: %s\n", p->identidade);
        printf("Endereço: %s\n", p->endereco);
        printf("Telefone: %s\n", p->telefone);
        printf("Nome do Supermercado: %s\n", p->nomesuper);
        printf("Valor do Cheque: %f\n", p->valor);
        printf("Data do Cheque: %s\n", p->data);
        printf("Identificador: %d\n", p->identificador);
        printf("-------------------------------------------");
        printf("\n\n");
        p=p->prox;
    }
    return 1;
}

//Procura o processo na lista através da chave de registro do mesmo
int ConsultaElemento(pilha *F, int processo)
{
    int encontrado;
    telemento_pilha *p;
    p=F->inicio;
    if (VerificaPilhaVazia(*F))
    {
        printf ("O processo %d não está na pilha e a pilha está vazia\n",processo);
        return 0;
    }
    while(p!=NULL)
    {
        if (p->identificador == processo)
        {
            encontrado = 1;
            break;
        }
        p=p->prox;
    }

    if(encontrado == 1)
    {
        printf("-------------------------------------------\n");
        printf("Nome: %s\n", p->nome);
        printf("Identidade: %s\n", p->identidade);
        printf("Endereço: %s\n", p->endereco);
        printf("Telefone: %s\n", p->telefone);
        printf("Nome do Supermercado: %s\n", p->nomesuper);
        printf("Valor do Cheque: %f\n", p->valor);
        printf("Data do Cheque: %s\n", p->data);
        printf("Identificador: %d\n", p->identificador);
        printf("-------------------------------------------");
        printf("\n\n");
        return 1;
    }
    else
    {
        printf("O processo não está na pilha\n");
        return 0;
    }
}

int Ordena(pilha *F ,int tamanho)
{
    int aux_valor, i=0, j;
    int Identificador[tamanho], aux_identificador;
    float Valor[tamanho];
    char *nome[tamanho], *aux_nome, *Identidade[tamanho], *aux_identidade, *Endereco[tamanho], *aux_endereco, *Telefone[tamanho], 
    *aux_telefone, *Data[tamanho], *aux_data, *Nomesuper[tamanho], *aux_nomesuper;
    telemento_pilha *p;
    p=F->inicio;

	if (VerificaPilhaVazia(*F) || tamanho == 1)
    {
        return 0;
    }

	//copiando lista para o vetor
    while(p!=NULL)
    {

        Identidade[i] = (char*) malloc(10*sizeof(char));
        nome[i] = (char*) malloc(20*sizeof(char));
        Endereco[i] = (char*) malloc(100*sizeof(char));
        Telefone[i] = (char*) malloc(9*sizeof(char));
        Data[i] = (char*) malloc(10*sizeof(char));
        Nomesuper[i] = (char*) malloc(20*sizeof(char));
        aux_identidade = (char*) malloc(10*sizeof(char));
        aux_nome = (char*) malloc(20*sizeof(char));
        aux_endereco = (char*) malloc(100*sizeof(char));
        aux_telefone = (char*) malloc(9*sizeof(char));
        aux_data = (char*) malloc(10*sizeof(char));
        aux_nomesuper = (char*) malloc(20*sizeof(char));

        strcpy(nome[i],p->nome);
        strcpy(Identidade[i],p->identidade);
        strcpy(Endereco[i],p->endereco);
        strcpy(Telefone[i],p->telefone);
        Valor[i]=p->valor;
        strcpy(Data[i],p->data);
        strcpy(Nomesuper[i],p->nomesuper);
        Identificador[i]=p->identificador;
        DesEmpilha(F);
        i++;
        p=p->prox;
    }

    i=0;

    //ordenando
    for(j=tamanho-1; j>=1; j--)
    {
        for(i=0; i<j; i++)
        {
            if(Valor[i]>Valor[i+1])
            {
                strcpy(aux_nome,nome[i]);
                strcpy(aux_identidade,Identidade[i]);
                strcpy(aux_endereco,Endereco[i]);
                strcpy(aux_telefone,Telefone[i]);
                aux_valor=Valor[i];
                strcpy(aux_data,Data[i]);
                strcpy(aux_nomesuper,Nomesuper[i]);
                aux_identificador=Identificador[i];


                strcpy(nome[i],nome[i+1]);
                strcpy(Identidade[i],Identidade[i+1]);
                strcpy(Endereco[i],Endereco[i+1]);
                strcpy(Telefone[i],Telefone[i+1]);
                Valor[i]=Valor[i+1];
                strcpy(Data[i],Data[i+1]);
                strcpy(Nomesuper[i],Nomesuper[i+1]);
                Identificador[i]=Identificador[i+1];

                strcpy(nome[i+1],aux_nome);
                strcpy(Identidade[i+1],aux_identidade);
                strcpy(Endereco[i+1],aux_endereco);
                strcpy(Telefone[i+1],aux_telefone);
                Valor[i+1]=aux_valor;
                strcpy(Data[i+1],aux_data);
                strcpy(Nomesuper[i+1],aux_nomesuper);
                Identificador[i+1]=aux_identificador;
            }
        }
    }
    //reEmpilhando
    for(i=0; i<tamanho; i++)
    {
        Empilha (F, nome[i], Identidade[i], Endereco[i], Telefone[i], Valor[i], Data [i], Nomesuper[i], Identificador[i]);
    }

    free(aux_nome);
    free(aux_identidade);
    free(aux_endereco);
    free(aux_telefone);
    free(aux_data);
    free(aux_nomesuper);

	return 0;
}

int Prioridade(pilha *F, int tamanho, char *nomesuper)
{
    int aux_valor, i=0, j, b=0 /*, c*/;
    int Identificador[tamanho], aux_identificador;
    float Valor[tamanho];
    char *nome[tamanho], *aux_nome, *Identidade[tamanho], *aux_identidade, *Endereco[tamanho], *aux_endereco, *Telefone[tamanho], 
    *aux_telefone, *Data[tamanho], *aux_data, *Nomesuper[tamanho], *aux_nomesuper;
    telemento_pilha *p;
    p=F->inicio;

	if (VerificaPilhaVazia(*F) || tamanho == 1)
    {
        return 0;
    }


	//copiando lista para o vetor
    while(p!=NULL)
    {

        Identidade[i] = (char*) malloc(10*sizeof(char));
        nome[i] = (char*) malloc(20*sizeof(char));
        Endereco[i] = (char*) malloc(100*sizeof(char));
        Telefone[i] = (char*) malloc(9*sizeof(char));
        Data[i] = (char*) malloc(10*sizeof(char));
        Nomesuper[i] = (char*) malloc(20*sizeof(char));
        aux_identidade = (char*) malloc(10*sizeof(char));
        aux_nome = (char*) malloc(20*sizeof(char));
        aux_endereco = (char*) malloc(100*sizeof(char));
        aux_telefone = (char*) malloc(9*sizeof(char));
        aux_data = (char*) malloc(10*sizeof(char));
        aux_nomesuper = (char*) malloc(20*sizeof(char));

        strcpy(nome[i],p->nome);
        strcpy(Identidade[i],p->identidade);
        strcpy(Endereco[i],p->endereco);
        strcpy(Telefone[i],p->telefone);
        Valor[i]=p->valor;
        strcpy(Data[i],p->data);
        strcpy(Nomesuper[i],p->nomesuper);
        Identificador[i]=p->identificador;
        DesEmpilha(F);
        i++;
        p=p->prox;
    }

    i=0;

    //ordenando
    for(j=tamanho-1; j>=1; j--)
    {
        for(i=0; i<j; i++)
        {
            if(strcmp(nomesuper, Nomesuper[i]) == 0)
            {
                b++;
                strcpy(aux_nome,nome[i]);
                strcpy(aux_identidade,Identidade[i]);
                strcpy(aux_endereco,Endereco[i]);
                strcpy(aux_telefone,Telefone[i]);
                aux_valor=Valor[i];
                strcpy(aux_data,Data[i]);
                strcpy(aux_nomesuper,Nomesuper[i]);
                aux_identificador=Identificador[i];


                strcpy(nome[i],nome[i+1]);
                strcpy(Identidade[i],Identidade[i+1]);
                strcpy(Endereco[i],Endereco[i+1]);
                strcpy(Telefone[i],Telefone[i+1]);
                Valor[i]=Valor[i+1];
                strcpy(Data[i],Data[i+1]);
                strcpy(Nomesuper[i],Nomesuper[i+1]);
                Identificador[i]=Identificador[i+1];

                strcpy(nome[i+1],aux_nome);
                strcpy(Identidade[i+1],aux_identidade);
                strcpy(Endereco[i+1],aux_endereco);
                strcpy(Telefone[i+1],aux_telefone);
                Valor[i+1]=aux_valor;
                strcpy(Data[i+1],aux_data);
                strcpy(Nomesuper[i+1],aux_nomesuper);
                Identificador[i+1]=aux_identificador;
            }
        }
    }



    for(j=tamanho-1; j>=b+1; j--)
    {
        for(i=b+1; i<=j; i++)
        {
            if(Valor[i] > Valor[i+1])
            {
                strcpy(aux_nome,nome[i]);
                strcpy(aux_identidade,Identidade[i]);
                strcpy(aux_endereco,Endereco[i]);
                strcpy(aux_telefone,Telefone[i]);
                aux_valor=Valor[i];
                strcpy(aux_data,Data[i]);
                strcpy(aux_nomesuper,Nomesuper[i]);
                aux_identificador=Identificador[i];


                strcpy(nome[i],nome[i+1]);
                strcpy(Identidade[i],Identidade[i+1]);
                strcpy(Endereco[i],Endereco[i+1]);
                strcpy(Telefone[i],Telefone[i+1]);
                Valor[i]=Valor[i+1];
                strcpy(Data[i],Data[i+1]);
                strcpy(Nomesuper[i],Nomesuper[i+1]);
                Identificador[i]=Identificador[i+1];

                strcpy(nome[i+1],aux_nome);
                strcpy(Identidade[i+1],aux_identidade);
                strcpy(Endereco[i+1],aux_endereco);
                strcpy(Telefone[i+1],aux_telefone);
                Valor[i+1]=aux_valor;
                strcpy(Data[i+1],aux_data);
                strcpy(Nomesuper[i+1],aux_nomesuper);
                Identificador[i+1]=aux_identificador;
            }
        }
    }

    //reEmpilhando
    for(i=0; i<tamanho; i++)
    {
        Empilha (F, nome[i], Identidade[i], Endereco[i], Telefone[i], Valor[i], Data[i],Nomesuper[i], Identificador[i]);
    }

    free(aux_nome);
    free(aux_identidade);
    free(aux_endereco);
    free(aux_telefone);
    free(aux_data);
    free(aux_nomesuper);

	return 0;
}
