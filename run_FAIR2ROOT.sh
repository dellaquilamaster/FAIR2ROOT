#!/bin/bash

DATA_PATH="/mnt/md0/data/2018_TAUDEU_LNL/"

first_run=$1

if [ -z "$1" ]; then
  echo "Please type at least a valid run number"
  exit 1
fi

if [ -z "$2" ]; then
  last_run=$1
else
  last_run=$2
fi

if [ ! -z "$3" ]; then
  parallel_processes=$3
fi

for folder in $(ls ${DATA_PATH});
do
  re='^[0-9]+$'

  if ! [[ ${folder} =~ $re ]] ; then
       continue
  fi
    
    if [ -z $3 ]
    then
      if [ ${folder} -le ${last_run} ] && [ ${folder} -ge ${first_run} ] ;
      then
        echo "Unpacking file $run_name..."
        eval './exec_FAIR2ROOT.exe --run=${folder}'
      fi
    else
      if [ ${folder} -le ${last_run} ] && [ ${folder} -ge ${first_run} ] ;
      then
        echo "echo Unpacking file $run_name... && eval './exec_FAIR2ROOT.exe --run=${folder}'" >> parallel_runs.txt      
      fi
    
    fi
done

if [ ! -z "$3" ]; then
  parallel $parallel_processes < parallel_runs.txt
  rm -f parallel_runs.txt
fi
