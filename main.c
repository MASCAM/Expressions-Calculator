#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "pilha.h"

float resolve_expressao(t_pilha* pilha, float* aponta_numeros, char* expressao_de_saida) {
	int i = 0, j = 0;
	float operando_1, operando_2, resultado;
	char expressao[100];
	while (*expressao_de_saida != '\0') {
		if (*expressao_de_saida == ' ') {
			expressao[i] = '_';
		} else {
			expressao[i] = *expressao_de_saida;
		}
		expressao_de_saida++;
		i++;
	}
	expressao[i] = '\0';
	while (expressao[j] != '\0') {
		if (expressao[j] >= '0' && expressao[j] <= '9') {
			empilhar(pilha, 'w', *aponta_numeros);
			aponta_numeros++;
			while ((expressao[j] >= '0' && expressao[j] <= '9') || expressao[j] == ',') {
				j++;
			}
		} else if (expressao[j] == '+' && pilha->tamanho >= 2) {
			operando_1 = desempilhar_float(pilha);
			operando_2 = desempilhar_float(pilha);
			resultado = operando_2 + operando_1;
			empilhar(pilha, 'w', resultado);
		} else if (expressao[j] == '-' && pilha->tamanho >= 2) {
			operando_1 = desempilhar_float(pilha);
			operando_2 = desempilhar_float(pilha);
			resultado = operando_2 - operando_1;
			empilhar(pilha, 'w', resultado);
		} else if (expressao[j] == '/' && pilha->tamanho >= 2) {
			operando_1 = desempilhar_float(pilha);
			operando_2 = desempilhar_float(pilha);
			resultado = operando_2 / operando_1;
			empilhar(pilha, 'w', resultado);
		} else if (expressao[j] == '*' && pilha->tamanho >= 2) {
			operando_1 = desempilhar_float(pilha);
			operando_2 = desempilhar_float(pilha);
			resultado = operando_2 * operando_1;
			empilhar(pilha, '*', resultado);
		}
		j++;
	}	
	resultado = desempilhar_float(pilha);
	free(pilha);
	return resultado;
}

void posfixa(char* expressao_de_saida, char dados[100], t_pilha* pilha) {
	int i = 0, j = 0;
	char caractere = 'w';
	while (dados[i] != '\0') {
		if ((dados[i] >= '0' && dados[i] <= '9') || dados[i] == ',' ) {
			while ((dados[i] >= '0' && dados[i] <= '9') || dados[i] == ',' ) {
				*expressao_de_saida = dados[i]; 
				expressao_de_saida++;
				i++;
			}
			*expressao_de_saida = ' ';
			expressao_de_saida++;
		}
		if (dados[i] == '+' || dados[i] == '-') {
			if (pilha->tamanho == 0) {
				empilhar(pilha, dados[i], 0.0);
			} else {
				while ((caractere != '{' && caractere != '[' && caractere != '(') && pilha->tamanho != 0)  {
					caractere = desempilhar_char(pilha);
					if (caractere != '{' && caractere != '[' && caractere != '(') {
						*expressao_de_saida = caractere;
						expressao_de_saida++;
						*expressao_de_saida = ' ';
						expressao_de_saida++;
					} else {
						empilhar(pilha, caractere, 0.0);
					}
				}
				empilhar(pilha, dados[i], 0.0);
			} 

		} else if (dados[i] == '*' || dados[i] == '/') {
			caractere = '/';
			if (pilha->tamanho != 0) {
				while ((caractere == '/' || caractere == '*') && pilha->tamanho != 0) {
					caractere = desempilhar_char(pilha);
					if (caractere == '/' || caractere == '*') {
						*expressao_de_saida = caractere;
						expressao_de_saida++;
						*expressao_de_saida = ' ';
						expressao_de_saida++;
					} else {
						empilhar(pilha, caractere, 0.0);
					}
				}
			}
			empilhar(pilha, dados[i], 0.0);
		}  else if (dados[i] == '(' || dados[i] == '[' || dados[i] == '{') {
			empilhar(pilha, dados[i], 0.0);
		} else if (dados[i] == '}' || dados[i] == ']' || dados[i] == ')') {
			caractere = 'w';
			while ((caractere != '{' && caractere != '[' && caractere != '(') && pilha->tamanho != 0) {
				caractere = desempilhar_char(pilha);
				if (caractere != '{' && caractere != '[' && caractere != '(') {
					*expressao_de_saida = caractere;
					expressao_de_saida++;
					*expressao_de_saida = ' ';
					expressao_de_saida++;
				}
			}
		}
		i++;
	}
	while (pilha->tamanho != 0) {
		caractere = desempilhar_char(pilha);
		if (caractere != '{' && caractere != '[' && caractere != '(') {
			*expressao_de_saida = caractere;
			expressao_de_saida++;
			*expressao_de_saida = ' ';
			expressao_de_saida++;
		}
	}
	free(pilha);
	*expressao_de_saida = '\0';
}

int valida_expressao(t_pilha* pilha, char expressao[100]){
	t_elemento* auxiliar = pilha->topo;
	char comparador;
	int i = 0, contador = 0;
	while (expressao[i] != '\0'){
		if (expressao[i] == '{' || expressao[i] == '[' || expressao[i] == '(') {
			empilhar(pilha, expressao[i], 0.0);
			contador++;
		} else if (expressao[i] == '}') {
			if (pilha->tamanho == 0) {
				return 0;
			}
			comparador = desempilhar_char(pilha);
			if (comparador != '{') {
				esvazia_pilha(pilha);
				return 0;
			}
			contador--;
		} else if (expressao[i] == ']'){
			if (pilha->tamanho == 0) {
				return 0;
			}
			comparador = desempilhar_char(pilha);
			if (comparador != '[') {
				esvazia_pilha(pilha);
				return 0;
			}	
			contador--;
		} else if (expressao[i] == ')'){
			if (pilha->tamanho == 0) {
				return 0;
			}
			comparador = desempilhar_char(pilha);
			if (comparador != '(') {
				esvazia_pilha(pilha);
				return 0;
			}
			contador--;
		} 
		i++;
	}
	if (contador != 0) {
		return 0;
	}
	return 1;
}

int main(int argc, const char* argv[]) {
	t_pilha* pilha;
	int opcao = 1, sucesso = 0, quantidade_numeros = 0, i = 0, j = 0;
	char dados[100], inutil, expressao_de_saida[100];
	char* aponta_expressao_de_saida = &expressao_de_saida[0];
	char* aponta_dados = &dados[0];
	float numeros[100], resultado = 0.0;
	float* aponta_numeros = &numeros[0];
	while(opcao != 0) {
		while (aponta_expressao_de_saida != &expressao_de_saida[0]) {
			*aponta_expressao_de_saida = '\0';
			aponta_expressao_de_saida--;
		}
		for (i = 0; i < 100; i++) {
			dados[i] = '\0';
		}
		aponta_numeros = &numeros[0];
		aponta_expressao_de_saida = &expressao_de_saida[0];
		printf("1 - Resolucao de expressoes matematicas\n");
		printf("2 - Calculadora\n\n");
		printf("0 - Sair\n");
		scanf("%d", &opcao);
		if (opcao == 1){
			pilha = aloca_pilha();
			printf("Digite uma expressao matematica de ate 100 caracteres:\n");
			flush_in();
			scanf("%100[^\n]s", dados);
			sucesso = valida_expressao(pilha, dados);
			if (sucesso == 1) {
				printf("A expressao fornecida e valida. Pressione enter para continuar.\n");
				flush_in();
				scanf("%c", &inutil);
				esvazia_pilha(pilha);
				pilha = aloca_pilha();
				posfixa(aponta_expressao_de_saida, dados, pilha);
				printf("A expressao na forma posfixa e:\n");
				printf("%s\n\n", expressao_de_saida);
				printf("Pressione enter para continuar\n");
				flush_in();
				scanf("%c", &inutil);
				aponta_expressao_de_saida = &expressao_de_saida[0];
				quantidade_numeros = converte_valores(aponta_expressao_de_saida, aponta_numeros);
				aponta_numeros = &numeros[0];
				aponta_expressao_de_saida = &expressao_de_saida[0];
				pilha = aloca_pilha();
				resultado = resolve_expressao(pilha, aponta_numeros, aponta_expressao_de_saida);
				printf("O resultado da expressao e:\n");
				printf("%f\n", resultado);
				printf("Pressione enter para continuar\n");
				flush_in();
				scanf("%c", &inutil);
			} else {
				printf("A expressao fornecida nao e valida. Pressione enter para continuar.\n");
				flush_in();
				scanf("%c", &inutil);
			}
		} else if (opcao == 2) {
			float operando_1 = 0.0;
			float operando_2 = 0.0;
			pilha = aloca_pilha();
			quantidade_numeros = 0;
			while (dados[0] != 's') {
				system("clear");
				for (i = 0; i < 100; i++) {
					dados[i] = '\0';
				}
				i = 0;
				aponta_dados = &dados[0];
				printf("Calculadora. Digite s para sair\n");
				while (i < quantidade_numeros) {
					printf("%d. %f\n", i, numeros[i]);
					i++;
				}
				printf("%d.", i);
				flush_in();
				aponta_numeros = &numeros[i];
				scanf("%100s", dados);
				if (dados[0] == 's' || dados[0] == 'S') {
					break;
				} else if (dados[0] >= '0' && dados[0] <= '9') {
					quantidade_numeros+= converte_valores(aponta_dados, aponta_numeros);
					empilhar(pilha, 'w', numeros[quantidade_numeros - 1]);
				} else if ((dados[0] == '-') && (dados[1] >= '0' && dados[1] <= '9')) {
					aponta_dados = &dados[1];
					quantidade_numeros+= converte_valores(aponta_dados, aponta_numeros);
					numeros[quantidade_numeros -1]*= -1.0;
					empilhar(pilha, 'w', numeros[quantidade_numeros - 1]);
				} else if (dados[1] == '!') {
					if (dados[0] == '+') {
						if (pilha->tamanho >= 2) {
							while (pilha->tamanho >= 2) {
								operando_1 = desempilhar_float(pilha);
								operando_2 = desempilhar_float(pilha);
								quantidade_numeros--;
								numeros[quantidade_numeros - 1] = operando_2 + operando_1;
								empilhar(pilha, 'w', numeros[quantidade_numeros - 1]);	
							}	
						} else {
							printf("Quantidade de numeros insuficiente pra realizar esssa operacao. Pressione enter duas vezes para continuar\n");
							flush_in();
							scanf("%c", &inutil);
						}
						
					} else if (dados[0] == '-') {
						if (pilha->tamanho >= 2) {
							while (pilha->tamanho >= 2) {
								operando_1 = desempilhar_float(pilha);
								operando_2 = desempilhar_float(pilha);
								quantidade_numeros--;
								numeros[quantidade_numeros - 1] = operando_2 - operando_1;
								empilhar(pilha, 'w', numeros[quantidade_numeros - 1]);	
							}	
						} else {
							printf("Quantidade de numeros insuficiente pra realizar esssa operacao. Pressione enter duas vezes para continuar\n");
							flush_in();
							scanf("%c", &inutil);
						}
					} else if (dados[0] == '*') {
						if (pilha->tamanho >= 2) {
							while (pilha->tamanho >= 2) {
								operando_1 = desempilhar_float(pilha);
								operando_2 = desempilhar_float(pilha);
								quantidade_numeros--;
								numeros[quantidade_numeros - 1] = operando_2 * operando_1;
								empilhar(pilha, 'w', numeros[quantidade_numeros - 1]);	
							}	
						} else {
							printf("Quantidade de numeros insuficiente pra realizar esssa operacao. Pressione enter duas vezes para continuar\n");
							flush_in();
							scanf("%c", &inutil);
						}
					} else if (dados[0] == '/') {
						if (pilha->tamanho >= 2) {
							while (pilha->tamanho >= 2) {
								operando_1 = desempilhar_float(pilha);
								operando_2 = desempilhar_float(pilha);
								quantidade_numeros--;
								numeros[quantidade_numeros - 1] = operando_2 / operando_1;
								empilhar(pilha, 'w', numeros[quantidade_numeros - 1]);	
							}	
						} else {
							printf("Quantidade de numeros insuficiente pra realizar esssa operacao. Pressione enter duas vezes para continuar\n");
							flush_in();
							scanf("%c", &inutil);
						}
					}
				} else if (dados[0] == '+') {
					if (pilha->tamanho >= 2) {
						operando_1 = desempilhar_float(pilha);
						operando_2 = desempilhar_float(pilha);
						quantidade_numeros--;
						numeros[quantidade_numeros - 1] = operando_2 + operando_1;
						empilhar(pilha, 'w', numeros[quantidade_numeros - 1]);
					} else {
						printf("Quantidade de numeros insuficiente pra realizar esssa operacao. Pressione enter duas vezes para continuar\n");
						flush_in();
						scanf("%c", &inutil);
					}
				} else if (dados[0] == '-') {
					if (pilha->tamanho >= 2) {
						operando_1 = desempilhar_float(pilha);
						operando_2 = desempilhar_float(pilha);
						quantidade_numeros--;
						numeros[quantidade_numeros - 1] = operando_2 - operando_1;
						empilhar(pilha, 'w', numeros[quantidade_numeros - 1]);
					} else {
						printf("Quantidade de numeros insuficiente pra realizar esssa operacao. Pressione enter duas vezes para continuar\n");
						flush_in();
						scanf("%c", &inutil);
					}
				} else if (dados[0] == '*') {
					if (pilha->tamanho >= 2) {
						operando_1 = desempilhar_float(pilha);
						operando_2 = desempilhar_float(pilha);
						quantidade_numeros--;
						numeros[quantidade_numeros - 1] = operando_2 * operando_1;
						empilhar(pilha, 'w', numeros[quantidade_numeros - 1]);
					} else {
						printf("Quantidade de numeros insuficiente pra realizar esssa operacao. Pressione enter duas vezes para continuar\n");
						flush_in();
						scanf("%c", &inutil);
					}
				} else if (dados[0] == '/') {
					if (pilha->tamanho >= 2) {
						operando_1 = desempilhar_float(pilha);
						operando_2 = desempilhar_float(pilha);
						quantidade_numeros--;
						numeros[quantidade_numeros - 1] = operando_2 / operando_1;
						empilhar(pilha, 'w', numeros[quantidade_numeros - 1]);
					} else {
						printf("Quantidade de numeros insuficiente pra realizar esssa operacao. Pressione enter duas vezes para continuar\n");
						flush_in();
						scanf("%c", &inutil);
					}
				} else if (dados[0] == 'c') {
					if (pilha->tamanho >= 2) {
						operando_1 = desempilhar_float(pilha);
						operando_2 = desempilhar_float(pilha);
						if (operando_1 > 0) {
							quantidade_numeros-= 2;
							for (j = 0; j < operando_1; j++) {
								quantidade_numeros++;
								numeros[quantidade_numeros - 1] = operando_2;
								empilhar(pilha, 'w', numeros[quantidade_numeros - 1]);
							}	
						} else {
							empilhar(pilha, 'w', operando_2);
							empilhar(pilha, 'w', operando_1);
							printf("Voce digitou um valor negativo ou nulo para o numero de copias. Pressione enter duas vezes para continuar\n");
							flush_in();
							scanf("%c", &inutil);
						}
					} else {
						printf("Quantidade de numeros insuficiente pra realizar esssa operacao. Pressione enter duas vezes para continuar\n");
						flush_in();
						scanf("%c", &inutil);
					}	
				}

			}
			esvazia_pilha(pilha);
			free(pilha);
		} else {
			return 0;
		}
	}
	if (pilha != NULL) {
		esvazia_pilha(pilha);
	}	
	return 0;
	
}


