#ifndef PROJEK_PENUMPANG_H
#define PROJEK_PENUMPANG_H
#include <stdio.h>


typedef struct {
    char nama[100];
    char Email[100];
    char noHP[20];
    float harga;
} Penumpang;

void Penumpang() {
    printf("Nama Penumpang");
    printf("Nomor HP Penumpang");
    printf("Alamat Email Penumpang");
    printf("");
}


#endif //PROJEK_PENUMPANG_H