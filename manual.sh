#!/usr/bin/bash
doxygen onvif_C
cd doc/latex
make
cd ../..
cp doc/latex/refman.pdf manual.pdf
rm -rf doc