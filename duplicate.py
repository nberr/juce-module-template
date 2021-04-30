#!/usr/bin/python3

import sys, shutil, os, datetime

VERSION = "1.0"

def main():
    global VERSION
    print("juce-module duplicator v" + VERSION + " by nberr")
    
    numargs = len(sys.argv) - 1
    
    if not (numargs == 3):
        print("Usage: python duplicate.py module_ID name_space class_name")
        sys.exit(1)
    else:
        module_ID = sys.argv[1]
        name_space = sys.argv[2]
        class_name = sys.argv[3]
    
    src = os.path.dirname(os.path.realpath(__file__))
    src = src + '/module_template'
   
    dest = os.path.dirname(os.path.realpath(__file__))
    dest = dest + '/modules/' + module_ID
    
    # copy the directory
    shutil.copytree(src, dest)
    
    # rename the files
    
    # cpp and h file
    os.rename(dest + '/module_template.cpp', dest + '/' + module_ID + '.cpp')
    os.rename(dest + '/module_template.h', dest + '/' + module_ID + '.h')
    
    
    # .cpp internals
    with open (dest + '/' + module_ID + '.cpp', 'r') as cppfile:
        cppdata = cppfile.read()
    
    cppdata = cppdata.replace('MODULE_TEMPLATE_H_INCLUDED', module_ID.upper() + "_H_INCLUDED")
    cppdata = cppdata.replace('module_template.h', module_ID + ".h")
    cppdata = cppdata.replace('NameSpaceName', name_space)
    cppdata = cppdata.replace('ClassName', class_name)
    
    with open (dest + '/' + module_ID + '.cpp', 'w') as cppfile:
        cppfile.write(cppdata)
        
    with open (dest + '/' + module_ID + '.h', 'r') as hfile:
        hdata = hfile.read()
    
    hdata = hdata.replace('module_template', module_ID)
    hdata = hdata.replace('MODULE_TEMPLATE_H_INCLUDED', module_ID.upper() + "_H_INCLUDED")
    hdata = hdata.replace('NameSpaceName', name_space)
    hdata = hdata.replace('ClassName', class_name)
    
    
    with open (dest + '/' + module_ID + '.h', 'w') as hfile:
        hfile.write(hdata)
            

if __name__ == '__main__':
    main()
