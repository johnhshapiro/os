#! /bin/bash

for i in {1..5}
do
    echo "Process $$ $i"
    sleep 1
done

exit 5
