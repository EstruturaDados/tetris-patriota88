#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define TAM_FILA 5

//Peça
typedef struct 
{
    char tipo; 
    int id;
} Peca;

//Fila Circular
typedef struct 
{
    Peca itens[TAM_FILA];
    int frente;
    int fim;
    int total;
}FilaCiruclar;

//Criando uma fuçao para gerar uma peça
Peca gerarPeca() 
{
    char tipos[] = {'I', 'O', 'T', 'L'};
    Peca nova;
    nova.tipo = tipos[rand() % 4];
    nova.id = rand() % 1000 + 100; // entre ID 100 e 1100
    return nova;
}

//Fila com 5 peças
void iniciaLizarFila(FilaCiruclar *f) 
{
    f->frente = 0;
    f->fim = -1;
    f->total = 0;

    printf("Gerando fila inicial de pecas...\n");
    for(int i = 0; i < TAM_FILA; i++)
    {
        f->fim = (f->fim + 1) % TAM_FILA;
        f->itens[f->fim] = gerarPeca();
        f->total++;
    }
}

//Visualizar fila
void visualizarFila(FilaCiruclar f)
{
    printf("\n--- FILA DE PECAS (Proximas) ---\n");
    if(f.total == 0){
        printf("Fila vazia!\n");
        return;
    }
    int i = f.frente;
    for(int cont = 0; cont < f.total; cont++)
    {
        printf("[%c - ID: %d] ", f.itens[i].tipo, f.itens[i].id);
        i = (i + 1) % TAM_FILA; //Para gerar o movimento circualr
    }
    printf("\n----------------------------------------\n");
}

//Jogar
void jogarPeca(FilaCiruclar *f)
{
    if(f->total == 0)
    {
        printf("Erro: Nao ha pecas para jogar!\n");
        return;
    }

    //Remover
    Peca pecaJogada = f->itens[f->frente];
    printf("\n>>> Voce jogou a peca [%c]!\n", pecaJogada.tipo);
    f->frente = (f->frente + 1) % TAM_FILA;
    f->total--;

    //Adicionar nova peca ao fim da fila
    f->fim =(f->fim + 1) % TAM_FILA;
    f->itens[f->fim] = gerarPeca();
    f->total++;
    printf(">>> Nova peça gerada no final da fila\n");
}

int main()
{
   srand(time(NULL)); //Numeros aleatorios
   FilaCiruclar minhaFila;
   int opcao;
   
   iniciaLizarFila(&minhaFila);

   do {
    visualizarFila(minhaFila);
    printf("\nMENU TETRIS STACK (Novato)\n");
    printf("1. Jogar peca (Remover da frente)\n");
    printf("0. Sair\n");
    printf("Escolha: ");
    scanf("%d", &opcao);

    switch (opcao)
    {
    case 1: jogarPeca(&minhaFila);        
        break;
    case 0: printf("Saindo...\n");
        break;
    default: printf("Opçao invalida!\n");  
    }
   } while (opcao != 0);
   
   return 0;
}
