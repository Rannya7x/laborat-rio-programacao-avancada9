#include <string.h>
#include <stdlib.h>
#include <stdio.h>
//#include "mpeg.h"

void executar_split(FILE *arquivo_entrada, long long tam_max_bytes){
    int parte_atual = 1;
    char nome_arquivo_saida[10];
    sprintf(nome_arquivo_saida, "parte%d.mpg", parte_atual);

    //abre arquivo de saída para escrita e aloca buffer
    FILE *arquivo_saida = fopen(nome_arquivo_saida, "wb");
    unsigned char *buffer = malloc(tam_max_bytes);
    long long tam_buffer = 0, tam_total_saida = 0;
    unsigned char prefixo[4];

    
    while(fread(prefixo, 1,4,arquivo_entrada) == 4){
        //verifica se encontrou Sequence header
        if(memcmp(prefixo, "\x00\x00\x01\xB3", 4) == 0){
            // Se o buffer atual + o que já foi escrito estourar o limite
            if(tam_total_saida+tam_buffer > tam_max_bytes){
                fclose(arquivo_saida);
                sprintf(nome_arquivo_saida, "video_parte_%d.mpg", ++parte_atual);
                arquivo_saida = fopen(nome_arquivo_saida, "wb");
                tam_total_saida = 0;
            }

            // Escreve o buffer atual no arquivo de saída
            fwrite(buffer, 1, tam_buffer, arquivo_saida);
            tam_total_saida += tam_buffer;


            memcpy(buffer, prefixo, 4);
            tam_buffer = 4;
        } else {
            buffer[tam_buffer++] = prefixo[0];
            fseek(arquivo_entrada, -3, SEEK_CUR); // Volta 3 bytes para ler o próximo prefixo corretamente
        }

        fwrite(buffer, 1, tam_buffer, arquivo_saida);
        fclose(arquivo_saida);
        free(buffer);

    }

}