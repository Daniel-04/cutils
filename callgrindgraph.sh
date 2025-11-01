#!/bin/sh

if [ "$#" -lt 1 ]; then
    echo "Usage: $0 program"
    exit 1
fi

callgrind_out=$(mktemp /tmp/callgrind.XXXXXX.out)
image="${callgrind_out%.out}.svg"

valgrind --tool=callgrind --callgrind-out-file="$callgrind_out" -- "$@"
gprof2dot -f callgrind "$callgrind_out" | dot -Tsvg -o "$image"

if command -v xdg-open >/dev/null 2>&1; then
    xdg-open "$image"
else
    echo "Profile image generated at: $image"
fi
