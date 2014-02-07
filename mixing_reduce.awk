#!/bin/awk -f
{
	a[$1"\t"$2]+=$3
	b[$1"\t"$2]+=$4
}
END{
	for(i in a)print i"\t"a[i]"\t"b[i]
}
