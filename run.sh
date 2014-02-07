#!/bin/bash

#err(){
#	exit 1;
#}

pidList=()
declare -i finish=0

sampling=01

mat_sparse()
{
echo ${user}"-mult-${sampling}-"${part}
hadoop jar ~/hadoop/contrib/streaming/hadoop-streaming-1.0.0.jar -Dmapred.job.name="${user}-mult-${sampling}-${part}" -mapper "cat" -reducer "./mat_sparse" -file mat_sparse -input Adj-1070-part/${sampling}-indexing/part-000${part} -output Adj-1070-part/${sampling}-mult/${part} -numReduceTasks 8 -jobconf mapred.task.timeout=3600000 -jobconf mapred.reduce.tasks.speculative.execution=false
}

CheckSubPID()
{
finish=0
for pid in $@; 
do
	if [ -z "`ps aux | grep $pid | grep -v grep `" ]; then
		finish=finish+1
	fi  
done
}

function WaitChildProcess
{
if [ ${#pidList[@]} != 0 ]; then
	for ((;1;))
	do  
		CheckSubPID ${pidList[@]}
		if [ $finish = ${#pidList[@]} ]; then
			break
		fi
		sleep 60
	done
	unset pidList
	pidList=()
fi
}

check_finished()
{
	if [ -z "`ps aux | grep $1 | grep -v grep `" ]; then
		echo $1" has finished"
		return 1
	else
#		echo $1" has not finished"
		return 0
	fi
}

check_process_pool()
{
	for ((;1;))
	do
		declare -i i=0
#		echo "i="$i
		while [ $i -lt ${#pidList[@]} ];
		do
			check_finished ${pidList[$i]}
			# | read r
			r=$?
#			echo "result="$r
			if [ $r -eq 1 ]; then
				last=`expr ${#pidList[@]} - 1`
				pidList[$i]=${pidList[$last]}
				unset pidList[$last]
			else
				i=`expr $i + 1`
			fi
		done
		if [ ${#pidList[@]} -lt $standard ]; then
			break
		fi
		sleep 60
	done
}

declare -i standard=10
user=mwx
for((i=0;i<7;i++))
do
	if [ $i -lt 10 ];then
		part=0$i
	else
		part=$i
	fi
	mat_sparse &
#	pidList[${#pidList[@]}]=$!
#	echo "pids:"${#pidList[@]}
#	if [ ${#pidList[@]} -ge $standard ]; then
#		check_process_pool
#	fi
done
#WaitChildProcess
