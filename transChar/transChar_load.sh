#!/bin/sh
shopt -s extglob
module="trans"
device="trans"
mode="664"

#call insmod on module
/sbin/insmod ./$module.ko $* || exit 1

#remove any old nodes given to the device
rm -f /dev/${device}*

major=$(awk "\$2==\"$module\" {print \$1}" /proc/devices)

#make file node for every device 
#and give appropriate permissions
group="staff"
grep -q '^staff:' /etc/group || group="wheel"
count=0
mknod /dev/${device}0 c $major 0
chgrp $group /dev/${device}$(($count))
chmod $mode /dev/${device}$(($count))
count=$(($count+1))
