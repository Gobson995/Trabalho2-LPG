#ifndef ESTRUTURAS_H
#define ESTRUTURAS_H

typedef struct{
    int dia, mes, ano;
} Data;

typedef struct{
    int hora, minuto;
} Horario;

struct Evento{
    Data data;
    Horario inicio;
    Horario fim;
    char descricao[50];
    char local[50];
};

#endif