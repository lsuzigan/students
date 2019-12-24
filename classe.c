/**
 *	@authors Lucas Suzigan, Danilo Dias
 *
 *	@brief A program to read, write and edit files that contains a students class
 * 
 *	@bugs When edit a file, incluiding a new student, the file does not update
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define OPCAO_MIN 0
#define OPCAO_MAX 9
#define SAIR OPCAO_MIN


#define NOME 50
#define MATR 12
#define QTD 80
#define ARQ 50

// Estrutura de estudante
typedef struct
{
    char nome[NOME];
    char matricula[MATR];
    double prova1;
    double prova2;
    double prova3;
    double trab1;
    double trab2;
    double notafinal;
    unsigned int faltas;
    char situacao;
} Aluno;

/**
 * @brief Imprime as opções do 'menu principal' na tela.
 */
void menuPrincipal(void);


/**
 * @brief Imprime as opções do menu 'ler turma' na tela.
 */
void menuLerTurma(void);


/**
 * @brief Lê a opção digitada pelo usuário nos menus.
 *
 * @return Número inteiro digitado pelo usuário referente a opção do menu.
 */
unsigned int leiaOpcaoMenu(void);


/**
 * @brief Abre e lê o arquivo informado pelo usuário referente a turma.
 */
Aluno lerTurma(Aluno estudantes[QTD], unsigned int * qtd_estudante, char turma[ARQ]);


/**
 * @brief Cria um novo arquivo de turma
 */
void criaTurma(void);


/**
 * @brief Imprime a turma lida anteriormente.
 */
int imprimeTurma(Aluno estudantes[QTD], unsigned int * qtd_estudante);


/**
 * @brief Imprime as estatísticas da turma lida anteriormente.
 */
int imprimeEstatisticas(Aluno estudantes[QTD], unsigned int qtd_estudante);


/**
 * @brief Lê informações de um novo estudante e acrescenta ao final do arquivo aberto.
 */
int cadastraEstudante(Aluno estudantes[QTD], unsigned int * qtd_estudante, char turma[ARQ]);

/**
 * @brief Edita informações de um estudante.
 */
int editaEstudante(Aluno estudantes[QTD], unsigned int * qtd_estudante, char turma[ARQ]);


/**
 * @brief Imprime menu da tela de edição do estudante.
 */
void imprimeMenuEdicao(void);


/**
 * @brief Altera o nome do estudante.
 * 
 * @param estudantes Arranjo de um struct
 * @param i Contador
 */
void alteraNome(Aluno estudantes[QTD], int i);


/**
 * @brief Altera a matricula do estudante.
 * 
 * @param estudantes Arranjo de um struct
 * @param i Contador
 */
void alteraMatr(Aluno estudantes[QTD], int i);


/**
 * @brief Altera a matricula do estudante.
 * 
 * @param estudantes Arranjo de um struct
 * @param i Contador
 */
void alteraProva1(Aluno estudantes[QTD], int i);


/**
 * @brief Altera a matricula do estudante.
 * 
 * @param estudantes Arranjo de um struct
 * @param i Contador
 */
void alteraProva2(Aluno estudantes[QTD], int i);


/**
 * @brief Altera a matricula do estudante.
 * 
 * @param estudantes Arranjo de um struct
 * @param i Contador
 */
void alteraProva3(Aluno estudantes[QTD], int i);


/**
 * @brief Altera a matricula do estudante.
 * 
 * @param estudantes Arranjo de um struct
 * @param i Contador
 */
void alteraTrab1(Aluno estudantes[QTD], int i);


/**
 * @brief Altera a matricula do estudante.
 * 
 * @param estudantes Arranjo de um struct
 * @param i Contador
 */
void alteraTrab2(Aluno estudantes[QTD], int i);


/**
 * @brief Altera a matricula do estudante.
 * 
 * @param estudantes Arranjo de um struct
 * @param i Contador
 */
void alteraFaltas(Aluno estudantes[QTD], int i);


/**
 * @brief Relê o arquivo lido anteriormente.
 */
int relerTurma(Aluno estudantes[QTD], unsigned int * qtd_estudante, char turma[ARQ]);


/**
* @brief Executa as funções de acordo com a opção digitada pelo usuário.
*
* @param opcao Inteiro sem sinal correspondente ao número digitado pelo usuário para selecionar a opção do menu.
*/
void menu(unsigned int opcao);


int main(void){

    unsigned int opcao = 10;
    menu(opcao);

}// fim main


/**
 *  Funções
*/

void menuPrincipal(void)
{
    printf("=========================================\n");
    printf("              Menu Principal             \n");
    printf("=========================================\n");
    printf("Opções:\n\n"                                );
    printf("1 - Ler turma de estudantes do arquivo\n"   );
    printf("2 - Imprimir turma de estudantes\n"         );
    printf("3 - Imprimir estatı́sticas da turma\n"       );
    printf("4 - Cadastrar novo estudante\n"             );
    printf("5 - Editar informações de um estudante\n"   );
    printf("6 - Reler turma de estudantes do arquivo\n" );
    printf("7 - Salvar e sair\n"                        );
}// fim menuOpcoes


void menuLerTurma(void)
{
    printf("\n");
    printf("=========================================\n");
    printf("                 Ler Turma               \n");
    printf("=========================================\n");
    printf("Opções:\n\n"                                );
    printf("1 - Ler turma existente\n"                  );
    printf("2 - Criar nova turma\n"                     );
    printf("3 - Voltar ao menu principal\n"             );
}// fim menuLerTurma


unsigned int leiaOpcaoMenu(void)
{
    
	unsigned int opcao = 0;

	printf("\nDigite uma opção: ");
	scanf("%u", &opcao);
    getchar();

	while( !(OPCAO_MIN <= opcao && OPCAO_MAX >= opcao)){
		printf("Opção inválida! Digite uma opção válida.\n");
		scanf("%u", &opcao);
        getchar();
	}//while

	return(opcao);

}// fim leiaOpcaoMenu


Aluno lerTurma(Aluno estudantes[QTD], unsigned int * qtd_estudante, char turma[ARQ])
{
    printf("‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾\n\n");

    // Lê o caminho do arquivo da turma e coloca o '\0' no final da string
    printf("Digite o nome do arquivo a ser lido:\n\t");
    fgets(turma, ARQ, stdin);
    turma[strlen(turma)-1] = '\0';

    // Abre o arquivo
    FILE * fp = fopen(turma, "r");

    // Verifica se o arquivo existe e se realmente foi aberto
    if(fp == NULL){
        fprintf(stderr, "O arquivo %s não existe!\n", turma);
        exit(1);
    }// fim if    

    // Lê a quantidade de estudantes que possui no topo do arquivo
    fscanf(fp, "%u", qtd_estudante);
    fgetc(fp);    
    //printf("\n=%u=\n", qtd_estudante);

    // Lê o arquivo de estudantes
    for(int i = 0; i < *qtd_estudante; i++){
        fgets(estudantes[i].nome, sizeof(estudantes[QTD].nome), fp);
        estudantes[i].nome[strlen(estudantes[i].nome)-1] = '\0';

        fgets(estudantes[i].matricula, sizeof(estudantes[QTD].matricula), fp);
        estudantes[i].matricula [strlen(estudantes[i].matricula)-1] = '\0';
        
        fscanf(fp, "%lf", &estudantes[i].prova1);
        fgetc(fp);

        fscanf(fp, "%lf", &estudantes[i].prova2);
        fgetc(fp);

        fscanf(fp, "%lf", &estudantes[i].prova3);
        fgetc(fp);

        fscanf(fp, "%lf", &estudantes[i].trab1);
        fgetc(fp);

        fscanf(fp, "%lf", &estudantes[i].trab2);
        fgetc(fp);

        fscanf(fp, "%lf", &estudantes[i].notafinal);
        fgetc(fp);

        fscanf(fp, "%u", &estudantes[i].faltas);
        fgetc(fp);

        fscanf(fp, "%c", &estudantes[i].situacao);
        fgetc(fp);
        /*printfs
            printf("\n=%s=\n", estudantes[i].nome);
            printf("\n=%s=\n", estudantes[i].matricula);
            printf("\n=%lf=\n", estudantes[i].prova1);
            printf("\n=%lf=\n", estudantes[i].prova2);
            printf("\n=%lf=\n", estudantes[i].prova3);
            printf("\n=%lf=\n", estudantes[i].trab1);
            printf("\n=%lf=\n", estudantes[i].trab2);
            printf("\n=%lf=\n", estudantes[i].notafinal);
            printf("\n=%u=\n", estudantes[i].faltas);
            printf("\n=%c=\n", estudantes[i].situacao);
        */
    }// fim for


    printf("\nTurma lida com sucesso! Pressione ENTER para continuar.");
    getchar();
    fflush(stdin);

    printf("__________________________________________________\n");

}// fim lerTurma


void criaTurma(void)
{
    Aluno novos_estudantes[QTD];
    char ler_estudante = '\0';
    int i = 0;

    char nome_temp[NOME];
    char matr_temp[MATR];

    printf("‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾\n");

    // For para preencher o arranjo de estrutura 'novos_estudantes' para gravar no arquivo
    for(i = 0; ler_estudante != 'n'; i++){

        printf("\nInsira o nome do estudante:\n\t");
        fgets(nome_temp, sizeof(nome_temp), stdin);
        nome_temp[strlen(nome_temp)-1] = '\0';
        strcpy(novos_estudantes[i].nome, nome_temp);
       
        printf("\nInsira a matrícula do estudante:\n\t");
        fgets(matr_temp, sizeof(matr_temp), stdin);
        matr_temp[strlen(matr_temp)-1] = '\0';
        strcpy(novos_estudantes[i].matricula, matr_temp);
        
        printf("\nInsira a nota da primeira prova:\n\t");
        scanf("%lf", &novos_estudantes[i].prova1);
        getchar();
       
        printf("\nInsira a nota da segunda prova:\n\t");
        scanf("%lf", &novos_estudantes[i].prova2);
        getchar();
        
        printf("\nInsira a nota da terceira prova:\n\t");
        scanf("%lf", &novos_estudantes[i].prova3);
        getchar();
        
        printf("\nInsira a nota do primeiro trabalho:\n\t");
        scanf("%lf", &novos_estudantes[i].trab1);
        getchar();
        
        printf("\nInsira a nota do segundo trabalho:\n\t");
        scanf("%lf", &novos_estudantes[i].trab2);
        getchar();
        
        printf("\nInsira a nota final:\n\t");
        scanf("%lf", &novos_estudantes[i].notafinal);  
        getchar();
      
        printf("\nInsira a quantidade de faltas:\n\t");
        scanf("%u", &novos_estudantes[i].faltas);
        getchar();
        
        printf("\nInsira a situação final do estudante\n(A = Aprovado; R = Reprovado; F = Reprovado por faltas)\n\t");
        scanf("%c", &novos_estudantes[i].situacao);
        getchar();
        
        printf("\nDeseja incluir outro estudante? (s/n)\n\t");
        scanf("%c", &ler_estudante);
        getchar();
       
    }// fim for

    // Ler o nome do novo arquivo
    char nova_turma[ARQ];
    printf("\nDigite o nome do novo arquivo:\n\t");
    fgets(nova_turma, sizeof(nova_turma), stdin);
    nova_turma[strlen(nova_turma)-1] = '\0';
    fflush(stdin);

    // Abre o arquivo no modo de leitura binário e verificar se foi aberto corretamente
    FILE * fp = fopen(nova_turma, "w");
    if(fp == NULL){
        fprintf(stderr, "Erro ao gerar novo arquivo. Tente novamente.\n");
        exit(1);
    }// fim if

    // Imprime no topo do arquivo o número de estudantes inseridos
    fprintf(fp, "%u\n", i);

    // Escreve o arranjo de estrutura no arquivo
    for(int j = 0; j < i; j++){
        fprintf(fp, "%s\n", novos_estudantes[j].nome);
        fprintf(fp, "%s\n", novos_estudantes[j].matricula);
        fprintf(fp, "%lf\n", novos_estudantes[j].prova1);
        fprintf(fp, "%lf\n", novos_estudantes[j].prova2);
        fprintf(fp, "%lf\n", novos_estudantes[j].prova3);
        fprintf(fp, "%lf\n", novos_estudantes[j].trab1);
        fprintf(fp, "%lf\n", novos_estudantes[j].trab2);
        fprintf(fp, "%lf\n", novos_estudantes[j].notafinal);
        fprintf(fp, "%u\n", novos_estudantes[j].faltas);
        fprintf(fp, "%c\n", novos_estudantes[j].situacao);
    }// fim for

    // Fecha o arquivo
    fclose(fp);

    printf("\nArquivo criado com sucesso! Pressione ENTER para continuar.\n\n");
    getchar();

    printf("__________________________________________________\n");

}// fim criaTurma


int imprimeTurma(Aluno estudantes[QTD], unsigned int * qtd_estudante)
{
    // Verifica se há turma carregada
    if(*qtd_estudante < 1){
        printf("\nNão há turma carregada! Pressione ENTER para retornar.\n");
        getchar();
        return 0;
    }

    printf("___________________________________________________________________________________________\n");
    printf("                                      Turma de Estudantes                                  \n");
    printf("‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾\n");
    printf("Nome                           Matrícula    Nota Nota Nota Trab Trab Faltas  Nota  Situação\n");
    printf("                                            1    2    3    1    2            final\n");
    printf("‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾\n");

    for(int i = 0; i < *qtd_estudante; i++){
        printf("%-30s %-12s %-4.1lf %-4.1lf %-4.1lf %-4.1lf %-6.1lf %-5u %-8.1lf %c\n", estudantes[i].nome, 
                               estudantes[i].matricula,
                               estudantes[i].prova1,
                               estudantes[i].prova2,
                               estudantes[i].prova3,
                               estudantes[i].trab1,
                               estudantes[i].trab2,
                               estudantes[i].faltas,
                               estudantes[i].notafinal,
                               estudantes[i].situacao);
    }// fim for

    printf("‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾\n\n");

    printf("Pressione ENTER para continuar.");
    getchar();

}// fim imprimeTurma


int imprimeEstatisticas(Aluno estudantes[QTD], unsigned int qtd_estudante)
{
    // Verifica se há turma carregada
    if(qtd_estudante < 1){
        printf("\nNão há turma carregada! Pressione ENTER para retornar.\n");
        getchar();
        return 0;
    }// fim if

    // Verifica qual a maior nota das provas da turma lida
    double maior_nota_prova1 = 0.0;
    double maior_nota_prova2 = 0.0;
    double maior_nota_prova3 = 0.0;
    for(int i = 0; i < qtd_estudante; i++){        
        if(estudantes[i].prova1 > maior_nota_prova1){
            maior_nota_prova1 = estudantes[i].prova1;
        } if(estudantes[i].prova2 > maior_nota_prova2){
            maior_nota_prova2 = estudantes[i].prova2;
        } if(estudantes[i].prova3 > maior_nota_prova3){
            maior_nota_prova3 = estudantes[i].prova3;
        }
    }// fim for

    // Verifica qual a maior nota dos trabalhos da turma lida
    double maior_nota_trab1 = 0.0;
    double maior_nota_trab2 = 0.0;
    for(int j = 0; j < qtd_estudante; j++){        
        if(estudantes[j].trab1 > maior_nota_trab1){
            maior_nota_trab1 = estudantes[j].trab1;
        } if(estudantes[j].trab2 > maior_nota_trab2){
            maior_nota_trab2 = estudantes[j].trab2;
        }
    }// fim for

    // Verifica qual a maior nota final da turma lida
    double maior_nota_final = 0.0;
    for(int m = 0; m < qtd_estudante; m++){
        if(estudantes[m].notafinal > maior_nota_final)
            maior_nota_final = estudantes[m].notafinal;
    }// fim for

    // Verifica qual a menor nota das provas da turma lida
    double menor_nota_prova1 = 101.0; // Iniciando essas três variáveis em 101.0 para pegar os valores menores a esse
    double menor_nota_prova2 = 101.0; // no for abaixo.
    double menor_nota_prova3 = 101.0;
    for(int k = 0; k < qtd_estudante; k++){        
        if(estudantes[k].prova1 < menor_nota_prova1){
            menor_nota_prova1 = estudantes[k].prova1;
        } if(estudantes[k].prova2 < menor_nota_prova2){
            menor_nota_prova2 = estudantes[k].prova2;
        } if(estudantes[k].prova3 < menor_nota_prova3){
            menor_nota_prova3 = estudantes[k].prova3;
        }
    }// fim for

    // Verifica qual a menor nota dos trabalhos da turma lida
    double menor_nota_trab1 = 101.0; // Iniciando essas três variáveis em 101.0 para pegar os valores menores a esse
    double menor_nota_trab2 = 101.0; // no for abaixo.
    for(int l = 0; l < qtd_estudante; l++){        
        if(estudantes[l].trab1 < menor_nota_trab1){
            menor_nota_trab1 = estudantes[l].trab1;
        } if(estudantes[l].trab2 < menor_nota_trab2){
            menor_nota_trab2 = estudantes[l].trab2;
        }
    }// fim for

    // Verifica qual a menor nota final da turma lida
    double menor_nota_final = 101.0;
    for(int n = 0; n < qtd_estudante; n++){
        if(estudantes[n].notafinal < menor_nota_final)
            menor_nota_final = estudantes[n].notafinal;
    }// fim for

    // Conta a quantidade de estudantes aprovados (nota_final > 60)
    double aprovados = 0;
    for(int o = 0; o < qtd_estudante; o++){
        if(estudantes[o].notafinal >= 60)
            aprovados++;
    }// fim for

    // Calcula a porcentagem de estudantes aprovados
    double porcentagem_ap = 0.0;
    porcentagem_ap = (aprovados / qtd_estudante) * 100;

    // Conta a quantidade de estudantes reprovados (nota_final < 60)
    double reprovados = 0;
    for(int p = 0; p < qtd_estudante; p++){
        if(estudantes[p].notafinal <= 60)
            reprovados++;
    }// fim for

    // Calcula a porcentagem de estudantes reprovados
    double porcentagem_rp = 0.0;
    porcentagem_rp = (reprovados / qtd_estudante) * 100;

    //Conta a quantidade de estudantes reprovados por falta (situacao == F)
    double reprovados_f = 0;
    for(int q = 0; q < qtd_estudante; q++){
        if(estudantes[q].situacao == 'F')
            reprovados_f++;
    }// fim for

    // Calcula a porcentagem de estudantes reprovados
    double porcentagem_f = 0.0;
    porcentagem_f = (reprovados_f / qtd_estudante) * 100;

    // Calcula a média das notas da turma lida
    double media_prova1 = 0.0;
    double media_prova2 = 0.0;
    double media_prova3 = 0.0;
    double media_trab1 = 0.0;
    double media_trab2 = 0.0;
    double media_nota_final = 0.0;

    // Media das notas da prova1
    for(int r = 0; r < qtd_estudante; r++)
        media_prova1 += estudantes[r].prova1;
    media_prova1 = media_prova1 / qtd_estudante;
    
    // Média das notas da prova2
    for(int s = 0; s < qtd_estudante; s++)
        media_prova2 += estudantes[s].prova2;
    media_prova2 = media_prova2 / qtd_estudante;

    // Média das notas da prova3
    for(int t = 0; t < qtd_estudante; t++)
        media_prova3 += estudantes[t].prova3;
    media_prova3 = media_prova3 / qtd_estudante;

    // Média das notas do trab1
    for(int u = 0; u < qtd_estudante; u++)
        media_trab1 += estudantes[u].trab1;
    media_trab1 = media_trab1 / qtd_estudante;

    // Média das notas do trab1
    for(int v = 0; v < qtd_estudante; v++)
        media_trab2 += estudantes[v].trab2;
    media_trab2 = media_trab2 / qtd_estudante;

    // Média da nota_final
    for(int w = 0; w < qtd_estudante; w++)
        media_nota_final += estudantes[w].notafinal;
    media_nota_final = media_nota_final / qtd_estudante;

    // Mediana das notas prova1
    double mediana_prova1 = 0.0;
    double mediana_prova2 = 0.0;
    double mediana_prova3 = 0.0;
    double mediana_trab1 = 0.0;
    double mediana_trab2 = 0.0;
    double mediana_notafinal = 0.0;
     
    // Calcula a mediana prova1
    if((qtd_estudante % 2) == 0){
        mediana_prova1 = (estudantes[qtd_estudante / 2].prova1 + estudantes[(qtd_estudante / 2) -1].prova1)/2;
    } else if(qtd_estudante % 2 == 1){
        mediana_prova1 = estudantes[qtd_estudante/2].prova1;
    }

    // Calcula a mediana prova2
    if((qtd_estudante % 2) == 0){
        mediana_prova2 = (estudantes[qtd_estudante / 2].prova2 + estudantes[(qtd_estudante / 2) -1].prova2)/2;
    } else if(qtd_estudante % 2 == 1){
        mediana_prova2 = estudantes[qtd_estudante/2].prova2;
    }

  // Calcula a mediana prova3  
    if((qtd_estudante % 2) == 0){
        mediana_prova3 = (estudantes[qtd_estudante / 2].prova3 + estudantes[(qtd_estudante / 2) -1].prova3)/2;
    } else if(qtd_estudante % 2 == 1){
        mediana_prova3 = estudantes[qtd_estudante/2].prova3;
    }

    // Calcula a mediana trab1
    if((qtd_estudante % 2) == 0){
        mediana_trab1 = (estudantes[qtd_estudante / 2].trab1 + estudantes[(qtd_estudante / 2) -1].trab1)/2;
    } else if(qtd_estudante % 2 == 1){
        mediana_trab1 = estudantes[qtd_estudante/2].trab1;
    }

  // Calcula a mediana trab2
    if((qtd_estudante % 2) == 0){
        mediana_trab2 = (estudantes[qtd_estudante / 2].trab2 + estudantes[(qtd_estudante / 2) -1].trab2)/2;
    } else if(qtd_estudante % 2 == 1){
        mediana_trab2 = estudantes[qtd_estudante/2].trab2;
    }

      // Calcula a mediana notafinal
    if((qtd_estudante % 2) == 0){
        mediana_notafinal = (estudantes[qtd_estudante / 2].notafinal + estudantes[(qtd_estudante / 2) -1].notafinal)/2;
    } else if(qtd_estudante % 2 == 1){
        mediana_notafinal = estudantes[qtd_estudante/2].notafinal;
    }

    printf("___________________________________________________________________________________________\n");
    printf("                                         Estatísticas                                      \n");
    printf("‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾\n");
    printf("                               Nota  Nota  Nota  Trab  Trab  Nota \n");
    printf("                               1     2     3     1     2     final\n");
    printf("‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾\n");
    printf("Maiores notas da turma         %4.1lf  %4.1lf  %4.1lf  %4.1lf  %4.1lf  %4.1lf\n", maior_nota_prova1
                                                                                                  , maior_nota_prova2
                                                                                                  , maior_nota_prova3
                                                                                                  , maior_nota_trab1
                                                                                                  , maior_nota_trab2
                                                                                                  , maior_nota_final);
    printf("Menores notas da turma         %4.1lf  %4.1lf  %4.1lf  %4.1lf  %4.1lf  %4.1lf\n", menor_nota_prova1
                                                                                                  , menor_nota_prova2
                                                                                                  , menor_nota_prova3
                                                                                                  , menor_nota_trab1
                                                                                                  , menor_nota_trab2
                                                                                                  , menor_nota_final);
    printf("Notas médias da turma          %4.1lf  %4.1lf  %4.1lf  %4.1lf  %4.1lf  %4.1lf\n", media_prova1
                                                                                                  , media_prova2
                                                                                                  , media_prova3
                                                                                                  , media_trab1
                                                                                                  , media_trab2
                                                                                                  , media_nota_final);
    printf("Notas medianas da turma        %4.1lf  %4.1lf  %4.1lf  %4.1lf  %4.1lf  %4.1lf\n\n",mediana_prova1
                                                                                                    ,mediana_prova2
                                                                                                    ,mediana_prova3
                                                                                                    ,mediana_trab1
                                                                                                    ,mediana_trab2
                                                                                                    ,mediana_notafinal);
    
    printf("Número de estudantes aprovados: %.0lf (%.1lf %%)\n", aprovados, porcentagem_ap);
    printf("Número de estudantes reprovados: %.0lf (%.1lf %%)\n", reprovados, porcentagem_rp);
    printf("Número de estudantes reprovados por falta: %.0lf (%.1lf %%)\n\n", reprovados_f, porcentagem_f);

    printf("Pressione ENTER para continuar.");
    getchar();

}// fim imprimeEstatisticas


int cadastraEstudante(Aluno estudantes[QTD], unsigned int * qtd_estudante, char turma[ARQ])
{
    char nome_temp[NOME];
    char matr_temp[MATR];
    unsigned int qtd_novo = *qtd_estudante + 1;

    // Verifica se há turma carregada
    if(*qtd_estudante < 1){
        printf("\nNão há turma carregada! Pressione ENTER para retornar.\n");
        getchar();
        return 0;
    }

    FILE * fp = fopen(turma, "w");

    // Imprime no topo do arquivo o número de estudantes inseridos
    fprintf(fp, "%u\n", qtd_novo);

     // Escreve o arranjo de estrutura no arquivo
    for(int j = 0; j < *qtd_estudante; j++){
        fprintf(fp, "%s\n", estudantes[j].nome);
        fprintf(fp, "%s\n", estudantes[j].matricula);
        fprintf(fp, "%lf\n", estudantes[j].prova1);
        fprintf(fp, "%lf\n", estudantes[j].prova2);
        fprintf(fp, "%lf\n", estudantes[j].prova3);
        fprintf(fp, "%lf\n", estudantes[j].trab1);
        fprintf(fp, "%lf\n", estudantes[j].trab2);
        fprintf(fp, "%lf\n", estudantes[j].notafinal);
        fprintf(fp, "%u\n", estudantes[j].faltas);
        fprintf(fp, "%c\n", estudantes[j].situacao);
    }// fim for

    fclose(fp);

    printf("==============================\n");
    printf("   Cadastrar Novo Estudante   \n");
    printf("==============================\n\n");
    printf("Digite o nome: ");
    fgets(nome_temp, sizeof(nome_temp), stdin);
    nome_temp[strlen(nome_temp)-1] = '\0';
    strcpy(estudantes[qtd_novo].nome, nome_temp);

    printf("Digite a matrícula: ");
    fgets(matr_temp, sizeof(matr_temp), stdin);
    matr_temp[strlen(matr_temp)-1] = '\0';
    strcpy(estudantes[qtd_novo].matricula, matr_temp);

    printf("Digite as três notas das provas: ");
    scanf("%lf %lf %lf", &estudantes[qtd_novo].prova1,
                         &estudantes[qtd_novo].prova2,
                         &estudantes[qtd_novo].prova3);
    getchar();

    printf("Digite as duas notas dos trabalhos: ");
    scanf("%lf %lf", &estudantes[qtd_novo].trab1,
                     &estudantes[qtd_novo].trab2);
    getchar();

    printf("Digite o número de faltas: ");
    scanf("%u", &estudantes[qtd_novo].faltas);
    getchar();

    estudantes[qtd_novo].notafinal = estudantes[qtd_novo].prova1 + estudantes[qtd_novo].prova2 + estudantes[qtd_novo].prova3 + estudantes[qtd_novo].trab1 + estudantes[qtd_novo].trab2;
    printf("\nNota final calculada: %.1lf\n", estudantes[qtd_novo].notafinal);

    if(estudantes[qtd_novo].notafinal >= 60.0 && estudantes[qtd_novo].faltas <= 18){
        printf("Situação final: Aprovado\n");
        estudantes[qtd_novo].situacao = 'A';
    } else if(estudantes[qtd_novo].faltas > 18){
        printf("Situação final: Reprovado por faltas\n");
        estudantes[qtd_novo].situacao = 'F';
    } else if(estudantes[qtd_novo].notafinal < 60.0){
        printf("Situação final: Reprovado\n");
        estudantes[qtd_novo].situacao = 'R';
    }// fim else if

    FILE * n_fp = fopen(turma, "a");

    fprintf(fp, "%s\n", estudantes[qtd_novo].nome);
    fprintf(fp, "%s\n", estudantes[qtd_novo].matricula);
    fprintf(fp, "%lf\n", estudantes[qtd_novo].prova1);
    fprintf(fp, "%lf\n", estudantes[qtd_novo].prova2);
    fprintf(fp, "%lf\n", estudantes[qtd_novo].prova3);
    fprintf(fp, "%lf\n", estudantes[qtd_novo].trab1);
    fprintf(fp, "%lf\n", estudantes[qtd_novo].trab2);
    fprintf(fp, "%lf\n", estudantes[qtd_novo].notafinal);
    fprintf(fp, "%u\n", estudantes[qtd_novo].faltas);
    fprintf(fp, "%c\n", estudantes[qtd_novo].situacao);

    fclose(n_fp);

    printf("\nNovo estudante incluído com sucesso!\n\n");

    printf("Pressione ENTER para continuar.");
    getchar(); 

    qtd_estudante++;

}// fim cadastraEstudante


int editaEstudante(Aluno estudantes[QTD], unsigned int * qtd_estudante, char turma[ARQ])
{
    unsigned int opcao = 0;
    unsigned int opcao2 = 0;
    char nome_temp[NOME];
    char matr_temp[MATR];
    unsigned int alterou = 0;
    int i = 0;
    int estd_mod = 0;// armazena a posição do estudante que foi modificado na struct
    
    // Verifica se há turma carregada
    if(*qtd_estudante < 1){
        printf("\nNão há turma carregada! Pressione ENTER para retornar.\n");
        getchar();
        return 0;
    }

    do{
        printf("=====================================\n");
        printf("   Editar Informações do Estudante   \n");
        printf("=====================================\n");
        printf("Opções:\n\n");
        printf("1 - Selecionar por número de matrícula\n");
        printf("2 - Selecionar por nome\n");
        printf("3 - Voltar ao menu principal\n\n");
        printf("Digite uma opção: ");
        scanf("%u", &opcao);
        getchar();

        switch(opcao){
            case 1:
                printf("\nInsira a matrícula do estudante:\n\t");
                fgets(matr_temp, sizeof(matr_temp), stdin);
                matr_temp[strlen(matr_temp)-1] = '\0';

               for(i = 0; i < *qtd_estudante; i++){ 
                    if(strcoll(estudantes[i].matricula, matr_temp) == 0){

                        imprimeMenuEdicao();
                        scanf("%u", &opcao2);
                        getchar();

                        switch(opcao2)
                        {
                            case 1:
                                alteraNome(estudantes, i);
                                alterou = 1;
                                estd_mod = i;
                                break;

                            case 2:
                                alteraMatr(estudantes, i);
                                alterou = 1;
                                estd_mod = i;
                                break;

                            case 3:
                                alteraProva1(estudantes, i);
                                alterou = 1;
                                estd_mod = i;
                                break;

                            case 4:
                                alteraProva2(estudantes, i);
                                alterou = 1;
                                estd_mod = i;
                                break;

                            case 5:
                                alteraProva3(estudantes, i);
                                alterou = 1;
                                estd_mod = i;
                                break;

                            case 6:
                                alteraTrab1(estudantes, i);
                                alterou = 1;
                                estd_mod = i;
                                break;

                            case 7:
                                alteraTrab2(estudantes, i);
                                alterou = 1;
                                estd_mod = i;
                                break;

                            case 8:
                                alteraFaltas(estudantes, i);
                                alterou = 1;
                                estd_mod = i;
                                break;

                            case 9:
                                break;
                            
                        }// switch opcao2
                    }// fim if
                }// fim for

                if(alterou != 1){
                    printf("\nNúmero de matrícula inválido. Pressione ENTER para continuar.\n");
                    getchar();
                    break;
                }// fim if

                alterou = 0;
            break;// fim case 1

            case 2:
                printf("\nInsira o nome do estudante:\n\t");
                fgets(nome_temp, sizeof(nome_temp), stdin);
                nome_temp[strlen(nome_temp)-1] = '\0';

                for(i = 0; i < *qtd_estudante; i++){ 
                    if(strcoll(estudantes[i].nome, nome_temp) == 0){

                        imprimeMenuEdicao();
                        scanf("%u", &opcao2);
                        getchar();

                        switch(opcao2){
                            case 1:
                                alteraNome(estudantes, i);
                                alterou = 1;
                                estd_mod = i;
                                break;

                            case 2:
                                alteraMatr(estudantes, i);
                                alterou = 1;
                                estd_mod = i;
                                break;

                            case 3:
                                alteraProva1(estudantes, i);
                                alterou = 1;
                                estd_mod = i;
                                break;

                            case 4:
                                alteraProva2(estudantes, i);
                                alterou = 1;
                                estd_mod = i;
                                break;

                            case 5:
                                alteraProva3(estudantes, i);
                                alterou = 1;
                                estd_mod = i;
                                break;

                            case 6:
                                alteraTrab1(estudantes, i);
                                alterou = 1;
                                estd_mod = i;
                                break;

                            case 7:
                                alteraTrab2(estudantes, i);
                                alterou = 1;
                                estd_mod = i;
                                break;

                            case 8:
                                alteraFaltas(estudantes, i);
                                alterou = 1;
                                estd_mod = i;
                                break;

                            case 9:
                                break;
                            
                        }// switch opcao2
                    }// fim if
                }// fim for

                if(alterou != 1){
                    printf("\nNúmero de matrícula inválido. Pressione ENTER para continuar.\n");
                    getchar();
                    break;
                }// fim if
                
                alterou = 0;
                            
            break;// fim case 2

            case 3:
                return 0;
            break;// fim case 3
        }// fim switch opcao

        //Calcula a nota final e a situação final
        estudantes[estd_mod].notafinal = estudantes[estd_mod].prova1 + estudantes[estd_mod].prova2 + estudantes[estd_mod].prova3 + estudantes[estd_mod].trab1 + estudantes[estd_mod].trab2;

        if(estudantes[estd_mod].notafinal >= 60.0 && estudantes[estd_mod].faltas <= 18){
            estudantes[estd_mod].situacao = 'A';
        } else if(estudantes[estd_mod].faltas > 18){
            estudantes[estd_mod].situacao = 'F';
        } else if(estudantes[estd_mod].notafinal < 60.0){
            estudantes[estd_mod].situacao = 'R';
        }// fim else if

        //Reescreve o arquivo com as informações alteradas
        FILE * fp = fopen(turma, "w");

        // Imprime no topo do arquivo o número de estudantes inseridos
        fprintf(fp, "%u\n", i);

        for(int j = 0; j < *qtd_estudante; j++){
            fprintf(fp, "%s\n", estudantes[j].nome);
            fprintf(fp, "%s\n", estudantes[j].matricula);
            fprintf(fp, "%lf\n", estudantes[j].prova1);
            fprintf(fp, "%lf\n", estudantes[j].prova2);
            fprintf(fp, "%lf\n", estudantes[j].prova3);
            fprintf(fp, "%lf\n", estudantes[j].trab1);
            fprintf(fp, "%lf\n", estudantes[j].trab2);
            fprintf(fp, "%lf\n", estudantes[j].notafinal);
            fprintf(fp, "%u\n", estudantes[j].faltas);
            fprintf(fp, "%c\n", estudantes[j].situacao);
        }// fim for

        fclose(fp);

    }while(opcao != 3);// fim do while

}// fim editaEstudante


void imprimeMenuEdicao(void)
{
    printf("=====================================\n");
    printf("   Editar Informações do Estudante   \n");
    printf("=====================================\n");
    printf("Opções:\n\n");
    printf("1 - Alterar nome \n");
    printf("2 - Alterar matrícula\n");
    printf("3 - Alterar nota da prova 1\n");
    printf("4 - Alterar nota da prova 2\n");
    printf("5 - Alterar nota da prova 3\n");
    printf("6 - Alterar nota da trabalho 1\n");
    printf("7 - Alterar nota da trabalho 2\n");
    printf("8 - Alterar núremo de faltas\n");
    printf("9 - Voltar ao menu anterior\n\n");
    printf("Digite uma opção: ");
}// fim imprimeMenuEdicao

void alteraNome(Aluno estudantes[QTD], int i)
{
    char novo_nome[NOME];

    printf("\nDigite o novo nome do estudante:\n\t");
    fgets(novo_nome, sizeof(novo_nome), stdin);
    novo_nome[strlen(novo_nome)-1] = '\0';

    for(int j = 0; j < NOME; j++)
        estudantes[i].nome[j] = novo_nome[j];

}// fim alteraNome


void alteraMatr(Aluno estudantes[QTD], int i)
{
    char nova_matr[MATR];

    printf("\nDigite o nova matrícula do estudante:\n\t");
    fgets(nova_matr, sizeof(nova_matr), stdin);
    nova_matr[strlen(nova_matr)-1] = '\0';

    for(int j = 0; j < MATR; j++)
        estudantes[i].matricula[j] = nova_matr[j];
}// fim alteraMatr


void alteraProva1(Aluno estudantes[QTD], int i)
{
    double nova_prova1 = 0.0;

    printf("\nDigite a nova nota da prova 1:\n\t");
    scanf("%lf", &nova_prova1);
    getchar();

    estudantes[i].prova1 = nova_prova1;
}// fim alteraProva1


void alteraProva2(Aluno estudantes[QTD], int i)
{
    double nova_prova2 = 0.0;

    printf("\nDigite a nova nota da prova 2:\n\t");
    scanf("%lf", &nova_prova2);
    getchar();

    estudantes[i].prova2 = nova_prova2;
}// fim alteraProva2


void alteraProva3(Aluno estudantes[QTD], int i)
{
    double nova_prova3 = 0.0;

    printf("\nDigite a nova nota da prova 3:\n\t");
    scanf("%lf", &nova_prova3);
    getchar();

    estudantes[i].prova3 = nova_prova3;
}// fim alteraProva3


void alteraTrab1(Aluno estudantes[QTD], int i)
{
    double novo_trab1 = 0.0;

    printf("\nDigite a nova nota do trabalho 1:\n\t");
    scanf("%lf", &novo_trab1);
    getchar();

    estudantes[i].trab1 = novo_trab1;
}// fim alteratrab1


void alteraTrab2(Aluno estudantes[QTD], int i)
{
    double novo_trab2 = 0.0;

    printf("\nDigite a nova nota do trabalho 2:\n\t");
    scanf("%lf", &novo_trab2);
    getchar();

    estudantes[i].trab2 = novo_trab2;
}// fim alteratrab2


void alteraFaltas(Aluno estudantes[QTD], int i)
{
    unsigned int nova_faltas = 0;

    printf("\nDigite o novo número de faltas:\n\t");
    scanf("%u", &nova_faltas);
    getchar();

    estudantes[i].faltas = nova_faltas;
}// fim alteraFaltas


int relerTurma(Aluno estudantes[QTD], unsigned int * qtd_estudante, char turma[ARQ])
{
    // Verifica se há turma carregada
    if(*qtd_estudante < 1){
        printf("\nNão há turma carregada! Pressione ENTER para retornar.\n");
        getchar();
        return 0;
    }

    for(int j = 0; j < *qtd_estudante; j++){
    
        for(int k = 0; k < strlen(estudantes[j].nome); k++)
            estudantes[j].nome[k] = '\0';

        for(int l = 0; l < strlen(estudantes[j].matricula); l++)
            estudantes[j].matricula[l] = '\0';

        estudantes[j].prova1 = 0.0;
        estudantes[j].prova2 = 0.0;
        estudantes[j].prova3 = 0.0;
        estudantes[j].trab1 = 0.0;
        estudantes[j].trab2 = 0.0;
        estudantes[j].notafinal = 0.0;
        estudantes[j].faltas = 0;
        estudantes[j].situacao = '\0';

    }

    FILE * fp = fopen(turma, "r");
    
    // Verifica se o arquivo existe e se realmente foi aberto
    if(fp == NULL){
        fprintf(stderr, "O arquivo %s não existe!\n", turma);
        exit(1);
    }// fim if

    fscanf(fp, "%u", qtd_estudante);
    fgetc(fp);

    for(int i = 0; i < *qtd_estudante; i++){
        fgets(estudantes[i].nome, sizeof(estudantes[QTD].nome), fp);
        estudantes[i].nome[strlen(estudantes[i].nome)-1] = '\0';

        fgets(estudantes[i].matricula, sizeof(estudantes[QTD].matricula), fp);
        estudantes[i].matricula [strlen(estudantes[i].matricula)-1] = '\0';
        
        fscanf(fp, "%lf", &estudantes[i].prova1);
        fgetc(fp);

        fscanf(fp, "%lf", &estudantes[i].prova2);
        fgetc(fp);

        fscanf(fp, "%lf", &estudantes[i].prova3);
        fgetc(fp);

        fscanf(fp, "%lf", &estudantes[i].trab1);
        fgetc(fp);

        fscanf(fp, "%lf", &estudantes[i].trab2);
        fgetc(fp);

        fscanf(fp, "%lf", &estudantes[i].notafinal);
        fgetc(fp);

        fscanf(fp, "%u", &estudantes[i].faltas);
        fgetc(fp);

        fscanf(fp, "%c", &estudantes[i].situacao);
        fgetc(fp);
    }// fim for

    printf("Turma lida com sucesso! Pressione ENTER para continuar.");
    getchar();

}// fim relerTurma


void menu(unsigned int opcao)
{

    Aluno estudantes[QTD];
    unsigned int qtd_estudante = 0;
    char turma[ARQ];

	while(opcao != SAIR){

		menuPrincipal();
		opcao = leiaOpcaoMenu();
        
		if(opcao == 1){ // 

            do{

                menuLerTurma();
                opcao = leiaOpcaoMenu();

                switch(opcao){
                    case 1: lerTurma(estudantes, &qtd_estudante, turma);
                        break;
                    
                    case 2: criaTurma();
                        break;
                    
                    case 3:
                        break;

                }// fim switch(opcao) menuLerTurma

            }while(opcao != 3);
            
		} else if(opcao == 2){ // 

            imprimeTurma(estudantes, &qtd_estudante);

        } else if(opcao == 3){ // 
            
            imprimeEstatisticas(estudantes, qtd_estudante);

        } else if(opcao == 4){ // 

            cadastraEstudante(estudantes, &qtd_estudante, turma);
            
        } else if(opcao == 5){ // 

            editaEstudante(estudantes, &qtd_estudante, turma);
            
        } else if(opcao == 6){ // 

            relerTurma(estudantes, &qtd_estudante, turma);            
            
        } else if(opcao == 7){ // Salvar e sair  

            exit(1);
        }
        
	}//while

}// fim menu
