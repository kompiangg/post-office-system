#include <stdio.h>
#include <stdlib.h>

#define MAX_INTEGER 2147483647

int jmlNode = 6, jmlEdgeMurni; jmlEdgeSangatMurni;


// int mTetangga[100][100]; //comment baris ini jika ingin menggunakan matriks yang sudah ditentukan


// List matriks yang sudah kami siapkan jika Ibu ingin memeriksa program kami dengan cepat (dapat digunakan)
// Untuk menggunakan matriks yang sudah kami siapkan, mohon lakukan hal berikut:
// 1. Comment mTetangga[][] pada baris 8
// 2. Hilangkan Comment pada matriks yang ingin ibu gunakan
// 3. Comment seluruh baris yang kami beri deskripsi "comment baris ini jika ingin menggunakan matriks yang sudah ditentukan"
        //dapat dijumpai pada baris 762, 764, dan 765 

// Matriks dengan 7 Node, dan setiap Node memiliki derajat genap (untuk algoritma Chinese Postman Problem)
// int mTetangga[7][7] = {
//     {0, 1, 0, 1, 0, 0, 0},
//     {1, 0, 1, 0, 0, 0, 0},
//     {0, 1, 0, 1, 1, 1, 0},
//     {1, 0, 1, 0, 0, 0, 0},
//     {0, 0, 1, 0, 0, 0, 1},
//     {0, 0, 1, 0, 0, 0, 1},
//     {0, 0, 0, 0, 1, 1, 0}
// };

// Matriks dengan 6 Node, dibuat sedemikian rupa agar backtracking terjadi dalam proses Traveling Salesman Problem
int mTetangga[6][6] = {
    {0, 1, 1, 0, 0, 0},
    {1, 0, 0, 1, 1, 0},
    {1, 0, 0, 1, 0, 0},
    {0, 1, 1, 0, 0, 1},
    {0, 1, 0, 0, 0, 1},
    {0, 0, 0, 1, 1, 0}
};

//Matriks dengan 9 Node, dibuat sedimikian rupa
// int mTetangga[9][9] = {
//     {0, 4, 0, 0, 0, 0, 0, 8, 0}, 
//     {4, 0, 8, 0, 0, 0, 0, 11, 0}, 
//     {0, 8, 0, 7, 0, 4, 0, 0, 2},
//     {0, 0, 7, 0, 9, 14, 0, 0, 0},
//     {0, 0, 0, 9, 0, 10, 0, 0, 0},
//     {0, 0, 4, 14, 10, 0, 2, 0, 0},
//     {0, 0, 0, 0, 0, 2, 0, 1, 6},
//     {8, 11, 0, 0, 0, 0, 1, 0, 7},
//     {0, 0, 2, 0, 0, 0, 6, 7, 0}
// };

void cleanScreen(int);
void konfirmasiLanjut();

void shortestPath() {
    typedef struct Node {
        int jarakDariAsal;
        int kota;
        struct Node *prev;
    } Node;

    int visited[jmlNode];
    int unvisited[jmlNode];
    Node nodeKota[jmlNode];
    Node *temp;
    int asal, tujuan, diproses, terkecilNilai, terkecilNode;
    int ditemukan = 0;
    cleanScreen(1);
    do {
        printf("Masukkan kota asal (%d - %d): ", 0, jmlNode - 1);
        scanf("%d", &asal);
        printf("Masukkan kota tujuan (%d - %d dan bukan %d): ", 0, jmlNode - 1, asal);
        scanf("%d", &tujuan);

        if (asal == tujuan) {
            cleanScreen(1);
            printf("Anda memasukkan kota tujuan yang sama dengan kota asal\n");
        }
    } while (asal == tujuan);

    for (int i = 0; i < jmlNode; i++) {
        visited[i] = 0;
        unvisited[i] = 1;

        nodeKota[i].jarakDariAsal = MAX_INTEGER;
        nodeKota[i].prev = NULL;
        nodeKota[i].kota = i;
    }

    nodeKota[asal].jarakDariAsal = 0;

    diproses = asal;
    for (int i = 0; i < jmlNode; i++) {
        visited[diproses] = 1;
        unvisited[diproses] = 0;

        for (int j = 0; j < jmlNode; j++) {
            if (mTetangga[diproses][j] > 0) {
                if (mTetangga[diproses][j] + nodeKota[diproses].jarakDariAsal < nodeKota[j].jarakDariAsal) {
                    nodeKota[j].jarakDariAsal = (nodeKota[diproses].jarakDariAsal + mTetangga[diproses][j]);
                    nodeKota[j].prev = &nodeKota[diproses];
                    printf("\nDidapatkan jarak terpendek Kota %d yang baru bernilai %d melalui Kota %d", j, nodeKota[j].jarakDariAsal, diproses);
                }
            }
        }

        terkecilNilai = MAX_INTEGER;
        terkecilNode = -1;
        for (int j = 0; j < jmlNode; j++) {
            if (unvisited[j] == 1) {
                if (nodeKota[j].jarakDariAsal > 0 && nodeKota[j].jarakDariAsal < terkecilNilai) {
                    terkecilNilai = nodeKota[j].jarakDariAsal;
                    terkecilNode = j;
                }
            }
        }

        printf("\nDidapatkan node baru yang akan divisit & diproses: %d", terkecilNode);
        diproses = terkecilNode;
        if (diproses == tujuan) {
            ditemukan = 1;
            break;
        }
    }

    if (ditemukan == 1) {
        printf("\n\nDitemukan jarak tempuh terpendek dari %d ke %d adalah: %d", asal, tujuan, nodeKota[tujuan].jarakDariAsal);
        printf("\nDengan rute: ");
        temp = &nodeKota[tujuan];
        while (temp->prev != NULL) {
            printf("Kota %d, ", temp->kota);
            temp = temp->prev;
        }
        printf("Kota %d\n", temp->kota);
        konfirmasiLanjut();
    }
}

void algoritmaKruskal() {
    cleanScreen(5);

    typedef struct Node {
        int nilai;
        int grup;
    } Node;

    typedef struct Edge {
        int bobot;
        int v1;
        int v2;
    } Edge;

    int k = 0, diganti;
    Edge jalan[jmlEdgeMurni];
    Edge jalanTemp;
    Edge solutionSet[jmlEdgeMurni];
    Node kota[jmlEdgeMurni];
    int jmlMemberGrup[jmlNode];

    for (int i = 0; i < jmlNode; i++) {
        kota[i].nilai = i;
        kota[i].grup = -1;
    } 

    for (int i = 0; i < jmlNode; i++) {
        for (int j = (i + 1); j < jmlNode; j++) {
            jalan[k].bobot = mTetangga[i][j];
            jalan[k].v1 = i;
            jalan[k].v2 = j;

            k++;
        }
    }
    printf("\nPanjang jalan yang telah dirurutkan dari terpendek -> terpanjang:\n");
    do {
        diganti = 0;
        for (int i = 0; i < (jmlEdgeMurni); i++) {
            if (jalan[i].bobot > jalan[i + 1].bobot) {
                jalanTemp = jalan[i + 1];
                jalan[i + 1] = jalan[i];
                jalan[i] = jalanTemp;
                diganti = 1;
            }
        }
    }
    while (diganti == 1);

    for (int i = 0; i < jmlEdgeMurni; i++) {
        if (jalan[i].bobot > 0) {
            printf("Jalan antar Kota %d dengan Kota %d memiliki panjang: %d\n", jalan[i].v1, jalan[i].v2, jalan[i].bobot);
        }
    }

    int solSetTersedia = -1;
    int grupTersedia = -1;
    int grupTemp;
    Node *vAsal, *vLawan;
    konfirmasiLanjut();
    

    for (int i = 0; i < jmlEdgeMurni; i++) {
        if (jalan[i].bobot > 0) {
            vAsal = &kota[jalan[i].v1];
            vLawan = &kota[jalan[i].v2];
            printf("Memproses Kota %d (Grup %d) dengan Kota %d (Grup %d)...\n", vAsal->nilai, vAsal->grup, vLawan->nilai, vLawan->grup);
            if ((*vAsal).grup == -1 && (*vLawan).grup == -1) {
                grupTersedia++;
                solSetTersedia++;
                printf("Kota %d dan Kota %d membuat grup baru: %d\n", (*vAsal).nilai, (*vLawan).nilai, grupTersedia);
                (*vAsal).grup = grupTersedia;
                (*vLawan).grup = grupTersedia;
                
                solutionSet[solSetTersedia] = jalan[i];
                jmlMemberGrup[solSetTersedia] = 2;
            }
            else if ((*vAsal).grup == -1 && (*vLawan).grup > -1) {
                printf("Kota %d masuk kedalam grup %d melalui Kota %d\n", (*vAsal).nilai, (*vLawan).grup, (*vLawan).nilai);
                (*vAsal).grup = (*vLawan).grup;
                solSetTersedia++;
                solutionSet[solSetTersedia] = jalan[i];
                jmlMemberGrup[solSetTersedia]++;
            }
            else if ((*vAsal).grup > -1 && (*vLawan).grup == -1) {
                printf("Kota %d masuk kedalam grup %d melalui Kota %d\n", (*vLawan).nilai, (*vAsal).grup, (*vAsal).nilai);
                (*vLawan).grup = (*vAsal).grup;
                solSetTersedia++;
                solutionSet[solSetTersedia] = jalan[i];
                jmlMemberGrup[solSetTersedia]++;
            }
            else if ((*vAsal).grup > -1 && (*vLawan).grup > -1) {
                if ((*vAsal).grup == (*vLawan).grup) {
                    printf("Kota %d dan Kota %d akan membentuk Cycle, proses diabaikan...\n", (*vAsal).nilai, (*vLawan).nilai);
                }
                else {
                    solSetTersedia++;
                    solutionSet[solSetTersedia] = jalan[i];


                    printf("Dua grup berbeda bertemu: (Grup %d) dengan (Grup %d) Melalui Kota %d dan Kota %d\n", (*vAsal).grup, (*vLawan).grup, (*vAsal).nilai, (*vLawan).nilai);
                    printf("Seluruh subset dari grup %d telah berpindah ke grup %d dimana grup %d: (", (*vLawan).grup, (*vAsal).grup, vLawan->grup);
                    grupTemp = vLawan->grup;
                    for (int j = 0; j < jmlNode; j++) {
                        if (kota[j].grup == grupTemp) {
                            kota[j].grup = (*vAsal).grup;
                            printf("Kota %d ", kota[j].nilai);
                        }
                    }
                    printf(")\n");
                }
            }
            printf("\n");
        }
    }
    int minimumCost = 0;
    printf("\nSolution Set: {");
    for (int i = 0; i < solSetTersedia + 1; i++) {
        printf("(Kota %d, Kota %d)", solutionSet[i].v1, solutionSet[i].v2);
        minimumCost += solutionSet[i].bobot;

        if (i < solSetTersedia) {printf(", ");}
        else {printf(" ");}

    }
    printf("}\nMinimum Cost: %d\n", minimumCost);
    konfirmasiLanjut();
}

void algoritmaPrim() {

    typedef struct Edge {
        int v1;
        int v2;
        int bobot;
    } Edge;

    cleanScreen(4);
    int visited[jmlNode], solSetTersedia, diproses, terkecil = MAX_INTEGER, terkecilNodeHome = -1, terkecilNodeAway;
    Edge solutionSet[jmlEdgeMurni];

    for (int i = 0; i < jmlNode; i++) {
        visited[i] = 0;
    }

    diproses = 2;
    solSetTersedia = -1;
    for (int i = 0; i < jmlNode; i++) {
        visited[diproses] = 1;
        printf("\nKota %d masuk kedalam Visited", diproses);

        terkecil = MAX_INTEGER;

        terkecilNodeHome = -1;
        terkecilNodeAway = -1;
        for (int j = 0; j < jmlNode; j++) {
            if (visited[j] == 1) {
                for (int k = 0; k < jmlNode; k++) {
                    if (mTetangga[j][k] > 0 && mTetangga[j][k] < terkecil && visited[k] == 0) {
                        printf("\nDitemukan jalan terpendek terbaru: %d", mTetangga[j][k]);
                        terkecil = mTetangga[j][k];
                        terkecilNodeHome = j;
                        terkecilNodeAway = k;
                    } 
                }
            }
        }

        if (terkecilNodeAway > -1) {
            solSetTersedia++;
            printf("\n\nKota %d dan Kota %d masuk kedalam Solution Set", terkecilNodeHome, terkecilNodeAway);
            solutionSet[solSetTersedia].v1 = terkecilNodeHome;
            solutionSet[solSetTersedia].v2 = terkecilNodeAway;
            solutionSet[solSetTersedia].bobot = terkecil;
            diproses = terkecilNodeAway;
        } else {
            break;
        }

        
    }
    int minimumCost = 0;
    printf("\nSolution Set: {");
    for (int i = 0; i < solSetTersedia + 1; i++) {
        printf("(Kota %d, Kota %d)", solutionSet[i].v1, solutionSet[i].v2);
        minimumCost += solutionSet[i].bobot;

        if (i < solSetTersedia) {printf(", ");}
        else {printf(" ");}

    }
    printf("}\nMinimum Cost: %d\n", minimumCost);
    konfirmasiLanjut();
}

void tspBacktracking() {
    typedef struct Node {
        struct Node *next;
        struct Node *prev;
        int kota;
        int jarakDariPrev;
        int nodePernahDivisit[100];
    } Node;

    

    int awal, stop, skip, solSetTersedia = 0, nodeSebelum = -1;
    int nodeDalamStack;
    Node *kotaBaru;
    Node *head;
    Node *tail;
    Node *solutionSets[100];

    do {
        cleanScreen(2);
        printf("\nMohon tentukan kota awal perjalanan (Tersedia Kota %d - Kota %d): ", 0, jmlNode - 1);
        scanf("%d", &awal);
    } while ((awal < 0) || (awal > jmlNode - 1));

    cleanScreen(2);
    printf("Kota awal start yang dipilih: Kota %d\n", awal);
    konfirmasiLanjut();

    cleanScreen(2);
    printf("\nMemulai algoritma Backtracking untuk mencari Konsep Hamilton Cycle");
    printf("\nMemasukkan kota start kedalam Stack");
    // kotaBaru ini maksudnya solutionset yang dibuat jadi LinkedList
    kotaBaru = (Node*) malloc(sizeof(Node));
    kotaBaru->jarakDariPrev = 0;
    kotaBaru->kota = awal;
    kotaBaru->next = NULL;
    kotaBaru->prev = NULL;

    // ini inisialisasi ngasi tau bahwa setiap node BELUM penrah divisit
    // karena nanti pakai backtracking.
    for (int i = 0; i < jmlNode; i++) {
        kotaBaru->nodePernahDivisit[i] = 0;
    }

    // circular doubly linkedlist
    head = kotaBaru;
    tail = kotaBaru;

    // stop kalok misalkan dia kembali ke awal dan semua tetangga ada di solution set (success)
    // atau kembali ke awal dan semua tetangga sudah di visit, tetapi tidak semua ada di solution set (fail)
    stop = 0;
    // skip = 1 itu artinya kalau ditemuin tetangga yang belum pernah di visit
    skip = 0;
    while (stop == 0) {

        kotaBaru = head;
        nodeDalamStack = 1;
        // ini untuk keperuan ngeprint node saja, ngecek berapa jumlah node didalam linkedlist solution set
        while (kotaBaru->next != NULL) {
            kotaBaru = kotaBaru->next;
            nodeDalamStack++;
        }
        printf("\nJml Node dalam Stack: %d", nodeDalamStack);
        // reset state skip
        skip = 0;
        // for loop untuk ngecek tetangga apakah dia sudah pernah divsit oleh node yang sedang ditunjuk
        for (int i = 0; i < jmlNode; i++) {
            // kalok ketemu tetangga, dia bukan node awal, belum di skip, brarti gass cek
            if (i != tail->kota && mTetangga[tail->kota][i] > 0 && i != awal && skip == 0) {
                kotaBaru = head;
                // nodesebelum = 0 itu artinya node yang ditunjuk belum ada di solution set
                nodeSebelum = 0;
                while (kotaBaru->next != NULL) {
                    kotaBaru = kotaBaru->next;
                    if (kotaBaru->kota == i) {
                        nodeSebelum = 1;
                        break;
                    }
                }
                if (kotaBaru->nodePernahDivisit[i] == 1) {
                    nodeSebelum = 1;
                }
                
                if (nodeSebelum == 0) {
                    kotaBaru = (Node*) malloc(sizeof(Node));

                    kotaBaru->jarakDariPrev = mTetangga[tail->kota][i];
                    kotaBaru->kota = i;
                    kotaBaru->prev = tail;
                    tail->next = kotaBaru;
                    tail->nodePernahDivisit[i] = 1;
                    kotaBaru->next = NULL;
                    tail = kotaBaru;

                    for (int j = 0; j < jmlNode; j++) {
                        kotaBaru->nodePernahDivisit[j] = 0;
                    }

                    printf("\n%d ditambahkan ke stack", i);
                    printf("\nStack menjadi: (");

                    kotaBaru = head;
                    while (kotaBaru->next != NULL) {
                        printf("%d, ", kotaBaru->kota);
                        kotaBaru = kotaBaru->next;
                    }
                    printf("%d)", kotaBaru->kota);

                    skip = 1;
                }
                // ini else if untuk misalkan solusi ditemukan 
                // kalok yang lagi diperiksa == awal, dan nodeDalam solution set sama dengan jumlah node
            } else if (i == awal && nodeDalamStack == jmlNode && mTetangga[tail->kota][i] > 0) {
                kotaBaru = (Node*) malloc(sizeof(Node));

                kotaBaru->jarakDariPrev = mTetangga[tail->kota][i];
                kotaBaru->kota = i;
                kotaBaru->prev = tail;
                tail->next = kotaBaru;
                kotaBaru->next = NULL;
                tail = kotaBaru;

                printf("\nSolusi untuk Traveling Salesman Problem ditemukan untuk kota yang anda analisis.\nDengan rute: ");
                kotaBaru = head;
                int totalCost;
                while (kotaBaru->next != NULL) {
                    totalCost += kotaBaru->jarakDariPrev;
                    printf("%d, ", kotaBaru->kota);
                    kotaBaru = kotaBaru->next;
                }
                skip = 1;
                stop = 1;
                totalCost += kotaBaru->jarakDariPrev;
                printf("%d\nDengan total jarak: %d\n", kotaBaru->kota, totalCost);

                konfirmasiLanjut();
            }
        }
        // atau kalok kembali ke awal tetapi solutionset belum sebanyak jumlah kota
        // atau jalan buntu tetapi belum kembali ke awal
        if (skip == 0) {
            if (tail->prev != NULL) {
                kotaBaru = tail->prev;
                kotaBaru->next = NULL;
                printf("\nTidak ditemukan tetangga apapun, kembali ke node sebelumnnya (backtracking) ke %d", kotaBaru->kota);
                printf("\nNode node yang pernah dikunjungi oleh node sebelum dari node yang di backtracking:");
                for (int j = 0; j < jmlNode; j++) {
                    if (kotaBaru->nodePernahDivisit[j] == 1) {
                        printf(" %d", j);
                    }
                }
                
                free(tail);
                tail = kotaBaru;
                // ini kalok gagal
            } else {
                printf("\nBacktracking kembali ke Node awal dan tidak menemukan tetangga lainnya yang belum dikunjungi");
                printf("\nSepertinnya tidak terdapat solusi untuk Traveling Salesman Problem pada kota yang anda analisa, mohon maaf :(\n");
                stop = 1;
                konfirmasiLanjut();
            }
        }
        printf("\n");
    }
}

void cppEulerianCycle() {
    typedef struct Edge {
        int v1;
        int v2;
        struct Edge *next;
        struct Edge *prev;
    } Edge;

    typedef struct Node {
        struct Node *next;
        struct Node *prev;
        int kota;
        int jarakDariPrev;
        int totalEdgePernahDivisit;
        struct Edge *edgePernahDivisit[100];
    } Node;

    cleanScreen(3);
    int derajatNode[jmlNode][jmlNode];
    int derajatGanjil = 0, derajat, awal, stop, skip, edgeSebelum;
    int edgeDalamStack = 0;
    Node *kotaBaru;
    Node *head;
    Node *tail;
    Edge *jalanHead = NULL;
    Edge *jalanTail = NULL;
    Edge *jalanBaru;
    Edge *solsetHead = NULL;
    Edge *solsetTail = NULL;
    Edge *solsetBaru;
    
    for (int i = 0; i < jmlNode; i++) {
        derajat = 0;
        for (int j = 0; j < jmlNode; j++) {
            if (mTetangga[i][j] > 0) {
                derajat++;
            }
        }
        derajat = derajat % 2;
        if (derajat == 1) {
            derajatGanjil = 1;
            break;
        }
    }

    if (derajatGanjil == 1) {
        printf("Sepertinnya terdapat Kota yang jumlah jalan akses keluar/masuk bernilai ganjil\nUntuk memungkinkan menggunakan fitur ini, mohon analisis daerah dimana setiap kota HARUS memiliki jumlah jalan masuk/keluar berupa genap\n");
        konfirmasiLanjut();
    } else {
        do {
            printf("Mohon tentukan Kota awal / start (tersedia Kota %d - Kota %d): ", 0, jmlNode - 1);
            scanf("%d", &awal);
        } while(awal < 0 || awal > jmlNode - 1);

        cleanScreen(2);
        printf("Kota awal start yang dipilih: Kota %d\n", awal);
        konfirmasiLanjut();

        kotaBaru = (Node*) malloc(sizeof(Node));
        kotaBaru->kota = awal;
        kotaBaru->next = NULL;
        kotaBaru->prev = NULL;
        kotaBaru->jarakDariPrev = 0;
        kotaBaru->totalEdgePernahDivisit = 0;

        head = kotaBaru;
        tail = kotaBaru;
        
        stop = 0;
        skip = 0;
        while (stop == 0) {
            skip = 0;
            for (int i = 0; i < jmlNode; i++) {
                if (i != tail->kota && mTetangga[tail->kota][i] > 0 && i != awal && skip == 0) {
                    edgeSebelum = 0;
                    for (int j = 0; j < tail->totalEdgePernahDivisit; j++) {
                        jalanBaru = tail->edgePernahDivisit[j];
                        printf("\n%d ||| %d", j, jalanBaru->v1, jalanBaru->v2);
                        if ((jalanBaru->v1 == i && jalanBaru->v2 == tail->kota) || (jalanBaru->v1 == tail->kota && jalanBaru->v2 == i)) {
                            edgeSebelum = 1;
                        }
                    }
                    if (solsetTail != NULL) {
                        solsetBaru = solsetTail;
                        
                        while (solsetBaru->prev != NULL) {
                            if ((solsetBaru->v1 == i && solsetBaru->v2 == tail->kota) || (solsetBaru->v1 == tail->kota && solsetBaru->v2 == i)) {
                                edgeSebelum = 1;
                                break;
                            }
                            solsetBaru = solsetBaru->prev;
                        }
                        
                        if ((jalanBaru->v1 == i && jalanBaru->v2 == tail->kota) || (jalanBaru->v1 == tail->kota && jalanBaru->v2 == i)) {
                            edgeSebelum = 1;
                        }
                        if (edgeSebelum == 0) {
                            jalanBaru = (Edge*) malloc(sizeof(Edge));
                            jalanBaru->v1 = tail->kota;
                            jalanBaru->v2 = i;
                            jalanBaru->next = NULL;
                            jalanBaru->prev = jalanTail;

                            jalanTail->next = jalanBaru;
                            jalanTail = jalanBaru;

                            solsetBaru = (Edge*) malloc(sizeof(Edge));
                            solsetBaru->v1 = tail->kota;
                            solsetBaru->v2 = i;
                            solsetBaru->next = NULL;
                            solsetBaru->prev = solsetTail;

                            solsetTail->next = solsetBaru;
                            solsetTail = solsetBaru;


                            kotaBaru = (Node*) malloc(sizeof(Node));
                            kotaBaru->kota = i;
                            kotaBaru->jarakDariPrev = mTetangga[tail->kota][i];
                            kotaBaru->totalEdgePernahDivisit = 0;
                            kotaBaru->next = NULL;
                            kotaBaru->prev = tail;

                            edgeDalamStack++;
                            printf("\nJalan yang menghubungkan Kota %d dengan Kota %d dimasukkan kedalam stack", tail->kota, i);
                            tail->next = kotaBaru;
                            tail->edgePernahDivisit[tail->totalEdgePernahDivisit] = jalanTail;
                            tail->totalEdgePernahDivisit++;
                            tail = kotaBaru;

                            printf("\nStack menjadi: (");
                            kotaBaru = head;
                            while (kotaBaru->next != NULL) {
                                printf("Kota %d, ", kotaBaru->kota);
                                kotaBaru = kotaBaru->next;
                            }
                            printf("Kota %d)", kotaBaru->kota);
                            skip = 1;
                        }
                    } 
                    else {
                        jalanBaru = (Edge*) malloc(sizeof(Edge));
                        jalanBaru->v1 = tail->kota;
                        jalanBaru->v2 = i;
                        jalanBaru->next = NULL;
                        jalanBaru->prev = NULL;

                        jalanHead = jalanBaru;
                        jalanTail = jalanBaru;

                        solsetBaru = (Edge*) malloc(sizeof(Edge));
                        solsetBaru->v1 = tail->kota;
                        solsetBaru->v2 = i;
                        solsetBaru->next = NULL;
                        solsetBaru->prev = solsetTail;

                        solsetHead = solsetBaru;
                        solsetTail = solsetBaru;

                        kotaBaru = (Node*) malloc(sizeof(Node));
                        kotaBaru->kota = i;
                        kotaBaru->jarakDariPrev = mTetangga[tail->kota][i];
                        kotaBaru->totalEdgePernahDivisit = 0;
                        kotaBaru->next = NULL;
                        kotaBaru->prev = tail;

                        edgeDalamStack++;

                        printf("\nJalan yang menghubungkan Kota %d dengan Kota %d dimasukkan kedalam stack", tail->kota, i);
                        tail->next = kotaBaru;
                        tail->edgePernahDivisit[tail->totalEdgePernahDivisit] = jalanTail;
                        tail->totalEdgePernahDivisit++;
                        tail = kotaBaru;
                        

                        printf("\nStack menjadi: (");
                        kotaBaru = head;
                        while (kotaBaru->next != NULL) {
                            printf("Kota %d, ", kotaBaru->kota);
                            kotaBaru = kotaBaru->next;
                        }
                        skip = 1;
                        printf("Kota %d)", kotaBaru->kota);
                    }
                } 
                else if (i == awal && edgeDalamStack == jmlEdgeSangatMurni - 1 && mTetangga[tail->kota][i] > 0) {
                    kotaBaru = (Node*) malloc(sizeof(Node));

                    kotaBaru->jarakDariPrev = mTetangga[tail->kota][i];
                    kotaBaru->kota = i;
                    kotaBaru->prev = tail;
                    tail->next = kotaBaru;
                    kotaBaru->next = NULL;
                    tail = kotaBaru;

                    printf("\nSolusi untuk Chinese Postman Problem ditemukan pada kota yang anda analisis.\nDengan rute: ");
                    kotaBaru = head;
                    int totalCost = 0;
                    while (kotaBaru->next != NULL) {
                        printf("Kota %d (%d), ", kotaBaru->kota, kotaBaru->jarakDariPrev);
                        totalCost = totalCost + kotaBaru->jarakDariPrev;
                        kotaBaru = kotaBaru->next;
                    }
                    skip = 1;
                    stop = 1;
                    totalCost += kotaBaru->jarakDariPrev;
                    printf("Kota %d\nDengan total jarak: %d\n", kotaBaru->kota, totalCost);

                    konfirmasiLanjut();
                }
            }
            if (skip == 0) {
                if (tail->prev != NULL) {
                    kotaBaru = tail->prev;
                    kotaBaru->next = NULL;

                    printf("\nTidak ditemukan tetangga apapun, kembali ke node sebelumnnya (backtracking) ke %d", kotaBaru->kota);
                    printf("\nEdge edge yang pernah divisit oleh node sebelum dari node yang di backtracking (%d):", kotaBaru->totalEdgePernahDivisit);
                    
                    
                    for (int j = 0; j < kotaBaru->totalEdgePernahDivisit; j++) {
                        jalanBaru = kotaBaru->edgePernahDivisit[j];
                        printf(" (%d, %d)", jalanBaru->v1, jalanBaru->v2);
                    }
                    free(tail);
                    tail = kotaBaru;

                    edgeDalamStack = edgeDalamStack - 1;

                    printf("\nEdge (%d %d) dikeluarkan dari Solution Set", solsetTail->v1, solsetTail->v2);
                    solsetBaru = solsetTail->prev;
                    solsetBaru->next = NULL;
                    free(solsetTail);
                    solsetTail = solsetBaru;
                    printf("\nEdge edge yang ada dalam solution set sekarang:");
                    
                    solsetBaru = solsetHead;
                    while (solsetBaru->next != NULL) {
                        printf("(%d %d) ", solsetBaru->v1, solsetBaru->v2);
                        solsetBaru = solsetBaru->next;
                    }
                    printf("(%d %d) ", solsetBaru->v1, solsetBaru->v2);
                } else {
                    printf("\nBacktrackking kembali ke Node semula dan tidak terdapat tetangga lainnya yang belum dikunjungi\nSepertinnya tidak terdapat solusi untuk Chinese Postman Problem pada kota yang anda analisa, mohon maaf :(\n");
                    stop = 1;
                }
 
             }
             printf("\n");
        }
        konfirmasiLanjut();
    }
}

int main() {
    int pilihan;
    void (*menuPilihan[5])();
    menuPilihan[0] = shortestPath;
    menuPilihan[1] = tspBacktracking;
    menuPilihan[2] = cppEulerianCycle;
    menuPilihan[3] = algoritmaPrim;
    menuPilihan[4] = algoritmaKruskal;

    do {
        cleanScreen(0);
        printf("Selamat datang bapak/ibu manajer, mohon masukkan jumlah kota yang ingin anda analisa: ");
        // scanf("%d", &jmlNode);

        cleanScreen(0);
        // printf("Jumlah kota yang akan dianalisis: %d", jmlNode);
        // mTetangga[jmlNode][jmlNode];
        // printf("\nMohon beri detail jarak antar kota sebagai berikut (0 jika tidak terhubung):\n");
        // jmlEdgeMurni = 0;

        // for (int i = 0; i < jmlNode; i++) {
        //     for (int j = (i + 1); j < jmlNode; j++) {
        //         printf("Kota %d ke kota %d: ", i, j);
        //         scanf("%d", &pilihan); // comment baris ini jika ingin menggunakan matriks yang sudah ditentukan

        //         mTetangga[i][j] = pilihan; // comment baris ini jika ingin menggunakan matriks yang sudah ditentukan
        //         mTetangga[j][i] = pilihan; // comment baris ini jika ingin menggunakan matriks yang sudah ditentukan

        //         jmlEdgeMurni++;

        //         if (mTetangga[i][j] > 0) {
        //             jmlEdgeSangatMurni++;
        //         }
        //     }
        // }

        cleanScreen(0);
        printf("Berikut matriks ketetanggaan dari kota yang akan bapak/ibu manajer analisa:\n");
         for (int i = 0; i < jmlNode; i++) {
            for (int j = 0; j < jmlNode; j++) {
                printf("%d ", mTetangga[i][j]);
            }
            printf("\n");
        }
        konfirmasiLanjut();
        cleanScreen(0);

        do {
            printf("Apakah yang ingin bapak/ibu manajer analisa dari kota tersebut?\n");
            printf("1. Mencari jalan terpendek dari kota X ke kota Y (Shortest Path)\n2. Mencari rute terpendek dari kumpulan kota tersebut (Traveling Salesman Problem)\n3. Mencari rute terpendek dari kumpulan jalan yang ada (Chinese Postman Problem)\n4. Mencari jangkauan terpendek menggunakan Algoritma Prim\n5. Mencari jangkauan terpendek menggunakan Algoritma Kruskal\n6. Akhiri program\nPilihan: ");
            scanf("%d", &pilihan);
            if (pilihan > 0 && pilihan < 7) {
                pilihan = pilihan - 1;
                if (pilihan < 5) {
                    menuPilihan[pilihan]();
                }
                cleanScreen(0);
            } else {
                cleanScreen(0);
                printf("Bapak/ibu manajer memasukkan pilihan yang tidak tersedia\n");
            }
        }
        while (pilihan != 5);

    }
    while (pilihan == 7);

    return 0;
}

void cleanScreen(int bagian) {
    system("cls");
    printf("Putu Audi Pasuatmadi\t\t\t\t(1908561095)\n");

    switch(bagian) {
        case 1:
            printf("(Mencari jalan terpendek)");
            break;
        case 2:
            printf("(Mencari rute antar-kota terpendek (Traveling Salesman Problem) menggunakan Backtracking)");
            break;
        case 3:
            printf("(Mencari total panjang jalan antar-kota (Chinese Postman Problem) menggunakan Eulerian Cycle)");

            break;
        case 4:
            printf("(Mencari rentang antar-kota menggunakan Algoritma Prim)");
            break;
        case 5:
            printf("(Mencari rentang antar-kota menggunakan Algoritma Kruskal)");
            break;
        
    }

    printf("\n-------------------------------------------------------------------\n");
}

void konfirmasiLanjut() {
    fflush(stdin);
    printf("Tekan apapun untuk melanjutkan program.......\n");
    getchar();
    fflush(stdin);
}