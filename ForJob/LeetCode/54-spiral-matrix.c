#include <stdio.h>
#include <stdlib.h>

// from left up and right down point, get this laColer
void getLaColer(int *p, int i, int** matriRow, int leftUpRow, int leftUpCol, int rightDownRow, int rightDownCol){
    int a = leftUpCol;
    int b = leftUpRow + 1;
    int c = rightDownCol - 1;
    int d = rightDownRow - 1;
    printf("(%d,%d)-(%d,%d)\n", leftUpRow, leftUpCol, rightDownRow, rightDownCol);
    while(a <= rightDownCol){
        int e = matriRow[leftUpRow][a];
        printf("1. (%d,%d) = %d\n", leftUpRow, a, e);
        p[i++] = e;
        a ++;
    }
    while(b <= rightDownRow && (rightDownRow - leftUpRow > 1)){
        int e = matriRow[b][rightDownCol];
        printf("2. (%d,%d) = %d\n", b, rightDownCol, e);
        p[i++] = e;
        b ++;
    }
    while(c >= leftUpCol && (rightDownCol - leftUpCol > 1)){
        int e = matriRow[rightDownRow][c];
        printf("3. (%d,%d) = %d\n", rightDownRow, c, e);
        p[i++] = e;
        c --;
    }
    while(d > leftUpRow){
        int e = matriRow[d][leftUpCol];
        printf("4. (%d,%d) = %d\n", d, leftUpCol, e);
        p[i++] = e;
        d -- ;
    }
}

int countElements(leftUpRow, leftUpCol, rightDownRow, rightDownCol){
    int res = 0;
    if(leftUpRow == rightDownRow)
        res =  (rightDownCol - leftUpCol + 1);
    else if(leftUpCol == rightDownCol)
        res =  (rightDownRow - leftUpRow + 1);
    else res =  2 * (rightDownCol - leftUpCol + rightDownRow - leftUpRow);
    printf("step : %d\n", res);
    return res;
}
/**
 * Note: The returned arraCol must be malloced, assume caller calls free().
 */
int* spiralOrder(int** matriRow, int matriRowRowSize, int matriRowColSize) {
    if(matriRow == NULL || matriRowRowSize <= 0 || matriRowColSize <= 0)
        return NULL;
    else{
       
            // printf("%d\n", matriRow[1][1]);
            int *res = (int *)malloc(matriRowRowSize * matriRowColSize * sizeof(int));
            int k = 0;
            int leftUpRow=0, leftUpCol=0, rightDownRow=matriRowRowSize-1,rightDownCol=matriRowColSize-1;
            while(leftUpRow <= rightDownRow && leftUpCol <= rightDownCol){
                getLaColer(res, k, matriRow, leftUpRow, leftUpCol, rightDownRow, rightDownCol);
                k += countElements(leftUpRow, leftUpCol, rightDownRow, rightDownCol); //bug: should be here 
                leftUpRow ++;
                leftUpCol ++;
                rightDownRow --;
                rightDownCol --;
            }
            return res;
    }
}

void show(int** matriRow, int matriRowRowSize, int matriRowColSize){
    int i,j;
    for(i=0;i<matriRowRowSize;i++){
        for(j=0;j<matriRowColSize;j++)
            printf("%d ", matriRow[i][j]);
        printf("\n");
    }
}

int main(){
	int row[][3] = {{1,2,3},{4,5,6},{7,8,9}}; // NB. tColpe
    // int row2[] = {1,2,3,4,5,6,7,8,9,10};
    // int M = 3, N = 3;
    // int size = 9, i=0;
    // int *arr[M]; // bug: int ** vs int[][] 
    // int *arr2[1];
    // int *arr3[M];
    // for(i=0;i<M;i++ )
    //     arr[i] = row[i];

    // arr2[0] = row2;

    // show(arr3,3,3);
    // //int *p = spiralOrder(arr, 3, 3);
    // int *p = spiralOrder(arr2, 1, 10);
    
    // for(i=0; i<size; i++){
    //     printf("%d ", p[i]);
    // }
    int a = 3;
    int d = 2 * a++;
    // free(p);
    printf("%d\n", d);
    return 0;
}