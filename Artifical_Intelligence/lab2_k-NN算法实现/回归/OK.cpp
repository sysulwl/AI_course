#include <stdio.h>
#define lie 9
main() 
{ 
	int i,j;
	FILE *fid; 
	int a[246][9];
	char str[256],str2,str3;
	fid=fopen("Dataset_train.csv","r");
	for(i=0; i<246; i++){
	fscanf(fid,"%256[^,]",&str);printf("%s\n",str);
	for(j=0; j<lie; j++){
	fscanf(fid,",%d",&a[i][j]);
	printf("%d\n",a[i][j]);}}
	for(i=0; i<246; i++){
	for(j=0; j<lie; j++){
	printf("%d ",a[i][j]);}
	printf("\n");}
}
