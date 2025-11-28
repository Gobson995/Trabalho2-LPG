#ifndef funcoes_principais_h
#define funcoes_principais_h

#include "estruturas.h"
#include "funcoes_auxiliares.h"

void cadastrar_eventos(struct Evento **vetor, int *numeroEventos);
void mostrar_todos(struct Evento *vetor, int numeroEventos);
void mostrar_data(struct Evento *vetor, int nemeroEventos);
void mostrar_descricao(struct Evento *vetor, int numeroEventos);

#endif