#!/bin/sh
for d in $(find . -type d)
do
    NO_CUR=`ls -l "$d" | grep ^- | wc -l`
    echo -e "\nFiles in $d: $NO_CUR\n"
    echo -e "\nListing subdirectories in $d: \n----------------------------------------------------------------------"
    ls -l "$d" | grep ^d
    echo -e "\nListing files in $d: \n-----------------------------------------------------------------------"
    ls -l "$d" | grep ^-
done

