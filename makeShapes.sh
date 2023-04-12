#!/bin/bash

for REGION in cmsdijet cmsdijetCRmiddle cmsdijetCRhigh; do
	for SYST in "" _jesUp _jesDown _jerUp _jerDown; do
		OUTPUTS=()
		for SHAPE in inputs/input_shapes_svj_*_${REGION}${SYST}.py; do
			SUFFIX=$(echo $SHAPE | cut -d'_' -f4-6)
			ONAME=ResonanceShapes_svj_13TeV_${SUFFIX}_${REGION}${SYST}.root
			python getResonanceShapes.py -i $SHAPE -o ${ONAME} -f svj -x ${SUFFIX} --massrange 1500 5100 100 --fineBinning
			OUTPUTS+=($ONAME)
		done
		hadd ResonanceShapes_svj_13TeV_${REGION}${SYST}.root ${OUTPUTS[@]}
	done
done

