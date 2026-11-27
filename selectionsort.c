#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void selectionSort(int arr[], int n) {
    int i, j, min, temp;

    for (i = 0; i < n - 1; i++) {
        min = i;
        for (j = i + 1; j < n; j++) {
            if (arr[j] < arr[min]) {
                min = j;
            }
        }
        if (min != i) {
            temp = arr[i];
            arr[i] = arr[min];
            arr[min] = temp;
        }
    }
}

int main() {
    int ukuran[] = {10, 50, 100, 500, 1000, 2000, 5000};
    int jumlah = 7;
    int i, k, r;

    FILE *f = fopen("hasil_selection.csv", "w");
    fprintf(f, "n,waktu_us,memori_array_bytes,memori_tambahan_bytes\n");

    printf("n\twaktu(us)\tmemori(byte)\n");

    srand(42);
    for (k = 0; k < jumlah; k++) {
        int n = ukuran[k];
        int *asli = malloc(n * sizeof(int));
        int *salin = malloc(n * sizeof(int));

        for (i = 0; i < n; i++) {
            asli[i] = rand() % 10000;
        }

        // diulang biar waktunya kebaca, makin kecil n makin banyak ulangannya
        int ulang = 200000 / n;
        clock_t mulai = clock();
        for (r = 0; r < ulang; r++) {
            for (i = 0; i < n; i++) {
                salin[i] = asli[i];
            }
            selectionSort(salin, n);
        }
        clock_t selesai = clock();

        double waktu = (double)(selesai - mulai) / CLOCKS_PER_SEC * 1000000 / ulang;
        long memori = n * sizeof(int);
        long tambahan = 4 * sizeof(int); // i, j, min, temp

        printf("%d\t%.2f\t\t%ld\n", n, waktu, memori);
        fprintf(f, "%d,%.2f,%ld,%ld\n", n, waktu, memori, tambahan);

        free(asli);
        free(salin);
    }

    fclose(f);
    return 0;
}
