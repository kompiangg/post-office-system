#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

#ifdef _WIN32
    #include <conio.h>
    #define BKSPC 8
    #define ENTER 13
#endif

typedef struct user{
    char username[25];
    char password[25];
} user;

user account[2][13];

unsigned int hash_func(char *username) {
    unsigned int result = 0;
    for (int i = 0 ; username[i] ; i++) result += username[i];
    for (int i = 0 ; username[i] ; i+=2) result *= username[i];
    return result % 13;
}

void hash_proc(user temp_data_account, int region) {
    int index = hash_func(temp_data_account.username);

    if (region == 1) {
        strcpy(account[0][index].username, temp_data_account.username);
        strcpy(account[0][index].password, temp_data_account.password);
    }
    else {
        strcpy(account[1][index].username, temp_data_account.username);
        strcpy(account[1][index].password, temp_data_account.password);
    }
}

char* get_pass(){
    char *pwd = (char*) malloc(25);
    #ifdef _WIN32
        char ch;
        int indeks = 0;
        while (1) {
            ch = getch();

            if (ch == ENTER) {
                pwd[indeks] = '\0';
                break;
            }
            else if (ch == BKSPC) {
                printf("\b \b");
            }
            else {
                pwd[indeks++] = ch;
                printf("*");
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

int main() {
    // puts("================");
    // puts(" 1. Gudang Bali ");
    // puts(" 2. Gudang Jawa ");
    // puts("================");
    
    // DONT TOUCH!!!!!
    // puts("MENU ADMIN");
    // char user_admin[6], *pwd_admin;
    // do {
    //     printf("Username : ");
    //     scanf("%s", user_admin);
    //     printf("Password : ");
    //     pwd_admin = get_pass();
    //     if (!(strcmp(user_admin, "Admin") && strcmp(pwd_admin, "admin"))) {
    //         puts("\nSelamat datang Admin");
    //         break;
    //     }
    //     puts("Username atau Password yang anda masukan salah");
    // } while(1);

    return 0;
}