#!/bin/awk -f
BEGIN{
	last=""
	deg=0
	OFS="\t"
}
{
	if(last!="" && last!=$1)
	{
		split(last,a,":");
		print a[1], a[2], deg;
		deg=0;
	}
	last=$1
	deg+=$2
#	if($1=="100000:1437")
#	{
#		print $0
#	}
}
END{
	split(last, a, ":");
	print a[1], a[2], deg;
}
