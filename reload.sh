#!/bin/bash
watch=$1
action=$2


eval $action &
pid=$!
inotifywait -q -m -e close_write "$watch" | while read line; do
	echo "-- Restarting --"
	kill $pid
	eval $action &
	pid=$!
done
