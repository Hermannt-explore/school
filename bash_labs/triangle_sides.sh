#!/bin/bash
read x
xs=0
t=0
flag=0
for (( y=0; y<$x; y++ ))
do
	if [[ flag -eq 1 ]]
	then
		break
	fi
	for (( z=0; z<$x; z++ ))
	do
		xs=`expr $x \* $x`
		t=`expr $(($y * $y)) + $(($z * $z))`
		if [[ xs -eq t ]]
		then	
			echo YES
			flag=1
		break
		fi
	done
	
done
if [[ xs -ne t ]]
then
	echo NO
fi



