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

typedef struct user {
    char username[25], password[25];
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

user account[2][13];
gudang gudang_bali = {.banyak = 0, .berat = 0};

/*Kita akan menggunakan akun*/
// unsigned int hash_func(char *username) {
//     unsigned int result = 0;
//     for (int i = 0 ; username[i] ; i++) result += username[i];
//     for (int i = 0 ; username[i] ; i+=2) result *= username[i];
//     return result % 13;
// }

// void hash_proc(user temp_data_account, int region) {
//     int index = hash_func(temp_data_account.username);

//     if (region == 1) {
//         strcpy(account[0][index].username, temp_data_account.username);
//         strcpy(account[0][index].password, temp_data_account.password);
//     }
//     else {
//         strcpy(account[1][index].username, temp_data_account.username);
//         strcpy(account[1][index].password, temp_data_account.password);
//     }
// }

char* get_pwd(){
    char *pwd = (char*) malloc(25);
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

barang *buffer_barang() {
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

    will_insert = buffer_barang();
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
            printf("Alamat   : %s\n", temp->alamat);
            printf("Penerima : %s\n", temp->penerima);
            printf("Pengirim : %s\n", temp->pengirim);
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

void list_akan_dikirim(barang **list_barang, container *truck){
    //dequeue
    barang *temp = *list_barang;
    while((truck->berat_muatan += temp->berat) <= TRUCK_SIZE) {
        truck->banyak_barang++;
        gudang_bali.banyak--;
        gudang_bali.berat -= temp->berat;
        if(temp->next != NULL) temp = temp->next;
        else break;
    }
    if (truck->berat_muatan > TRUCK_SIZE) {
        truck->berat_muatan -= temp->berat;
        truck->banyak_barang--;
        gudang_bali.banyak++;
        gudang_bali.berat += temp->berat;
    }
    truck->muatan = (barang*) malloc(truck->banyak_barang * sizeof(barang));
    for (int i = 0 ; i < truck->banyak_barang ; i++) {
        truck->muatan[i] = **list_barang;
        *list_barang = (*list_barang)->next;
    }
}

void sort(barang *unsorted, int banyak_barang) {
    printf("here2");
    int banyak_unsorted = banyak_barang;
    barang temp;
    for (int i = banyak_unsorted - 1; i > 0;i--) {
        for(int j = 0 ; j < i ; j++) {
            if (unsorted[j].volume > unsorted[j + 1].volume) {
                temp = unsorted[j];
                unsorted[j] = unsorted[j+1];
                unsorted[j+1] = temp;
            }
        }
    }
}

void masuk_truck(container *list, container *truck) {
    truck->banyak_barang = list->banyak_barang;
    truck->berat_muatan = list->berat_muatan;
    truck->muatan = (barang*) malloc(list->banyak_barang * sizeof(barang));
    for (int i = 0 ; i < list->banyak_barang ; i++) truck->muatan[i] = list->muatan[i];
}

int main() {
    barang *list_barang_gudang = NULL, *temp;
    int counter = 0, partai_bali = 0, partai_jawa = 0, menu;
    int banyak_barang_truck = 0, berat_barang_truck = 0;
    container truck[3], list_kirim = {.berat_muatan = 0, .banyak_barang = 0};

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
        if (menu == 1) {
            puts("Selamat datang di Gudang Bali");
            // puts("Silakan login");
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
                    counter == 0 ? list_barang_gudang = buffer_barang() : insert(&list_barang_gudang);
                    counter++;
                }
                else if (menu == 2) {
                    list_akan_dikirim(&list_barang_gudang, &list_kirim);
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
                }
                else if (menu == 3) {
                    lihat_gudang(list_barang_gudang);
                }
                else if (menu == 4) {
                    break;
                }
            }
        }
        else if (menu == 2) {
            
        }
        else if (menu == 3) {
            // DONT TOUCH!!!!!
            // ITS WORK
            clear();
            puts("HALAMAN ADMIN");
            char user_admin[6], *pwd_admin;
            do {
                printf("Username : ");
                scanf("%s", user_admin);
                printf("Password : ");
                pwd_admin = get_pwd();
                if (!(strcmp(user_admin, "Admin") && strcmp(pwd_admin, "admin"))) {
                    puts("\nSelamat datang Admin");
                    break;
                }
                puts("Username atau Password yang anda masukan salah");
                clear();
            } while(1);
        }
        else if (menu == 4) {
            return 0;
        }
    }
}