#!/bin/bash

for ((i=0;i<10;i=i+1))
do
	./nonblock_client &
done
