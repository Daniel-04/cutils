#!/usr/bin/bash

if [ -z "$1" ]; then
    echo "$0 executable"
    exit 1
fi

rand_prefix=$RANDOM

# Set output filenames with the random prefix
perfdata="/tmp/${rand_prefix}_output.perfdata"
image="/tmp/${rand_prefix}_output.svg"

perf record -F max -g -o $perfdata -- "$@"
perf script -i $perfdata | c++filt | gprof2dot -f perf --show-samples | dot -Tsvg -o $image
xdg-open $image
