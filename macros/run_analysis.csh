#!/bin/csh

 setenv LD_LIBRARY_PATH /gpfs/mnt/gpfs02/sphenix/user/trinn/fitting_algorithm_playing/analysis/tim_signal_analysis/build/lib/:$LD_LIBRARY_PATH


 root -b -q Fun4All_analysis.C
