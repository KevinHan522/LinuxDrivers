#!/bin/sh
shopt -s extglob
module="trans"
device="trans"
mode="664"

#call insmod on module
/sbin/insmod ./$module.ko $* || exit 1

#remove any old nodes given to the device
rm -f /dev/${device}[0-9][0-9][0-9]

major=$(awk "\$2==\"$module\" {print \$1}" /proc/devices)

#make file node for every device 
#and give appropriate permissions
group="staff"
grep -q '^staff:' /etc/group || group="wheel"
count=0
for i in $major
do
	mknod /dev/${device}$i c $major $i
	chgrp $group /dev/${device}$(($major+$count))
	chmod $mode /dev/${device}$(($major+$count))
	count=$(($count+1))
done

