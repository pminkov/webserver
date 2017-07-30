#!/bin/bash

make clean
make server
make client

./server &
SID=$!

sleep 1 

PASS=true
if ! ./client /static/exampl2e_org.html | grep "font-family";  then
  echo "bad request"
  PASS=false
fi

if $PASS; then
  echo "PASSED"
else
  echo "FAILED"
fi

kill -9 $SID

