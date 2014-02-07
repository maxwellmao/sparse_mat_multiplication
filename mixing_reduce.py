#!/usr/bin/env python2.6
import os, sys


def get_mixing(s10,s70,s1070):
	total=s10+s70+s1070
	s10/=total
	s1070/=2*total
	s70/=total
	a10=s10+s1070
	a70=s70+s1070
	mixing=(s10+s70-a10*a10-a70*a70)/(1-a10*a10-a70*a70)
	print 'Mixing:%s' % mixing


mixing=dict()
for line in sys.stdin:
	item=line.strip().split()
	edge=mixing.get('\t'.join(item[0:2]), [0.0, 0])
	edge[0]+=float(item[2])
	edge[1]+=int(item[3])
	mixing['\t'.join(item[0:2])]=edge

print '\n'.join(['\t'.join([str(k), str(v[0]), str(v[1])]) for k,v in mixing.items()])
get_mixing(mixing['1\t1'][0], mixing['7\t7'][0], mixing['1\t7'][0])
