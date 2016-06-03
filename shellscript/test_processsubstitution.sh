#!/bin/bash

a=()
a+=( "a" "b" )

cat <<EOF | while read LINE
test
EOF
do
	a+=( `echo c` )
	echo ${a[@]}
	break
done

echo ${a[@]}
