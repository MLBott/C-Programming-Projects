
#include	<stdlib.h>
#include	<stdio.h>

const int	LINE_LEN	= 256;
const int	MIN_LENGTH	= 2;
const int	MAX_LENGTH	= 16;


//  PURPOSE:  To ask the user to enter an integer between 'MIN_LENGTH' and
//	'max'.  Repeated asks user until such an integer has been entered.
//	Returns entered integer.
int		getLength	(int	max
				)
{
  int	toReturn;
  char	line[LINE_LEN];
	int conditional = 1;
  // YOUR CODE HERE
  while (conditional == 1)
  {
  	printf("Enter an integer between %d and %d ", MIN_LENGTH, MAX_LENGTH);
	  scanf("%d", &toReturn);
	  if (toReturn > MIN_LENGTH && toReturn < MAX_LENGTH)
	 	{
	    conditional = 0;
	 	}	
	 	else
	 	{
	 		conditional = 1;
		}
  	
  }
	return(toReturn);
}



//  PURPOSE:  To create an array on integers on the heap of length 'length',
//	and let user enter each integer.  Returns array.
int*		createArray	(int	length
				)
{
  int*	array	= (int*)calloc(length,sizeof(int));
  int	i;
  char	line[LINE_LEN];

  // YOUR CODE HERE
	for (i = 0; i < length; i++)
	{
		//printf("Enter an integer for the array: ");
	
		scanf("%d", &array[i]);
	}

  return(array);
}


//  PURPOSE:  To iterate over the 'length' integers of
//	'array', and set '*lowest1stPtr' to the lowest integer and set
//	'lowest2ndPtr' equal to the second lowest integer.  (They may be the
//	 same number if the lowest appears twice.)  If the lowest does appear
//	twice then it returns '1', otherwise it returns '0'.
int		areLowestEqual	(const int*	array,
				 int		length,
				 int*		lowest1stPtr,
				 int*		lowest2ndPtr
				)
{
  int	i;

  // YOUR CODE HERE
	int low = array[0];
	int secLow = array[1];
	for (i = 0; i < length; i++)
	{
		if (array[i] < low)
		{
			low = array[i];
			lowest1stPtr = &low;
		}
		if (i > 0 && array[i - 1] < secLow && secLow != low)
		{
			secLow = array[i - 1];
			lowest2ndPtr = &secLow;
		}
	}
	
	
}


int		main		()
{
  int		length	= getLength(MAX_LENGTH);
  int*		array	= createArray(length);
  int		lowest;
  int		secondLowest;
  int		areEqual= areLowestEqual(array,length,&lowest,&secondLowest);

  printf("The 1st lowest is: %d\n"
         "The 2nd lowest is: %d\n"
	 "They %sare equal.\n",
	 lowest,secondLowest,
	 areEqual ? "" : "not "
	);
  free(array);
}

