#!/bin/sh

/usr/bin/doxygen ./documentation.cfg

echo
echo
echo "Done... "
grep "OUTPUT_DIRECTORY       = " ./documentation.cfg
