#!/bin/bash
# Javier Sánchez Rois <jsanchez@gradiant.org>, 2015
# This script formats the QTestLib results to color output
# To use it, run 
#	./tst_mytestsname | color.sh

red='\033[0;31m'
green='\033[0;32m'
orange='\033[1;33m'
NC='\033[0m' # No Color

while read -r line; do
 if [[ "$line" =~ ^PASS ]]; then
  echo -e "${green}$line${NC}"
 elif [[ "$line" =~ ^FAIL ]]; then
  echo -e "${red}$line${NC}"
 elif [[ "$line" =~ ^SKIP ]]; then
  echo -e "${orange}$line${NC}"
 else	
  echo "$line"
 fi
done

