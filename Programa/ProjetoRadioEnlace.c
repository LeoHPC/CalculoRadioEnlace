/*Programa criado por Leonardo Henrique Petreca Costa
Data: 20/03/2021
O programa se trata de um projeto de rádio enlance, do qual o usuário deve 
entrar com uma série de dados para, então, o programa informar as saídas
padrões de um projeto desse tipo, tais como a importante decisão de dizer 
se o projeto possuirá ou não uma linha de visada, potência recebida, 
potência efetivamente recebida e sinal entregue ao receptor.
O código foi todo escrito em C. Espero que goste!
Todos os direitos reservados! GitHub: @LeoHPC*/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define PI 3.1416

struct topografico{
    float distancia;
    float altura;
};

float calculoRaio(struct topografico *perfil, float distanciaRadioEnlace, float frequencia, int quantidadePontos);
void calculoAtenuacao(float distanciaRadioEnlace, float frequencia);
void calculoPotenciaRecebida(float potenciaTx, float ganhoTx, float ganhoRx, float distanciaRadioEnlace, float frequencia);
void calculoPotenciaIrradiada(float potenciaTx, float ganhoTx, float atenuacaoCabo, float atenuacaoConector, float alturaTx, float alturaRx, struct topografico *perfil, int quantidadePontos, float distanciaRadioEnlace);
int calcularEgerarResultado(struct topografico *perfil, float alturaTx, float alturaRx, float raio, int quantidadePontos);

int main(void){
    float alturaTx, alturaRx, potenciaTx, atenuacaoPorConector, atenuacaoConector, ganhoTx, ganhoRx, distanciaRadioEnlace, frequencia, atenuacaoCabo, raio;
    int quantidadeConecectores, quantidadePontos, op, lineOfSight;
    register int i;

    printf("Bem-vindo ao nosso programa de Radio Enlace!\n");
    printf("Informe os dados ao programa e ele te dara todas as respotas!\n");
    printf("Digite a altura da torre do transmissor (Tx) em metros: \n");
    scanf("%f", &alturaTx);
    printf("Digite a altura da torre do receptor (Rx) em metros: \n");
    scanf("%f", &alturaRx);
    printf("Digite a distancia do radio enlance em km: \n");
    scanf("%f", &distanciaRadioEnlace);
    printf("Digite o valor da frequencia de operacao em GHz: \n");
    scanf("%f", &frequencia);
    printf("Para criar um perfil topografico, eh necessario montar uma tabela de dados. Digite o numero de pontos que seu perfil tera: \n");
    scanf("%d", &quantidadePontos);

    struct topografico perfil[quantidadePontos];

    for(i=0; i<quantidadePontos; i++){
        printf("Digite a distancia do ponto %d em km: \n", i);
        scanf("%f", &perfil[i].distancia);
        printf("Digite a altura do ponto %d em m: \n", i);
        scanf("%f", &perfil[i].altura);
    }

    system("cls");

    raio = calculoRaio(perfil, distanciaRadioEnlace, frequencia, quantidadePontos);
    lineOfSight = calcularEgerarResultado(perfil, alturaTx, alturaRx, raio, quantidadePontos);
    if(lineOfSight == 1){
        printf("Como seu perfil tera uma linha de visada, vamos, agora, calcular os proximos detalhes do projeto.\n");
        printf("---------------------------------------------------------------------------------------------------------------\n");
        system("pause");
        printf("Digite a potencia do transmissor (Ptx) em W: \n");
        scanf("%f", &potenciaTx);
        printf("Digite o numero de conectores: \n");
        scanf("%d", &quantidadeConecectores);
        printf("Digite a atenuacao por conector em dB: \n");
        scanf("%f", &atenuacaoPorConector);
        
        atenuacaoConector = quantidadeConecectores * atenuacaoPorConector;

        printf("Digite o ganho da antena de transmissao (Gtx) em dBi: \n");
        scanf("%f", &ganhoTx);
        printf("Digite o ganho da antena de recepcao (Grx) em dBi: \n");
        scanf("%f", &ganhoRx);

        system("cls");

        printf("Para o projeto, eh necessario escolher o cabo desejado.\n");
        printf("Nosso programa oferece algumas opcoes, porem voce pode construir a sua!\n");
        printf("Segue abaixo algumas opcoes. Digite a que mais lhe interessa: \n");
        printf("1 - Cabo TRI-LAN-400 50 ohms -> 2.4 GHz -> 0.22 dB de atenuacao por metro de cabo\n");
        printf("2 - Cabo RG-174 50 ohms -> 2.4 GHz -> 2.40 dB de atenuacao por metro de cabo\n");
        printf("3 - Cabo TRI-LAN-240 50 ohms -> 2.4 GHz -> 0.40 dB de atenuacao por metro de cabo\n");
        printf("4 - Cabo RF-7 50 ohms -> 2.4 GHz -> 0.39 dB de atenuacao por metro de cabo\n");
        printf("5 - Cabo DATALINK LMR 600 50 ohms -> 2.4 GHz -> 0.14 dB de atenuacao por metro de cabo\n");
        printf("6 - Cabo RG 213 50 ohms -> 2.4 GHz -> 0.25 dB de atenuacao por metro de cabo\n");
        printf("7 - Cabo TRI-LAN-240 50 ohms -> 5 GHz -> 0.60 dB de atenuacao por metro de cabo\n");
        printf("8 - Cabo TRI-LAN-400 50 ohms -> 5 GHz -> 0.32 dB de atenuacao por metro de cabo\n");
        printf("9 - Cabo DATALINK LMR 600 50 ohms -> 5 GHz -> 0.20 dB de atenuacao por metro de cabo\n");
        printf("10 - Cabo DATALINK DLC 8 Premium 50 ohms -> 5 GHz -> 0.34 dB de atenuacao por metro de cabo\n");
        printf("11 - Cabo DATALINK DLC 213 Premium 50 ohms -> 5 GHz -> 0.37 dB de atenuacao por metro de cabo\n");
        printf("12 - Crie seu cabo! Digite a atenuacao (em dB) por metro desejada: \n");
        printf("Digite a opcao que mais lhe interessa: \n");
        scanf("%d", &op);
        switch (op){
        case 1:
            atenuacaoCabo = 0.22;
            break;

        case 2:
            atenuacaoCabo = 2.40;
            break;

        case 3:
            atenuacaoCabo = 0.40;
            break;

        case 4:
            atenuacaoCabo = 0.39;
            break;

        case 5:
            atenuacaoCabo = 0.14;
            break;

        case 6:
            atenuacaoCabo = 0.25;
            break;

        case 7:
            atenuacaoCabo = 0.6;
            break;

        case 8:
            atenuacaoCabo = 0.32;
            break;

        case 9:
            atenuacaoCabo = 0.20;
            break;

        case 10:
            atenuacaoCabo = 0.34;
            break;

        case 11:
            atenuacaoCabo = 0.37;
            break;

        case 12:
            scanf("%f", &atenuacaoCabo);
            break;
        
        default:
            break;
        }

        system("cls");

        printf("Confira os dados finais de seu projeto: \n");
        printf("---------------------------------------------------------------------------------------------------------------\n");

        raio = calculoRaio(perfil, distanciaRadioEnlace, frequencia, quantidadePontos);
        lineOfSight = calcularEgerarResultado(perfil, alturaTx, alturaRx, raio, quantidadePontos);
        calculoAtenuacao(distanciaRadioEnlace, frequencia);
        calculoPotenciaRecebida(potenciaTx, ganhoTx, ganhoRx, distanciaRadioEnlace, frequencia);
        calculoPotenciaIrradiada(potenciaTx, ganhoTx, atenuacaoCabo, atenuacaoConector, alturaTx, alturaRx, perfil, quantidadePontos, distanciaRadioEnlace);

        } else
    if(lineOfSight == 2){
        return 0;        
    }   
}

float calculoRaio(struct topografico *perfil, float distanciaRadioEnlace, float frequencia, int quantidadePontos){

    float raio, aux2, maior = 0;
    int aux;
    register int i;
    for(i=0; i<quantidadePontos; i++){
        if(perfil[i].altura > maior){
            maior = perfil[i].altura;
            aux = i;
        }
    }
    printf("O ponto critico de seu perfil topografico eh o ponto: %d, na distancia: %.2f km e com uma altura de: %.2f m!\n", aux, perfil[aux].distancia, perfil[aux].altura);
    printf("---------------------------------------------------------------------------------------------------------------\n");

    aux2 = distanciaRadioEnlace - perfil[aux].distancia;

    raio = 547.72 * sqrt((perfil[aux].distancia * aux2) / ((frequencia * 1000) * distanciaRadioEnlace));
    printf("O raio da Zona de Fresnel de seu perfil eh de: %.2f m!\n", raio);
    printf("---------------------------------------------------------------------------------------------------------------\n");
    
    return raio;
}

void calculoAtenuacao(float distanciaRadioEnlace, float frequencia){

    float fspl;
    fspl = (20 * log10(distanciaRadioEnlace) + (20 * log10(frequencia)) + 92.45);

    printf("O nivel de sinal entregue ao receptor eh de %.2f dB!\n", fspl);
    printf("---------------------------------------------------------------------------------------------------------------\n");

}

void calculoPotenciaRecebida(float potenciaTx, float ganhoTx, float ganhoRx, float distanciaRadioEnlace, float frequencia){

    float potenciadBm, potenciaRxdBm, aux, comprimentoDeOnda;

    comprimentoDeOnda = (300000000/(frequencia * 1000000000));
    potenciadBm = 10 * log10(1000*potenciaTx);
    aux = ((4 * PI * distanciaRadioEnlace * 1000)/comprimentoDeOnda);

    potenciaRxdBm = potenciadBm + ganhoTx + ganhoRx - (20 * log10(aux));

    printf("O valor da potencia recebida eh de %.2f dBm!\n", potenciaRxdBm);
    printf("---------------------------------------------------------------------------------------------------------------\n");

}

int calcularEgerarResultado(struct topografico *perfil, float alturaTx, float alturaRx, float raio, int quantidadePontos){

    register int i;
    int aux3;
    float aux1, aux2, mediaAltura, maior;

    aux1 = perfil[0].altura + alturaTx;
    aux2 = perfil[(quantidadePontos -1)].altura + alturaRx;

    mediaAltura = (aux1 + aux2) / 2;

    for(i=0; i<quantidadePontos; i++){
        if(perfil[i].altura > maior){
            maior = perfil[i].altura;
            aux3 = i;
        }
    }

    if((mediaAltura - raio) > perfil[aux3].altura){
        printf("O seu perfil topografico tera uma linha de visada!\n");
        printf("-------------------------------------------------------------------------------------------------------------\n-");
        return 1;
    } else{
        printf("O seu perfil topografico nao tera uma linha de visada!\n");
        printf("---------------------------------------------------------------------------------------------------------------\n");
        return 2;
    }

}

void calculoPotenciaIrradiada(float potenciaTx, float ganhoTx, float atenuacaoCabo, float atenuacaoConector, float alturaTx, float alturaRx, struct topografico *perfil, int quantidadePontos, float distanciaRadioEnlace){

    float EIRP, potenciaTxdBm, aux, tamanhoCabo, atenuacaoTotalCabo;

    potenciaTxdBm = 10 * log10(1000 * potenciaTx);
    if((perfil[0].altura + alturaTx) == (perfil[quantidadePontos-1].altura + alturaRx)){
        tamanhoCabo = distanciaRadioEnlace * 1000;
    }
    if((perfil[0].altura + alturaTx) != (perfil[quantidadePontos-1].altura + alturaRx)){
        aux = ((perfil[0].altura + alturaTx) - (perfil[(quantidadePontos-1)].altura + alturaRx));
        if(aux < 0){
            aux = aux * (-1);
        }

        tamanhoCabo = sqrt((pow(distanciaRadioEnlace * 1000, 2)) + (pow(aux, 2)));
    }
    atenuacaoTotalCabo = tamanhoCabo * atenuacaoCabo;

    EIRP = potenciaTxdBm + ganhoTx - atenuacaoTotalCabo - atenuacaoConector;

    printf("A potencia efetivamente recebida eh de %.2f dBm!\n", EIRP);
    printf("---------------------------------------------------------------------------------------------------------------\n");

}