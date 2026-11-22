#include <stdio.h>
#include <string.h>

struct Produto{
    int codigo;
    char nome[50];
    float preco;
    int estoque;
};

struct Venda{
    struct Produto produto;
    int quantidade;
    float valorTotal;
};

int buscarProduto(struct Produto produtos[], int total, int codigo){
    for(int i = 0; i < total; i++){
        if(produtos[i].codigo == codigo){
            return i;
        }
    }
    return -1;
}

int main(){
    struct Produto produtos[10];
    struct Venda vendas[20];
    int totalProdutos = 0;
    int totalVendas = 0;
    int opcao, codigo, pos, qtd, maior;
    float faturamento, fatProduto, maiorFat;

    do{
        printf("\n- LOJA -\n");
        printf("1 - Cadastrar produto\n");
        printf("2 - Listar produtos\n");
        printf("3 - Registrar venda\n");
        printf("4 - Faturamento\n");
        printf("0 - Sair\n");
        printf("Escolha uma opcaoo: ");
        scanf("%d", &opcao);
        getchar();

        switch(opcao){
            case 1:
                if(totalProdutos == 10){
                    printf("Limite de 10 produtos atingido!\n");
                    break;
                }
                printf("Digite o codigo: ");
                scanf("%d", &produtos[totalProdutos].codigo);
                getchar();

                printf("Digite o nome: ");
                fgets(produtos[totalProdutos].nome, 50, stdin);
                produtos[totalProdutos].nome[strcspn(produtos[totalProdutos].nome, "\n")] = '\0';

                printf("Digite o preco: ");
                scanf("%f", &produtos[totalProdutos].preco);
                getchar();

                printf("Digite o estoque: ");
                scanf("%d", &produtos[totalProdutos].estoque);
                getchar();

                totalProdutos++;
                printf("Produto cadastrado!\n");
                break;

            case 2:
                if(totalProdutos == 0){
                    printf("Nenhum produto cadastrado.\n");
                }
                for(int i = 0; i < totalProdutos; i++){
                    printf("Codigo: %d / Nome: %s / Preco: R$ %.2f / Estoque: %d\n",
                           produtos[i].codigo, produtos[i].nome, produtos[i].preco, produtos[i].estoque);
                }
                break;

            case 3:
                if(totalVendas == 20){
                    printf("Limite de 20 vendas atingido!\n");
                    break;
                }
                printf("Digite o codigo do produto: ");
                scanf("%d", &codigo);
                getchar();
                pos = buscarProduto(produtos, totalProdutos, codigo);
                if(pos == -1){
                    printf("Produto nao cadastrado!\n");
                    break;
                }
                printf("Digite a quantidade vendida: ");
                scanf("%d", &qtd);
                getchar();
                if(qtd > produtos[pos].estoque){
                    printf("Estoque insuficiente! So existem %d unidades.\n", produtos[pos].estoque);
                    break;
                }

                produtos[pos].estoque = produtos[pos].estoque - qtd;

                vendas[totalVendas].produto = produtos[pos];
                vendas[totalVendas].quantidade = qtd;
                vendas[totalVendas].valorTotal = qtd * produtos[pos].preco;
                printf("Venda registrada! Valor: R$ %.2f\n", vendas[totalVendas].valorTotal);
                totalVendas++;
                break;

            case 4:
                if(totalVendas == 0){
                    printf("Nenhuma venda registrada.\n");
                    break;
                }
                faturamento = 0;
                for(int i = 0; i < totalVendas; i++){
                    faturamento = faturamento + vendas[i].valorTotal;
                }
                printf("Faturamento total: R$ %.2f\n", faturamento);

                maior = 0;
                maiorFat = 0;
                for(int i = 0; i < totalProdutos; i++){
                    fatProduto = 0;
                    for(int j = 0; j < totalVendas; j++){
                        if(vendas[j].produto.codigo == produtos[i].codigo){
                            fatProduto = fatProduto + vendas[j].valorTotal;
                        }
                    }
                    if(fatProduto > maiorFat){
                        maiorFat = fatProduto;
                        maior = i;
                    }
                }
                printf("Produto com maior faturamento: %s (R$ %.2f)\n", produtos[maior].nome, maiorFat);
                break;

            case 0:
                printf("Saindo...\n");
                break;

            default:
                printf("Opcao invalida!\n");
        }
    }while(opcao != 0);

    return 0;
}