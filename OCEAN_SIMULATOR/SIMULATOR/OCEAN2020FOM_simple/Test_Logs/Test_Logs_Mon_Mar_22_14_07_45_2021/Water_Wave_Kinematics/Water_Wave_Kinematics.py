import os
import sys
import numpy as np
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D  # noqa: F401 unused import

def plot_2d_graph(stamp):
    file1 = open("2d_surface_waves_" + stamp + ".txt", "r") 
    Lines = file1.readlines()
    area =  Lines[-1] 
    Lines = Lines[:-1]
    squares = []
    values = []
    for i in Lines:
        squares.append([[i.split()[0],i.split()[1]],[i.split()[2],i.split()[3]],[i.split()[4],i.split()[5]],[i.split()[6],i.split()[7]]])  
    tmp = []
    for i in squares:
        for j in i:
            tmp.append([float(j[0]), float(j[1])])   
    return tmp

def plot_graph(t,target, wave, stamp):
    fig, ax = plt.subplots()
    tt = 0
    plot_2d = plot_2d_graph(stamp)
    for j in plot_2d:
        points5, = ax.plot(float(j[0]), float(j[1]) , marker='o', color="g", linestyle='None', alpha=0.5)
        points5.set_data(float(j[0]), float(j[1]))
    move = []
    for i in t :
        if tt == 0:
            points1, = ax.plot(float(i[0]), float(i[1]) , marker='o', color="b", linestyle='None')
            points2, = ax.plot(float(target[0]), float(target[1]) , marker='o', color="r", linestyle='None')
            ax.set_xlim(0, 600) 
            ax.set_ylim(0, 600) 
        else:
            if tt == int(wave[tt]):
                points3, = ax.plot(float(i[0]), float(i[1]) , marker='o', color="y", linestyle='None', markersize= 15, alpha=0.5)
                points3.set_data(float(i[0]), float(i[1]))
            points1, = ax.plot(float(i[0]), float(i[1]) , marker='o', color="b", linestyle='None')
            points1.set_data(float(i[0]), float(i[1]))
        plt.pause(0.1)
        tt = tt + 1
    plt.pause(60)

def main():
    if len(sys.argv) !=2:
        exit()

    logs = str(sys.argv[1])
    file1 = open(logs, 'r') 
    Lines = file1.readlines() 
    target = Lines[-1].split()
    del Lines[-1]
    t = []
    wave = []
    for i in Lines:
        A = [i.split()[0],i.split()[1],i.split()[2]]
        t.append(A)
    stamp = logs.split(".txt")[0][-1]
    waves = str("Wave_hits"+ stamp  +".txt")
    file2 = open(waves, 'r') 
    Lines2 = file2.readlines() 
    for i in Lines2:
        wave.append(i)

    plot_graph(t, target, wave, stamp)


if __name__ == "__main__":
    main()