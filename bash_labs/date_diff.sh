#!/bin/bash
#lab2_1
read m1 y1 m2 y2

if [[ $m1 -lt 0 ]] || [[ $y1 -lt 0 ]] || [[ $m2 -lt 0 ]] || [[ $y2 -lt 0 ]]
  then
  echo "No negative numbers please" 
elif [[ $m1 -gt 12 || $m2 -gt 12 || $m1 -eq 0 || $m2 -eq 0 ]]
  then
  echo "Wrong month format"
elif [[ $m1 -gt $m2 || $y1 -gt $y2 ]]
  then
  echo "date1 is bigger than date2"
else
  m=`expr $m2 - $m1`
  y=`expr $y2 - $y1`
  echo "$y years and $m months"   
fi




