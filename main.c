#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#ifdef _WIN32
    #include <conio.h>
    #define BKSPC 8
    #define ENTER 13
#elif __linux__
    #include <unistd.h>
#endif

#define TRUCK_SIZE 100 // Dalam Kg
#define MAX_A_DAY 300 // Dalam Kg
#define MAX_ACCOUNT 13

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

user account[2][MAX_ACCOUNT];
gudang gudang_bali = {.banyak = 0, .berat = 0}, gudang_jawa = {.banyak = 0, .berat = 0};

void init_table() {
    for (int i = 0 ; i < MAX_ACCOUNT ; i++) {
        account[0][i].apakah_terisi = 0;
        account[1][i].apakah_terisi = 0;
    }
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
                puts("Akun berhasil dibuat!");
                return ;
            }
        } while (temp_geser != index);
        puts("Akun tidak berhasil dibuat!");
        puts("Banyak akun sudah melampaui batas");
        return ;
    }
    strcpy(account[region][index].username, temp_data_account.username);
    strcpy(account[region][index].password, temp_data_account.password);
    account[region][index].apakah_terisi = 1;
    puts("Akun berhasil dibuat!");
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

    puts("Data pengirim & penerima");
    printf("Masukkan nama pengirim : ");
    scanf("%[^\n]", temp_input->pengirim);
    getchar();
    printf("Masukkan nama penerima : ");
    scanf("%[^\n]", temp_input->penerima);
    getchar();
    printf("Masukkan alamat penerima : ");
    scanf("%[^\n]", temp_input->alamat);
    getchar();
    printf("Masukkan nomor telepon penerima : ");
    scanf("%[^\n]", temp_input->no_telp);
    getchar();

    puts("Data barang");
    puts("Masukan berat barang (dalam kg): ");
    scanf("%u", &(temp_input->berat));
    getchar();
    puts("Masukan volume barang (dalam m^3): ");
    scanf("%u", &(temp_input->volume));
    getchar();

    gudang_bali.banyak++;
    gudang_bali.berat += temp_input->berat;

    if (gudang_bali.berat >= TRUCK_SIZE) puts("Berat sudah cukup atau melebihi");

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
        puts("Sudah melebihi kuota dalam sehari");
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
        puts("=====================================================");
        do
        {
            printf("Penerima : %s\n", temp->penerima);
            printf("Pengirim : %s\n", temp->pengirim);
            printf("Alamat   : %s\n", temp->alamat);
            printf("No telp  : %s\n", temp->no_telp);
            printf("Berat    : %u\n", temp->berat);
            printf("Volume   : %u\n", temp->volume);
            puts("=====================================================");
            temp = temp->next;
        } while (temp != NULL);        
    }
    else{
        printf("NULL");
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
                printf("\nMohon, maaf. Sistem graph tidak dapat menentukan alamat secara otomatis. Silakan pakai otak Anda sendiri\n");
                stop = 1;
                return NULL;
            }
        }
        printf("\n");
    }
    return head;
}

int main() {
    barang *list_barang_gudang_bali = NULL, *list_barang_gudang_jawa = NULL;
    int counter = 0, partai_bali = 0, partai_jawa = 0, menu;
    int banyak_barang_truck = 0, berat_barang_truck = 0, kembali;
    int partai_kurir = 0;
    container truck[3], list_kirim = {.berat_muatan = 0, .banyak_barang = 0};
    container kurir = {.berat_muatan = 0, .banyak_barang = 0};
    char user_username[50], *user_password, konfirmasi;

    init_table();
    for (int i = 0 ; i < 3 ; i++) { 
        truck[i].berat_muatan = 0; truck[i].banyak_barang = 0;
    }
    while (1) {
        puts("==================");
        puts(" 1. Gudang Bali ");
        puts(" 2. Gudang Jawa ");
        puts(" 3. Halaman Admin ");
        puts(" 4. Exit");
        puts("==================");
        printf("Input : ");
        scanf("%d", &menu);
        getchar();
        // Menu 1
        if (menu == 1) {
            // Login Feature
            // while(1) {
            //     puts("Selamat datang di Gudang Bali");
            //     printf("1. Login\n2. Kembali\n");
            //     printf("input : ");
            //     scanf("%d", &menu);
            //     getchar();
            //     if (menu == 1) {
            //         puts("Silakan login");
            //         puts("\nMasukan user dan password");
            //         printf("Username : ");
            //         scanf("%s", user_username);
            //         getchar();
            //         printf("Password : ");
            //         user_password = get_pwd();
            //         if (check_login(user_username, user_password, 0) == 1) {
            //             puts("Berhasil login!");
            //             puts("Tekan enter untuk melanjutkan");
            //             getchar();
            //             break;
            //         }
            //         else {
            //             puts("\nUsername atau password salah");
            //             puts("Tekan enter untuk kembali");
            //             getchar();
            //         }
            //     }
            //     else if (menu == 2) {
            //         kembali = 1;
            //         break;
            //     }
            // }
            // if (kembali == 1) continue;

            clear();
            while(1) {
                puts("MENU");
                puts("1. Input barang ke gudang");
                puts("2. Memasukan barang ke truck");
                puts("3. Melihat isi gudang");
                puts("4. Kembali");
                scanf("%d", &menu);
                getchar();
                if (menu == 1) {
                    puts("Masukan keterangan barang");
                    counter == 0 ? list_barang_gudang_bali = initialize_node_barang() : insert(&list_barang_gudang_bali);
                    counter++;
                }
                else if (menu == 2) {
                    list_akan_dikirim(&list_barang_gudang_bali, &list_kirim, 0);
                    sort(list_kirim.muatan, list_kirim.banyak_barang);
                    masuk_truck(&list_kirim, &truck[partai_bali]);
                    puts("Barang di dalam truck");
                    puts("=====================================================");
                    for(int i = 0 ; i < truck[partai_bali].banyak_barang ; i++) {
                        printf("Alamat   : %s\n", truck[partai_bali].muatan[i].alamat);
                        printf("Penerima : %s\n", truck[partai_bali].muatan[i].penerima);
                        printf("Pengirim : %s\n", truck[partai_bali].muatan[i].pengirim);
                        printf("No telp  : %s\n", truck[partai_bali].muatan[i].no_telp);
                        printf("Berat    : %u\n", truck[partai_bali].muatan[i].berat);
                        printf("Volume   : %u\n", truck[partai_bali].muatan[i].volume);
                        puts("=====================================================");
                    }
                    puts("Truck akan langsung dikirim");
                    partai_bali++;
                    counter = 0;
                }
                else if (menu == 3) {
                    lihat_gudang(list_barang_gudang_bali);
                }
                else if (menu == 4) {
                    break;
                }
            }
        }
        // Menu 2
        else if (menu == 2) {
            // Login Feature
            // while(1) {
            //     puts("Selamat datang di Gudang Jawa");
            //     printf("1. Login\n2. Kembali\n");
            //     printf("input : ");
            //     scanf("%d", &menu);
            //     getchar();
            //     if (menu == 1) {
            //         puts("Silakan login");
            //         puts("\nMasukan user dan password");
            //         printf("Username : ");
            //         scanf("%s", user_username);
            //         getchar();
            //         printf("Password : ");
            //         user_password = get_pwd();
            //         if (check_login(user_username, user_password, 1) == 1) {
            //             puts("Berhasil login!");
            //             puts("Tekan enter untuk melanjutkan");
            //             getchar();
            //             break;
            //         }
            //         else {
            //             puts("\nUsername atau password salah");
            //             puts("Tekan enter untuk kembali");
            //             getchar();
            //         }
            //     }
            //     else if (menu == 2) {
            //         kembali = 1;
            //         break;
            //     }
            // }
            // if (kembali == 1) continue;
            //
            clear();
            while(1) {
                puts("MENU");
                puts("1. Konfirmasi kedatangan truck");
                puts("2. Kirim pesanan ke pelanggan");
                puts("3. Melihat isi gudang");
                puts("4. Kembali");
                scanf("%d", &menu);
                getchar();

                if (menu == 1) {
                    printf("Apakah truck partai %d sudah datang?\nInput (Y/y/n) : ", partai_jawa + 1);
                    scanf("%c", &konfirmasi);
                    getchar();
                    if (konfirmasi == 'y' || konfirmasi == 'Y') {
                        printf("Tekan enter untuk memasukan barang dari truck ke gudang");
                        getchar();
                        list_barang_gudang_jawa = masuk_gudang_jawa(truck, partai_jawa);
                        partai_jawa++;
                    }
                    else {
                        continue;
                    }
                }
                else if (menu == 2) {
                    if (list_barang_gudang_jawa != NULL) {
                        list_akan_dikirim(&list_barang_gudang_jawa, &kurir, 1);
                        char indexing_alamat[kurir.banyak_barang + 1][50];
                        for (int i = 0 ; i < kurir.banyak_barang + 1 ; i++) {
                            if (i == 0) {
                                strcpy(indexing_alamat[i], "Kantor si Kang Paket");
                                continue;
                            }
                            strcpy(indexing_alamat[i], kurir.muatan[i-1].penerima);
                        }
                        int matriks_ketetanggan[kurir.banyak_barang + 1][kurir.banyak_barang + 1];
                        int hubungan;
                        for (int i = 0 ; i < kurir.banyak_barang + 1; i++) {
                            printf("Hubungan alamat %s\n", indexing_alamat[i]);
                            printf("Masukan 1 apabila terdapat hubungan, 0 jika tidak\n");
                            for (int j = i ; j < kurir.banyak_barang + 1; j++) {
                                if (i == j) {
                                    matriks_ketetanggan[i][j] = 0;
                                    continue;
                                }
                                printf("\tHubungan alamat %s dengan alamat %s", indexing_alamat[i], indexing_alamat[j]);
                                scanf("%d", &hubungan);
                                getchar();
                                matriks_ketetanggan[i][j] = hubungan;
                                matriks_ketetanggan[j][i] = hubungan;
                            }
                        }
                        Node *solution = hamilton(kurir.banyak_barang + 1, matriks_ketetanggan);
                        if (solution != NULL) {
                            while(solution->next != NULL) {
                                printf("%s", indexing_alamat[solution->kota]);
                                solution = solution->next;
                                if (solution != NULL) printf(" -> ");
                            }
                            printf("%s", indexing_alamat[solution->kota]);
                        }
                        else {

                        }
                        printf("\n");
                    }

                }
                else if (menu == 3) {
                    puts("MENU");
                    puts("1. Lihat gudang keseluruhan");
                    puts("2. Cari barang");
                    puts("3. Kembali");
                    printf("Input : ");
                    scanf("%d", &menu);
                    getchar();
                    
                    if (menu == 1) {
                        lihat_gudang(list_barang_gudang_jawa);
                        printf("\nBanyak barang = %d", gudang_jawa.banyak);
                    }
                    else if (menu == 2) {

                    }
                    else if (menu == 3) {
                        continue;
                    }
                }
                else if (menu == 4) {
                    break;
                }
            }
        }
        // Menu 3
        else if (menu == 3) {
            clear();
            puts("HALAMAN ADMIN");
            char user_admin[6], *pwd_admin;
            user temp;
            int menu;
            do {
                printf("Username : ");
                scanf("%s", user_admin);
                printf("Password : ");
                pwd_admin = get_pwd();
                if (strcmp(user_admin, "Admin") == 0 && strcmp(pwd_admin, "admin") == 0) {
                    puts("\nSelamat datang Admin");
                    break;
                }
                else puts("Username atau Password yang anda masukan salah");
                clear();
            } while(1);
            while (1) {
                puts("MENU");
                printf("1. Tambah akun\n");
                printf("2. Hapus akun\n");
                printf("3. Kembali\n");
                printf("input : ");
                scanf("%d", &menu);
                if (menu == 1) {
                    puts("MENU");
                    printf("1. Gudang Bali\n");
                    printf("2. Gudang Jawa\n");
                    printf("input : ");
                    scanf("%d", &menu);
                    if (menu == 1) {
                        puts("Masukan user dan password yang diinginkan");
                        printf("Username : ");
                        scanf("%s", temp.username);
                        printf("Password : ");
                        scanf("%s", temp.password);
                        add_account(temp, 0);
                    }
                    else if (menu == 2) {
                        puts("Masukan user dan password yang diinginkan");
                        printf("Username : ");
                        scanf("%s", temp.username);
                        printf("Password : ");
                        scanf("%s", temp.password);
                        add_account(temp, 1);
                    }
                }
                else if (menu == 3) {
                    break;
                }
            }
        }
        else if (menu == 4) {
            return 0;
        }
    }
}