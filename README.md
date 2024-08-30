# Arquivos 24.1 - CEFET-Rj - Projetos
Trabalhos e códigos relacionados a matéria de arquivos do período 24.1 no CEFET-Rj.

## Projetos
1. [Hash Join em C](#hashjoinemc)
2. [Busca Binária em C](#buscabinariaemc)

<div id='hashjoinemc'/>  

## Hash Join em C

Descrição do trabalho em base/labarquivos.pdf.

1. Rode o arquivo reduzArquivo.c para reduzir um arquivo em 80%, com registros selecionados aleatoriamente.

~~~~javascript
gcc -o reduzArquivo reduzArquivo.c
./reduzArquivo
~~~~

> Será necessário rodar 2 vezes, para criar 2 arquivos reduzidos em 80% que serão os operadores da interseção mais a frente

2. Rode o arquivo de criação de indices da tabela hash, para apenas 1 dos arquivos reduzidos.

~~~~javascript
gcc -o criaIndiceBloco criaIndiceBloco.c
./criaIndiceBloco
~~~~

3. Rode o arquivo de interseção, que irá verificar quais registros do outro arquivo reduzido se encontra na tabela hash, caso sejam iguais, imprime em um arquivo "saida.dat" (que deve ser criado previamente vazio).

~~~~javascript
gcc -o intersecaoIndice intersecaoIndice.c
./intersecaoIndice
~~~~

<div id='buscabinariaemc'/>  

## Busca Binaria em C
 
 ***Em breve :)***
