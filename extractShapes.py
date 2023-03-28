#!/usr/bin/env python

from argparse import ArgumentParser
import numpy as np
from collections import defaultdict

def main():
    # usage description
    usage = "Example: ./extractShapes.py -i InputShapes_RSGqq_PU30_Spring15.root"

    # input parameters
    parser = ArgumentParser(description='Script extracting resonance shapes from an input ROOT file and printing them in a format used by the interpolation code',epilog=usage)

    parser.add_argument("-i", "--input_file", dest="input_file", required=True,
                        help="Input file",
                        metavar="INPUT_FILE")

    parser.add_argument("-d", "--dir", dest="dir",
                        default='',
                        help="Path to TDirectory containing histograms (This parameter is optional (default: %(default)s)",
                        metavar="DIR")

    parser.add_argument("--debug", dest="debug", default=False, action="store_true", help="Debug printout")

    args = parser.parse_args()

    shapes = defaultdict(dict)
    binxcenters = []

    # import ROOT stuff
    from ROOT import TFile, TH1F, TH1D
    # open input file
    input_file = TFile.Open(args.input_file)

    directory = input_file
    if args.dir != '':
        directory = input_file.Get(args.dir)

    # get the number of histograms
    nEntries = directory.GetListOfKeys().GetEntries()

    # loop over histograms in the input ROOT file
    for h in range(0, nEntries):
        hName = directory.GetListOfKeys()[h].GetName()
        if "widejetmassrel" not in hName: continue
        mZprime = int(hName.split('_')[2])
        param_region = '_'.join(hName.split('_')[3:])
        param_region = param_region.replace(".","")

        if args.debug: print "Extracting shapes for m =", mZprime, "GeV for", param_region, "..."

        histo = directory.Get(hName)

        bincontents = []

        for i in range(1,histo.GetNbinsX()+1):
            bincontents.append(histo.GetBinContent(i))
            if len(binxcenters) < histo.GetNbinsX():
                binxcenters.append(histo.GetBinCenter(i))

        normbincontents = np.array(bincontents)
        normbincontents = normbincontents/np.sum(normbincontents)

        shapes[param_region][mZprime] = normbincontents.tolist()

    for param_region, shape in shapes.iteritems():
        with open("inputs/input_shapes_svj_{}.py".format(param_region),'w') as ofile:
            ofile.write("shapes = "+repr(shape))
            ofile.write("\n\n")
            ofile.write("binxcenters = "+repr(binxcenters))

if __name__ == '__main__':
    main()
