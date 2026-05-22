
#include <stdio.h>
#include <stdlib.h>

int main (int argc, char **argv) {
    //verifica se existem os argumentos necessários
    if (argc < 3){
        printf("Uso: %s <arquivo.mpg> <tamanho_mb>\n", argv);
        return 1;
    }

    FILE *arquivo_entrada = fopen(argv[2], "rb");
    if(!arquivo_entrada){
        perror("Erro ao abrir o arquivo de entrada.\n");
        return 1;
    }

     //converte o argumento do tamanho máximo de bytes para long long
    long long tam_max_bytes = atoll(argv[3]) *1024 * 1024;
    return 0;

    //chama motor de divisao
    executar_split(arquivo_entrada, tam_max_bytes);
    
    //fecha arquivo de entrada
    fclose(arquivo_entrada);
    return 0;
}