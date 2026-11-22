#include <stdio.h>
#include <string.h>

struct Data{
    int dia;
    int mes;
    int ano;
};

struct Paciente{
    int codigo;
    char nome[50];
};

struct Consulta{
    struct Paciente paciente;
    struct Data data;
    char descricao[100];
};

int buscarPaciente(struct Paciente pacientes[], int total, int codigo){
    for(int i = 0; i < total; i++){
        if(pacientes[i].codigo == codigo){
            return i;
        }
    }
    return -1;
}

int main(){
    struct Paciente pacientes[15];
    struct Consulta consultas[30];
    struct Data dataBusca;
    int totalPacientes = 0;
    int totalConsultas = 0;
    int opcao, codigo, pos, achou, qtd, maior, qtdMaior;

    do{
        printf("\n- CLINICA -\n");
        printf("1 - Cadastrar paciente\n");
        printf("2 - Registrar consulta\n");
        printf("3 - Consultas de um paciente (pelo código)\n");
        printf("4 - Consultas de uma data\n");
        printf("5 - Numero de consultas por paciente\n");
        printf("6 - Paciente com mais atendimentos\n");
        printf("0 - Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);
        getchar();

        switch(opcao){
            case 1:
                if(totalPacientes == 15){
                    printf("Limite de 15 pacientes atingido!\n");
                    break;
                }
                printf("Digite o codigo do paciente: ");
                scanf("%d", &codigo);
                getchar();
                if(buscarPaciente(pacientes, totalPacientes, codigo) != -1){
                    printf("Esse codigo ja existe!\n");
                    break;
                }
                pacientes[totalPacientes].codigo = codigo;

                printf("Digite o nome do paciente: ");
                fgets(pacientes[totalPacientes].nome, 50, stdin);
                pacientes[totalPacientes].nome[strcspn(pacientes[totalPacientes].nome, "\n")] = '\0';

                totalPacientes++;
                printf("Paciente cadastrado!\n");
                break;

            case 2:
                if(totalConsultas == 30){
                    printf("Limite de 30 consultas atingido!\n");
                    break;
                }
                printf("Digite o codigo do paciente: ");
                scanf("%d", &codigo);
                getchar();
                pos = buscarPaciente(pacientes, totalPacientes, codigo);
                if(pos == -1){
                    printf("Paciente nao encontrado!\n");
                    break;
                }
                consultas[totalConsultas].paciente = pacientes[pos];

                printf("Digite o dia da consulta: ");
                scanf("%d", &consultas[totalConsultas].data.dia);
                getchar();
                printf("Digite o mes da consulta: ");
                scanf("%d", &consultas[totalConsultas].data.mes);
                getchar();
                printf("Digite o ano da consulta: ");
                scanf("%d", &consultas[totalConsultas].data.ano);
                getchar();

                printf("Digite a descricao do atendimento: ");
                fgets(consultas[totalConsultas].descricao, 100, stdin);
                consultas[totalConsultas].descricao[strcspn(consultas[totalConsultas].descricao, "\n")] = '\0';

                totalConsultas++;
                printf("Consulta registrada!\n");
                break;

            case 3:
                printf("Digite o codigo do paciente: ");
                scanf("%d", &codigo);
                getchar();
                achou = 0;
                for(int i = 0; i < totalConsultas; i++){
                    if(consultas[i].paciente.codigo == codigo){
                        printf("Paciente: %s | Data: %02d/%02d/%d | %s\n",
                               consultas[i].paciente.nome, consultas[i].data.dia,
                               consultas[i].data.mes, consultas[i].data.ano, consultas[i].descricao);
                        achou = 1;
                    }
                }
                if(achou == 0){
                    printf("Nenhuma consulta encontrada para esse codigo.\n");
                }
                break;

            case 4:
                printf("Digite o dia: ");
                scanf("%d", &dataBusca.dia);
                getchar();
                printf("Digite o mes: ");
                scanf("%d", &dataBusca.mes);
                getchar();
                printf("Digite o ano: ");
                scanf("%d", &dataBusca.ano);
                getchar();
                achou = 0;
                for(int i = 0; i < totalConsultas; i++){
                    if(consultas[i].data.dia == dataBusca.dia &&
                       consultas[i].data.mes == dataBusca.mes &&
                       consultas[i].data.ano == dataBusca.ano){
                        printf("Paciente: %s | %s\n", consultas[i].paciente.nome, consultas[i].descricao);
                        achou = 1;
                    }
                }
                if(achou == 0){
                    printf("Nenhuma consulta nessa data.\n");
                }
                break;

            case 5:
                for(int i = 0; i < totalPacientes; i++){
                    qtd = 0;
                    for(int j = 0; j < totalConsultas; j++){
                        if(consultas[j].paciente.codigo == pacientes[i].codigo){
                            qtd++;
                        }
                    }
                    printf("Paciente: %s | Consultas: %d\n", pacientes[i].nome, qtd);
                }
                break;

            case 6:
                maior = -1;
                qtdMaior = 0;
                for(int i = 0; i < totalPacientes; i++){
                    qtd = 0;
                    for(int j = 0; j < totalConsultas; j++){
                        if(consultas[j].paciente.codigo == pacientes[i].codigo){
                            qtd++;
                        }
                    }
                    if(qtd > qtdMaior){
                        qtdMaior = qtd;
                        maior = i;
                    }
                }
                if(maior == -1){
                    printf("Nenhuma consulta registrada.\n");
                }else{
                    printf("Paciente com mais atendimentos: %s (%d consultas)\n", pacientes[maior].nome, qtdMaior);
                }
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