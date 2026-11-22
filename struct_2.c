#include <stdio.h>
#include <string.h>

struct Produto{
    int codigo;
    char nome[50];
    float preco;
    int quantidade;
};

int buscarProduto(struct Produto produtos[], int total, int codigo){
    for(int i = 0; i < total; i++){
        if(produtos[i].codigo == codigo){
            return i;
        }
    }
    return -1;
}

void reporEstoque(struct Produto *p, int qtd){
    p->quantidade = p->quantidade + qtd;
}

int registrarVenda(struct Produto *p, int qtd){
    if(qtd > p->quantidade){
        return 0;
    }
    p->quantidade = p->quantidade - qtd;
    return 1;
}

int main(){
    struct Produto produtos[15];
    int total = 0;
    int opcao, codigo, pos, qtd, maior;
    float totalEstoque;

    do{
        printf("\n--- PAPELARIA ---\n");
        printf("1 - Cadastrar produto\n");
        printf("2 - Listar produtos\n");
        printf("3 - Repor estoque\n");
        printf("4 - Registrar venda\n");
        printf("5 - Consultar produto pelo codigo\n");
        printf("6 - Valor total do estoque\n");
        printf("0 - Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);
        getchar();

        switch(opcao){
            case 1:
                if(total == 15){
                    printf("Limite de 15 produtos atingido!\n");
                    break;
                }
                printf("Digite o codigo: ");
                scanf("%d", &codigo);
                getchar();

                if(buscarProduto(produtos, total, codigo) != -1){
                    printf("Esse codigo ja existe!\n");
                    break;
                }
                produtos[total].codigo = codigo;

                printf("Digite o nome: ");
                fgets(produtos[total].nome, 50, stdin);
                produtos[total].nome[strcspn(produtos[total].nome, "\n")] = '\0';

                printf("Digite o preco: ");
                scanf("%f", &produtos[total].preco);
                getchar();

                printf("Digite a quantidade em estoque: ");
                scanf("%d", &produtos[total].quantidade);
                getchar();

                total++;
                printf("Produto cadastrado!\n");
                break;

            case 2:
                if(total == 0){
                    printf("Nenhum produto cadastrado.\n");
                }
                for(int i = 0; i < total; i++){
                    printf("Codigo: %d / Nome: %s / Preco: R$ %.2f / Estoque: %d\n",
                           produtos[i].codigo, produtos[i].nome, produtos[i].preco, produtos[i].quantidade);
                }
                break;

            case 3:
                printf("Digite o codigo do produto: ");
                scanf("%d", &codigo);
                getchar();
                pos = buscarProduto(produtos, total, codigo);
                if(pos == -1){
                    printf("Produto nao encontrado!\n");
                    break;
                }
                printf("Digite a quantidade a repor: ");
                scanf("%d", &qtd);
                getchar();
                reporEstoque(&produtos[pos], qtd);
                printf("Novo estoque: %d\n", produtos[pos].quantidade);
                break;

            case 4:
                printf("Digite o codigo do produto: ");
                scanf("%d", &codigo);
                getchar();
                pos = buscarProduto(produtos, total, codigo);
                if(pos == -1){
                    printf("Produto nao encontrado!\n");
                    break;
                }
                printf("Digite a quantidade vendida: ");
                scanf("%d", &qtd);
                getchar();
                if(registrarVenda(&produtos[pos], qtd) == 1){
                    printf("Venda registrada! Estoque atual: %d\n", produtos[pos].quantidade);
                }else{
                    printf("Venda nao realizada! So existem %d unidades.\n", produtos[pos].quantidade);
                }
                break;

            case 5:
                printf("Digite o codigo do produto: ");
                scanf("%d", &codigo);
                getchar();
                pos = buscarProduto(produtos, total, codigo);
                if(pos == -1){
                    printf("Produto nao encontrado!\n");
                }else{
                    printf("Nome: %s\n", produtos[pos].nome);
                    printf("Preco: R$ %.2f\n", produtos[pos].preco);
                    printf("Estoque: %d\n", produtos[pos].quantidade);
                }
                break;

            case 6:
                if(total == 0){
                    printf("Nenhum produto cadastrado.\n");
                    break;
                }
                totalEstoque = 0;
                maior = 0;
                for(int i = 0; i < total; i++){
                    totalEstoque = totalEstoque + produtos[i].preco * produtos[i].quantidade;
                    if(produtos[i].preco * produtos[i].quantidade > produtos[maior].preco * produtos[maior].quantidade){
                        maior = i;
                    }
                }
                printf("Valor total em estoque: R$ %.2f\n", totalEstoque);
                printf("Produto com maior valor em estoque: %s (R$ %.2f)\n",
                       produtos[maior].nome, produtos[maior].preco * produtos[maior].quantidade);
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