import os
import numpy as np

basepath_inp = 'INPUT_FILES/'
basepath_out = 'OUTPUT_FILES/'

for entry in os.scandir(basepath_inp):
    name = entry.name[:-4]
    
    link_inp = basepath_inp + name + '.txt'
    link_out = basepath_out + name + '.out'

    INP = open(link_inp,"r")
    OUT = open(link_out,"r")

    number_of_photos = (int)(INP.readline())

    dir = []
    tag = []

    label = {}

    for i in range(number_of_photos):
        info = INP.readline().split(' ')
        info[-1] = info[-1][:-1]

        dir.append(info[0])
        tag.append(info[2:])

    number_of_slides = (int)(OUT.readline())
    last_tag = {}

    total_score = 0

    for i in range(number_of_slides):
        photos = OUT.readline().split(' ')
        photos[-1] = photos[-1][:-1]

        current_tag = {-1}

        for id in photos:
            for Tag in tag[(int)(id)]:
                Hash = 0
                for c in Tag:
                    Hash = Hash * 31
                    Hash = Hash + ord(c) - 96
                    Hash = Hash % 1000000007
                
                current_tag.add(Hash)
        
        size3 = len(current_tag.intersection(last_tag))
        size2 = len(current_tag) - size3
        size1 = len(last_tag) - size3

        total_score = total_score + min(size1,size2,size3)
        current_tag.remove(-1)

        last_tag = current_tag
    
    print("{}:{}".format(name[0],total_score))


    