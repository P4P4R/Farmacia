#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_REMEDIO 50

typedef struct {
    int codigo;
    char nome[MAX_REMEDIO];
    float preco;
    int quantidade_estoque;
    int generico;
    char categoria[MAX_REMEDIO];
    char fabricante[MAX_REMEDIO];
}remedio;

int verificar(int codigo){
	remedio r;
	int contador = 0;

	FILE *arquivo = fopen("remedios.dat", "rb");

    while (fread(&r, sizeof(remedio), 1, arquivo) != NULL){
        if (r.codigo == codigo){
        	return contador = 1;

			break;
		}
    }
    fclose(arquivo);

}

void cadastrar(){
	remedio r;
    int contador, codigo;
    FILE *arquivo = fopen("remedios.dat", "ab");
    
    printf("Digite o codigo do remedio: ");
    scanf("%d", &codigo);
    fflush(stdin);
    
    contador = verificar(codigo);
    
    if(contador == 1){
    	do{
    		printf("Codigo repetido digite novamente: ");
    		scanf("%d", &codigo);
    		contador = verificar(codigo);
		}while(contador == 1);
	}
	r.codigo = codigo;
    if(contador != 1){
	fflush(stdin);
    printf("Digite o nome do remedio: ");
    fgets(r.nome, MAX_REMEDIO, stdin);
    r.nome[strcspn(r.nome, "\n")] = '\0';
    
    printf("Digite o preco do remedio: ");
    scanf("%f", &r.preco);
    fflush(stdin);
    
    printf("Digite a quantidade em estoque do remedio: ");
    scanf("%d", &r.quantidade_estoque);
    fflush(stdin);
    
    printf("O remedio eh generico (1 sim ou 0 nao)? ");
    scanf("%d", &r.generico);
    fflush(stdin);

    
    printf("Digite a categoria do remedio: ");
    fgets(r.categoria, MAX_REMEDIO, stdin);
    r.categoria[strcspn(r.categoria, "\n")] = '\0';
    fflush(stdin);

    printf("Digite o fabricante do remedio: ");
    fgets(r.fabricante, MAX_REMEDIO, stdin);
    r.fabricante[strcspn(r.fabricante, "\n")] = '\0';
}
    fwrite(&r, sizeof(remedio), 1, arquivo);
    
    fclose(arquivo);
}


void consultar() {
	remedio r;
	FILE *arquivo = fopen("remedios.dat", "rb");
	int codigo, encontrou = 1;

    printf("Codigo: ");
    scanf("%d", &codigo);
    fflush(stdin);
    
    

    while (fread(&r, sizeof(remedio), 1, arquivo) == 1) {
        if (r.codigo == codigo) {
            encontrou = 1;
            printf(" Codigo \tNome\t\tCategoria\tGenerico\tFabricante\tQuantidade\tPreco\n");
            printf(" %d \t%s", r.codigo, r.nome);
            printf("\t\t%s", r.categoria);
            printf("\t\t%s", r.generico ? "Sim" : "Nao");
            printf("\t\t%s", r.fabricante);
            printf("\t\t%d", r.quantidade_estoque);
            printf("\t\t%.2f\n", r.preco);

				
            break;
        }
    }

    if (!encontrou) {
        printf("Medicamento nao encontrado!\n");
    }

    fclose(arquivo);
}

void alterar(){
remedio r;

int codigo, contador = 0, posicao, op = 0, encontrado;
printf("Digite codigo do remedio para ser alterado: ");
scanf("%d", &codigo);

contador= verificar(codigo);


FILE *arquivo = fopen("remedios.dat", "rb+");

if (contador != 1){
		do{
			printf("\nCodigo nao encontrado\n");
 			printf("\nDigite o Codigo do remedio novamente: ");
    		scanf("%d", &codigo);
    		contador = verificar(codigo);
		}while(contador != 1);
	}

if (contador == 1){
	while (fread(&r, sizeof(remedio), 1, arquivo) != NULL) {
        if (r.codigo == codigo) {
    printf(" Codigo\tNome\tCategoria\tFabricante\tGenerico\tQuantidade\tPreco\n");
    printf(" %d", r.codigo);
    printf(" - \t%s\t%s\t\t%s\t\t%s\t\t%d\t\t%.2f", r.nome, r.categoria, r.fabricante, r.generico ? "Sim" : "Nao", r.quantidade_estoque, r.preco);
 break;
        }
    }
}

while(op < 7){

printf("\n\nEscolha as seguintes opcoes\n");
		printf("1- Para mudar o nome do remedio\n");
		printf("2- Para mudar a categoria do remedio\n");
		printf("3- Para mudar o frabricante do remedio\n");
		printf("4- Para mudar se eh generico ou nao\n");
		printf("5- Para mudar a quantidade do remedio\n");
		printf("6- Para mudar o preco do remedio\n");
		printf("7- Para voltar\n");
		scanf("%d", &op);
fflush(stdin);

    if(op == 1){
    	rewind(arquivo); //ir para o inicio do arquivo
		encontrado = 0;
    	while (fread(&r, sizeof(remedio), 1, arquivo) == 1) {
                    if (r.codigo == codigo) {
                        printf("\nNovo nome: ");
       					fgets(r.nome, 50, stdin);
    					r.nome[strcspn(r.nome, "\n")] = '\0';

                        fseek(arquivo, -sizeof(remedio), SEEK_CUR); 
                        fwrite(&r, sizeof(remedio), 1, arquivo); 
                        printf("\nNome atualizado com sucesso!\n");
                        encontrado = 1;
                        break;
                    }
                }
                if (!encontrado) {
                    printf("\nProduto nao encontrado.\n");
                }
                break;


    }
    if(op == 2){
    	rewind(arquivo); 
		encontrado = 0;
    	while (fread(&r, sizeof(remedio), 1, arquivo) == 1) {
                    if (r.codigo == codigo) {
                        printf("\nNova categoria");
						fgets(r.categoria, 50, stdin);
    					r.categoria[strcspn(r.categoria, "\n")] = '\0';

                        fseek(arquivo, -sizeof(remedio), SEEK_CUR); // volta para o registro anterior
                        fwrite(&r, sizeof(remedio), 1, arquivo); // atualiza o registro
                        printf("\nCategoria atualizado com sucesso!\n");
                        encontrado = 1;
                        break;
                    }
                }
                if (!encontrado) {
                    printf("\nProduto nao encontrado.\n");
                }
                break;


	}
	if(op == 3){
		rewind(arquivo);
		encontrado = 0;
    	while (fread(&r, sizeof(remedio), 1, arquivo) == 1) {
                    if (r.codigo == codigo) {
                        printf("\nNova fabricante: ");
                            	fgets(r.fabricante, 50, stdin);
    							r.fabricante[strcspn(r.fabricante, "\n")] = '\0';

                        fseek(arquivo, -sizeof(remedio), SEEK_CUR); // volta para o registro anterior
                        fwrite(&r, sizeof(remedio), 1, arquivo); // atualiza o registro
                        printf("\nFabricante atualizado com sucesso!\n");
                        encontrado = 1;
                        break;
                    }
                }
                if (!encontrado) {
                    printf("\nProduto nao encontrado.\n");
                }
                break;

	}

	if(op == 4){
		rewind(arquivo);
		encontrado = 0;
    	while (fread(&r, sizeof(remedio), 1, arquivo) == 1) {
                    if (r.codigo == codigo) {
                        printf("Generico (0 - Nao, 1 - Sim): ");
                        scanf("%d", &r.generico);

                        fseek(arquivo, -sizeof(remedio), SEEK_CUR);
                        fwrite(&r, sizeof(remedio), 1, arquivo);
                        printf("\nPreco atualizado com sucesso!\n");
                        encontrado = 1;
                        break;
                    }
                }
                if (!encontrado) {
                    printf("\nProduto nao encontrado.\n");
                }
                break;
	}

	if(op == 5){
		rewind(arquivo);
		encontrado = 0;
    	while (fread(&r, sizeof(remedio), 1, arquivo) == 1) {
                    if (r.codigo == codigo) {
                        printf("Digite a nova quantidade: ");
                        scanf("%d", &r.quantidade_estoque);

                        fseek(arquivo, -sizeof(remedio), SEEK_CUR); // volta para o registro anterior
                        fwrite(&r, sizeof(remedio), 1, arquivo); // atualiza o registro
                        printf("\nPreco atualizado com sucesso!\n");
                        encontrado = 1;
                        break;
                    }
                }
                if (!encontrado) {
                    printf("\nProduto nao encontrado.\n");
                }
                break;
	}

	if(op == 6){
		rewind(arquivo);
		encontrado = 0;
    	while (fread(&r, sizeof(remedio), 1, arquivo) == 1) {
                    if (r.codigo == codigo) {
                        printf("Digite o novo preco: ");
                        scanf("%f", &r.preco);

                        fseek(arquivo, -sizeof(remedio), SEEK_CUR);
                        fwrite(&r, sizeof(remedio), 1, arquivo);
                        printf("\nPreco atualizado com sucesso!\n");
                        encontrado = 1;
                        break;
                    }
                }
                if (!encontrado) {
                    printf("\nProduto nao encontrado.\n");
                }
                break;
	}


	}

fclose(arquivo);
}

void remover(){
int codigo, achou = 0;
system("cls");
printf("Digite codigo do registro a ser excluido: ");
scanf("%d", &codigo);

FILE *arquivo = fopen("remedios.dat", "rb");
FILE *temp = fopen("temp.dat", "ab");
remedio r;

while(fread(&r, sizeof(remedio), 1, arquivo) != NULL){
    if(r.codigo == codigo){
        achou = 1;
    }
    else{
        fwrite(&r, sizeof(remedio), 1, temp);
    }
}
if(achou == 0){
    printf("\nCodigo nao encontrado\n");
}
else{
    printf("\nRegistro excluido");
}
fclose(arquivo);
remove("remedios.dat");
fclose(temp);
rename("temp.dat", "remedios.dat");
remove("temp.dat");
}

void exibir() {
	remedio r;
	system("cls");
    FILE *arquivo = fopen("remedios.dat", "rb");

    printf("Codigo \tNome\t\tCategoria\tGenerico\tFabricante\tQuantidade\tPreco\n");
    while (fread(&r, sizeof(remedio), 1, arquivo) != NULL) {

            printf("%d \t%s", r.codigo, r.nome);
            printf("\t\t%s", r.categoria);
            printf("\t\t%s", r.generico ? "Sim" : "Nao");
            printf("\t\t%s", r.fabricante);
            printf("\t\t%d", r.quantidade_estoque);
            printf("\t\t%.2f\n", r.preco);
    }

    fclose(arquivo);
}

int main(){
	int op=0;

	printf("Programa iniciado");

	while(op < 6){
		printf("\n\nEscolha as seguintes opcoes\n");
		printf("1- Para cadastrar um remedio\n");
		printf("2- Para consultar os remedios\n");
		printf("3- Para alterar um remedio\n");
		printf("4- Para remover um remedio\n");
		printf("5- Para exibir todos os remedios\n");
		printf("6- Para sair\n");
		scanf("%d", &op);
		switch(op){

			case 1:
				cadastrar();
				break;

			case 2:
				consultar();
				break;

			case 3:
				alterar();
				break;

			case 4:
				remover();
				break;

			case 5:
				exibir();
				break;
		}
	}
return 0;
}
