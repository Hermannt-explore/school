#!/bin/bash -e
lru="lru"
no_lru="no_lru"
clean="clean"
if [[ "$1" == "$lru" ]]
then
	gcc mmu_lru.c -o mmu_lru
	./mmu_lru BACKING_STORE.bin addresses.txt 

elif [[ "$1" == "$no_lru" ]]
then
	gcc mmu.c -o mmu
	./mmu BACKING_STORE.bin addresses.txt 
elif [[ "$1" == "$clean" ]]
then
	rm mmu
	rm mmu_lru 	
	rm output.csv
else
	echo "For phase one of project, type in (bash test.sh no_lru) ."
	echo "For phase two of project, type in (bash test.sh lru) ."
fi

