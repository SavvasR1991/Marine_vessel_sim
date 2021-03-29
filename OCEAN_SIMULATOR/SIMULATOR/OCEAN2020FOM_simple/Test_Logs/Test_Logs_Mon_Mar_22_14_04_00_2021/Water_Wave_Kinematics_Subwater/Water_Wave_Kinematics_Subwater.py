import os
import sys
import math
import numpy as np
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D  # noqa: F401 unused import

def plot_graph(t, values,  area, wave,stamp):
    file1 = open('Logs' +stamp+'_subwater.txt', 'r') 
    Lines = file1.readlines() 
    points = []
    fig = plt.figure()
    ax = fig.add_subplot(111, projection='3d')
    counter = 0
    first_line = 0	
               
    points.append([float(t[0][0][0]), float(t[0][0][1]), float(t[0][0][2])]) 
    points.append([float(t[-1][3][0]), float(t[-1][3][1]),float(t[-1][3][2])]) 
    x_text =  (points[0][0])        
    y_text =  (points[0][1])
    z_text =  (points[0][2])  
    ax.text(x_text,y_text,z_text + 3,"NW: (" + str(t[0][0][0]) + "," + str(t[0][0][1]) + ",0)")  
    ax.scatter(x_text, y_text, z_text - 2, color="g")  
    
    x_text =  (points[1][0])        
    y_text =  (points[1][1])
    z_text =  (points[1][2])  
    ax.text(x_text,y_text,z_text ,"SE: (" + str(t[-1][3][0]) + "," + str(t[-1][3][1]) + "," + str(t[-1][3][2]) +")")  
    ax.scatter(x_text, y_text, z_text - 2, color="g")  
    
    ax.set_xlabel('Longtitude Label')
    ax.set_ylabel('Latitude Label')
    ax.set_zlabel('Depth Label')
    
    tt = 0
    c = []
    for i in Lines:
        f = i.split()
        ax.scatter(float(f[0]), float(f[1]), float(f[2]), c="r")
        if tt == int(wave[tt]):
            ax.scatter(float(f[0]), float(f[1]), float(f[2]), s= 60, c  = "b", alpha = 0.4)
        plt.pause(0.1)
        tt = tt + 1
    plt.show()

def main():
    if len(sys.argv) !=2:
        exit()

    logs = str(sys.argv[1])
    file1 = open(logs, 'r') 
    Lines = file1.readlines() 
    area = Lines[-1].split()
    del Lines[-1]
    value = []
    squares = []
    for i in Lines:
        A = [i.split()[0],i.split()[1],i.split()[2]]
        B = [i.split()[3],i.split()[4],i.split()[5]]
        C = [i.split()[6],i.split()[7],i.split()[8]]
        D = [i.split()[9],i.split()[10],i.split()[11]]
        E = [i.split()[12],i.split()[13],i.split()[14]]
        F = [i.split()[15],i.split()[16],i.split()[17]]
        G = [i.split()[18],i.split()[19],i.split()[20]]
        H = [i.split()[21],i.split()[22],i.split()[23]]
        squares.append([A,B,C,D,E,F,G,H])
        value.append([i.split()[24],i.split()[25],i.split()[26]]) 
        
    stamp = logs.split(".txt")[0][-1]
    waves = str("Wave_hits"+ stamp  +"_subwater.txt")
    wave = []
    file2 = open(waves, 'r') 
    Lines2 = file2.readlines() 
    for i in Lines2:
        wave.append(i)


    plot_graph(squares, value, area,wave,stamp)

if __name__ == "__main__":
    main()

