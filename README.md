# Laboratório 09: Dividindo Vídeos MPEG

## 1. Objetivo

Exercitar a manipulação de arquivos e dados binários através da decodificação e divisão de um arquivo de vídeo MPEG em partes menores e independentes.

## 2. Lógica de Identificação (MPEG Streams)

O formato MPEG é composto por fluxos (streams) independentes que iniciam com um start code prefix de 3 bytes: `\x00\x00\x01`. O byte seguinte identifica o tipo do fluxo.

### 2.1 Ponto de Corte: Sequence Header

Para que as partes divididas funcionem de forma independente, o corte deve ocorrer obrigatoriamente no início de um fluxo do tipo **Sequence (0xB3)**. Este cabeçalho contém metadados vitais, como largura, altura e taxa de quadros, necessários para que os reprodutores de vídeo iniciem a exibição corretamente.

## 3. Critérios de Divisão e Busca

O programa utiliza uma técnica de busca deslizante para localizar os pontos de corte sem perder dados entre os fluxos.

### 3.1 Busca Deslizante

A lógica consiste em ler 4 bytes do arquivo. Se o prefixo lido não for o de Sequence (`00 00 01 B3`), o programa salva apenas o primeiro byte e retrocede o ponteiro do arquivo em 3 bytes para garantir a varredura byte a byte.

```c
// Exemplo da lógica de busca deslizante
while (fread(prefixo, 1, 4, arq_in) == 4) {
    if (memcmp(prefixo, "\x00\x00\x01\xB3", 4) == 0) {
        // Encontrou início de Sequence: decide se realiza o split
    } else {
        // Não é Sequence: salva 1 byte e volta 3
        buffer[tam_buffer++] = prefixo;
        fseek(arq_in, -3, SEEK_CUR);
    }
}
```

### 3.2 Gerenciamento de Tamanho

O limite de tamanho é passado em Megabytes (MB) e convertido para bytes (MB×1024×1024). Um novo arquivo só é criado se o tamanho do arquivo atual somado ao tamanho do buffer acumulado (que contém um fluxo Sequence completo) ultrapassar o limite definido.

## 4. Fluxo de Execução e Interface

O programa opera via terminal e gera arquivos numerados automaticamente seguindo o padrão `video_parte_%d.mpg`.

O executável recebe o nome do vídeo original e o tamanho máximo desejado para cada parte.

```bash
./program <arquivo.mpg> <tamanho_mb>
```

O programa deve notificar o usuário a cada novo arquivo criado.

```bash
Criando arquivo video_parte_1.mpg ..
Criando arquivo video_parte_2.mpg ..
Criando arquivo video_parte_3.mpg ..
Criando arquivo video_parte_3.mpg ..
```

## 5. Limpeza

Executar `make clean` no terminal para excluir os videos gerados.