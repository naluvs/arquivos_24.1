#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define N 1000
#define HASH_SIZE 1399

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

typedef struct _HashPage {
  short size;
  int keys[N];
  int pointers[N];
  int next;
} HashPage;

int hash(int key) { return key % HASH_SIZE; }

int main() {
  FILE *f, *f2, *f3;
  HashPage hp;
  Endereco e;
  int recordNumber = 0;

  f = fopen("cepReduzidoEm80-2.dat", "rb");
  if (f == NULL) {
    perror("Erro ao abrir o arquivo cep.dat");
    fclose(f);
    return 1;
  }

  f2 = fopen("cep-hash-bloco.dat", "rb");
  if (f2 == NULL) {
    perror("Erro ao abrir o arquivo cep-hash-bloco.dat");
    fclose(f2);
    return 1;
  }

  f3 = fopen("saida.dat", "r+b");
  if (f3 == NULL) {
    perror("Erro ao abrir o arquivo saida.dat");
    fclose(f2);
    return 1;
  }

  while (1) {
    int bytesRead = fread(&e, sizeof(Endereco), 1, f);

    if (bytesRead == 0) {
      break;
    }

    e.lixo[0] = '\0';
    int key = atoi(e.cep);
    int hashValue = hash(key);

    fseek(f2, hashValue * sizeof(hp), SEEK_SET);

    fread(&hp, sizeof(hp), 1, f2);

    for (int i = 0; i < hp.size; i++) {
      if (hp.keys[i] == key) {
        fwrite(&e, sizeof(Endereco), 1, f3);
      }
    }
  }

  fclose(f);
  fclose(f2);
  fclose(f3);

  return 0;
}