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
    kotaBaru = (Node*) malloc(sizeof(Node));
    kotaBaru->jarakDariPrev = 0;
    kotaBaru->kota = awal;
    kotaBaru->next = NULL;
    kotaBaru->prev = NULL;

    for (int i = 0; i < jmlNode; i++) {
        kotaBaru->nodePernahDivisit[i] = 0;
    }

    head = kotaBaru;
    tail = kotaBaru;

    stop = 0;
    skip = 0;
    while (stop == 0) {

        kotaBaru = head;
        nodeDalamStack = 1;
        while (kotaBaru->next != NULL) {
            kotaBaru = kotaBaru->next;
            nodeDalamStack++;
        }
        printf("\nJml Node dalam Stack: %d", nodeDalamStack);
        
        skip = 0;
        for (int i = 0; i < jmlNode; i++) {
            if (i != tail->kota && mTetangga[tail->kota][i] > 0 && i != awal && skip == 0) {
                kotaBaru = head;
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
