#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define JUMLAH_UKURAN 5
#define PENGULANGAN   5

/* Selection Sort */
void selectionSort(int arr[], int n)
{
    for (int i = 0; i < n - 1; i++) {
        int minIdx = i;
        for (int j = i + 1; j < n; j++) {
            if (arr[j] < arr[minIdx])
                minIdx = j;
        }
        if (minIdx != i) {
            int temp = arr[i];
            arr[i] = arr[minIdx];
            arr[minIdx] = temp;
        }
    }
}

void isiDataAcak(int arr[], int n)
{
    for (int i = 0; i < n; i++)
        arr[i] = rand() % 100000;
}

int sudahUrut(int arr[], int n)
{
    for (int i = 0; i < n - 1; i++)
        if (arr[i] > arr[i + 1]) return 0;
    return 1;
}

int main(void)
{
    int ukuran[JUMLAH_UKURAN] = {100, 500, 1000, 5000, 10000};
    FILE *csv = fopen("hasil_selection.csv", "w");

    srand(42); /* seed tetap agar data sama di semua program */

    printf("=== SELECTION SORT ===\n");
    printf("%-10s %-18s %-18s\n", "Ukuran", "Waktu (ms)", "Memori (byte)");
    printf("--------------------------------------------------\n");
    if (csv) fprintf(csv, "ukuran,waktu_ms,memori_byte\n");

    for (int u = 0; u < JUMLAH_UKURAN; u++) {
        int n = ukuran[u];
        double totalWaktu = 0.0;

        for (int r = 0; r < PENGULANGAN; r++) {
            int *arr = (int *)malloc(n * sizeof(int));
            if (arr == NULL) {
                printf("Alokasi memori gagal!\n");
                return 1;
            }
            isiDataAcak(arr, n);

            clock_t mulai = clock();
            selectionSort(arr, n);
            clock_t selesai = clock();

            if (!sudahUrut(arr, n))
                printf("Peringatan: data belum terurut!\n");

            totalWaktu += (double)(selesai - mulai) * 1000.0 / CLOCKS_PER_SEC;
            free(arr);
        }

        double rataWaktu = totalWaktu / PENGULANGAN;

        /* Memori = array + variabel bantu (i, j, minIdx, temp) */
        size_t memArray = n * sizeof(int);
        size_t memBantu = 4 * sizeof(int);
        size_t memTotal = memArray + memBantu;

        printf("%-10d %-18.3f %-18zu\n", n, rataWaktu, memTotal);
        if (csv) fprintf(csv, "%d,%.3f,%zu\n", n, rataWaktu, memTotal);
    }

    if (csv) {
        fclose(csv);
        printf("\nHasil disimpan di hasil_selection.csv\n");
    }
    return 0;
}

    
