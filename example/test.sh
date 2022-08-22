#!/bin/bash
cd $(dirname $0)
OUTPUT=$(./main)
TRUTH=$(cat ./truth)

if test "$OUTPUT" = "$TRUTH"; then
    echo "OK"
fi