# DijetShapeInterpolator

## Instructions

```
cmsrel CMSSW_7_4_6
cd CMSSW_7_4_6/test
cmsenv

git clone git@github.com:CMSDIJET/DijetShapeInterpolator.git DijetShapeInterpolator

cd DijetShapeInterpolator

./getResonanceShapes.py -i input_shapes_qq_13TeV_PU20_Phys14.py -f qq \
--massrange 400 10000 100 -o ResonanceShapes_qq_13TeV_PU20_Phys14.root
```

For more command line options, run

```
./getResonanceShapes.py -h
```
