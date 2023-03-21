#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int extraMemoryAllocated;

// implement merge sort
// extraMemoryAllocated counts bytes of extra memory allocated
// Merge Function For MergeSort, Will Be Used Within MergeSort Function
void merge(int pData[], int l, int m, int r) {
    int n1 = m - l + 1;
    int n2 = r - m;
    // Output Array
    int L[n1], R[n2];
    for (int i = 0; i < n1; i++)
        L[i] = pData[l + i];
    for (int j = 0; j < n2; j++)
        R[j] = pData[m + 1 + j];
    // Local Variable
    int i = 0;
    int j = 0;
    int k = l;
    // Compare Elements
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            pData[k] = L[i];
            i++;
        }
        else {
            pData[k] = R[j];
            j++;
        }
        k++;
    }
    //Add Remaining Elements To Output Array
    while (i < n1) {
        pData[k] = L[i];
        i++;
        k++;
    }
    while (j < n2) {
        pData[k] = R[j];
        j++;
        k++;
    }
}
// Merge Sorting Function
void mergeSort(int pData[], int l, int r) {
    if (l < r) {
        // Divide Array
        int m = l + (r - l) / 2;
        // Recursion
            //Sort Left
        mergeSort(pData, l, m);
            //Sort Right
        mergeSort(pData, m + 1, r);
            //Merge Both Sorted Halves
        merge(pData, l, m, r);
    }
}

// implement insertion sort
// extraMemoryAllocated counts bytes of memory allocated
void insertionSort(int* pData, int n) {
    int i, turb, j;
    for (i = 1; i < n; i++) {
        turb = pData[i];
        j = i - 1;

        while (j >= 0 && pData[j] > turb) {
            pData[j + 1] = pData[j];
            j = j - 1;
        }
        pData[j + 1] = turb;
    }
}

// implement bubble sort
// extraMemoryAllocated counts bytes of extra memory allocated
void bubbleSort(int* pData, int n) {
    int i, j;
    for (i = 0; i < n - 1; i++)
        for (j = 0; j < n - i - 1; j++)
            if (pData[j] > pData[j + 1]) {
                int temp = pData[j];
                pData[j] = pData[j + 1];
                pData[j + 1] = temp;
            }
}

// implement selection sort
// extraMemoryAllocated counts bytes of extra memory allocated
void selectionSort(int* pData, int n) {
    int i, j, minimum;
    for (i = 0; i < n - 1; i++) {
        minimum = i;
        for (j = i + 1; j < n; j++)
            if (pData[j] < pData[minimum])
                minimum = j;
        int temp = pData[minimum];

        pData[minimum] = pData[i];
        pData[i] = temp;
    }
}

// parses input file to an integer array
int parseData(char *inputFileName, int **ppData) {
    FILE* inFile = fopen(inputFileName,"r");
    int dataSz = 0;
    *ppData = NULL;
    if (inFile) {
        fscanf(inFile,"%d\n",&dataSz);
        *ppData = (int *)malloc(sizeof(int) * dataSz);
        if (*ppData) {
            for (int i=0;i<dataSz;++i) {
                fscanf(inFile,"%d\n",&((*ppData)[i]));
            }
        }
    }
    fclose(inFile);
    return dataSz;
}



// prints first and last 100 items in the data array
void printArray(int pData[], int dataSz)
{
    int i, sz = dataSz - 100;
    printf("\tData:\n\t");
    for (i = 0;i < 100; ++i)
    {
        printf("%d ",pData[i]);
    }
    printf("\n\t");

    for (i = sz;i < dataSz; ++i)
    {
        printf("%d ",pData[i]);
    }
    printf("\n\n");
}

int main(void)
{
    clock_t start, end;
    int i;
    double cpu_time_used;
    char* fileNames[] = {"input1.txt", "input2.txt", "input3.txt"};

    for (i=0;i<3;++i)
    {
        int *pDataSrc, *pDataCopy;
        int dataSz = parseData(fileNames[i], &pDataSrc);

        if (dataSz <= 0)
            continue;

        pDataCopy = (int *)malloc(sizeof(int)*dataSz);

        printf("---------------------------\n");
        printf("Dataset Size : %d\n",dataSz);
        printf("---------------------------\n");

        printf("Selection Sort:\n");
        memcpy(pDataCopy, pDataSrc, dataSz*sizeof(int));
        extraMemoryAllocated = 0;
        start = clock();
        selectionSort(pDataCopy, dataSz);
        end = clock();
        cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
        printf("\truntime\t\t\t: %.1lf\n",cpu_time_used);
        printf("\textra memory allocated\t: %d\n",extraMemoryAllocated);
        printArray(pDataCopy, dataSz);

        printf("Insertion Sort:\n");
        memcpy(pDataCopy, pDataSrc, dataSz*sizeof(int));
        extraMemoryAllocated = 0;
        start = clock();
        insertionSort(pDataCopy, dataSz);
        end = clock();
        cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
        printf("\truntime\t\t\t: %.1lf\n",cpu_time_used);
        printf("\textra memory allocated\t: %d\n",extraMemoryAllocated);
        printArray(pDataCopy, dataSz);

        printf("Bubble Sort:\n");
        memcpy(pDataCopy, pDataSrc, dataSz*sizeof(int));
        extraMemoryAllocated = 0;
        start = clock();
        bubbleSort(pDataCopy, dataSz);
        end = clock();
        cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
        printf("\truntime\t\t\t: %.1lf\n",cpu_time_used);
        printf("\textra memory allocated\t: %d\n",extraMemoryAllocated);
        printArray(pDataCopy, dataSz);

        printf("Merge Sort:\n");
        memcpy(pDataCopy, pDataSrc, dataSz*sizeof(int));
        extraMemoryAllocated = 0;
        start = clock();
        mergeSort(pDataCopy, 0, dataSz - 1);
        end = clock();
        cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
        printf("\truntime\t\t\t: %.1lf\n",cpu_time_used);
        printf("\textra memory allocated\t: %d\n",extraMemoryAllocated);
        printArray(pDataCopy, dataSz);

        free(pDataCopy);
        free(pDataSrc);
    }

}
