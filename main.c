#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "lib/support_file.h"

int main() {
    barang *list_barang_gudang_bali = NULL, *list_barang_gudang_jawa = NULL;
    int counter = 0, partai_bali = 0, partai_jawa = 0, menu;
    int banyak_barang_truck = 0, berat_barang_truck = 0, kembali;
    int partai_kurir = 0;
    container truck[3], list_kirim = {.berat_muatan = 0, .banyak_barang = 0};
    container kurir = {.berat_muatan = 0, .banyak_barang = 0};
    char user_username[50], *user_password, konfirmasi;

    init_table();
    init_acc();
    clear();

    puts("\n====================================================");
    puts("=                  Final Project                   =");
    puts("====================================================");
    puts("=                 Anggota Kelompok                 =");
    puts("====================================================");
    puts("=                Nama                 =     NIM    =");
    puts("====================================================");
    puts("= Kompiang Gede Sukadharma            = 2008561083 =");
    puts("= Ida Ayu Taria Putri Mahadewi        = 2008561081 =");
    puts("= Wahyu Vidiadivani                   = 2008561082 =");
    puts("= I Ketut Teguh Wibawa Lessmana ...   = 2008561084 =");
    puts("====================================================");
    getchar();

    for (int i = 0 ; i < 3 ; i++) { 
        truck[i].berat_muatan = 0; truck[i].banyak_barang = 0;
    }
    while (1) {
        si_kang_paket();
        puts("\t\t==================");
        puts("\t\t    MENU UTAMA   ");
        puts("\t\t==================");
        puts("\t\t 1. Gudang Bali ");
        puts("\t\t 2. Gudang Jawa ");
        puts("\t\t 3. Halaman Admin ");
        puts("\t\t 0. Exit");
        puts("\t\t==================");
        printf("\t\tInput : ");
        scanf("%d", &menu);
        getchar();
        // Menu 1
        if (menu == 1) {
            // Login Feature

            while(1) {
                si_kang_paket();
                puts("\t\t===================");
                puts("\t\t     MENU UTAMA   ");
                puts("\t\t    GUDANG  BALI   ");
                puts("\t\t===================");
                puts("\t\t  Selamat datang");
                puts("\t\t  di Gudang Bali");
                printf("\t\t  1. Login\n\t\t  0. Kembali\n");
                puts("\t\t===================");
                printf("\t\t  Input : ");
                scanf("%d", &menu);
                getchar();
                if (menu == 1) {
                    si_kang_paket();
                    puts("\t\t===================");
                    puts("\t\t   Silakan login");
                    puts("\t\t===================");
                    puts("\n\t    Masukan user dan password");
                    printf("\t    Username : ");
                    scanf("%s", user_username);
                    getchar();
                    printf("\t    Password : ");
                    user_password = get_pwd();
                    if (check_login(user_username, user_password, 0) == 1) {
                        puts("\n\n\t    Berhasil login!");
                        puts("\t    Tekan enter untuk melanjutkan");
                        getchar();
                        break;
                    }
                    else {
                        puts("\n\n\t    Username atau password salah");
                        puts("\t    Tekan enter untuk kembali");
                        getchar();
                    }
                }
                else if (menu == 0) {
                    kembali = 1;
                    break;
                }
                else continue;
            }

            if (kembali == 1) continue;

            clear();
            while(1) {
                if (partai_bali == 3) {
                    si_kang_paket();
                    puts("\t\t=========");
                    puts("\t\t| Tutup |");
                    puts("\t\t=========");
                    tahan();
                    break;
                } 
                si_kang_paket();
                puts("\t==================================");
                puts("\t              MENU");
                puts("\t==================================");
                puts("\t1. Input barang ke gudang");
                puts("\t2. Memasukan barang ke truck");
                puts("\t3. Melihat isi gudang");
                puts("\t0. Kembali");
                puts("\t==================================");
                printf("\tInput : ");
                scanf("%d", &menu);
                getchar();
                if (menu == 1) {
                    si_kang_paket();
                    puts("\t    Masukan keterangan barang\n");
                    counter == 0 ? list_barang_gudang_bali = initialize_node_barang() : insert(&list_barang_gudang_bali);
                    counter++;
                    tahan();
                }
                else if (menu == 2) {
                    si_kang_paket();
                    list_akan_dikirim(&list_barang_gudang_bali, &list_kirim, 0);
                    sort(list_kirim.muatan, list_kirim.banyak_barang);
                    masuk_truck(&list_kirim, &truck[partai_bali]);
                    puts("\tBarang di dalam truck");
                    puts("\t=====================================================");
                    for(int i = 0 ; i < truck[partai_bali].banyak_barang ; i++) {
                        printf("\tAlamat   : %s\n", truck[partai_bali].muatan[i].alamat);
                        printf("\tPenerima : %s\n", truck[partai_bali].muatan[i].penerima);
                        printf("\tPengirim : %s\n", truck[partai_bali].muatan[i].pengirim);
                        printf("\tNo telp  : %s\n", truck[partai_bali].muatan[i].no_telp);
                        printf("\tBerat    : %u\n", truck[partai_bali].muatan[i].berat);
                        printf("\tVolume   : %u\n", truck[partai_bali].muatan[i].volume);
                        puts("\t=====================================================");
                    }
                    puts("\n\tTRUCK AKAN LANGSUNG DIKIRIM");
                    partai_bali++;
                    counter = 0;
                    tahan();
                }
                else if (menu == 3) {
                    while(1) {
                        si_kang_paket();
                        puts("\t==================================");
                        puts("\t              MENU");
                        puts("\t==================================");
                        puts("\t1. Lihat gudang keseluruhan");
                        puts("\t2. Cari barang");
                        puts("\t0. Kembali");
                        puts("\t==================================");
                        printf("\tInput : ");
                        scanf("%d", &menu);
                        getchar();
                        
                        si_kang_paket();
                        if (menu == 1) {
                            lihat_gudang(list_barang_gudang_bali);
                        }
                        else if (menu == 2) {
                            // Find feature
                            char string_dicari[50];
                            barang *barang_dicari;

                            printf("\tMasukan nama penerima/pengirim/alamat\n");
                            printf("\tinput : ");
                            scanf("%[^\n]", string_dicari);
                            getchar();
                            if ((barang_dicari = find(&list_barang_gudang_bali, string_dicari)) != NULL) {
                                puts("\n\t=====================================================");
                                printf("\tPenerima : %s\n", barang_dicari->penerima);
                                printf("\tPengirim : %s\n", barang_dicari->pengirim);
                                printf("\tAlamat   : %s\n", barang_dicari->alamat);
                                printf("\tNo telp  : %s\n", barang_dicari->no_telp);
                                printf("\tBerat    : %u\n", barang_dicari->berat);
                                printf("\tVolume   : %u\n", barang_dicari->volume);
                                puts("\t=====================================================");
                            }
                            else  puts("\tBarang yang dicari tidak ada");
                        }
                        else if (menu == 0) break;
                        else {
                            puts("\tInput yang benar");
                            continue;
                        };
                        tahan();
                    }
                }
                else if (menu == 0) break;
                else continue;
            }
        }
        // Menu 2
        else if (menu == 2) {
            // Login Feature
            while(1) {
                 si_kang_paket();
                    puts("\t\t===================");
                    puts("\t\t     MENU UTAMA   ");
                    puts("\t\t    GUDANG  JAWA   ");
                    puts("\t\t===================");
                    puts("\t\t  Selamat datang");
                    puts("\t\t  di Gudang Jawa");
                    printf("\t\t  1. Login\n\t\t  0. Kembali\n");
                    puts("\t\t===================");
                    printf("\t\t  Input : ");
                    scanf("%d", &menu);
                    getchar();
                    if (menu == 1) {
                        si_kang_paket();
                        puts("\t\t===================");
                        puts("\t\t   Silakan login");
                        puts("\t\t===================");
                        puts("\n\t    Masukan user dan password");
                        printf("\t    Username : ");
                        scanf("%s", user_username);
                        getchar();
                        printf("\t    Password : ");
                        user_password = get_pwd();
                        if (check_login(user_username, user_password, 1) == 1) {
                            puts("\n\n\t    Berhasil login!");
                            puts("\t    Tekan enter untuk melanjutkan");
                            getchar();
                            break;
                        }
                        else {
                            puts("\n\n\t    Username atau password salah");
                            puts("\t    Tekan enter untuk kembali");
                            getchar();
                        }
                    }
                    else if (menu == 0) {
                        kembali = 1;
                        break;
                    }
                    else continue;
            }
            if (kembali == 1) continue;
            
            clear();
            while(1) {
                if (partai_jawa == 3) {
                    si_kang_paket();
                    puts("\t\t=========");
                    puts("\t\t| Tutup |");
                    puts("\t\t=========");
                    tahan();
                    break;
                } 
                si_kang_paket();
                puts("\t==================================");
                puts("\t              MENU");
                puts("\t==================================");
                puts("\t1. Konfirmasi kedatangan truck");
                puts("\t2. Kirim pesanan ke pelanggan");
                puts("\t3. Melihat isi gudang");
                puts("\t0. Kembali");
                puts("\t==================================");
                printf("\tInput : ");
                scanf("%d", &menu);
                getchar();

                if (menu == 1) {
                    si_kang_paket();
                    printf("\tApakah truck partai %d sudah datang?\n\tInput (Y/y/n) : ", partai_jawa + 1);
                    scanf("%c", &konfirmasi);
                    getchar();
                    if (konfirmasi == 'y' || konfirmasi == 'Y') {
                        printf("\tTekan enter untuk memasukan barang dari truck ke gudang");
                        getchar();
                        list_barang_gudang_jawa = masuk_gudang_jawa(truck, partai_jawa);
                        partai_jawa++;
                    }
                    else {
                        continue;
                    }
                }
                else if (menu == 2) {
                    si_kang_paket();
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
                            printf("\tHubungan alamat %s\n", indexing_alamat[i]);
                            printf("\tMasukan 1 apabila terdapat hubungan, 0 jika tidak\n");
                            for (int j = i ; j < kurir.banyak_barang + 1; j++) {
                                if (i == j) {
                                    matriks_ketetanggan[i][j] = 0;
                                    continue;
                                }
                                printf("\t\tHubungan alamat %s dengan alamat %s : ", indexing_alamat[i], indexing_alamat[j]);
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
                        printf("\n");
                        tahan();
                    }

                }
                else if (menu == 3) {
                    si_kang_paket();
                    puts("\t==================================");
                    puts("\t              MENU");
                    puts("\t==================================");
                    puts("\t1. Lihat gudang keseluruhan");
                    puts("\t2. Cari barang");
                    puts("\t3. Kembali");
                    puts("\t==================================");
                    printf("\tInput : ");
                    scanf("%d", &menu);
                    getchar();
                    
                    if (menu == 1) {
                        lihat_gudang(list_barang_gudang_jawa);
                        tahan();
                    }
                    else if (menu == 2) {
                        // Find feature
                        char string_dicari[50];
                        barang *barang_dicari;

                        printf("\tMasukan nama penerima/pengirim/alamat\n");
                        printf("\tinput : ");
                        scanf("%[^\n]", string_dicari);
                        getchar();
                        if ((barang_dicari = find(&list_barang_gudang_jawa, string_dicari)) != NULL) {
                            puts("\t=====================================================");
                            printf("\tPenerima : %s\n", barang_dicari->penerima);
                            printf("\tPengirim : %s\n", barang_dicari->pengirim);
                            printf("\tAlamat   : %s\n", barang_dicari->alamat);
                            printf("\tNo telp  : %s\n", barang_dicari->no_telp);
                            printf("\tBerat    : %u\n", barang_dicari->berat);
                            printf("\tVolume   : %u\n", barang_dicari->volume);
                            puts("\t=====================================================");
                        }
                        else {
                            puts("\tBarang yang dicari tidak ada");
                        }
                        tahan();
                    }
                    else if (menu == 3) {
                        continue;
                    }
                }
                else if (menu == 0) {
                    break;
                }
            }
        }
        // Menu 3
        else if (menu == 3) {
            si_kang_paket();
            puts("\t\t===================");
            puts("\t\t     MENU UTAMA   ");
            puts("\t\t   HALAMAN ADMIN   ");
            puts("\t\t===================");
            char user_admin[6], *pwd_admin;
            user temp;
            int menu;
            do {
                printf("\t\tUsername : ");
                scanf("%s", user_admin);
                printf("\t\tPassword : ");
                pwd_admin = get_pwd();
                if (strcmp(user_admin, "Admin") == 0 && strcmp(pwd_admin, "admin") == 0) {
                    puts("\n\t\tSelamat datang Admin");
                    break;
                }
                else puts("\t\tUsername atau Password yang anda masukan salah");
                clear();
            } while(1);
            while (1) {
                si_kang_paket();
                puts("\t==================================");
                puts("\t              MENU");
                puts("\t==================================");
                puts("\t1. Tambah akun");
                puts("\t2. Hapus akun");
                puts("\t0. Kembali");
                puts("\t==================================");
                printf("\tInput : ");
                scanf("%d", &menu);
                if (menu == 1) {
                    while (1) {
                        si_kang_paket();
                        puts("\t==================================");
                        puts("\t         MENU TAMBAH AKUN         ");
                        puts("\t==================================");
                        puts("\t1. Gudang Bali");
                        puts("\t2. Gudang Jawa");
                        puts("\t0. Kembali");
                        puts("\t==================================");
                        printf("\tInput : ");
                        scanf("%d", &menu);
                        if (menu == 1) {
                            puts("\tMasukan user dan password yang diinginkan");
                            printf("\tUsername : ");
                            scanf("%s", temp.username);
                            printf("\tPassword : ");
                            scanf("%s", temp.password);
                            add_account(temp, 0);
                            tahan();
                        }
                        else if (menu == 2) {
                            puts("\tMasukan user dan password yang diinginkan");
                            printf("\tUsername : ");
                            scanf("%s", temp.username);
                            printf("\tPassword : ");
                            scanf("%s", temp.password);
                            add_account(temp, 1);
                            tahan();
                        }
                        else if (menu == 0) break;
                    }
                }
                else if (menu == 2) {
                    while (1) {
                        si_kang_paket();
                        puts("\t==================================");
                        puts("\t          MENU HAPUS AKUN         ");
                        puts("\t==================================");
                        puts("\t1. Gudang Bali");
                        puts("\t2. Gudang Jawa");
                        puts("\t0. Kembali");
                        puts("\t==================================");
                        printf("\tInput : ");
                        scanf("%d", &menu);
                        if (menu == 1) {
                            puts("\tMasukan user dan password yang ingin dihapus");
                            printf("\tUsername : ");
                            scanf("%s", temp.username);
                            printf("\tPassword : ");
                            scanf("%s", temp.password);
                            remove_account(temp,0);
                            tahan();
                        }
                        else if (menu == 2) {
                            puts("\tMasukan user dan password yang ingin dihapus");
                            printf("\tUsername : ");
                            scanf("%s", temp.username);
                            printf("\tPassword : ");
                            scanf("%s", temp.password);
                            remove_account(temp, 1);
                            tahan();
                        }
                        else if (menu == 0) break;
                    }
                }
                else if (menu == 0) {
                    break;
                }
            }
        }
        else if (menu == 0) {
            return 0;
        }
    }
}