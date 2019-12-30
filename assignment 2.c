/*-------------------------------------------------------------------------*
 *---									---*
 *---		floatLessThan.c						---*
 *---									---*
 *---	    This file compares with less-than two 32-bit IEEE floating 	---*
 *---	point numbers with integer operations.  Does not handle 'NaN'	---*
 *---	properly.							---*
 *---									---*
 *---	----	----	----	----	----	----	----	----	---*
 *---									---*
 *---	Version 1.0		2019 June 26		Joseph Phillips	---*
 *---									---*
 *-------------------------------------------------------------------------*/

#include	<stdlib.h>
#include	<stdio.h>
#include	<float.h>

const int	SIGN_MASK	= 0x80000000;

const int	EXPONENT_MASK	= 0x7F800000;

const int	MANTISSA_MASK	= 0x007FFFFF;


//  PURPOSE:  To use the masks and 'u' to determine if 'f' is zero.  Returns
//  	'1' if 'f' is '+0.0' or '-0.0', or returns '0' otherwise.
int		isZero		(float		f
				)
{
  unsigned int	u	= *(unsigned int*)&f;

  if  ( (u & (EXPONENT_MASK | MANTISSA_MASK) ) == 0x0 )
   return(1);

  return(0);
}


//  PURPOSE:  To use the masks and 'u' to determine if 'f' is positive.
//	Returns '1' if 'f' is positive, or '0' if it is
//	negative.
int		isPositive	(float		f
				)
{
  unsigned int	u	= *(unsigned int*)&f;

  //  YOUR CODE HERE
	if ((u & (SIGN_MASK)) == 0x0 )
		return(1);
		
	return(0);
}



//  PURPOSE:  To use the masks to determine if &lhs& is less than &rhs&.
//	Assumes both are positive.  Returns &1& if it is or &0& otherwise.
int		isLessThanForPositives
				(float		lhs,
				 float		rhs
				)
{
  unsigned int	lhsAsInt	= *(unsigned int*)&lhs;
  unsigned int	rhsAsInt	= *(unsigned int*)&rhs;
  
  
  if (lhsAsInt == rhsAsInt)
		return(0);	

  //  If the exponent of LHS is less than that of RHS, return 1
	if ((lhsAsInt & (EXPONENT_MASK)) < (rhsAsInt & (EXPONENT_MASK)))
	{
		return(1);
	}
  //  If the exponent of LHS is greater than that of RHS, return 0
	else if ((lhsAsInt & (EXPONENT_MASK)) > (rhsAsInt & (EXPONENT_MASK)))
	{
		return(0);
	}
  //  If you get here the exponents are equal, how would you use the mantissa?
	if ((lhsAsInt & (MANTISSA_MASK)) < (rhsAsInt & (MANTISSA_MASK)))
	{
  	return(1);
	}
  
  else if ((lhsAsInt & (MANTISSA_MASK)) >= (rhsAsInt & (MANTISSA_MASK)))
	{
  	return(0);
	}

}



//  PURPOSE:  To use the masks to determine if &lhs& is less than &rhs&.
//	Returns &1& if it is or &0& otherwise.
//	May only use isPositive() and isLessThanForPositives()
int		isLessThan	(float		lhs,
				 float		rhs
				)
{
	unsigned int	lhsAsInt	= *(unsigned int*)&lhs;
  unsigned int	rhsAsInt	= *(unsigned int*)&rhs;
	
	
	
	if (lhsAsInt == rhsAsInt)
		return(0);
	
	if (isZero(lhs))
	{
		if (isZero(rhs))
			return(0);
		else if (isPositive(rhs))
			return(1);
		else if (!isPositive(rhs))
			return(0);	
	}
	
	if (isZero(rhs))
	{
		if (isZero(lhs))
			return(0);
		if (isPositive(lhs))
			return(0);
		else if (!isPositive(lhs))
			return(1);
	}
	
	if (isPositive(lhs) && isPositive(rhs))
	{
		if (isLessThanForPositives(lhs, rhs))
			return(1);
		
		return(0);	
	}
	
	if (!isPositive(lhs) && !isPositive(rhs))
	{
		if (!isLessThanForPositives(lhs, rhs))
			return(1);
			
		return(0);
	}
	
	if (!isPositive(lhs) && isPositive(rhs))
		return(1);
	if (isPositive(lhs) && !isPositive(rhs))
		return(0);
	
		
	
	
  //  Suggestion:
  //  (1) Handle when either is zero

  //  (2) Handle when they have different signs

  //  (3) Handle when they have the same sign

}



//  PURPOSE:  To run the less-than comparison program.  Ignores parameters.
//	Returns &EXIT_SUCCESS& to OS.
int		main		()
{
  float		TEST_ARRAY[]	= { -FLT_MAX,
				    -1e+10
				    -1.0
				    -1e-10,
				    -FLT_MIN,
				    -0.0,
				    +0.0,
				    +FLT_MIN,
				    +1e-10,
				    +1.0,
				    +1e+10,
				    +FLT_MAX
				  };
  const int	TEST_ARRAY_LEN	= sizeof(TEST_ARRAY) / sizeof(float);
  int		i;
  int		j;

  for  (i = 0;  i < TEST_ARRAY_LEN;  i++)
  {
    float	lhs	= TEST_ARRAY[i];

    for  (j = 0;  j < TEST_ARRAY_LEN;  j++)
    {
      float	rhs	= TEST_ARRAY[j];
      int	you	= isLessThan(lhs,rhs);
      int	hardware= (lhs < rhs);
      printf("%+12g < %+12g?\tYou: %5s\tHardware: %5s\t%s\n",
	     lhs,rhs,
	     (you ? "true" : "false"),
	     (hardware ? "true" : "false"),
	     ( (you == hardware) ? "yay!" : "Ruh-roh!" )
	    );
    }

  }

  return(EXIT_SUCCESS);
}
