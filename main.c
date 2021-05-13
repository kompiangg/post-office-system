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

typedef struct user {
    char username[25], password[25];
} user;

typedef struct gudang {
    int berat, banyak;
} gudang;

typedef struct barang {
    int berat, volume;
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
    printf("Masukkan nomor telepon penerima : ");
    scanf("%[^\n]", temp_input->no_telp);
    getchar();

    puts("Data barang");
    puts("Masukan berat barang (dalam kg): ");
    scanf("%d", &(temp_input->berat));
    getchar();
    puts("Masukan volume barang (dalam m^3): ");
    scanf("%d", &(temp_input->volume));
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

int main() {
    char menu;
    barang *list_barang;
    int counter = 0;
    container truck[3];

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
                puts("Apakah terdapat pelanggan (y jika ada)? ");
                if (getchar() == 'y') {
                    getchar();
                    puts("Masukan keterangan barang");
                    counter == 0 ? list_barang = buffer_barang() : insert(&list_barang);
                }
                counter++;

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