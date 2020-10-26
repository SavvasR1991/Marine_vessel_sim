import os
import math
import numpy as np
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D  # noqa: F401 unused import

def plot_graph(t):
    fig = plt.figure()
    ax = fig.add_subplot(111, projection='3d')
    
    for i in t :
        points = []
        for j in i:
            ax.scatter(float(j[0]), float(j[1]), float(j[2]))    
    points.append([float(t[0][0][0]), float(t[0][0][1]), float(t[0][0][2])]) 
    points.append([float(t[-1][3][0]), float(t[-1][3][1]),float(t[-1][3][2])]) 
    x_text =  (points[0][0])        
    y_text =  (points[0][1])
    z_text =  (points[0][2])  
    ax.text(x_text,y_text,z_text,"NW")  
    
    x_text =  (points[1][0])        
    y_text =  (points[1][1])
    z_text =  (points[1][2])  
    ax.text(x_text,y_text,z_text,"SE")     
    
    ax.set_xlabel('Longtitude Label')
    ax.set_ylabel('Latitude Label')
    ax.set_zlabel('Depth Label')
    plt.show()

def main():
    file1 = open('3d_current_waves.txt', 'r') 
    Lines = file1.readlines() 
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

    plot_graph(squares)

if __name__ == "__main__":
    main()

