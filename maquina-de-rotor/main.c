

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


void inicializaRotor(int rotor[], int tamChave, char chave[]){

    //Inicializa vetor S -> vetor de 256 inteiros
    int s[256];
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

    for (int i = 0; i < 256; i++) {
        rotor[i] = s[i];
    }


}


int main(int argc, char *argv[]){

    //Lê o modo(cifragem ou decifragem)
    char modo = argv[1][0];
    
    //Lê a quantidade de rotores
    int qtdRotor = atoi(argv[2]); //Função atoi converte uma string de um argumento em um inteiro
    
    //Lê a chave do usuário
    int tamChave = strlen(argv[3]); //Verifica o tamanho da chave a partir do argumento da linha de comando
    char chave[tamChave];
    strcpy(chave, argv[3]);


    //Cria array de rotores com base na quantidade de rotores, cada um com tamanho de 256 inteiros
    int rotores[qtdRotor][256];

    //Lê a chave e inicializa cada rotor 
    for(int i=0; i<qtdRotor; i++){
        //Lê a chave do usuário
        int tamChave = strlen(argv[3]); //Verifica o tamanho da chave a partir do argumento da linha de comando
        char chave[tamChave];
        strcpy(chave, argv[3]);

        inicializaRotor(rotores[i], tamChave, chave);
    }
   

    return 0;
}
