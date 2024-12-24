#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <time.h>

void LimparTela() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif

}

int TeladeSelacao() {
	LimparTela();
    int op, start = 0,i,j;

    printf("  BBBBB   III  N   N  GGGGG   OOO  \n");
    printf("  B    B   I   NN  N  G      O   O \n");
    printf("  BBBBB    I   N N N  G  GG  O   O \n");
    printf("  B    B   I   N  NN  G   G  O   O \n");
    printf("  BBBBB   III  N   N  GGGGG   OOO  \n\n\n");
    printf("O que deseja fazer primeiro?\n1. Regras\n2. Créditos\n3. Começar\n4. Sair\n");
    printf("Digite a opção desejada: ");
    scanf("%d", &op);

    switch (op) {
        case 1:
            LimparTela();
            printf("Regras:\n\n");
            printf("- Para ganhar, você precisa completar uma linha, coluna ou diagonal na cartela.\n");
            printf("- Símbolos na cartela:\n");
            printf("  X  - Número marcado na cartela.\n");
            printf("  00 - 'Free', número gratuito no centro da cartela(ele é um número q já vem marcado no incio do jogo).\n\n");
            printf("\nExemplo de preenchimento:\n");

            printf("Para ganhar por uma diagonal:\n\n");
            for (i = 0; i < 5; i++) {
                for (j = 0; j < 5; j++) {
                    if (i == j) printf(" X ");
                    else printf(" 0 ");
                }
                printf("\n");
            }printf("\npara diagonal secundaria também funciona\n");

            printf("\nPara ganhar por uma linha:\n\n");
            for (i = 0; i < 5; i++) {
                for (j = 0; j < 5; j++) {
                    if (i == 2) printf(" X ");
                    else printf(" 0 ");
                }
                printf("\n");
            }

            printf("\n\nPara ganhar por uma coluna:\n\n");
            for (i = 0; i < 5; i++) {
                for (j = 0; j < 5; j++) {
                    if (j == 2) printf(" X ");
                    else printf(" 0 ");
                }
                printf("\n");
            }

            printf("Aperte enter para voltar ao menu...\n");
            getchar(); getchar();
            start = TeladeSelacao();
            break;

        case 2:
            LimparTela();
            printf("Créditos:\n");
            printf("- Desenvolvido por Benjamin da Conceição Neves.\n");
            printf("- Este é com o objetivo de melhorar a prática com a linguagem C.\n- Algumas ideias e implementações foram inspiradas pelo repositório de rondinell no GitHub (https://gist.github.com/rondinell/508459be1f01343b71b563ed8051c532).\n- Agradeço pela inspiração e pelo trabalho compartilhado.\n");
            
            printf("Aperte enter para voltar ao menu...\n");
            getchar(); getchar();
            start = TeladeSelacao();
            break;

        case 3:
            start = 1;
            break;

        case 4:
            start = 0;
            break;

        default:
            printf("Opção inválida, Digite um número valido .\n\n");
            start = TeladeSelacao();
    }
		
    return start;
}

void NumerosRepetido(int nrepetido[75]) {
    int i;
    for (i = 0; i < 75; i++) {
        nrepetido[i] = 0;
    }
}

int NumeroNaoRepetido(int limiterand, int nrepetido[75]) {
    int n;
    
    do {
        n = rand() % 15 + limiterand;
    } while (nrepetido[n - 1] == 1);
    
    nrepetido[n - 1] = 1;
    
    return n;
}

void CartelaPreenchida(int cartela[5][5], int nrepetido[75]) {
    int i, j;
    for (i = 0; i < 5; i++) {
        for (j = 0; j < 5; j++) {
            if (j == 0) {
            	//                         (limiterand,nrepetido)
                cartela[i][j] = NumeroNaoRepetido(1, nrepetido);
            } else if (j == 1) {
                cartela[i][j] = NumeroNaoRepetido(16, nrepetido);
            } else if (j == 2) {
                if (i == 2 && j == 2) {
                    cartela[i][j] = 0;
                } else {
                    cartela[i][j] = NumeroNaoRepetido(31, nrepetido);
                }
            } else if (j == 3) {
                cartela[i][j] = NumeroNaoRepetido(46, nrepetido);
            } else if (j == 4) {
                cartela[i][j] = NumeroNaoRepetido(61, nrepetido);
            }
        }
    }
}

void MostrarCartela(int cartela[5][5], int listaSorteados[75], int c2) {
    LimparTela();
    int i, j;
    printf("+-----------------------------+\n");
    printf("¦  B  ¦  I  ¦  N  ¦  G  ¦  O  ¦\n");
    printf("¦-----+-----+-----+-----+-----¦\n");
    for (i = 0; i < 5; i++) {
        for (j = 0; j < 5; j++) {
            if (cartela[i][j] == 0) {
                printf("¦  00 ");
            } else if (cartela[i][j] == -1) {
                printf("¦  X  ");
            } else {
                printf("¦ %3d ", cartela[i][j]);
            }
        }
        printf("¦\n");
        if (i < 4) {
            printf("¦-----+-----+-----+-----+-----¦\n");
        }
    }
    printf("+-----------------------------+\n");
    printf("\nNúmeros sorteados: ");
    for (i = 0; i < c2; i++) {
        printf("%d ", listaSorteados[i]);
    }
    printf("\n");
}

void NumeroJaSorteado(int cartela[5][5], int sorteados[5][5], int num) {
    int i, j, encontrado = 0;
    for (i = 0; i < 5; i++) {
        for (j = 0; j < 5; j++) {
            if (cartela[i][j] == num) {
                sorteados[i][j] = 1;
                cartela[i][j] = -1;
                encontrado = 1;
            }
        }
    }
    if (encontrado) {
        printf("\nNúmero encontrado\n\n");
    } else {
        printf("\nNúmero não encontrado\n\n");
    }
}

int Bingo(int sorteados[5][5]) {
	// completa = 1 -> jogo ganho
	// completa = 0 -> ainda n ganhou
    int i, j, completa;
    // Linha
    for (i = 0; i < 5; i++) {
        completa = 1;
        for (j = 0; j < 5; j++) {
            if (sorteados[i][j] == 0) {
                completa = 0;
                break;
            }
        }
        if (completa) return 1;
    }
	//Coluna
    for (j = 0; j < 5; j++) {
        completa = 1;
        for (i = 0; i < 5; i++) {
            if (sorteados[i][j] == 0) {
                completa = 0;
                break;
            }
        }
        if (completa) return 1;
    }
	// Diagonal principal
    completa = 1;
    for (i = 0; i < 5; i++) {
        if (sorteados[i][i] == 0) {
            completa = 0;
            break;
        }
    }
    if (completa) return 1;
	// diagonal secundaria
    completa = 1;
    for (i = 0; i < 5; i++) {
        if (sorteados[i][4 - i] == 0) {
            completa = 0;
            break;
        }
    }
    if (completa) return 1;

    return 0;
}

void NumeroSorteado(int numerosSorteados[75]) {
    int i;
    for (i = 0; i < 75; i++) {
        numerosSorteados[i] = 0;
    }
}

int SorteioNumero(int numerosSorteados[75]) {
    int n;
    do {
        n = rand() % 75 + 1;
    } while (numerosSorteados[n - 1] == 1);
    numerosSorteados[n - 1] = 1;
    return n;
}

int main() {
    setlocale(LC_ALL, "portuguese");

    int numrepetido[75];
    int listaSorteados[75];
    int cartela[5][5];
    int sorteados[5][5] = {0};
    int numerosSorteados[75];
    int num, i, op, continuar,retorno, c = 0, c2 = 0;

    srand(time(NULL));
	
    NumerosRepetido(numrepetido);
    NumeroSorteado(numerosSorteados);
    CartelaPreenchida(cartela, numrepetido);
    
    retorno = TeladeSelacao();
	if (retorno == 1) {
		MostrarCartela(cartela, listaSorteados, c2);	
	}
    else {
        printf("Mas já? nem teminou o jogo...\nEncerrando Código...\n");
        return 0;
    }

while (1) {
    num = SorteioNumero(numerosSorteados);
    listaSorteados[c2++] = num;

    MostrarCartela(cartela, listaSorteados, c2);
    printf("\nNúmero sorteado: %d\nProcurando na cartela...", num);
    NumeroJaSorteado(cartela, sorteados, num);

    if (Bingo(sorteados)) {
        printf("\nBINGO! Por enquanto você não ganhou nada, perdão\n");
        break; 
    }

    printf("\nDigite 1 para continuar ou 0 para encerrar:\n");
    scanf("%d", &continuar);
    if (continuar != 1) {
        printf("Mas já? nem teminou o jogo...\nEncerrando Código...\n");
        break;
    }
}

return 0;
}
