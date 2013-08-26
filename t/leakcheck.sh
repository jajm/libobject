#!/bin/sh

dir=$(dirname $0)

for file in `ls $dir/*.t`; do
	output=$(libtool --mode=execute valgrind --leak-check=full --error-exitcode=2 ${file} 2>&1)
	exitcode=$?
	echo -n "$(basename ${file}) ... "
	if [ $exitcode -eq 2 ]; then
		echo "Leaks detected !!"
	else
		echo "No leaks detected."
	fi
done


