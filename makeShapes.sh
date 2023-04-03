#!/bin/bash

for REGION in cmsdijet cmsdijet_jesUp cmsdijet_jesDown cmsdijet_jerUp cmsdijet_jerDown cmsdijetCRmiddle cmsdijetCRhigh; do
	OUTPUTS=()
	for SHAPE in inputs/input_shapes_svj_*_${REGION}.py; do
		SUFFIX=$(echo $SHAPE | cut -d'_' -f4-6)
		ONAME=ResonanceShapes_svj_13TeV_${SUFFIX}_${REGION}.root
		python getResonanceShapes.py -i $SHAPE -o ${ONAME} -f svj -x ${SUFFIX} --massrange 1500 5100 100 --fineBinning
		OUTPUTS+=($ONAME)
	done
	hadd ResonanceShapes_svj_13TeV_${REGION}.root ${OUTPUTS[@]}
done

