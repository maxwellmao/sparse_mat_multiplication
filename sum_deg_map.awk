#!/bin/awk -f
{
	if(NF==3)
	{
		print $1":"$2"\t"$3
		print $2":"$1"\t"$3
	}
}
