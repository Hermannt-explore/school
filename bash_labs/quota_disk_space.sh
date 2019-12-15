#!/bin/bash
eclare -a array
quota=`quota -v`
quota=${quota##*: }
quota=${quota%% MB*}
array=($quota)
echo "You used ${array[0]} of ${array[2]} MB"
