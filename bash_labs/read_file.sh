#!/bin/bash

file1=$1
file2=$2
ID=$3
flag=0


if [[ -f $file1 ]] && [[ -f $file2 ]]
then
while read fname lname ID1
do
	
		if [[ "$3" == "$ID1" ]]
		then
			flag=1
			while read ID2 course grade
			do
				if [[ "$ID1" == "$ID2" ]]; then
					if [[ "$grade" == "P" ]] || [[ "$grade" == "F" ]]; then
					echo "$fname $lname has a grade of $grade in course $course"
				     	continue 
			         	fi
			     	 echo "$fname $lname has no grade in course $course"
				fi
			done < "$file2"
		fi
done < "$file1"
if [[ $flag -eq 0 ]]
then
	echo "No such ID"
fi

else
echo "files do not exist"
fi

		       
