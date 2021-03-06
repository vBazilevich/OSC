#!/bin/bash

FILE=numbers.txt

# Checking if file exists
if [ ! -f "$FILE" ] 
then
    echo "0" > $FILE
fi

while :
do
    # ACHTUNG!! Critical region starts here 
    # The smallest number after which I've noticed race condition is about 3000
    # Taking into account speed of modern computers, that is just a fraction of a second
 
    # Reading last number
    last_number=$(tail -n 1 < $FILE)

    # Computing next number
    next_number=$(( last_number + 1 ))

    echo $next_number >> $FILE
    
    # Critical region ends here
done
