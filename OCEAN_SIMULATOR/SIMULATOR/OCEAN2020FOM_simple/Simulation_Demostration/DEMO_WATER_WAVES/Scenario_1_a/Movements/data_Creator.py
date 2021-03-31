import math
from os import listdir
from os.path import isfile, join

class Data:        
    def unkwown_movement(refLatitude,refLongitude,radius):

        targets = []
        frames_num = 0
        mypath ="Logs/"
        movement = {}
        onlyfiles = [f for f in listdir(mypath) if isfile(join(mypath, f))]

        for files in onlyfiles:
            if "Target" in files:
                
                xyz = []
                file1 = open("Logs/"+files, 'r') 
                Lines = file1.readlines() 
                if int(Lines[0].split()[0]) > 1:
                    for l in range(0, int(Lines[0].split()[0])):
                        xyz.append([refLatitude + radius + 10,refLongitude + radius + 10,0])
                        
                for line in Lines: 
                    line = (line.split("[")[1].split(",")) 
                    xyz.append([float(line[0].strip()), float(line[1].strip()), float(line[2].strip().split("]")[0])])   
                    frames_num = frames_num + 1    
                targets.append(xyz)   
        return targets,frames_num

