#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "support_file.h"

user account[2][MAX_ACCOUNT];
gudang gudang_bali = {.banyak = 0, .berat = 0}, gudang_jawa = {.banyak = 0, .berat = 0};

void si_kang_paket() {
    clear();
    puts("\n\t==================================");
    puts("\t|  Program Sistem Tukang Paket   |");
    puts("\t|     Program Si Kang Paket      |");
    puts("\t==================================\n");
}

void tahan() {
    printf("\n\tTekan enter untuk melanjutkan...");
    getchar();
}

void init_table() {
    for (int i = 0 ; i < MAX_ACCOUNT ; i++) {
        account[0][i].apakah_terisi = 0;
        account[1][i].apakah_terisi = 0;
    }
}

void init_acc() {
    FILE *bali_acc = fopen("acc\\gudang_bali.txt", "r");
    FILE *jawa_acc = fopen("acc\\gudang_jawa.txt", "r");
    user temp_init_acc;

    fscanf(bali_acc, "%s %s", temp_init_acc.username, temp_init_acc.password);
    add_account(temp_init_acc, 0);
    
    fscanf(jawa_acc, "%s %s", temp_init_acc.username, temp_init_acc.password);
    add_account(temp_init_acc, 1);
    
    fclose(bali_acc);
    fclose(jawa_acc);
}

/*Kita akan menggunakan akun*/
unsigned int hash_func(char *username) {
    unsigned int result = 0;
    for (int i = 0 ; username[i] ; i++) result += username[i];
    for (int i = 0 ; username[i] ; i+=2) result *= username[i];
    return result % 13;
}

void add_account(user temp_data_account, int region) {
    int index = hash_func(temp_data_account.username);

    if(account[region][index].apakah_terisi == 1) {
        int temp_geser = index;
        do {
            temp_geser = (temp_geser + 1) % MAX_ACCOUNT;
            if (account[region][temp_geser].apakah_terisi == 0) {
                strcpy(account[region][temp_geser].username, temp_data_account.username);
                strcpy(account[region][temp_geser].password, temp_data_account.password);
                account[region][temp_geser].apakah_terisi = 1;
                puts("\tAkun berhasil dibuat!");
                return ;
            }
        } while (temp_geser != index);
        puts("\tAkun tidak berhasil dibuat!");
        puts("\tBanyak akun sudah melampaui batas");
        return ;
    }
    strcpy(account[region][index].username, temp_data_account.username);
    strcpy(account[region][index].password, temp_data_account.password);
    account[region][index].apakah_terisi = 1;
    puts("\tAkun berhasil dibuat!");
    return ;
}

void remove_account(user temp_data_account, int region) {
    int index = hash_func(temp_data_account.username);
    int temp_geser = index;
    do {
        if (strcmp(account[region][temp_geser].username, temp_data_account.username) == 0) {
            account[region][index].apakah_terisi = 0;
            account[region][temp_geser].username[0] = "\0";
            puts("\tAkun berhasil dihapus!!");
            return ;
        }
        temp_geser = (temp_geser + 1) % MAX_ACCOUNT;
    } while (temp_geser != index);
    puts("\tAkun tidak ada!");
    return ;
}

int check_login(char *username, char *password, int region) {
    int index = hash_func(username);
    int temp_geser = index;

    if (account[region][index].apakah_terisi == 0) {
        return 0;
    };
    do {
        if (account[region][temp_geser].apakah_terisi == 1 && \
            strcmp(username, account[region][temp_geser].username) == 0 && \
            strcmp(password, account[region][temp_geser].password) == 0) 
            return 1;
        temp_geser = (temp_geser + 1) % 13;
    } while (temp_geser != index);
    return 0;
}

char* get_pwd(){
    char *pwd = (char*) malloc(50);
    #ifdef _WIN32
        char character;
        unsigned int indeks = 0;
        while (1) {
            character = getch();

            if (character == ENTER) {
                printf("\b*");
                pwd[indeks] = '\0';
                break;
            }
            else if (character == BKSPC) {
                if (indeks == 0) continue;
                indeks--;
                printf("\b \b");
            }
            else {
                if (indeks > 0) {
                    printf("\b*");
                }
                pwd[indeks++] = character;
                printf("%c", character);
            }
        }
    #elif __linux__
        pwd = getpass("Your password: ");
    #endif
    return pwd;
}

void clear() {
    #ifdef _WIN32
        system("cls");
    #elif __linux__
        system("clear");
    #endif
}

barang *initialize_node_barang() {
    barang *head = NULL, *temp_input = NULL, *temp_node;

    temp_input = (barang*) malloc(sizeof(barang));
    temp_input->next = NULL;
    puts("\t==================================");
    puts("\t     Data pengirim & penerima     ");
    puts("\t==================================");
    printf("\tMasukkan nama pengirim : ");
    scanf("%[^\n]", temp_input->pengirim);
    getchar();
    printf("\tMasukkan nama penerima : ");
    scanf("%[^\n]", temp_input->penerima);
    getchar();
    printf("\tMasukkan alamat penerima : ");
    scanf("%[^\n]", temp_input->alamat);
    getchar();
    printf("\tMasukkan nomor telepon penerima : ");
    scanf("%[^\n]", temp_input->no_telp);
    getchar();

    puts("\t==================================");
    puts("\t           Data barang           ");
    puts("\t==================================");
    do {
        printf("\tMasukan berat barang (dalam kg): ");
        scanf("%u", &(temp_input->berat));
        getchar();
        if (temp_input->berat > 100) puts("\tBarang yang boleh dikirim hanya\n\tyang beratnya kurang dari 100 kg");
    } while(temp_input->berat > 100);
    printf("\tMasukan volume barang (dalam m^3): ");
    scanf("%u", &(temp_input->volume));
    getchar();

    gudang_bali.banyak++;
    gudang_bali.berat += temp_input->berat;

    if (gudang_bali.berat >= TRUCK_SIZE) {
        puts("\n\tBERAT SUDAH CUKUP ATAU MELEBIHI");
        puts("\tAPABILA SUDAH PARTAI 3 DAN BARANG");
        puts("\tMELEBIHI, BARANG YANG LEBIH TIDAK");
        puts("\tIKUT TERKIRIM\n");
    }

    if (head == NULL) {
        head = temp_input;
    }
    else {
        temp_node = head;
        while(temp_node->next != NULL){
            temp_node = temp_node->next;
        }
        temp_node->next = temp_input;
    }
    return head;
}

void insert(barang **ptr_head) {
    barang *will_insert, *temp = *ptr_head;

    will_insert = initialize_node_barang();
    if (gudang_bali.berat > MAX_A_DAY) {
        puts("\tSudah melebihi kuota dalam sehari");
        gudang_bali.banyak--;
        gudang_bali.berat -= will_insert->berat;
        return;
    }

    while (temp != NULL) {
        if (temp->next == NULL) {
            temp->next = will_insert;
            break;
        }
        temp = temp->next;
    }
}

void lihat_gudang(barang *ptr_head) {
    barang *temp = ptr_head;

    if (temp != NULL) {
        puts("\t=====================================================");
        puts("\t                     ISI GUDANG                      ");
        puts("\t=====================================================");
        do
        {
            printf("\tPenerima : %s\n", temp->penerima);
            printf("\tPengirim : %s\n", temp->pengirim);
            printf("\tAlamat   : %s\n", temp->alamat);
            printf("\tNo telp  : %s\n", temp->no_telp);
            printf("\tBerat    : %u\n", temp->berat);
            printf("\tVolume   : %u\n", temp->volume);
            puts("\t=====================================================");
            temp = temp->next;
        } while (temp != NULL);        
    }
    else{
        puts("\n\t===============");
        puts("\t|Gudang kosong|");
        puts("\t===============");
    }
    puts(" ");
}

void list_akan_dikirim(barang **list_barang, container *array, int region){
    //dequeue
    barang *temp = *list_barang;
    while((array->berat_muatan += temp->berat) <= TRUCK_SIZE) {
        array->banyak_barang++;
        if (region == 0) {
            gudang_bali.banyak--;
            gudang_bali.berat -= temp->berat;
        }
        else {
            gudang_jawa.banyak--;
            gudang_jawa.berat -= temp->berat;
        }
        if(temp->next != NULL) temp = temp->next;
        else break;
    }
    if (array->berat_muatan > TRUCK_SIZE) {
        array->berat_muatan -= temp->berat;
        if(region == 0) {
            gudang_bali.banyak++;
            gudang_bali.berat += temp->berat;
        }
        else {
            gudang_jawa.banyak++;
            gudang_jawa.berat += temp->berat;
        }
    }
    array->muatan = (barang*) malloc(array->banyak_barang * sizeof(barang));
    for (int i = 0 ; i < array->banyak_barang ; i++) {
        array->muatan[i] = **list_barang;
        *list_barang = (*list_barang)->next;
    }
}

void sort(barang *unsorted, int banyak_barang) {
    int banyak_unsorted = banyak_barang;
    barang temp;
    for (int i = banyak_unsorted - 1; i > 0;i--) {
        for(int j = 0 ; j < i ; j++) {
            if (unsorted[j].volume < unsorted[j + 1].volume) {
                temp = unsorted[j];
                unsorted[j] = unsorted[j+1];
                unsorted[j+1] = temp;
            }
        }
    }
}

void masuk_truck(container *list, container *truck) {
    // Push proccess
    truck->banyak_barang = list->banyak_barang;
    truck->berat_muatan = list->berat_muatan;
    truck->muatan = (barang*) malloc(list->banyak_barang * sizeof(barang));
    for (int i = 0 ; i < list->banyak_barang ; i++) truck->muatan[i] = list->muatan[i];
}

barang *masuk_gudang_jawa(container *truck, int partai) {
    barang *head = NULL, *temp_node, *temp;
    
    for(int i = truck[partai].banyak_barang - 1; i >= 0 ; i--) {
        temp_node = (barang*) malloc(sizeof(barang));
        *temp_node = truck[partai].muatan[i];
        gudang_jawa.banyak++;
        gudang_jawa.berat += temp_node->berat;
        temp_node->next = NULL;
        
        if (head == NULL) {
            head = temp_node;
        }
        else {
            temp = head;
            while (temp->next != NULL) temp = temp->next;
            temp->next = temp_node;
        }
    }
    return head;
}

Node *hamilton(int jumlah_node, int matriks_ketetanggaan[][jumlah_node]) {

    int awal = 0, stop, skip, sol_set_tersedia = 0, node_sebelum = -1;
    int node_dalam_stack; // * keperluan print node saja
    Node *list_temp_solution;
    Node *head;
    Node *tail;
    Node *solution_set = (Node*) malloc (sizeof(Node) * jumlah_node);

    // * list_temp_solution ini maksudnya solutionset yang dibuat jadi LinkedList
    list_temp_solution = (Node*) malloc(sizeof(Node));
    list_temp_solution->hubungan_ketetanggan = 0;
    list_temp_solution->kota = awal;
    list_temp_solution->next = NULL;
    list_temp_solution->prev = NULL;

    // * ini inisialisasi ngasi tau bahwa setiap node BELUM penrah divisit
    // * karena nanti pakai backtracking.
    for (int i = 0; i < jumlah_node; i++) {
        list_temp_solution->node_divisit[i] = 0;
    }

    // * circular doubly linkedlist
    head = list_temp_solution;
    tail = list_temp_solution;

    // * stop kalok misalkan dia kembali ke awal dan semua tetangga ada di solution set (success)
    // * atau kembali ke awal dan semua tetangga sudah di visit, tetapi tidak semua ada di solution set (fail)
    stop = 0;
    // * skip = 0 itu artinya kalau ditemuin tetangga yang belum pernah divisit
    skip = 0;
    while (stop == 0) {

        list_temp_solution = head;
        node_dalam_stack = 1;
        // * ini untuk keperuan ngeprint node saja, ngecek berapa jumlah node didalam linkedlist solution set
        while (list_temp_solution->next != NULL) {
            list_temp_solution = list_temp_solution->next;
            node_dalam_stack++;
        }
        // * reset state skip
        skip = 0;
        // * for loop untuk ngecek tetangga apakah dia sudah pernah divsit oleh node yang sedang ditunjuk
        for (int i = 0; i < jumlah_node; i++) {
            // * kalok ketemu tetangga, dia bukan node awal, belum di skip, brarti gass cek
            if (i != tail->kota && matriks_ketetanggaan[tail->kota][i] > 0 && i != awal && skip == 0) {
                list_temp_solution = head;
                // * node_sebelum = 0 itu artinya node yang ditunjuk belum ada di solution set
                node_sebelum = 0;
                while (list_temp_solution->next != NULL) {
                    list_temp_solution = list_temp_solution->next;
                    if (list_temp_solution->kota == i) {
                        node_sebelum = 1;
                        break;
                    }
                }
                if (list_temp_solution->node_divisit[i] == 1) {
                    node_sebelum = 1;
                }
                // ? kenapa make array?
                if (node_sebelum == 0) {
                    list_temp_solution = (Node*) malloc(sizeof(Node));

                    list_temp_solution->hubungan_ketetanggan = matriks_ketetanggaan[tail->kota][i];
                    list_temp_solution->kota = i;
                    list_temp_solution->prev = tail;
                    tail->next = list_temp_solution;
                    tail->node_divisit[i] = 1;
                    list_temp_solution->next = NULL;
                    tail = list_temp_solution;

                    for (int j = 0; j < jumlah_node; j++) {
                        list_temp_solution->node_divisit[j] = 0;
                    }

                    list_temp_solution = head;

                    skip = 1;
                }
                // * ini else if untuk misalkan solusi ditemukan 
                // * kalok yang lagi diperiksa == awal, dan nodeDalam solution set sama dengan jumlah node
            } 
            else if (i == awal && node_dalam_stack == jumlah_node && matriks_ketetanggaan[tail->kota][i] > 0) {
                list_temp_solution = (Node*) malloc(sizeof(Node));

                list_temp_solution->hubungan_ketetanggan = matriks_ketetanggaan[tail->kota][i];
                list_temp_solution->kota = i;
                list_temp_solution->prev = tail;
                tail->next = list_temp_solution;
                list_temp_solution->next = NULL;
                tail = list_temp_solution;

                list_temp_solution = head;
                skip = 1;
                stop = 1;
            }
        }
        // * atau kalok kembali ke awal tetapi solutionset belum sebanyak jumlah kota
        // * atau jalan buntu tetapi belum kembali ke awal
        if (skip == 0) {
            if (tail->prev != NULL) {
                list_temp_solution = tail->prev;
                list_temp_solution->next = NULL;
                
                free(tail);
                tail = list_temp_solution;
                // * ini kalok gagal
            } else {
                printf("\n\tMohon, maaf. Sistem graph tidak dapat menentukan alamat secara otomatis. Silakan pakai otak Anda sendiri\n");
                stop = 1;
                return NULL;
            }
        }
        printf("\n");
    }
    return head;
}

barang *find(barang **list_barang_gudang, char *dicari) {
    if (*list_barang_gudang != NULL) {
        barang *temp = *list_barang_gudang;
        char *temp_char;
        for (int i = 0; dicari[i] ; i++) dicari[i] = tolower(dicari[i]);

        do {
            temp_char = temp->penerima;
            for (int i = 0; temp_char[i] ; i++) temp_char[i] = tolower(temp_char[i]);
            if (strcmp(temp_char, dicari) == 0) return temp;
            
            temp_char = temp->pengirim;
            for (int i = 0; temp_char[i] ; i++) temp_char[i] = tolower(temp_char[i]);
            if (strcmp(temp_char, dicari) == 0) return temp;

            temp_char = temp->alamat;
            for (int i = 0; temp_char[i] ; i++) temp_char[i] = tolower(temp_char[i]);
            if (strcmp(temp_char, dicari) == 0) return temp;
            
            temp = temp->next;
        } while (temp != NULL);
        return NULL;
    }
    else{
        puts("\n\t===============");
        puts("\t|Gudang kosong|");
        puts("\t===============");

    }

}