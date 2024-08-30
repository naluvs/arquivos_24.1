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
  FILE *f, *f2;
  HashPage hp;
  Endereco e;

  int recordNumber = 0; 

  f = fopen("cepReduzidoEm80.dat", "rb");
  if (f == NULL) {
    perror("Erro ao abrir o arquivo cepReduzidoEm80.dat");
    fclose(f);
    return 1;
  }

  f2 = fopen("cep-hash-bloco.dat", "wb");
  if (f2 == NULL) {
    perror("Erro ao abrir o arquivo cep-hash-bloco.dat");
    fclose(f2);
    return 1;
  }

  memset(&hp, 0, sizeof(HashPage)); 
  for (int i = 0; i < HASH_SIZE; ++i) {
    fwrite(&hp, sizeof(HashPage), 1, f2); 
  }

  fclose(f2);
  f2 = fopen("cep-hash-bloco.dat", "r+b");

  while (1) {
    int bytesRead = fread(&e, sizeof(Endereco), 1, f);
    if (bytesRead == 0) {
      break; 
    }

    e.lixo[0] = '\0';
    int key = atoi(e.cep);
    int hashValue = hash(key);
    fseek(f2, hashValue * sizeof(HashPage), SEEK_SET);
    fread(&hp, sizeof(HashPage), 1, f2);
    if (hp.size < N) {
      hp.keys[hp.size] = key;
      hp.pointers[hp.size] = recordNumber;
      hp.size += 1;
      fseek(f2, hashValue * sizeof(HashPage), SEEK_SET);
      fwrite(&hp, sizeof(HashPage), 1, f2);
    }
    recordNumber++;
  }

  fclose(f);
  fclose(f2);

  return 0;
}