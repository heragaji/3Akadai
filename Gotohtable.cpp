#include<stdio.h>
#include<stdlib.h>

int d = 5;
int e = 3;
int mismatch = -1;
int match = 1;
int min = -5000;

int max1(int a, int b, int c){
	if (a >= b && a >= c)
		return a;
	else if (b >= c)
		return b;
	else return c;
}
int max2(int a, int b){
	if (a >= b)
		return a;
	else return b;
}
int wmax(int a, int b, int c){
	if (a >= b && a >= c)
		return 0;
	else if (b >= c)
		return 1;
	else return -1;
}
int ismatch(char a, char b){
	if (a == b) return match;
	else return mismatch;
}

void printMatrix(int **M, int len1, int len2){
	for (int j = 0; j < len2; j++){
		for (int i = 0; i < len1; i++){
			printf("%d ", M[i][j]);
		}
		printf("\n");
	}
}
void Gotoh(char *A, char *B, int len1, int len2, int** M, int** Ix, int **Iy,int** tr){
	
	M[0][0] = 0;
	Ix[0][0] = min;
	Iy[0][0] = min;
	for (int i = 1; i < len1; i++){
		M[i][0] = min;
		Iy[i][0] = min;
		Ix[i][0] = M[0][0] - d - e*(i - 1);
		tr[i][0] = 1;
	}
	for (int j = 1; j < len2; j++){
		M[0][j] = min;
		Ix[0][j] = min;
		Iy[0][j] = M[0][0] - d - e*(j - 1);
		tr[0][j] = -1;
	}
	//‰Šú‰»
	
	for (int i = 1; i < len1; i++){
		for (int j = 1; j < len2; j++){
			M[i][j] = max1(M[i-1][j-1], Ix[i-1][j-1], Iy[i-1][j-1]) + ismatch(A[i - 1], B[j - 1]);
			Ix[i][j] = max1(M[i - 1][j] - d, Ix[i - 1][j] - e, Iy[i-1][j] - d);
			Iy[i][j] = max2(M[i][j - 1] - d, Iy[i][j - 1] - e);
			tr[i][j] = wmax(M[i][j], Ix[i][j], Iy[i][j]);
		}
	}
	
	return;

}
int main(){
	int size1, size2;
	size1 = 1;
	size2 = 1;
	FILE *fp;
	if ((fp = fopen("test1.txt", "r")) == NULL){
		printf("file open error!!\n");
		exit(EXIT_FAILURE);
	}
	while (fgetc(fp) != EOF){
		size1++;
	}
	char* A = (char *)malloc(sizeof(char)*size1);
	fclose(fp);
	if ((fp = fopen("test1.txt", "r")) == NULL){
		printf("file open error!!\n");
		exit(EXIT_FAILURE);
	}
	int i = 0;
	while (i<size1 - 1){
		A[i] = fgetc(fp);
		i++;
	}
	fclose(fp);
	if ((fp = fopen("test2.txt", "r")) == NULL){
		printf("file open error!!\n");
		exit(EXIT_FAILURE);
	}
	while (fgetc(fp) != EOF){
		size2++;
	}
	char* B = (char *)malloc(sizeof(char)*size2);
	fclose(fp);
	if ((fp = fopen("test2.txt", "r")) == NULL){
		printf("file open error!!\n");
		exit(EXIT_FAILURE);
	}
	i = 0;
	while (i<size2 - 1){
		B[i] = fgetc(fp);
		i++;
	}
	fclose(fp);
	int **M = (int**)malloc(sizeof(char*)* size1);
	for (int i = 0; i < size1; i++){
		M[i] = (int*)malloc(sizeof(char)*size2);
	}
	int **Ix = (int**)malloc(sizeof(int*)* size1);
	for (int i = 0; i < size1; i++){
		Ix[i] = (int*)malloc(sizeof(int)*size2);
	}
	int **Iy = (int**)malloc(sizeof(int*)* size1);
	for (int i = 0; i < size1; i++){
		Iy[i] = (int*)malloc(sizeof(int)*size2);
	}
	int **tr = (int**)malloc(sizeof(int*)* size1);
	for (int i = 0; i < size1; i++){
		tr[i] = (int*)malloc(sizeof(int)*size2);
	}
	Gotoh(A, B, size1, size2, M, Ix, Iy,tr);
	/*
	printf("M\n");
	printMatrix(M,size1,size2);
	printf("Ix\n");
	printMatrix(Ix, size1, size2);
	printf("Iy\n");
	printMatrix(Iy, size1, size2);
	*/
	i = size1-1;
	int j = size2-1;
	while (i!=0 || j!=0){
		if (tr[i][j] == 0){
			printf("%c - %c\n", A[i-1], B[j-1]);
			i--;
			j--;
			continue;
		}
		else if (tr[i][j] == 1){
			printf("%c - -\n", A[i-1]);
			i--;
			continue;
		}
		else if(tr[i][j]==-1){
			printf("- - %c\n", B[j-1]);
			j--;
			continue;
		}
		else{
			printf("tr[i][j] = %d\n", tr[i][j]);
		}
	}
	return 0;
}