#!/bin/bash

for REGION in cmsdijet cmsdijetCRmiddle cmsdijetCRhigh; do
	for MZPRIME in 2100 3100 4100; do
		for MDARK_RINV in 1_03 20_0 20_03 20_07 100_03; do
				python getResonanceShapes.py -i inputs/input_shapes_svj_${MDARK_RINV}_peak_${REGION}.py -o ResonanceShapes_svj_13TeV_${MDARK_RINV}_peak_${REGION}.root -f svj --massrange 1500 5100 100
				python getResonanceShapes.py -i inputs/input_shapes_svj_${MDARK_RINV}_peak_${REGION}.py -o ResonanceShapes_svj_13TeV_${MDARK_RINV}_peak_${REGION}_test${MZPRIME}.root -f svj --massrange 1500 5100 100 --test $MZPRIME
		done
	done
done
