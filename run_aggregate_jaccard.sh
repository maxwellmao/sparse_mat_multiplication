#!/bin/sh
sampling=01
hadoop dfs -rmr Adj-1070-part/${sampling}-mult-all
hadoop jar ~/hadoop/contrib/streaming/hadoop-streaming-1.0.0.jar -mapper "awk -f sum_deg_map.awk"  -reducer "awk -f sum_deg_reduce.awk" -jobconf map.output.key.field.separator=: -jobconf num.key.fields.for.partition=1 -file sum_deg_map.awk -file sum_deg_reduce.awk -numReduceTasks 80 -input Adj-1070-part/${sampling}-mult/* -output Adj-1070-part/${sampling}-mult-all
