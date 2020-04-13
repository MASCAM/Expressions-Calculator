#define PILHA_H

typedef struct elemento{
	char dado;
	float numero;
	struct  elemento* anterior;
} t_elemento;

typedef struct {
	t_elemento* topo;
	int tamanho;
} t_pilha;

void empilhar(t_pilha* pilha, char dados, float numero);

char desempilhar_char(t_pilha* pilha);

float desempilhar_float(t_pilha* pilha);

int converte_valores(char* aponta_expressao_de_saida, float* aponta_numeros);

void esvazia_pilha(t_pilha* pilha);

t_pilha* aloca_pilha();

void flush_in();

float resolve_expressao(t_pilha* pilha, float* aponta_numeros, char* expressao_de_saida);

void posfixa(char* expressao_de_saida, char dados[100], t_pilha* pilha);

int valida_expressao(t_pilha* pilha, char expressao[100]);

