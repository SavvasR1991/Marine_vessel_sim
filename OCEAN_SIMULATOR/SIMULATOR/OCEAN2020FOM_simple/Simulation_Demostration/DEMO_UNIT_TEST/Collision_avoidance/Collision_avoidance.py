import os
import sys
import numpy as np
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D  # noqa: F401 unused import

def plot_graph(t,area,axis):
    fig, ax = plt.subplots()
    tt = 0
    for i in t :
        if tt == 0:
            points1, = ax.plot(float(i[0]), float(i[1]) , marker='o', color="b", linestyle='None',markersize= float(area[0]))
            points2, = ax.plot(float(i[2]), float(i[3]) , marker='o', color="b", linestyle='None',markersize= float(area[1]))
            points3, = ax.plot(float(i[2]), float(i[3]) , marker='o', color="r", linestyle='None',markersize= float(area[2]), alpha=0.5)
            points4, = ax.plot(float(i[2]), float(i[3]) , marker='o', color="g", linestyle='None',markersize= float(area[3]), alpha=0.5)
            if float(axis[0]) < 0:
                ax.set_xlim(float(axis[0]),0) 
            else:
                ax.set_xlim(0, float(axis[0])) 

            if float(axis[1]) < 0:
                ax.set_ylim(float(axis[1]),0) 
            else:
                ax.set_ylim(0, float(axis[1]))
        else:
            points5, = ax.plot(float(i[4]), float(i[5]) , marker='o', color="y", linestyle='None',markersize= float(i[6]), alpha=0.1)
            points1.set_data(float(i[0]), float(i[1]))
            points2.set_data(float(i[2]), float(i[3]))
            points3.set_data(float(i[2]), float(i[3]))
            points4.set_data(float(i[2]), float(i[3]))
            points5.set_data(float(i[4]), float(i[5]))
        plt.pause(0.1)
        tt = 1
    plt.pause(120)

def main():
    if len(sys.argv) !=2:
        exit()

    logs = str(sys.argv[1])
    file1 = open(logs, 'r') 
    Lines = file1.readlines() 
    axis=  Lines[-1]
    Lines = Lines[:-1]
    area =  Lines[-1] 
    Lines = Lines[:-1]
    t = []
    for i in Lines:
        A = [i.split()[0],i.split()[1],i.split()[2],i.split()[3],i.split()[4],i.split()[5],i.split()[6]]
        t.append(A)
    area  = [area.split()[0],area.split()[1],area.split()[2],area.split()[3]]
    axis  = [axis.split()[0],axis.split()[1]]
    plot_graph(t,area, axis)

if __name__ == "__main__":
    main()