#!/bin/bash

path_to_file="$path_to_file/Users/$USER/Desktop"
export USER
export path_to_file

current_dir=$(pwd)
echo -n $current_dir > "other/config.conf"

echo "Hello! You are installing the Calculator_taleayos to ~/Desktop"

source venv/bin/activate
python3 setup.py py2app -A
mv dist/SmartCalc_Taleayos.app ~/Desktop/
cp other/config.conf ~/Desktop/SmartCalc_Taleayos.app/
rm -rf dist build


