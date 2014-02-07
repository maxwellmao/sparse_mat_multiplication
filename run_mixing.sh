#!/bin/sh
part=01
hdfsPath=Adj-1070-part
truthPath=/data/streaming/data_process/file_1070
#hadoop jar ~/hadoop/contrib/streaming/hadoop-streaming-1.0.0.jar -Dmapred.job.name="mwx-mixing" -mapper "python2.6 mixing_map.py --file=${part}-info" -reducer "python2.6 mixing_reduce.py" -file mixing_map.py -file mixing_reduce.py -file ${truthPath}/${part}-info -input ${hdfsPath}/${part}-mult-all -output ${hdfsPath}/${part}-mixing

hdfsPath=Adj-1070-part-01
truthPath=/data/streaming/adsorption/result/01day
#hadoop jar ~/hadoop/contrib/streaming/hadoop-streaming-1.0.0.jar -Dmapred.job.name="mwx-mixing" -mapper "python2.6 mixing_map.py --file=${part}-info" -reducer "python2.6 mixing_reduce.py" -file mixing_map.py -file mixing_reduce.py -file ${truthPath}/${part}-info -input ${hdfsPath}/${part}-mult -output ${hdfsPath}/${part}-mixing &

hdfsPath=Adj-1070-part-01-03
#truthPath=/data/streaming/adsorption/result/01-03day
#hadoop jar ~/hadoop/contrib/streaming/hadoop-streaming-1.0.0.jar -Dmapred.job.name="mwx-mixing" -mapper "python2.6 mixing_map.py --file=${part}-info" -reducer "python2.6 mixing_reduce.py" -file mixing_map.py -file mixing_reduce.py -file ${truthPath}/${part}-info -input ${hdfsPath}/${part}-mult -output ${hdfsPath}/${part}-mixing &

hdfsPath=Adj-1070-part-01-07
truthPath=/data/streaming/adsorption/result/01-07day
hadoop jar ~/hadoop/contrib/streaming/hadoop-streaming-1.0.0.jar -Dmapred.job.name="mwx-mixing" -mapper "python2.6 mixing_map.py --file=${part}-info" -reducer "python2.6 mixing_reduce.py" -file mixing_map.py -file mixing_reduce.py -file ${truthPath}/${part}-info -input ${hdfsPath}/${part}-mult -output ${hdfsPath}/${part}-mixing
