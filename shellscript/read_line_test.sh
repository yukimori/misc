#!/bin/bash
 
cnt=0
while read line
do
    cnt=`expr $cnt + 1`
    echo "LINE $cnt : $line"
done <<EOF
ABC DEF GHI JKL MNO PQR STU VWX YZA
BCD EFG HIJ KLM NOP QRS TUV WXY ZAB
CDE FGH IJK LMN OPQ RST UVW XYZ ABC
EOF

cnt=0
cat ./test.txt | while read line
do
    cnt=`expr $cnt + 1`
    echo "LINE $cnt : $line"
done

DATA=`cat ./test.txt`
 
cnt=0
while read line
do
    cnt=`expr $cnt + 1`
    echo "LINE $cnt : $line"
done <<EOF
$DATA
EOF

cnt=0
while read line
do
    cnt=`expr $cnt + 1`
    echo "LINE $cnt : $line"
done < ./test.txt

DATA=`cat ./test.txt`

echo 
echo "----------- OH-MY-GOT -----------"
cnt=0
while read line
do
    cnt=`expr $cnt + 1`
    echo "LINE $cnt : $line"
done <<OH-MY-GOT
$DATA
OH-MY-GOT
 
echo
echo "----------- !!! -----------"
cnt=0
while read line
do
    cnt=`expr $cnt + 1`
    echo "LINE $cnt : $line"
done <<!!!
$DATA
!!!
 
echo
echo "----------- %%% -----------"
cnt=0
while read line
do
    cnt=`expr $cnt + 1`
    echo "LINE $cnt : $line"
done <<%%%
$DATA
%%%
