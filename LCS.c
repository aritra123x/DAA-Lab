#include<stdio.h>
#include<string.h>
int max(int a, int b) {
    return (a > b) ? a : b;
}
int main() 
{
    char str1[100], str2[100];
    printf("Enter 1st string: ");
    scanf("%s", str1);
    printf("Enter 2nd string: ");
    scanf("%s", str2);   
    int m = strlen(str1), n = strlen(str2);
    int ar[m+1][n+1];
    for (int i = 0; i <= m; i++)
        ar[i][0] = 0;
    for (int i = 0; i <= n; i++)
        ar[0][i] = 0;
    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= n; j++) {
            if (str1[i-1] == str2[j-1])
                ar[i][j] = ar[i-1][j-1] + 1;
            else
                ar[i][j] = max(ar[i-1][j], ar[i][j-1]);
        }
    }
    int lcs_length = ar[m][n];
    char lcs[lcs_length + 1];
    lcs[lcs_length] = '\0';
	for(int i=0;i<=m;i++)
	{
		for(int j=0;j<=n;j++)
		printf("%d ",ar[i][j]);
		printf("\n");
	}
    int i = m, j = n, k = lcs_length - 1;
    while (i > 0 && j > 0) {
        if (str1[i-1] == str2[j-1]) {
            lcs[k--] = str1[i-1];
            i--; j--;
        }
        else if (ar[i-1][j] > ar[i][j-1])
            i--;
        else
            j--;
    }
    printf("LCS: %s\n", lcs);
    printf("LCS Length: %d\n", lcs_length);
    
    return 0;
}
