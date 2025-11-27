#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "funcoes_principais.h"
#include "funcoes_auxiliares.h"
#include "estruturas.h"

void cadastrar_eventos(struct Evento **vetor, int *numeroEventos){
    ordenar_eventos(*vetor, *numeroEventos);
    struct Evento novo;

    printf("Digite o dia, mês e ano do evento: ");
    scanf("%d %d %d", &novo.data.dia, &novo.data.mes, &novo.data.ano);

    if(!data_valida(novo.data.dia, novo.data.mes, novo.data.ano)){
        printf("Data inválida \n");
        return;
    }

    printf("Digite o horário de início (Hora : Minuto): ");
    scanf("%d %d", &novo.inicio.hora, &novo.inicio.minuto);

    if(!horario_valido(novo.inicio.hora, novo.inicio.minuto)){
        printf("Horário inválido\n");
        return;
    }

    printf("Digite o horário final (Hora : Minuto): ");
    scanf("%d %d", &novo.fim.hora, &novo.fim.minuto);

    if(!horario_valido(novo.fim.hora, novo.fim.minuto)){
        printf("Horário inválido\n");
        return;
    }

    if(novo.fim.hora < novo.inicio.hora || (novo.inicio.hora == novo.fim.hora && novo.fim.minuto < novo.inicio.minuto)){
        printf("Horário inválido\n");
        return;
    }

    getchar();

    printf("Digite a descrição: ");
    fgets(novo.descricao, sizeof(novo.descricao), stdin);
    novo.descricao[strcspn(novo.descricao, "\n")] = '\0';

    printf("Digite o local: ");
    fgets(novo.local, sizeof(novo.local), stdin);
    novo.local[strcspn(novo.local, "\n")] = '\0';


    for(int i = 0;i < *numeroEventos;i++){
        struct Evento evento = (*vetor)[i];

        if(evento.data.dia == novo.data.dia && 
            evento.data.mes == novo.data.mes && 
            evento.data.ano == novo.data.ano)
        {

            int inicio1 = novo.inicio.hora * 60 + novo.inicio.minuto;
            int final1 = novo.fim.hora * 60 + novo.fim.minuto;

            int inicio2 = evento.inicio.hora * 60 + evento.inicio.minuto;
            int final2 = evento.fim.hora * 60 + evento.fim.minuto;

            int sobrepoe = 0;
            if(final1 > inicio2 && inicio1 < final2) sobrepoe = 1;

            if(sobrepoe){
                if(strcmp(novo.descricao, evento.descricao) == 0 && strcmp(novo.local, evento.local) == 0){
                    printf("Esse evento já existe!\n");
                    return;
                }

                printf("Esse evento sobrepoe outro!\n");
                return;
            }
        }
    }

    struct Evento *aux = realloc(*vetor, (*numeroEventos + 1) * sizeof(struct Evento));
    if(!aux){
        printf("Erro de memória\n");
        return;
    }

    *vetor = aux;
    (*vetor)[*numeroEventos] = novo;
    (*numeroEventos)++;
    ordenar_eventos(*vetor, *numeroEventos);


    FILE *f = fopen("eventos.txt", "a");
    ordenar_eventos(*vetor, *numeroEventos);
    salvar_arquivo(*vetor, *numeroEventos);

    fclose(f);
    printf("Evento cadastrado com sucesso!\n");

}


void mostrar_todos(struct Evento *vetor, int numeroEventos){

    if(numeroEventos == 0){
        printf("Nenhum evento cadastrado na agenda.\n");
        return;
    }

    printf("----- Lista de eventos (%d) -----\n\n", numeroEventos);

    for(int i = 0; i < numeroEventos; i++){
        struct Evento eventos = vetor[i];

        printf("Evento %d:\n", i + 1);
        printf("%02d/%02d/%04d\n", eventos.data.dia, eventos.data.mes, eventos.data.ano);
        printf("Horário inicial: %02d:%02d\n", eventos.inicio.hora, eventos.inicio.minuto);
        printf("Horário final: %02d:%02d\n", eventos.fim.hora, eventos.fim.minuto);
        printf("Descrição: %s\n", eventos.descricao);
        printf("Local: %s\n", eventos.local);
        printf("\n");

    }
}




