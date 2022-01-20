/* ======================================================
SFile: SystemIO.h
SDate: 2022.01.19.
SRevision: S
SCreator: Gergely Zara
SNotice: S
======================================================*/

#include <stdio.h>

void* ReadFileIntoBuffer(void* Data, char* FilePath, size_t* DataSize)
{
	size_t UnitSize = sizeof(unsigned long long);
	//size_t DataSize = 0;
	FILE* File; 

	if( (File = fopen( FilePath, "r")) == NULL)
 	{
    		printf("Could not open file");
    		exit(-1);
 	}

	fseek(File, 0, SEEK_END);
	*DataSize = ftell(File);
	rewind(File);

	if ( (Data = malloc(*DataSize * UnitSize)) == NULL )
	{
		printf("Could not allocate memory");
    	exit(-1);
	}

	fread(Data, UnitSize, *DataSize, File);

	fclose(File);

	return Data;
}