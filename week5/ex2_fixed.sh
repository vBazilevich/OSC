#!/bin/bash

FILE=numbers.txt
LOCK="$FILE.lock"

# Checking if file exists
if [ ! -f "$FILE" ] 
then
    echo "0" > $FILE
fi

while :
do
    # Busy waiting until file is locked
    while [ -f "$LOCK" ]
    do
        sleep 1
    done

    ## Locking file
    ln $FILE $LOCK

    # ACHTUNG!! Critical regino starts here 
    # The smallest number after which I've noticed race condition is about 3000
    # Taking into account speed of modern computers, that is just a fraction of a second
 
    # Reading last number
    last_number=$(tail -n 1 < $FILE)

    # Computing next number
    next_number=$(( last_number + 1 ))

    echo $next_number >> $FILE
    
    # Critical region ends here

    # Removing lock
    rm $LOCK
done
