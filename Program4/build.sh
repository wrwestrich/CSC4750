
#!/bin/bash

#the current working directory, spaces escaped
DIR=`printf "%q\n" "$(pwd)"`

clear
make -kj 4 $1 PROJECT_DIR="$DIR"
