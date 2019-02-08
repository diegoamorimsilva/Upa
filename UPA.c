#include <stdio.h>
#include <stdlib.h>
#if defined(_WIN32) || defined(WIN32)
#define LIMPA_TERM system("cls")
#else
#define LIMPA_TERM system("clear")
#endif

void cabecalho();	//Cabeçalho da UPA
void cadastro();	// Função para cadastrar os pacientes
void sintomas();	// Função para receber os sintomas
void lista_triagem(); 		// Mostrando os dados
void chamar_triagem();
void separador();


typedef struct cad
{
	char nome[100];								//Struct para o cadastro dos pacientes
	char endereco[100];
	char cpf[10];
	char sintomas[100][100];
	int qtd_sintomas;
	int prd;
}hospital;
int n_pacientes;
int opcao;
int pacientes_salvos;
int main()
{
	cabecalho();
	int aux;
	printf("\t\t\t1 - Cadastrar pacientes\n");
	printf("\t\t\t2 - Visualizar pacientes para triagem\n");
	printf("\t\t\t3 - Chamar para a triagem\n");
	printf("\t\t\t4 - Visualizar pacientes avaliados\n");
	printf("\t\t\t5 - Chamar paciente para atendimento \n");
	printf("\t\t\t6 - Salvar em arquivo texto\n");
	printf("\t\t\t7 - Salvar em arquivo binario\n");
	printf("\t\t\t8 - Carregar um arquivo texto\n");
	printf("\t\t\t9 - Carregar um arquivo binario\n");
	printf("\t\t\t0 - Sair\n");
	printf("\t\t\t");
	scanf("%d",&opcao);
	LIMPA_TERM;
	switch (opcao)
	{
		case 1:
		printf("Hoje qual sera o maximo de pacientes a ser atendido?: ");	// Recebendo a quantidade de pacientes que serão atendidos
		scanf("%d",&n_pacientes);

		cadastro();
		break;

		case 2:
		lista_triagem();
		break;

		case 3:
		chamar_triagem();
		break;
	}

	return 0;
}



void cabecalho()
{
	printf("\t\t\t\t\t----------------------------------\n");
	printf("\t\t\t\t\t---------Atendimento UPA----------\n");			//Cabeçalho para para ficar bonitinho
	printf("\t\t\t\t\t----------------------------------\n");
}
void separador()
{
	printf("-------------------------------------\n\n");
}

void cadastro()
{
printf("\n");

	char duvida;
	int vet[n_pacientes];
	int posi[n_pacientes];
	int n_sintomas;
	FILE *arquivo;
	hospital cadastro[n_pacientes];					// Criando uma variavel vetor com a quantidade de pacientes "STRUCT HOSPITAL"
	pacientes_salvos = 0;
	arquivo = fopen("atendimento.txt","wb");		// Abrindo arquivo

	if (arquivo == NULL)
	{
		printf("Impossivel abrir o arquivo\n");
		exit(0);
	}

	else

	{

			

			for (int i = 0; i < n_pacientes; i++)
		{
			pacientes_salvos ++;
			cadastro[i].qtd_sintomas = 0;

			fflush(stdin);
			printf("\nEntre com o nome do paciente\n");		// Recebendo nome do paciente
			gets(cadastro[i].nome);
			fflush(stdin);
			printf("\nEntre com o cpf do paciente\n");		// recebendo cpf do paciente
			gets(cadastro[i].cpf);

			fflush(stdin);
			printf("\nEntre com a rua do paciente\n");		// recebendo endereço do paciente
			gets(cadastro[i].endereco);
			
			printf("Entre com a quantidade de sintomas: ");
			scanf("%d",&n_sintomas);

			

				for (int j = 0; j < n_sintomas; j++)
					{	
						fflush(stdin);
						printf("Qual e o sintoma?\n");
						gets(cadastro[i].sintomas[j]);
						printf("%s\n",cadastro[i].sintomas[j]);
						cadastro[i].qtd_sintomas++;
						
						fflush(stdin);
						printf("Deseja continuar acrescentando sintomas?\n");		// Condição caso o usuario deseje parar de acrescentar sintomas
						printf("S ou N\n");
						scanf("%c",&duvida);

						if (duvida == 's' || duvida == 'S') j = j;

						else j = n_sintomas;
					}

							
							fwrite(&cadastro[i], sizeof(hospital), 1, arquivo);	// Escrevendo os dados no arquivo binario
			
			fflush(stdin);
			printf("\nDeseja fazer mais cadastros?\n");		// Dando a opção do usuario fazer mais cadastros ou não
			printf("S ou N: ");
			scanf("%c",&duvida);

			if (duvida == 's' || duvida == 'S') i = i;
					
			else 

				{
					i = n_pacientes;							// condição para o loop ser finalizado caro o usuario queira cancelar os cadastros antes
					exit(0);
				}
			
		}
		
			


	}
	fwrite(&pacientes_salvos, sizeof(pacientes_salvos), 1, arquivo); // salvar quantidade de pessoas 

	fclose(arquivo);

}

void lista_triagem()
{
	hospital cadastro;

	FILE * arquivo;

	arquivo = fopen("atendimento.txt","rb");		// Abrindo arquivo

	if (arquivo == NULL)
	{
		printf("Impossivel abrir o arquivo\n");
		exit(0);
	}

	else
	{
		while(fread(&cadastro, sizeof(hospital), 1, arquivo) == 1)
		{
			
			printf("Nome: %s\n",cadastro.nome);
			printf("cpf: %s\n",cadastro.cpf);
			printf("Endereco: %s\n",cadastro.endereco);	
			for (int i = 0; cadastro.qtd_sintomas > i; i++)
			printf("Sintomas: %s\n",cadastro.sintomas[i]);	
			separador();
		}

	}
	fclose(arquivo);

}
void chamar_triagem ()
{
	hospital cadastro;

	FILE * arquivo;

	arquivo = fopen("atendimento.txt","rb");		// Abrindo arquivo

	if (arquivo == NULL)
	{
		printf("Impossivel abrir o arquivo\n");
		exit(0);
	}

	else
	{
		do{
			fread(&cadastro, sizeof(hospital), 1, arquivo);
			LIMPA_TERM;			
			printf("Nome: %s\n",cadastro.nome);
			printf("cpf: %s\n",cadastro.cpf);
			printf("Endereco: %s\n",cadastro.endereco);	
			for (int i = 0; cadastro.qtd_sintomas > i; i++)
			printf("Sintomas: %s\n",cadastro.sintomas[i]);
			printf("Qual o nivel de prioridade do paciente ?\n");
			printf(" 1 - Verde  2 - Amarelo 3 - Vermelho\n");
			scanf("%d",&cadastro.prd);
			printf("Deseja chamar o proximo paciente ? \n \t s - sim   n - não \n");
			getchar();
		}while(getchar()==115);
	}
	fclose(arquivo);

}
 