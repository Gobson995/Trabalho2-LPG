#ifndef funcoes_auxiliares_h
#define funcoes_auxiliares_h

#include "estruturas.h"

void carregar_arquivo(struct Evento **vetor, int *numeroEventos);
int data_valida(int dia, int mes, int ano);
int horario_valido(int hora, int minuto);
void ordenar_eventos(struct Evento *vetor, int numeroEventos);
int compara_eventos(struct Evento a, struct Evento b);
void salvar_arquivo(struct Evento *vetor, int numeroEventos);

#endif