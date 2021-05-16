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
### 5. Proses Hamiltonian
#### 5.1. Pakai LinkedList untuk SolutionSet
#### 5.2. Cek setiap tetangga dari vertex yang diuji
5.2.1. Tetangga belum visited & bukan di awal & bukan dirinya sendiri, maka masukkan ke solutionset
5.2.2. Tetangga belum visited & di awal & jumlah solutionset = jumlah total vertex, maka
solutionset ditmeukan & sudah final.
5.2.3. Tidak ditemukan tetangga, backtracking
5.2.4. Ditemukan tetangga tetapi itu "awal", dan solutionset tidak sama dengan jumlah total vertex, maka backtracking
#### 5.3. Kalok terus backtracking sampai kembali ke awal dan setiap tetangga di awal sudah visited, maka tidak ada solutionset
#### 5.4. Tetangga belum visited & di awal & jumlah solutionset = jumlah total vertex, maka
solutionset ditmeukan & sudah final.


# Cara Integrasi
- Yang penting ada matriks tetangga, ada jumlah total vertex, aman.
- Matriks tetangga boleh isi bobot, 1 0 1 0 cukup.
- Input vertex awal keberangkatan