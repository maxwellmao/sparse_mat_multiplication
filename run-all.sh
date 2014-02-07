#!/bin/sh

user=mwx
sampling=00-15
#hadoop jar ~/hadoop/contrib/streaming/hadoop-streaming-1.0.0.jar -Dmapred.job.name="${user}-mult-${sampling}" -mapper "./mat_sparse -m" -reducer "awk -f sum_deg_reduce.awk" -jobconf mapred.min.split.size=1099511627776 -file mat_sparse -file sum_deg_reduce.awk -input Adj-1070-part-01/${sampling}-indexing -output Adj-1070-part-01/${sampling}-mult -numReduceTasks 80 -jobconf mapred.task.timeout=7200000 -jobconf mapred.reduce.tasks.speculative.execution=false

hdfsPath=Adj-1070-all-parts/01-day
hadoop jar ~/hadoop/contrib/streaming/hadoop-streaming-1.0.0.jar -Dmapred.job.name="${user}-mult-${sampling}" -mapper "./mat_sparse -m" -reducer "awk -f sum_deg_reduce.awk" -jobconf mapred.min.split.size=1099511627776 -file mat_sparse -file sum_deg_reduce.awk -input ${hdfsPath}/${sampling}-indexing -output ${hdfsPath}/${sampling}-mult -numReduceTasks 1000 -jobconf mapred.task.timeout=7200000 -jobconf mapred.reduce.tasks.speculative.execution=false

hdfsPath=Adj-1070-part-01-07
#hadoop jar ~/hadoop/contrib/streaming/hadoop-streaming-1.0.0.jar -Dmapred.job.name="${user}-mult-${sampling}" -mapper "./mat_sparse -m" -reducer "awk -f sum_deg_reduce.awk" -jobconf mapred.min.split.size=1099511627776 -file mat_sparse -file sum_deg_reduce.awk -input ${hdfsPath}/${sampling}-indexing -output ${hdfsPath}/${sampling}-mult -numReduceTasks 80 -jobconf mapred.task.timeout=7200000 -jobconf mapred.reduce.tasks.speculative.execution=false
