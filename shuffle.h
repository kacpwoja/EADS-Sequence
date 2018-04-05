#ifndef SHUFFLE
#define SHUFFLE

#include "sequence.h"

template <typename Key, typename Info>
Sequence<Key, Info> shuffle( const Sequence<Key, Info> &S1, int start1, int len1,
                             const Sequence<Key, Info> &S2, int start2, int len2, int repeat)
{
	if( start1 < 0 || start2 < 0 || len1 < 0 || len2 < 0 || repeat < 1 )
		return Sequence<Key, Info>();

	//Creating an output sequence, integers to store the current index being copied
	Sequence<Key, Info> outseq;
	int index1 = start1, index2 = start2;
	int size1 = S1.length(), size2 = S2.length();
	//Declaring temporary Key and Info to store the data being copied
	Key tkey = Key();
	Info tinfo = Info();
	//Copyting elements
	for( ; repeat > 0; repeat-- )
	{
		for( int i = 0; index1 < size1 && i < len1; i++ )
		{
			if( S1.getNode( index1, tkey, tinfo ) )
				outseq.pushBack( tkey, tinfo );
			index1++;
		}
		for( int i = 0; index2 < size2 && i < len2; i++ )
		{
			if( S2.getNode( index2, tkey, tinfo ) )
				outseq.pushBack( tkey, tinfo );
			index2++;
		}
	}
	//Returning the created sequence
	return outseq;
}

#endif