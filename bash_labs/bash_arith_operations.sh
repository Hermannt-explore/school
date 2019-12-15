#!/bin/bash
#test expr, (()), let, incr


a=25
b=0
c=6

a=$((++a))
b=`expr $a + $b`
echo "$a and $b"

c=$(echo "scale=2; sqrt($a)" | bc)
echo $c
s="this is s a string"
sn=${s//is/ha}
echo $s
echo $sn
