#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct _Endereco Endereco;

struct _Endereco {
  char logradouro[72];
  char bairro[72];
  char cidade[72];
  char uf[72];
  char sigla[2];
  char cep[8];
  char lixo[2];
};

int calculaPosicao() {

  double numAleatorioLimitado = (double)rand() / RAND_MAX;

  if (numAleatorioLimitado < 0.8) {
    return 1;
  }

  return 0;
}

int main(int argc, char **argv) {
  srand(time(NULL));
  FILE *f, *f2;
  Endereco e;

  f = fopen("cep.dat", "rb");
  if (f == NULL) {
    perror("Erro ao abrir o arquivo cepReduzido.dat");
    return 1;
  }

  f2 = fopen("cepReduzidoEm80.dat", "wb");
  if (f2 == NULL) {
    perror("Erro ao abrir o arquivo cepReduzido80.dat");
    fclose(f);
    return 1;
  }

  fread(&e, sizeof(Endereco), 1, f);

  while (!feof(f)) {
    if (calculaPosicao()) {
      fwrite(&e, sizeof(Endereco), 1, f2);
    }
    fread(&e, sizeof(Endereco), 1, f);
  }

  fclose(f);
  fclose(f2);
  return 0;
}
