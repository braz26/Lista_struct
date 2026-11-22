#include <stdio.h>
#include <string.h>

struct Aluno{
    int matricula;
    char nome[50];
    float nota1;
    float nota2;
    float media;
};

float calcularMedia(float nota1, float nota2){
    return (nota1 + nota2) / 2;
}

int main(){
    struct Aluno alunos[10];
    int maior = 0;
    int menor = 0;
    int acima = 0;
    float soma = 0;
    float mediaGeral;

   
    for(int i = 0; i < 10; i++){
        printf("\n--- Aluno %d ---\n", i + 1);

        printf("Digite a matricula: ");
        scanf("%d", &alunos[i].matricula);
        getchar(); 

        printf("Digite o nome: ");
        fgets(alunos[i].nome, 50, stdin);
        alunos[i].nome[strcspn(alunos[i].nome, "\n")] = '\0';

        printf("Digite a nota 1: ");
        scanf("%f", &alunos[i].nota1);
        getchar();

        printf("Digite a nota 2: ");
        scanf("%f", &alunos[i].nota2);
        getchar();

       
        alunos[i].media = calcularMedia(alunos[i].nota1, alunos[i].nota2);

        soma = soma + alunos[i].media;
    }

    
    printf("\n--- Situacao dos alunos ---\n");
    for(int i = 0; i < 10; i++){
        printf("Nome: %s / Media: %.2f | ", alunos[i].nome, alunos[i].media);
        if(alunos[i].media >= 6.0){
            printf("Aprovado\n");
        }else{
            printf("Reprovado\n");
        }
    }

    
    for(int i = 1; i < 10; i++){
        if(alunos[i].media > alunos[maior].media){
            maior = i;
        }
        if(alunos[i].media < alunos[menor].media){
            menor = i;
        }
    }
    printf("\nMaior media: %s (%.2f)\n", alunos[maior].nome, alunos[maior].media);
    printf("Menor media: %s (%.2f)\n", alunos[menor].nome, alunos[menor].media);

    
    mediaGeral = soma / 10;
    printf("Media geral da turma: %.2f\n", mediaGeral);

    for(int i = 0; i < 10; i++){
        if(alunos[i].media > mediaGeral){
            acima++;
        }
    }
    printf("Alunos acima da media geral: %d\n", acima);

    return 0;
}