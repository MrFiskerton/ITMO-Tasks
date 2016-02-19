#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
	int n;
	scanf("%d", &n);
    n++;

    int i,j;

    int **data = (int**)malloc(n*sizeof(int*));
    for( i = 0; i < n; i++) {
        data[i] = (int*)malloc(n*sizeof(int));
    }

   	for( i = 0; i < n; i++){
   		for( j = i; j < n; j++){
   			data[i][j] = data[j][i] = i*j;
   		}
   	}

   	int x1,y1;
   	int x2,y2;
   	scanf("%d", &x1);
   	while( x1 != 0 ){
   		scanf("%d%d%d", &y1, &x2, &y2);

   		char format[5];
   		int t = data[x2][y2];
   		char ln = 1;
   		while( t != 0 ){
   			ln++;
   			t /= 10;
  	 	}
  	 	sprintf(format, "%c%d%c", '%', ln, 'd');

   		for( i = x1; i <= x2; i++){
   			for( j = y1; j <= y2; j++){
   				printf( format, data[i][j] );
   			}
   			printf("\n");
   		}
   		scanf("%d", &x1);
   	}

   	for( i = 0; i < n; i++) {
        free(data[i]);
    }
    free(data);
   	return 0;
}
