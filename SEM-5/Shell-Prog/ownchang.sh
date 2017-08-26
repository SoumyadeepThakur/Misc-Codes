#!/bin/sh
#part 1
chmod a+r --recursive ./CSE-44
echo "File read access granted to all users"
#part 2
chmod o-rwx --recursive ./CSE-44
echo "File read/write/exec access removed from users outside the group"
chmod ug+x --recursive ./CSE-44
chmod u+rw --recursive ./CSE-44
echo "File read/write/exec access granted to owner and exec acces granted to group members"

