#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define JUMLAH_UKURAN 5
#define PENGULANGAN   5

/* Bubble Sort (dengan optimasi flag tukar) */
void bubbleSort(int arr[], int n)
{
    for (int i = 0; i < n - 1; i++) {
        int tukar = 0;
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
                tukar = 1;
            }
        }
        if (!tukar) break;
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
    FILE *csv = fopen("hasil_bubble.csv", "w");

    srand(42); /* seed tetap agar data sama di semua program */

    printf("=== BUBBLE SORT ===\n");
    printf("%-10s %-18s %-18s\n", "Ukuran", "Waktu (ms)", "Memori (KB)");
    printf("--------------------------------------------------\n");
    if (csv) fprintf(csv, "ukuran,waktu_ms,memori_kb\n");

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
            bubbleSort(arr, n);
            clock_t selesai = clock();

            if (!sudahUrut(arr, n))
                printf("Peringatan: data belum terurut!\n");

            totalWaktu += (double)(selesai - mulai) * 1000.0 / CLOCKS_PER_SEC;
            free(arr);
        }

        double rataWaktu = totalWaktu / PENGULANGAN;

        /* Memori = array + variabel bantu (i, j, tukar, temp), dalam KB */
        size_t memArray = n * sizeof(int);
        size_t memBantu = 4 * sizeof(int);
        double memKB = (double)(memArray + memBantu) / 1024.0;

        printf("%-10d %-18.3f %-18.3f\n", n, rataWaktu, memKB);
        if (csv) fprintf(csv, "%d,%.3f,%.3f\n", n, rataWaktu, memKB);
    }

    if (csv) {
        fclose(csv);
        printf("\nHasil disimpan di hasil_bubble.csv\n");
    }
    return 0;
}
