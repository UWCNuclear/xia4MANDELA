#!/bin/bash


SCOPE=xia4ids
CONF=conf/config_mandela
CAL=cal/first.cal
DATADIR=./raw
SCOPE2=./histo_ldf


for (( RUN=0; RUN<=88; RUN++ )) do

	if [ $RUN -lt 10 ]; then
		if [ -e $DATADIR/run_00${RUN}.ldf ]
		then
			$SCOPE $CONF $CAL <<echo
			${RUN}
			${RUN}
echo

			$SCOPE2 Run00${RUN}.root
                fi
        elif [ $RUN -lt 100 ]; then
                if [ -e $DATADIR/run_0${RUN}.ldf ]
                then
			$SCOPE $CONF $CAL <<echo
			${RUN}
			${RUN}
echo
			$SCOPE2 Run0${RUN}.root			
                fi
        else
                if [ -e $DATADIR/run_${RUN}.ldf ]
                then
			$SCOPE $CONF $CAL <<echo
			${RUN}
			${RUN}
echo
			$SCOPE2 Run${RUN}.root
                fi
	fi 
				
done

mv log*.txt logs/
#mv histo_*.root histos/
#gadd -f histo_Sum.root histos/histo_*.root
