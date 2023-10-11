

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int inicializaRotor(int rotor[], int tamChave, char chave[], int s[]){

    //Inicializa vetor S -> vetor de 256 inteiros
    for(int i=0; i<256; i++){
        s[i] = i;
    }

    //Permutação do vetor s com base na chave dada pelo usuário
    int j = 0;
    for(int i=0; i<256; i++){
        j = (j + s[i] + chave[i % tamChave]) % 256;
        unsigned char temp = s[i];
        s[i] = s[j];
        s[j] = temp;
    }

    //Imprime o vetor s
    for(int i=0; i<256; i++){
        printf("%d ", s[i]);
        if(i%16 == 0 && i != 0){
            printf("\n");
        }
    }

    return s;
}

unsigned char cifraBit(unsigned char c, int rotores, int rotorIndex){
    unsigned char x;
    x = c + rotores % 256;
    return x;
}


int main(int argc, char *argv[]){

    //Lê o modo(cifragem ou decifragem)
    int modo = argv[1][0];
    
    //Lê a quantidade de rotores
    int qtdRotor = atoi(argv[2]); //Função atoi converte uma string de um argumento em um inteiro
    
    //Lê a chave do usuário
    int tamChave = strlen(argv[3]); //Verifica o tamanho da chave a partir do argumento da linha de comando
    char chave[tamChave];
    strcpy(chave, argv[3]);


    //Cria array de rotores com base na quantidade de rotores, cada um com tamanho de 256 inteiros
    int rotores[qtdRotor][256];

    int s[256];

    //Lê a chave e inicializa cada rotor 
    for(int i=0; i<qtdRotor; i++){
        //Lê a chave do usuário
        int tamChave = strlen(argv[3]); //Verifica o tamanho da chave a partir do argumento da linha de comando
        char chave[tamChave];
        strcpy(chave, argv[3]);

        inicializaRotor(rotores[i], tamChave, chave, s);

        for(int j=0; j<256; j++){
            rotores[i][j] = s[j];
        }
    }

    printf("\n--------------\n");
    for(int i=0; i<256; i++){
        printf("%d ", rotores[0][i]);
        if(i%16 == 0 && i != 0){
            printf("\n");
        }
    }

    //Variaveis para controlar o deslocamento dos rotores
    int k[qtdRotor]; //A cada quantos símboloso os rotores se movem
    int l[qtdRotor]; //Quantas posições os rotores se movem
   
   //Lê e armazena nos vetores o k e l lido da linha de comando
    for(int i=0; i<qtdRotor; i++){
        k[i] = atoi(argv[3+qtdRotor+i]);
        l[i] = atoi(argv[3+(2*qtdRotor)+i]);
    }

    //Abre o arquivo txt contendo o texto claro
    FILE *entrada;
    entrada = fopen(argv[argc-2], "rb");

    //Criar o arquivo de saida
    FILE *saida;
    saida = fopen(argv[argc-1], "wb");

    //Lê cada bit do texto claro e cifra ele
    int rotorIndex = 0;

    unsigned char c;
    unsigned char x;
   
    while(1){
        c = fgetc(entrada);
        if(feof(entrada)){
            break;
        }
        printf("NÃO CIFRADO: %d\n", c);
        if(modo == 'C'){
            x = cifraBit(c, rotores[0][rotorIndex], rotorIndex);
            unsigned char *p = &x;
            fwrite(p, 1, 1, saida);
            
            printf("CIFRADO: %d\n", x);
        }
        rotorIndex = rotorIndex + 1;
    }


    return 0;
}
