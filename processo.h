#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Declaração da Struct
typedef struct elemento_fila
{
    //int dado;
    char *nome;
    char *identidade;
    char *endereco;
    char *telefone;
    float valor;
    char *nomesuper;
    int identificador;
    struct elemento_fila* prox; //estrutura que define os processos da fila
} telemento_fila;

typedef struct fila
{
    telemento_fila* inicio;
    telemento_fila* final;      //estrutura que define a estrutura da fila
} fila;

int tamanho;

int VerificaFilaVazia (fila F);
void CriaFila(fila *F);
int Enfileira (fila *F, char *Nome, char *Identidade, char *Endereco, char *Telefone, float Valor, char *Nomesuper, int cont);
int Desenfileira (fila *F);
int ImprimeFila(fila *F);
int ConsultaElemento(fila *F, int processo);
void Ordena(fila *F ,int tamanho);

//Verifica se a pilha de processos está vazia
int main(int argc, char *argv[])
{
    fila no;
    fila *b;
    int cont;
    int opcao=1;
    float Valor;
    char *Nome, *Identidade, *Endereco, *Telefone, *Nomesuper;
    CriaFila(&no);

    srand(time(NULL));

    while(opcao != 0)
    {
        //system("clear"); //se for rodar no linux
        //system("cls"); // se for rodar no windows

        printf("==================== FILA ====================\n");
        printf("1 - Inserir processo na fila\n");
        printf("2 - Remover processo da fila\n");
        printf("3 - Listar todos os processos\n");
        printf("4 - Consultar processo\n");
        printf("0 - Sair\n");
        scanf("%d",&opcao);

        switch(opcao)
        {
        case 1:

            Nome = (char*) malloc(20*sizeof(char));
            Identidade = (char*) malloc(10*sizeof(char));
            Endereco = (char*) malloc(100*sizeof(char));
            Telefone = (char*) malloc(9*sizeof(char));
            Nomesuper = (char*) malloc(20*sizeof(char));

            printf("Digite o valor \n");
            scanf("%f",&Valor);
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
            Enfileira (&no , Nome, Identidade, Endereco, Telefone, Valor, Nomesuper, cont);
            if(tamanho > 1)
            {
                Ordena(&no , tamanho);
            }
            printf("O processo foi colocado na fila!\n\n\n");
            break;
        case 2:
            Desenfileira(&no);
            printf("O primeiro processo foi retirado da fila!\n\n\n");
            break;
        case 3:
            ImprimeFila(&no);
            break;
        case 4:
            printf("Qual o processo que deseja buscar na fila?\n");
            scanf("%f",&Valor);
            ConsultaElemento(&no,Valor);
            break;
        }
    }

    getchar();
    return 0;
}
