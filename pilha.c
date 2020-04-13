#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "pilha.h"


void flush_in() {
	int ch;
	do {
		ch = fgetc(stdin);       // função que limpa a entrada de dados //
	} while (ch != EOF && ch != '\n');
}

void empilhar(t_pilha* pilha, char dados, float numero) {
	t_elemento* elemento = (t_elemento*) malloc(sizeof(t_elemento));
	elemento->dado = dados;
	elemento->numero = numero;
	elemento->anterior = pilha->topo;
	pilha->topo = elemento;
	pilha->tamanho++;
}

t_pilha* aloca_pilha() {
	t_pilha* pilha = (t_pilha*) malloc(sizeof(t_pilha));
	pilha->tamanho = 0;
	pilha->topo = NULL;
	return pilha;
}

char desempilhar_char(t_pilha* pilha) {
	char inutil, dado;
	if (pilha->tamanho != 0) {
		dado = pilha->topo->dado;
		t_elemento* auxiliar = pilha->topo->anterior;
		free(pilha->topo);
		pilha->topo = auxiliar;	
		pilha->tamanho--;
	} else {
		printf("Ocorreu um underflow na pilha (ou esta sendo esvaziada). Pressione enter para continuar.\n");
		flush_in();
		scanf("%c", &inutil);
		flush_in();
		free(pilha);
		return 'w';
	}
	return dado;
}

float desempilhar_float(t_pilha* pilha) {
	char inutil;
	float dado;
	if (pilha->tamanho != 0) {
		dado = pilha->topo->numero;
		t_elemento* auxiliar = pilha->topo->anterior;
		free(pilha->topo);
		pilha->topo = auxiliar;	
		pilha->tamanho--;
	} else {
		printf("Ocorreu um underflow na pilha (ou esta sendo esvaziada). Pressione enter para continuar.\n");
		flush_in();
		scanf("%c", &inutil);
		flush_in();
		free(pilha);
		return 0.0;
	}
	return dado;
}

void esvazia_pilha(t_pilha* pilha) {
	char esvazia = 'z';
	while (esvazia != 'w') {
		esvazia = desempilhar_char(pilha);
	}
}

int converte_valores(char* aponta_expressao_de_saida, float* aponta_numeros) {
	int quantidade = 0, indice = 0, i = 0, j = 0;
	float soma = 0.0, unidade = 1.0;
	char expressao[100];
	while (*aponta_expressao_de_saida != '\0') {
		if (*aponta_expressao_de_saida == ' ') {
			expressao[i] = '_';
		} else {
			expressao[i] = *aponta_expressao_de_saida;
		}
		aponta_expressao_de_saida++;
		i++;
	}
	expressao[i] = '\0';
	while (expressao[j] != '\0') {
		indice = 0;
		unidade = 1.0;
		soma = 0.0;
		if (expressao[j] >= '0' && expressao[j] <= '9') {
			while ((expressao[j] >= '0' && expressao[j] <= '9') || expressao[j] == ',' ) {
				if (expressao[j] == ',') {
					indice = 1;
				}
				if (indice == 0 && soma == 0.0 && expressao[j] != ',') {
					soma+= expressao[j] - '0';
				} else if (indice == 0 && expressao[j] != ',') {
					soma*= 10.0;
					soma+= expressao[j] - '0';
				} else if (indice == 1 && expressao[j] != ',') {
					soma+= (expressao[j] - '0') * (unidade * 0.1);
					unidade*= 0.1;
				}
				j++;
			}
			*aponta_numeros = soma;
			aponta_numeros++;
			quantidade++;	
		}
		j++;
	}
	return quantidade;
}