#ifndef __SUPPORT_FILE_
    #define __SUPPORT_FILE_
    #include "adt.h"

    void si_kang_paket();
    void tahan();
    void init_table();
    void init_acc();
    void add_account(user temp_data_account, int region);
    void remove_account(user temp_data_account, int region);
    unsigned int hash_func(char *username);
    int check_login(char *username, char *password, int region);
    char* get_pwd();
    void clear();
    barang *initialize_node_barang();
    void insert(barang **ptr_head);
    void lihat_gudang(barang *ptr_head);
    void list_akan_dikirim(barang **list_barang, container *array, int region);
    void sort(barang *unsorted, int banyak_barang);
    void masuk_truck(container *list, container *truck);
    barang *masuk_gudang_jawa(container *truck, int partai);
    Node *hamilton(int jumlah_node, int matriks_ketetanggaan[][jumlah_node]);
    barang *find(barang **list_barang_gudang, char *dicari);
#endif