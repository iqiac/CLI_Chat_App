#!/bin/bash

echo "Press a key (q to quit):"
while true; do
    read -rsn1 key
    if [[ $key == "q" ]]; then
        echo "Exiting..."
        break
    fi
    printf "You pressed: %s\n" "$key"
done
