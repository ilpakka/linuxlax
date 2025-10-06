#!/bin/bash

tunti=$(date +%H)

if [ "$tunti" -ge 6 ] && [ "$tunti" -lt 10 ]; then 
	n="Huomenta"
elif [ "$tunti" -ge 10 ] && [ "$tunti" -lt 18 ]; then
	n="Päivää"
elif [ "$tunti" -ge 18 ] && [ "$tunti" -lt 23 ]; then
	n="Iltaa"
else
	n="Yömyöhää"
fi

echo "Hyvää $n $USER!"
echo "Nyt on $(date)"
