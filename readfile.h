#ifndef READFILE_H
#define READFILE_H

#include <stdio.h>

//>cl modsam1.c readfile.c /link ole32.lib user32.lib mmdevapi.lib

typedef struct dataholder{
	int currposition;
	int root;
	int nextposition;
}dataholder;

UINT32* data_cave;

UINT32* modsam_entry;


typedef enum splash{
	PROCESSING_DONE,
}splash;

void dataupdater(dataholder* hold);

void retriever(UINT32* loadbuffer ,FILE* fp, dataholder* dt);

int entry(BYTE*loadbuffer, int position, UINT32 datax);

void fillbuffer(UINT32* loadbuffer,  UINT32* data_cave, dataholder* dt);

#endif
