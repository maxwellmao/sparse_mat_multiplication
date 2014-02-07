#!/bin/usr/env python2.6
from __future__ import division
import sys, os
import getopt

fileInfo=[]
optlist, arg=getopt.getopt(sys.argv[1:], '', 'file=')
for opt in optlist:
	if opt[0].startswith('--file'):
		fp=open(opt[1])
		while True:
			lines=fp.readlines(100000)
			if not lines:
				break
			for line in lines:
				item=line.strip().split()
#				fileDict[int(item[-1])]=item[1:3]
				fileInfo.append([int(i) for i in item[1:3]])
		fp.close()

m_1010=0.0
#the no. of edges whose two ends are both 10
n_1010=0
m_1070=0.0
n_1070=0
m_7070=0.0
n_7070=0
for line in sys.stdin:
	item=line.strip().split()
	if len(item)==3:
		#sys.stderr.write('\t'.join([str(fileInfo[int(item[0])-1][0]), str(fileInfo[int(item[1])-1][0]), item[2]])+'\n')
		deg1=fileInfo[int(item[0])-1][0]
		deg2=fileInfo[int(item[1])-1][0]
		union=deg1+deg2-int(item[2])
		if deg1<int(item[2]) or deg2<int(item[2]) or union<=0:
			sys.stderr.write(line)
			sys.stderr.write(' '.join([item[0], item[1]])+'\n')
			sys.stderr.write('\t'.join([str(fileInfo[int(item[0])-1][0]), str(fileInfo[int(item[1])-1][0]), item[2]])+'\n')
			raise KeyError(line)
		else:
			jaccard=int(item[2])/union
			if fileInfo[int(item[0])-1][1]==1 and fileInfo[int(item[1])-1][1]==1:
				m_1010+=jaccard
				n_1010+=1
			elif fileInfo[int(item[0])-1][1]==7 and fileInfo[int(item[1])-1][1]==7:
				m_7070+=jaccard
				n_7070+=1
			else:
				m_1070+=jaccard
				n_1070+=1

print '\t'.join(['1', '1', str(m_1010), str(n_1010)])
print '\t'.join(['1', '7', str(m_1070), str(n_1070)])
print '\t'.join(['7', '7', str(m_7070), str(n_7070)])
