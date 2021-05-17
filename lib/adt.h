#ifndef __ADT_
    #define __ADT_
    #define TRUCK_SIZE 100 // Dalam Kg
    #define MAX_A_DAY 300 // Dalam Kg
    #define MAX_ACCOUNT 13

    #ifdef _WIN32
        #include <conio.h>
        #define BKSPC 8
        #define ENTER 13
    #elif __linux__
        #include <unistd.h>
    #endif

    typedef struct user {
        char username[50], password[50];
        int apakah_terisi;
    } user;

    typedef struct gudang {
        int berat, banyak;
    } gudang;

    typedef struct barang {
        unsigned int berat, volume;
        char pengirim[50], penerima[50], alamat[75];
        char no_telp[13];
        struct barang *next;
    } barang;

    typedef struct container {
        int berat_muatan, banyak_barang;
        barang *muatan;
    } container;

    // Keperluan Graph
    typedef struct Node {
        struct Node *next;
        struct Node *prev;
        int kota;
        int hubungan_ketetanggan;
        int node_divisit[100];
    } Node;

    
#endif