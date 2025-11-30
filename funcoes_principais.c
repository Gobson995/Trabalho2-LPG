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

void mostrar_data (struct Evento *vetor, int numeroEventos) {
    if (numeroEventos == 0) {
        printf("Nenhum evento cadastrado na agenda. \n");
        return;
    }

    int dia, mes, ano;
    printf("Digite a data que deseja buscar (dia mes ano): ");
    scanf("%d %d %d", &dia, &mes, &ano);

    if (!data_valida(dia, mes, ano)) {
        printf("Data inválida.\n");
        return;
    }

    struct Evento inicioBusca;
    inicioBusca.data.dia = dia;
    inicioBusca.data.mes = mes;
    inicioBusca.data.ano = ano;
    inicioBusca.inicio.hora = 0;
    inicioBusca.inicio.minuto = 0;

    struct Evento fimBusca;
    fimBusca.data.dia = dia;
    fimBusca.data.mes = mes;
    fimBusca.data.ano = ano;
    fimBusca.inicio.hora = 23;
    fimBusca.inicio.minuto = 59;

    int encontrou = 0;

    printf("\n Evento do dia %02d/%02d/%04d \n\n", dia, mes, ano);
    
    struct Evento *atual = NULL;

    int j = 0;

    for (int i = 0; i < numeroEventos; i++) {

        if (compara_eventos(vetor[i], inicioBusca) >= 0 && compara_eventos(vetor[i], fimBusca) <= 0) {
            encontrou = 1;

            struct Evento *aux = realloc(atual, (j + 1) * sizeof(struct Evento));
            atual = aux;
            atual[j] = vetor[i];
            j++;
        } 
    }

    if (!encontrou) {
        printf("Nenhum evento encontrado nesta data.\n");
        return;
    }

    mostrar_todos(atual, j);
    free(atual);
}

void mostrar_descricao(struct Evento *vetor, int numeroEventos) {
    if(numeroEventos == 0) {
        printf("Nenhum evento cadastrado na agenda.\n");
        return;
    }

    char descricaoBusca[50];

    getchar(); 
    printf("Digite a descrição que deseja buscar: ");
    fgets(descricaoBusca, sizeof(descricaoBusca), stdin);
    descricaoBusca[strcspn(descricaoBusca, "\n")] = '\0';

    int encontrou = 0;

    struct Evento *atual = NULL;
    int j = 0;

    for (int i = 0; i < numeroEventos; i++) {
        if(strstr(vetor[i].descricao, descricaoBusca) != NULL) {
            encontrou = 1;

            struct Evento *aux = realloc(atual, (j+1) * sizeof(struct Evento));

            if (aux == NULL) {
                printf("Erro de memória.\n");
                free(atual);
                return;
            }

            atual = aux;
            atual[j] = vetor[i];
            j++;
        }
    }

    if(!encontrou){
        printf("Nenhum evento encontrado contendo \"%s\".\n", descricaoBusca);
        return;
    }

    printf("\n----- Eventos contendo \"%s\" -----\n\n", descricaoBusca);

    mostrar_todos(atual, j);
    free(atual);
}
void remover_evento(struct Evento **vetor, int *numeroEventos) {
    if(*numeroEventos == 0) {
        printf("Nenhum evento cadastrado na agenda.\n");
        return;
    }

    Data dataEvento;
    Horario horaEvento;
    printf("Digite o dia, mês e ano do evento: ");
    scanf("%d %d %d", &dataEvento.dia, &dataEvento.mes, &dataEvento.ano);
    if(!data_valida(&dataEvento.dia, &dataEvento.mes, &dataEvento.ano)){
        printf("Data inválida \n");
        return;
    }
    printf("Digite o hora, minuto do evento: ");
    scanf("%d %d ", &horaEvento.hora, &horaEvento.minuto);
    if(!horario_valido(&horaEvento.hora, &horaEvento.minuto)){
        printf("Data inválida \n");
        return;
    }
    int encontrou = 0;

    for (int i = 0; i < *numeroEventos; i++) {
        if(data_equals(dataEvento, (*vetor)[i].data) && 
           horario_equals(horaEvento, (*vetor)[i].inicio)) {
            
            encontrou = 1;
            
            for(int j = i; j < *numeroEventos - 1; j++){
                (*vetor)[j] = (*vetor)[j + 1];
            }
            (*numeroEventos)--;
            struct Evento *aux = realloc(*vetor, (*numeroEventos) * sizeof(struct Evento));
            if(*numeroEventos > 0 || aux != NULL) {
                *vetor = aux;
            }
            printf("Evento removido com sucesso!\n");
            salvar_arquivo(*vetor, *numeroEventos);
            break;
        }
    }

    if(!encontrou){
        printf("Nenhum evento encontrado na data \"%02d/%02d/%04d\" às %02d:%02d.\n",
               dataEvento.dia, dataEvento.mes, dataEvento.ano, horaEvento.hora, horaEvento.minuto);
    }
}