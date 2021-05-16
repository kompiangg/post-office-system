# Final Project Guide
## Step By Step
### 1. Inisialisasi Matriks Tetangga
### 2. Masukkan Jumlah Kota
### 3. Input Matriks Tetangga

```c
// Line 755
printf("Jumlah kota yang akan dianalisis: %d", jmlNode);
mTetangga[jmlNode][jmlNode];
printf("\nMohon beri detail jarak antar kota sebagai berikut (0 jika tidak terhubung):\n");
jmlEdgeMurni = 0;

for (int i = 0; i < jmlNode; i++) {
    for (int j = (i + 1); j < jmlNode; j++) {
        printf("Kota %d ke kota %d: ", i, j);
        scanf("%d", &pilihan); // comment baris ini jika ingin menggunakan matriks yang sudah ditentukan

        mTetangga[i][j] = pilihan; // comment baris ini jika ingin menggunakan matriks yang sudah ditentukan
        mTetangga[j][i] = pilihan; // comment baris ini jika ingin menggunakan matriks yang sudah ditentukan

        jmlEdgeMurni++;

        if (mTetangga[i][j] > 0) {
            jmlEdgeSangatMurni++;
        }
    }
}
// note
/*
    jmlNode = jumlah kota
    jmlEdgeMurni = jumlah kota yang terhubung di matriks tetangga
    jmlEdgeMurni = total edge
*/
```

### 4. Panggil Hamiltonian
### 5. 