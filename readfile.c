#include <stdio.h>
#include <windows.h>
#include "readfile.h"




void dataupdater(dataholder* hold){
	if(hold!=NULL){
		hold->nextposition = hold->nextposition + hold->root;
		printf("dataupdater value == %d", hold->nextposition);
	}
}


/*void toberead(){
	printf("current_position == %d\n", dt->currposition);
			printf("current_position_pointer == %p\n", &dt->currposition);
			 dataholder* dx = (dataholder*)0x00929438;
			 printf("dx_pointer_number_is == %p\n", dx);
			break;
}*/


void retriever(FILE* fp, dataholder* dt){
	UINT32 data;
	while(fscanf(fp, "%d", &data)!=EOF){
		printf("%d \n", data);
		if(dt->currposition == dt->nextposition){
			printf("new curr_position == %d\n", dt->currposition);
			dataupdater(dt);
			printf("new curr_position == %d\n", dt->currposition);

		}
			 dt->currposition++;
	}

	free(dt);
}


int entry(BYTE* loadbuffer,int position)
{

	printf("retrieving audio data...");

	dataholder* dt = (dataholder*)malloc(sizeof(dataholder));
	dt->currposition = 0;
	dt-> root = position;
	dt->nextposition = position;

	FILE *filepointer;
	
	filepointer = fopen("data.txt", "r");
	if(filepointer == NULL)
		printf("file not opened");

	retriever(filepointer, dt);

	fclose(filepointer);

	return PROCESSING_DONE;
}