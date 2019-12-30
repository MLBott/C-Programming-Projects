/*	
	cachelab
	Michael Bottom
*/

#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include "cachelab.h"
#include <sys/types.h> 
#include <sys/stat.h> 
#include <fcntl.h>
#include <unistd.h>
#include <math.h>

// globals
int line;
int hit_total= 0, miss_total= 0, eviction_total= 0;
int timeStamp;


struct State {
	int stamp;
	long long tag;
};

void printUsage()
{
	printf( "Usage: csim [-hv] -s <s> -E <E> -b <b> -t <tracefile>\n" );
}

int evictPresent(int numMod, struct State result[])
{
	int position = numMod * line;
	int i;
	for (i = 0; i < line; i++)
	{
		if(result[i + (numMod * line)].stamp == 0 )
		{
			return (i + (numMod * line)) ;}
		else if(result[i + (numMod * line)].stamp < result[position].stamp)
		{
			position=i+(numMod*line);
		}
	}
	eviction_total++;
	return position;
}

	
	// compute the number of tag bits
	
	// allocate the cache
	
	// zero out the cache
	
	// initialize the time variable
	
	// open the trace file
	

void CsimSimulate(char flag, long long address,  int markBits, int setBits, int blockBitsCsim, struct State result2[])
{
	int j;
	int evictPres;
	long long numBits;
	long long markSeq;
	long long maskBits;
	

	maskBits=((long long)pow(2, setBits))-1;
	numBits=((address) >> (blockBitsCsim))&maskBits;
	markSeq=(( long long) address) >> (setBits+blockBitsCsim);

	for (j = 0; j < line; j++)
	{
		if(markSeq == ((( long long) result2[j + (numBits*line)].tag) >> (setBits+blockBitsCsim)) && result2[j +(numBits*line)].stamp != 0 )
		{
			result2[j + (numBits*line)].stamp = timeStamp;
			hit_total++;
			timeStamp++;
			
			return;
		}
	}


	miss_total++;
	evictPres = evictPresent(numBits, result2);
	result2[evictPres].stamp = timeStamp;
	result2[evictPres].tag = address;
	timeStamp++;

	return;
}



int main( int argc, char * argv[] )
{
	// using getopt(), parse the command line arguments
	char * filename= NULL;
	int option;
	line= 0;
	int s_bits= 0, block_bits= 0, tag_bits= 0;
	FILE* traceFile_f;
	char scanned = ' ';
	timeStamp = 1;
	
#ifdef CHECK
	char verbose= 0;
#endif


	while ( (option= getopt( argc, argv, "hvs:E:b:t:" )) != -1 )
	{
		switch( option )
		{
		case 'h':
			printUsage();
			exit(EXIT_SUCCESS);
			break;
#ifdef CHECK
		case 'v':
			verbose = 1;
			break;
#endif
		case 's':
			s_bits= atoi( optarg );
			break;
		case 'E':
			line= atoi( optarg );
			break;
		case 'b':
			block_bits= atoi( optarg );
			break;
		case 't':
			filename= optarg;
			break;
		default:
			printf( "Unknown option encountered\n" );
			printUsage();
			exit(EXIT_FAILURE);
		}		
	}
	if ( s_bits == 0 || line == 0 || block_bits == 0 )
	{
		printf( "Value for cache parameter not passed on command line\n" );
		printUsage();
		exit(EXIT_FAILURE);
	}

	
	
	// read each line in the trace file
	//   if the line represents an instruction
	//     skip over it
	//   compute the set and tag bits
	//   if the data exists in the cache
	//     increment counter(s) and update the entry time
	//   else
	//     get the next free line in the set
	//     if no free line exists, evict a line using the LRU algorithm
	//     place the data in the cache and set the entry time
	//     increment counter(s)
	
	// close the file
	
	// free the cache


	char adjustInstrc = 'a';
	long long adjustMem= 0;
	int chunk = 0;
	int aggregate = (int)(pow(2, s_bits)*line);
	struct State cacheArray[aggregate];
	tag_bits = sizeof(long long) * 8 - (s_bits+block_bits);
	int fFile = open(filename, O_RDONLY);
	read(fFile, &scanned, 1);
	timeStamp = 1;
	int x;

	for (x = 0; x < aggregate; x++)
	{
		cacheArray[x].tag = 0;
		cacheArray[x].stamp = 0;
		
	}
	traceFile_f = fopen(filename, "r");
	while(fscanf(traceFile_f, " %c %llx,%d", &adjustInstrc, &adjustMem, &chunk) == 3)
	{
		if (adjustInstrc =='I')
		{
			continue;
		}
		else if(adjustInstrc =='M')
		{
			CsimSimulate(adjustInstrc, adjustMem, tag_bits, s_bits,block_bits, cacheArray);
			hit_total++;
		}
		else
			{CsimSimulate(adjustInstrc, adjustMem, tag_bits, s_bits,block_bits, cacheArray);}
	}
	
	printSummary( hit_total, miss_total, eviction_total );
	
    return 0;
}
