#ifndef READFILE_H
#define READFILE_H

#include <stdio.h>

typedef struct dataholder{
	int currposition;
	int root;
	int nextposition;
}dataholder;


typedef enum splash{
	PROCESSING_DONE,
}splash;

void dataupdater(dataholder* hold);

void retriever(FILE* fp, dataholder* dt);

int entry(BYTE*loadbuffer, int position);

#endif
