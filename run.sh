#!/bin/bash

print_usage() {
    echo 'usage: $0 <arg>'
    echo 'arg:'
    echo '    0 = build only'
    echo '    1 = build and run'
    exit 1
}

if [ "$#" -ne 1 ] || \
   [ "$1" != "0" ] && [ "$1" != "1" ]; then
    print_usage
fi

PURPLE='\033[0;35m'
NC='\033[0m'
print () {
    echo -n -e ${PURPLE}
    echo -n "> "$1
    echo -e ${NC}
}
print_and_run () {
    print "$1"

    cmd=$1" || exit 1"
    eval $cmd
}

print_and_run "mkdir -p build"
print_and_run "cd build"
print_and_run "cmake .."
print_and_run "cmake --build ."

if [ "$1" == "1" ]; then
    print_and_run "cd bin"
    print_and_run "./test_darnel.exe"
fi

print "done"
