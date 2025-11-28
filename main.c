#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "funcoes_principais.h"
#include "funcoes_auxiliares.h"
#include "estruturas.h"

int main(){

    int numeroEventos = 0;
    struct Evento *vetor = NULL;

    carregar_arquivo(&vetor, &numeroEventos);
    ordenar_eventos(vetor, numeroEventos);
    salvar_arquivo(vetor, numeroEventos);
    
    int rodaPrograma = 1;
    while(rodaPrograma){
        printf("------------------ Menu de texto ------------------\n\n");

        printf("A seguir digite o valor para: \n");
        printf("1. Cadastrar (somente um) novo evento na agenda \n");
        printf("2. Mostrar todos os eventos da agenda \n");
        printf("3. Mostrar eventos com dada uma data \n");
        printf("4. Mostrar eventos com dada descrição \n");
        printf("5. Remover evento \n");
        printf("6. Sair \n");

        printf("\n----------------------------------------------------\n");
        
        int escolha;
        scanf("%d", &escolha);
        if(escolha > 6 || escolha < 1) escolha = 7;

        switch(escolha){

        case 1:
            cadastrar_eventos(&vetor, &numeroEventos);  
            break;
        case 2:
            mostrar_todos(vetor, numeroEventos);
            break;
        case 3:
            mostrar_data(vetor, numeroEventos);
            break;
        case 4: 
            mostrar_descricao(vetor, numeroEventos);
            break;
        case 5: 
            remover_evento(vetor,numeroEventos);
            break;
        case 6:
            rodaPrograma = 0;
            // salva_libera();
            break;
        case 7:
            printf("Você digitou um elemento inválido, digite novamente \n");
            break;
        }

    }
}



