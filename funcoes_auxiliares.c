#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "funcoes_principais.h"
#include "funcoes_auxiliares.h"
#include "estruturas.h"    


int data_valida(int dia, int mes, int ano){
    
    if(mes > 12 || mes < 1 || dia > 31 || dia < 1 || ano < 1) return 0;
    
    if((mes == 4 || mes == 6 || mes == 9 || mes == 11) && dia == 31) return 0;

    if(mes == 2 && dia > 28) return 0;

    return 1;
}

int horario_valido(int hora, int minuto){
    if(hora >= 24 || hora < 0 || minuto >= 60 || minuto < 0) return 0;
    return 1;
}

void carregar_arquivo(struct Evento **vetor, int *numeroEventos){
    
    ordenar_eventos(*vetor, *numeroEventos);
    FILE *f = fopen("eventos.txt", "r");

    if(f == NULL){
        *vetor = NULL;
        *numeroEventos = 0;
        return;
    }

    char linha[300];
    struct Evento aux; 
    *vetor = NULL; 
    *numeroEventos = 0;

    while(fgets(linha, sizeof(linha), f)){

        int lidos = sscanf(linha, "%d/%d/%d", &aux.data.dia, &aux.data.mes, &aux.data.ano);
        if(lidos != 3) break;

        if(!fgets(linha, sizeof(linha), f)) break;
        lidos = sscanf(linha, "Horário inicial: %02d:%02d", &aux.inicio.hora, &aux.inicio.minuto);
        if(lidos != 2) break;

        if(!fgets(linha, sizeof(linha), f)) break;
        lidos = sscanf(linha, "Horário final: %02d:%02d", &aux.fim.hora, &aux.fim.minuto);
        if(lidos != 2) break;


        if(!fgets(linha, sizeof(linha), f)) break;
        else{

            char *prefixoDescricao = "Descrição: ";
            int tamanho = strlen(prefixoDescricao);

            if(strncmp(linha, prefixoDescricao, tamanho) == 0){
                strncpy(aux.descricao, linha + tamanho, sizeof(aux.descricao) - 1);
            }
            else{
                strncpy(aux.descricao, linha, sizeof(aux.descricao) - 1);
            }

            aux.descricao[sizeof(aux.descricao) - 1] = '\0';
            aux.descricao[strcspn(aux.descricao, "\n")] = '\0';

        }

        if(!fgets(linha, sizeof(linha), f)) break;
        else{

            char *prefixoLocal = "Local: ";
            int tamanho = strlen(prefixoLocal);

            if(strncmp(linha, prefixoLocal, tamanho) == 0){
                strncpy(aux.local, linha + tamanho, sizeof(aux.local) - 1);
            }
            else{
                strncpy(aux.local, linha, sizeof(aux.local) - 1);
            }

            aux.local[sizeof(aux.local) - 1] = '\0';
            aux.local[strcspn(aux.local, "\n")] = '\0';
        }

        fgets(linha, sizeof(linha), f);

        struct Evento *aux2 = realloc(*vetor, (*numeroEventos + 1) * sizeof(struct Evento));

        if(!aux2){
            printf("Erro de memória ao carregar arquivo\n");
            free(*vetor);
            *vetor = NULL;
            *numeroEventos = 0;
            fclose(f);
            return;
        }

        *vetor = aux2;
        (*vetor)[*numeroEventos] = aux;
        (*numeroEventos)++;
    }

    fclose(f);
}

int compara_eventos(struct Evento a, struct Evento b){
    
    if(a.data.ano != b.data.ano) return a.data.ano - b.data.ano;
    if(a.data.mes != b.data.mes) return a.data.mes - b.data.mes;
    if(a.data.dia != b.data.dia) return a.data.dia - b.data.dia;

    int inicioA = a.inicio.hora * 60 + a.inicio.minuto;
    int inicioB = b.inicio.hora * 60 + b.inicio.minuto;

    return inicioA - inicioB;
}

void ordenar_eventos(struct Evento *vetor, int numeroEventos){
    for(int i = 0;i < numeroEventos - 1;i++){
        for(int j = i + 1;j < numeroEventos;j++){
            if(compara_eventos(vetor[j], vetor[i]) < 0){
                struct Evento aux = vetor[i];
                vetor[i] = vetor[j];
                vetor[j] = aux;
            }
        }
    }
}

void salvar_arquivo(struct Evento *vetor, int numeroEventos){
    FILE *f = fopen("eventos.txt", "w");
    if(f == NULL){
        printf("Erro ao abrir arquivo para salvar!\n");
        return;
    }

    for(int i = 0;i < numeroEventos;i++){
        struct Evento evento = vetor[i];
        fprintf(f, "%02d/%02d/%04d\n", evento.data.dia, evento.data.mes, evento.data.ano);
        fprintf(f, "Horário inicial: %02d:%02d\n", evento.inicio.hora, evento.inicio.minuto);
        fprintf(f, "Horário final: %02d:%02d\n", evento.fim.hora, evento.fim.minuto);
        fprintf(f, "Descrição: %s\n", evento.descricao);
        fprintf(f, "Local: %s\n\n", evento.local);
    }

    fclose(f);
}
