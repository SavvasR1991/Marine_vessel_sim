import os
import math
import numpy as np
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D  # noqa: F401 unused import

def plot_graph(t, values,  area):
    fig = plt.figure()
    ax = fig.add_subplot(111, projection='3d')
    counter = 0
    first_line = 0	
    for i in t :
        points = []
        for j in i:
            if float(j[2]) == float(t[0][0][2]) or float(j[2]) == float(t[-1][3][2]):
                if counter == 0:
                    ax.scatter(float(j[0]), float(j[1]), float(j[2]), color="r", s=15)   
                else:
                    ax.scatter(float(j[0]), float(j[1]), float(j[2]), color="g")  
                first_line = first_line + 1  
        if float(values[counter][0]) != 0 or float(values[counter][1]) != 0 or float(values[counter][2]) != 0:
            print("Area : " + str(counter+1))  
            print("    Intensity: " + values[counter][0] + " seconds")
            print("    Direction: " + values[counter][1] + " degrees")
            print("    Height:    " + values[counter][2] + " meters\n")
        counter = counter +1 
            
    points.append([float(t[0][0][0]), float(t[0][0][1]), float(t[0][0][2])]) 
    points.append([float(t[-1][3][0]), float(t[-1][3][1]),float(t[-1][3][2])]) 
    x_text =  (points[0][0])        
    y_text =  (points[0][1])
    z_text =  (points[0][2])  
    ax.text(x_text,y_text,z_text + 3,"NW: (" + str(t[0][0][0]) + "," + str(t[0][0][1]) + "," + str(t[0][0][2]) +")")  
    ax.text(x_text,y_text,z_text + 7,"Area: " + str(area[0]) + "x" + str(area[1]) + "x" + str(area[2]))  
    
    x_text =  (points[1][0])        
    y_text =  (points[1][1])
    z_text =  (points[1][2])  
    ax.text(x_text,y_text,z_text ,"SE: (" + str(t[-1][3][0]) + "," + str(t[-1][3][1]) + "," + str(t[-1][3][2]) +")")  
    
    ax.set_xlabel('Longtitude Label')
    ax.set_ylabel('Latitude Label')
    ax.set_zlabel('Depth Label')
    plt.show()

def main():
    file1 = open('3d_current_waves.txt', 'r') 
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
    plot_graph(squares, value, area)

if __name__ == "__main__":
    main()

