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


void retriever(UINT32* loadbuffer ,FILE* fp, dataholder* dt){
	UINT32 data;
	while(fscanf(fp, "%d", &data)!=EOF){
		*data_cave = data;
		printf("file in data_cavex ==> %d \n", *data_cave);
		/*if(dt->currposition == dt->nextposition){
			//printf("new curr_position == %d\n", dt->currposition);
			//dataupdater(dt);

		}*/
			 dt->currposition++;
			 data_cave++;
	}

	fillbuffer(loadbuffer, data_cave, dt);

}

void fillbuffer(UINT32* loadbuffer,  UINT32* data_cave, dataholder* dt){
	int new;

	if(dt->nextposition == 0){
		new = dt->root;
		for(int i = 0; i< new; i++){
			*loadbuffer++ = data_cave[i]; 
		}
	}else{
		new = dt->root * dt->nextposition;
		int x = new + dt->root;
		for(int i = new; i< x; i++){
			*loadbuffer++ = data_cave[i]; 
		}
	}
	
}


int entry(BYTE* loadbuffer,int position, UINT32 datax)
{
	modsam_entry = (UINT32*)loadbuffer;
	dataholder* dt =(dataholder*)malloc(sizeof(dataholder));
	dt->currposition = 0;
	dt-> root = datax;
	dt->nextposition = position;
	printf("buffer count ==> %d \n", datax);
	if(dt->nextposition != 0){
		printf("position != 0\n");
		fillbuffer(modsam_entry,data_cave, dt);
	}else{
		printf("position == 0\n");
		printf("retrieving audio data...\n");
		data_cave = (UINT32*)malloc(118500 * sizeof(UINT32));
		//data_cave = (UINT32*)calloc(118500, sizeof(UINT32));

		
		FILE *filepointer;
		filepointer = fopen("data.txt", "r");
		if(filepointer == NULL)
		printf("file not opened");


	retriever(modsam_entry,filepointer, dt);

	fclose(filepointer);
	}
	free(dt);
	free(data_cave);

	return PROCESSING_DONE;
}