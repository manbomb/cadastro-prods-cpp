#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct {
    char codigo[20];
    char descricao[100];
    float valor;
} Produto;

typedef struct {
    int cod_compra;
    char codigo[20];
    int quantidade;
    int num_parc;
    int num_parc_pagas;
} Compra;

Produto produtos_cadastrados[30];
Compra compras_realizadas[100];

int ponteiro_produtos = 0;
int ponteiro_compras = 0;

int existe_produto(char cod[]) {
    for(int i = 0; i < ponteiro_produtos; i++) {
        if (strcmp(produtos_cadastrados[i].codigo, cod) == 0) {
            return 1;
            break;
        }
    }
    return 0;
}

Produto buscaProduto(char cod[]) {
    for(int i = 0; i < ponteiro_produtos; i++) {
        if (strcmp(produtos_cadastrados[i].codigo, cod) == 0) {
            return produtos_cadastrados[i];
            break;
        }
    }
}

void printProduto(Produto prod) {
    printf("\n COD: %s", prod.codigo);
    printf("\n DESCRICAO: %s", prod.descricao);
    printf("\n VALOR: %.2f \n", prod.valor);
}

void printCompra(Compra compra) {
    printf("\n COD. COMPRA: %i", compra.cod_compra);
    printf("\n PRODUTO: <%s> [%s]", buscaProduto(compra.codigo).descricao, compra.codigo);
    printf("\n QTD.: %i", compra.quantidade);
    printf("\n NUM. PARCELAS: %i", compra.num_parc);
    printf("\n NUM. PARCELAS PAGAS: %i \n", compra.num_parc_pagas);
}

int main()
{

    printf("----------------------------------------------\n");
    printf("-----------> CADASTRO DE PRODUTOS <-----------\n");
    printf("----------------------------------------------\n\n");
    
    while(1) {
        int op = 0;
        
        printf("\nEscolha uma opcao:\n");
        printf("1 - Cadastrar um produto\n");
        printf("2 - Cadastrar uma compra\n");
        printf("3 - Saldo devedor\n");
        printf("4 - Listar produtos parcelados não pagos\n");
        printf("5 - Listar todos os produtos\n");
        printf("6 - Sair do programa\n");
        printf("\nEscolha: ");
        scanf("%d", &op);
        
        switch(op) {
            case 1:
                printf("\nCadastro de um novo produto:\n\n");
                
                Produto novo_produto;
                
                char novo_codigo[] = "";
                
                while(strlen(novo_codigo) < 1 || strlen(novo_codigo) > 20) {
                    printf("Codigo do produto (ate 20 caracteres sem espacos): ");
                    scanf("%s", novo_codigo);
                    if (strlen(novo_codigo) > 20) printf("\nCodigo muito grande!\n");
                }
                
                strcpy(novo_produto.codigo, novo_codigo);
                
                char nova_descricao[] = "";
                
                while(strlen(nova_descricao) < 1 || strlen(nova_descricao) > 100) {
                    printf("Descricao do produto (ate 100 caracteres): ");
                    scanf(" %[^\n]", nova_descricao);
                    if (strlen(nova_descricao) > 100) printf("\nDescricao muito grande!\n");
                }
                
                strcpy(novo_produto.descricao, nova_descricao);
                
                printf("Valor do produto: ");
                scanf("%f", &(novo_produto.valor));

                strcpy(produtos_cadastrados[ponteiro_produtos].codigo, novo_produto.codigo);
                strcpy(produtos_cadastrados[ponteiro_produtos].descricao, novo_produto.descricao);
                produtos_cadastrados[ponteiro_produtos].valor = novo_produto.valor;
                ponteiro_produtos = ponteiro_produtos + 1;
                
                printf("\n\nNovo produto cadastrado!");
                printProduto(produtos_cadastrados[ponteiro_produtos-1]);
                printf("\nTotal de %d produto(s) cadastrados.\n", ponteiro_produtos);
                
                break;
            case 2:
                printf("\nCadastro de uma nova compra:\n\n");

                Compra nova_compra;

                nova_compra.cod_compra = ponteiro_compras;

                char codigo_produto[] = "";
                
                while(strlen(codigo_produto) < 1 || strlen(codigo_produto) > 20 || existe_produto(codigo_produto) == 0) {
                    printf("\nCodigo do produto (ate 20 caracteres sem espacos): ");
                    scanf("%s", codigo_produto);

                    if (strlen(codigo_produto) > 20) printf("\nCodigo muito grande!\n");
                    if (existe_produto(codigo_produto) == 0) printf("\nEste produto nao esta cadastrado.\n");
                }

                strcpy(nova_compra.codigo, codigo_produto);

                int nova_quantidade = 0;

                while (nova_quantidade < 1) {
                    printf("Quantidade (inteiro maior ou igual a 1): ");
                    scanf("%i", &nova_quantidade);
                    if (nova_quantidade < 1) printf("\nPor favor, coloque um valor válido.\n\n");
                }

                nova_compra.quantidade = nova_quantidade;

                int nova_num_parc = 0;

                while (nova_num_parc < 1) {
                    printf("Total de parcelas (inteiro maior ou igual a 1): ");
                    scanf("%i", &nova_num_parc);
                    if (nova_num_parc < 1) printf("\nPor favor, coloque um valor válido.\n\n");
                }

                nova_compra.num_parc = nova_num_parc;

                int nova_num_parc_pagas = 0;

                while (nova_num_parc_pagas < 1 || nova_num_parc_pagas > nova_compra.num_parc) {
                    printf("Total de parcelas pagas (inteiro maior ou igual a 1): ");
                    scanf("%i", &nova_num_parc_pagas);
                    if (nova_num_parc_pagas < 1) printf("\nPor favor, coloque um valor válido.\n\n");
                    if (nova_num_parc_pagas > nova_compra.num_parc) printf("\nPor favor, coloque um valor menor que o numero de parcelas.\n\n");
                }

                nova_compra.num_parc_pagas = nova_num_parc_pagas;

                compras_realizadas[ponteiro_compras].cod_compra = nova_compra.cod_compra;
                strcpy(compras_realizadas[ponteiro_compras].codigo, nova_compra.codigo);
                compras_realizadas[ponteiro_compras].num_parc = nova_compra.num_parc;
                compras_realizadas[ponteiro_compras].num_parc_pagas = nova_compra.num_parc_pagas;
                compras_realizadas[ponteiro_compras].quantidade = nova_compra.quantidade;
                ponteiro_compras = ponteiro_compras + 1;

                printf("\n\nNova compra cadastrada!");
                printCompra(compras_realizadas[ponteiro_compras-1]);
                printf("\nTotal de %d compra(s) cadastradas.\n", ponteiro_compras);

                break;
            case 3: ;
                float saldo_devedor = 0.0;
                for(int i = 0; i < ponteiro_compras; i++) {
                    Compra item = compras_realizadas[i];
                    float valor_devedor = item.num_parc-item.num_parc_pagas;
                    valor_devedor = valor_devedor/item.num_parc;
                    valor_devedor = valor_devedor*item.quantidade;
                    valor_devedor = valor_devedor*buscaProduto(item.codigo).valor;
                    saldo_devedor = saldo_devedor + valor_devedor;
                }
                printf("\n\n Saldo devedor calculado = %.2f \n\n", saldo_devedor);
                break;
            case 4:
                printf("\nLista de produtos parcelados não pagos integralmente:\n\n");
                printf("|COD. COMPRA\t|DESC. PROD.\t|COD. PROD.\t|SALDO DEVEDOR\t|");
                for(int i = 0; i < ponteiro_compras; i++) {
                    Compra item = compras_realizadas[i];

                    if (item.num_parc == item.num_parc_pagas) continue;

                    float valor_devedor = item.num_parc-item.num_parc_pagas;
                    valor_devedor = valor_devedor/item.num_parc;
                    valor_devedor = valor_devedor*item.quantidade;
                    valor_devedor = valor_devedor*buscaProduto(item.codigo).valor;

                    printf("\n|%i\t|%.14s\t|%.14s\t|%.2f\t|", item.cod_compra, buscaProduto(item.codigo).descricao, item.codigo, valor_devedor);
                }
                printf("\n\n");
                break;
            case 5:
                printf("\nLista de produtos:\n\n");
                printf("|COD. COMPRA\t|DESC. PROD.\t|COD. PROD.\t|VALOR PAGO\t|");

                float valor_gasto = 0.0;

                for(int i = 0; i < ponteiro_compras; i++) {
                    Compra item = compras_realizadas[i];

                    float valor_pago = item.num_parc_pagas;
                    valor_pago = valor_pago/item.num_parc;
                    valor_pago = valor_pago*item.quantidade;
                    valor_pago = valor_pago*buscaProduto(item.codigo).valor;
                    valor_gasto = valor_gasto + valor_pago;

                    printf("\n|%i\t|%.14s\t|%.14s\t|%.2f\t|", item.cod_compra, buscaProduto(item.codigo).descricao, item.codigo, valor_pago);
                }
                printf("\n\nVALOR GASTO = %f", valor_gasto);
                printf("\n\n");
                break;
            case 6:
                printf("\nPrograma encerrando...\n");
                return 0;
        }
    }
}


