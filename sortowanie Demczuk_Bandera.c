#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

unsigned int ns[] = { 10, 500, 1000, 3500, 7000, 10000, 15000, 20000, 30000, 43000 };

void fill_increasing(int *t, unsigned int n) {
	int a = 0;
    for(unsigned int i = 0; i < n; i++){
    	t[i] = a++;
    }
}

void fill_decreasing(int *t, unsigned int n) {
    int a = 108495;
    for(unsigned int i = 0; i < n; i++){
    	t[i] = a--;
    }
}

void fill_vshape(int *t, unsigned int n) {
    int *begin = t;
    int *end = t + n - 1;

    int a = n;
    *begin = a;
    begin++;
    a--;

    for(int i = 0; i < n/2; i++){
        *end = a;
        *begin = --a;
        begin++;
        end--;
        a--;
    }
}

void selection_sort(int *t, unsigned int n) {
    int i = 0;
    int j = 0;
    int min, temp, index;
    for(i = 0; i < n; i++){
        min = t[i];
        for(j = i; j < n; j++)
            if(min > t[j]){
                min = t[j];
                index = j;
            }
        if(min != t[i]){
            temp = t[i];
            t[i] = min;
            t[index] = temp;
        }
    }
}

void insertion_sort(int *t, unsigned int n) {
    int temp;
    int j;
    for(int i = 1; i < n; i++){
        temp = t[i];
        j = i - 1;
        while((j >= 0) && (t[j]>temp)){
            t[j+1] = t[j];
            t[j] = temp;
            j--;
        }
    }
}

void swap(int* a, int* b){
    int temp = *a;
    *a = *b;
    *b = temp;
}

int partition(int *t, int p, int r){
    int x = t[r];
    int i = p - 1;
    int temp;
    for(int j = p; j <= r - 1; j++){
        if(t[j] < x){
            i++;
            swap(&t[i], &t[j]);
        }
    }
    swap(&t[i + 1], &t[r]);
    return (i + 1);
}

int random_partition(int *t, int p, int r){
    int temp;
    srand(time(NULL));
    int i = rand() % (r - p) + p;
    temp = t[i];
    t[i] = t[r];
    t[r] = temp;
    return partition(t, p, r);
}

void quick_sort1(int *t, int p, int r){
    if(p < r){
        int q = partition(t, p, r);
        quick_sort1(t, p, q - 1);
        quick_sort1(t, q + 1, r);
    }
}

void quick_sort(int *t, unsigned int n){
    quick_sort1(t, 0, n - 1);
}

void quick_sort_rand1(int *t, int p, int r){
    if(p < r){
        int q = random_partition(t, p, r);
        quick_sort_rand1(t, p, q - 1);
        quick_sort_rand1(t, q + 1, r);
    }
}

void quick_sort_rand(int *t, unsigned int n){
    quick_sort_rand1(t, 0, n - 1);
}

void heap_sort(int *t, unsigned int n) {
    int parent, temp, j, l, r, a, index;
    int *heap = malloc(n * sizeof(*heap));
    memset(heap, 0, n);

    for(int i = 0; i < n; i++){
        heap[i] = t[i];
        index = i;
        while(1){
            if(index > 0){
                parent = (index - 1) / 2;
                if(heap[index] < heap[parent]){
                    temp = heap[index];
                    heap[index] = heap[parent];
                    heap[parent] = temp;
                }
            }
            else
                break;
            index = parent;
        }
        j = i + 1;
    }

    for(int i = 0; i < n; i++){
        t[i] = heap[0];
        j--;
        heap[0] = heap[j];
        index = 0;
        while(1){
            l = index * 2 + 1;
            r = index * 2 + 2;
            if(l >= j)
                break;
            if((r >= j) || (heap[l] < heap[r]))
                a = l;
            else
                a = r;
            if(heap[a] < heap[index]){
                temp = heap[a];
                heap[a] = heap[index];
                heap[index] = temp;
            }
            index = a;
        }
    }
}

void fill_random(int *t, unsigned int n) {
    srand(time(NULL));
    for (unsigned int i = 0; i < n; i++) {
        t[i] = rand();
    }
}

void is_random(int *t, unsigned int n) {
    return;
}

void is_increasing(int *t, unsigned int n) {
    for (unsigned int i = 1; i < n; i++) {
        assert(t[i] > t[i - 1]);
    }
}

void is_decreasing(int *t, unsigned int n) {
    for (unsigned int i = 1; i < n; i++) {
        assert(t[i] < t[i - 1]);
    }
}

void is_vshape(int *t, unsigned int n) {
    int *begin = t;
    int *end = t + n - 1;

    while (end - begin > 1) {
        assert(*begin > *end);
        begin++;
        assert(*end > *begin);
        end--;
    }
}

void is_sorted(int *t, unsigned int n) {
    for (unsigned int i = 1; i < n; i++) {
        assert(t[i] >= t[i - 1]);
    }
}

void (*fill_functions[])(int *, unsigned int) = { fill_random, fill_increasing, fill_decreasing, fill_vshape };
void (*check_functions[])(int *, unsigned int) = { is_random, is_increasing, is_decreasing, is_vshape };
void (*sort_functions[])(int *, unsigned int) = { selection_sort, insertion_sort, quick_sort, quick_sort_rand, heap_sort };

char *fill_names[] = { "Random", "Increasing", "Decreasing", "V-Shape" };
char *sort_names[] = { "SelectionSort", "InsertionSort", "QuickSort", "QuickSortRand", "HeapSort" };

int main() {
    for (unsigned int i = 0; i < sizeof(sort_functions) / sizeof(*sort_functions); i++) {
        void (*sort)(int *, unsigned int) = sort_functions[i];

        for (unsigned int j = 0; j < sizeof(fill_functions) / sizeof(*fill_functions); j++) {
            void (*fill)(int *, unsigned int) = fill_functions[j];
            void (*check)(int *, unsigned int) = check_functions[j];

            for (unsigned int k = 0; k < sizeof(ns) / sizeof(*ns); k++) {
                unsigned int n = ns[k];
                int *t = malloc(n * sizeof(*t));

                fill(t, n);
                check(t, n);

                clock_t begin = clock();
                sort(t, n);
                clock_t end = clock();
                is_sorted(t, n);

                printf("%s\t%s\t%u\t%f\n", sort_names[i], fill_names[j], n, (double)(end - begin) / (double) CLOCKS_PER_SEC);
                free(t);
            }
        }
    }
    return 0;
}
