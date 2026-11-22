#include <stdio.h>
#include <string.h>

struct Funcionario{
    int codigo;
    char nome[50];
    char cargo[50];
    float salarioBase;
    int horasExtras;
    float salarioBruto;
    float salarioLiquido;
};

int main(){
    struct Funcionario func[8];
    int n;
    int maior = 0;
    float valorHora, valorHoraExtra;
    float totalLiquido = 0;
    float totalBruto = 0;

    printf("Quantos funcionarios deseja cadastrar (maximo 8)? ");
    scanf("%d", &n);
    getchar();
    if(n > 8){
        n = 8;
    }

    for(int i = 0; i < n; i++){
        printf("\n--- Funcionário %d ---\n", i + 1);

        printf("Digite o codigo: ");
        scanf("%d", &func[i].codigo);
        getchar();

        printf("Digite o nome: ");
        fgets(func[i].nome, 50, stdin);
        func[i].nome[strcspn(func[i].nome, "\n")] = '\0';

        printf("Digite o cargo: ");
        fgets(func[i].cargo, 50, stdin);
        func[i].cargo[strcspn(func[i].cargo, "\n")] = '\0';

        printf("Digite o salario-base: ");
        scanf("%f", &func[i].salarioBase);
        getchar();

        printf("Digite a quantidade de horas extras: ");
        scanf("%d", &func[i].horasExtras);
        getchar();

        valorHora = func[i].salarioBase / 160;

        valorHoraExtra = valorHora * 1.5;

        func[i].salarioBruto = func[i].salarioBase + func[i].horasExtras * valorHoraExtra;

        func[i].salarioLiquido = func[i].salarioBruto - func[i].salarioBruto * 0.10;

        totalBruto = totalBruto + func[i].salarioBruto;
        totalLiquido = totalLiquido + func[i].salarioLiquido;

        if(func[i].salarioLiquido > func[maior].salarioLiquido){
            maior = i;
        }
    }

    printf("\n--- Folha de pagamento ---\n");
    for(int i = 0; i < n; i++){
        printf("Nome: %s / Cargo: %s / Bruto: R$ %.2f / Liquido: R$ %.2f\n",
               func[i].nome, func[i].cargo, func[i].salarioBruto, func[i].salarioLiquido);
    }

    printf("\nMaior salario liquido: %s (R$ %.2f)\n", func[maior].nome, func[maior].salarioLiquido);
    printf("Custo total da folha (soma dos liquidos): R$ %.2f\n", totalLiquido);
    printf("Total dos salarios brutos: R$ %.2f\n", totalBruto);

    return 0;
}