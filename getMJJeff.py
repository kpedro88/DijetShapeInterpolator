import ROOT as r

file = r.TFile.Open("ResonanceShapes_qq_13TeV_Spring16.root")

masses = range(1800,6800,100)
effs = []
for mass in masses:
    h = file.Get("h_qq_{}".format(mass))
    effs.append(h.Integral(h.FindBin(2438),-1))

print zip(masses,effs)
