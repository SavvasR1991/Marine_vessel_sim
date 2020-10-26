import os
import math
import numpy as np
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D  # noqa: F401 unused import

def plot_graph(t, area):
    fig = plt.figure()
    ax = fig.add_subplot(111)
    count = 1
    for i in t :
        tmp = []
        points = []
        for j in i:
            ax.scatter(float(j[0]), float(j[1])) 
            tmp.append([float(j[0]), float(j[1])])   
        x_text =  (tmp[0][0] + tmp[1][0])/2        

        y_text =  (tmp[1][1] + tmp[2][1])/2 

        ax.text(x_text,y_text,str(count))      

        count += 1 
    points.append([float(t[0][0][0]), float(t[0][0][1])]) 
    points.append([float(t[-1][3][0]), float(t[-1][3][1])]) 
    x_text =  (points[0][0])        
    y_text =  (points[0][1])
    ax.text(x_text,y_text+0.3,"NW ("+str(x_text) +","+str(y_text) +")")
  		
    x_text =  (points[1][0])        
    y_text =  (points[1][1])
    ax.text(x_text-1,y_text-0.3,"SE ("+str(x_text) +","+str(y_text) +")")     
    ax.text(x_text-1,y_text-0.6,"Points:"+ str(len(t)) )     
    ax.text(x_text-1,y_text-0.9,"Area  :"+ area.split()[0] + "x" + area.split()[1])     
        
    ax.set_xlabel('Longtitude Label')
    ax.set_ylabel('Latitude Label')

    mng = plt.get_current_fig_manager()
    mng.resize(*mng.window.maxsize())
    plt.show()

def main():
    file1 = open('2d_surface_waves.txt', 'r') 
    Lines = file1.readlines()
    area =  Lines[-1] 
    Lines = Lines[:-1]
    squares = []
    for i in Lines:
        squares.append([[i.split()[0],i.split()[1]],[i.split()[2],i.split()[3]],[i.split()[4],i.split()[5]],[i.split()[6],i.split()[7]]])
    plot_graph(squares, area)

if __name__ == "__main__":
    main()