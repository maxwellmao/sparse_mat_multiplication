#!/bin/awk -f
BEGIN{
	OFS="\t"
}
{
	if(type=="reduce")
	{	
		a[$1]+=$2
	}
	else{
		a[$2]+=1
	}
}
END{
	for(i in a)
		print i, a[i]
}
