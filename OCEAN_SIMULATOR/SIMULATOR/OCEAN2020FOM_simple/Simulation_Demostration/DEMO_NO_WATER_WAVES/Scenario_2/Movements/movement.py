import math 
import numpy as np
import matplotlib as mpl
import matplotlib.pyplot as plt
import mpl_toolkits.mplot3d as plt3d
import mpl_toolkits.mplot3d.art3d as art3d

from os import listdir
from os.path import isfile, join
from math import sin, cos, radians, pi
from mpl_toolkits.mplot3d import Axes3D
from matplotlib import animation
from data_Creator import *
from pathlib import Path

pause = False


def distance(ax,ay,bx,by):
    return math.sqrt((ax - bx)**2 + (ay - by)**2)

def angle_between_two_point(x0, y0, x1,y1):
    theta = math.degrees(math.atan2(y1-y0,x1-x0))
    theta = angle_normalization(theta)
    return theta

def point_pos(x0, y0, d, theta):
    theta_rad = np.deg2rad(theta)
    return x0 + d*cos(theta_rad), y0 + d*sin(theta_rad)
    
def angle_normalization(theta):
    if theta < 0:
        theta = 360 + theta
    elif theta > 360:
        theta = theta - 360 
    return theta  

def make_helix(xyz):
    x, y, z= zip(*xyz)
    helix = np.vstack((x, y, z))
    return helix

def onClick(event):
    global pause
    pause = True

def update(num, dataLines, lines , data2, lines2) :        
    for i in range(0, len(dataLines)):
        for line, data11 in zip(lines[i], dataLines[i]) :
            line.set_data(data11[0:2, num-1:num])
            line.set_3d_properties(data11[2,num-1:num])
            
    for i in range(0, len(data2)):
        for line1, data1 in zip(lines2[i], data2[i]) :
            line1.set_data(data1[0:2, num-1:num])
            line1.set_3d_properties(data1[2,num-1:num])
    print(num)
    return lines, lines2

def orthoProjection(ax, ay, bx, by, cx, cy):
    abx = bx - ax
    aby = by - ay
    acx = cx - ax
    acy = cy - ay
    if (abx * abx + aby * aby) == 0:
        f = 1
    else:
        f = (abx * abx + aby * aby)
    t = (abx * acx + aby * acy) / f
    px = ax + t * abx
    py = ay + t * aby
    return px, py

def distance(ax, ay, bx, by):
    return math.sqrt((ax-bx)**2+(ay-by)**2)
    
def read_movement_file():

    mypath ="Logs/"
    movement = {}
    onlyfiles = [f for f in listdir(mypath) if isfile(join(mypath, f))]

    list_files = list(onlyfiles)
    f = list_files.sort()
    cnt = 0
    for i in list_files:
        filepath = mypath + i
        coor = []
        print(filepath)
        with open(filepath) as fp:
            line = fp.readline()
            start_scanning = False
           
            while line:
                if start_scanning == True:
                    if ":" in line:
                        output = ((line.strip()).split("} -> "))   
                        point_1 = ((output[0].split(" {"))[0].split(": ")[1])
                        x = float(point_1.split(",")[0])
                        y = float(point_1.split(",")[1])
                        z = float(point_1.split(",")[2])
                        coor.append([x,y,z])
                if " End" in str(line):
                    start_scanning = True
                line = fp.readline()
            movement[str(cnt)] = coor
            cnt = cnt + 1
    return  movement
    
def start_animation(ax, fig, sectors,orth,movement,refLatitude,refLongitude,radius):
    xyz,frames_num = Data.unkwown_movement(refLatitude,refLongitude,radius)
    lines = []
    data = []
    for i in range(0, len(xyz)):
        data.append([make_helix(xyz[i])])
        lines.append( [ax.plot(data[i][0][0,0:1], data[i][0][1,0:1], data[i][0][2,0:1], 'o',color='r')[0]])

    data1 = []
    lines1 = []

    for i in range(0, sectors):
        xyz = movement[str(i)]
        data1.append([make_helix(xyz)])
        if data1[i][0][2,0:1] < 0 :
            lines1.append([ax.plot(data1[i][0][0,0:1], data1[i][0][1,0:1], data1[i][0][2,0:1], 'o',color='purple')[0]])
        else:
            lines1.append([ax.plot(data1[i][0][0,0:1], data1[i][0][1,0:1], data1[i][0][2,0:1], 'o',color='black')[0]])

    fig.canvas.mpl_connect('button_press_event', onClick)
    ani = animation.FuncAnimation(fig, update,frames=len(movement[str(i)]), fargs=(data, lines, data1 ,lines1), interval=1, blit=False, repeat=True)
    plt.show()

    
def desigh_eniviroment():
    refLatitude = 0
    refLongitude = 0
    radius = 5 
    subwater_vessel_radius = 5
    ship_length = 200
    sectors_sur = 0
    sectors_sub = 0
    Y = []
    X_ = []
    ortho = []
    chunks_left = []
    points_cycle = []
    file1 = open('Logs/ship_log_surface.txt', 'r') 
    Lines = file1.readlines() 
    
    file2 = open('Logs/element_attributes.txt','r')
    Lines2 = file2.readlines() 
    for line in Lines2: 
        if "Ship range" in line:
            ship_length = float((line.split(": ")[1]).split()[0])
        if "Ship reference coordinates" in line:
            input_line = line.split(":")[1].split(",")
            refLatitude = float(input_line[0].split("[")[1])
            refLongitude = float(input_line[1])        
        if "Ship surface vessels radius" in line:
            radius =  float(line.split(": ")[1])
        if "Ship subwater vessels radius" in line:
            subwater_vessel_radius =  float(line.split(": ")[1])         
    sectors_sur = len(Lines)
    radius = radius * 2
    chunks = ship_length/radius
    fig = plt.figure()
    ax = fig.add_subplot(111, projection='3d')

    onlyfiles = [f for f in listdir("Logs/") if isfile(join("Logs/", f))]
    z_depth_max = 0
    for t in onlyfiles:
        if "Target_" in t:
            file_tar = open('Logs/'+ t, 'r') 
            Line_tar = file_tar.readlines() 
            for kk in Line_tar:
                if float(kk.split(",")[2].strip().replace("]","")) <= z_depth_max:
                    z_depth_max = float(kk.split(",")[2].strip().replace("]",""))
            
    for line in Lines: 
        if line !="\n":
            for i in range(0, 3):
                output = line.strip().split("|")[i].split()
                Y.append('blue')
                X_.append([float(output[0]),float(output[1]),float(output[2])])
                
                if i == 0:
                    c = [float(output[0]),float(output[1]),float(output[2])]
                elif i == 1:
                    a = [float(output[0]),float(output[1]),float(output[2])]
                else:
                    b = [float(output[0]),float(output[1]),float(output[2])]
                    
            ax.plot([c[0], a[0]], [c[1],a[1]], [c[2],a[2]],color = 'b')
            ax.plot([b[0], a[0]], [b[1],a[1]], [b[2],a[2]],color = 'b')
            ax.plot([b[0], c[0]], [b[1],c[1]], [b[2],c[2]],color = 'b')

            perpendicular = orthoProjection(b[0],b[1],a[0],a[1],c[0],c[1])

            d = distance(perpendicular[0],perpendicular[1],c[0],c[1])
            if d <=0 :
                d = 1

            t = radius/d
            xt,yt = (1-t)*c[0]+t*perpendicular[0], (1-t)*c[1]+t*perpendicular[1]

            ortho.append((xt,yt))
            
            chunks_left = []
            chunks_right = []
            
            theta_chunk_left = angle_between_two_point(c[0], c[1], a[0], a[1])
            theta_chunk_right = angle_between_two_point(c[0], c[1], b[0], b[1])
            
            x_left = c[0]
            y_left = c[1]
            
            x_right = c[0]
            y_right = c[1]
            
            z_depth = c[2]
         
            for i in range(0, int(chunks)):
                chunks_left.append([x_left,y_left])
                x_left,y_left = point_pos(x_left, y_left, radius, theta_chunk_left)
                
                chunks_right.append([x_right,y_right])
                x_right,y_right = point_pos(x_right, y_right, radius, theta_chunk_right)

            chunks_left_ = np.array(chunks_left)
            ax.scatter(chunks_left_[:, 0], chunks_left_[:, 1], z_depth, s = 4, color = 'yellow')
            
            chunks_right_ = np.array(chunks_right)
            ax.scatter(chunks_right_[:, 0], chunks_right_[:, 1], z_depth, s = 10, color = 'red')
            
            ax.scatter(refLatitude, refLongitude, z_depth_max -10, s=1)

    my_file = Path("Logs/ship_log_subwater.txt")
    if my_file.is_file():
        file_sub1 = open('Logs/ship_log_subwater.txt', 'r') 
        Linessub = file_sub1.readlines() 
        sectors_sub = len(Linessub)
      
                    
        for line in Linessub: 
            a = []
            b = []
            c = []
            if line !="\n":
                for i in range(0, 3):
                    output = line.strip().split("|")[i].split()
                    Y.append('blue')
                    X_.append([float(output[0]),float(output[1]),float(output[2])])
                    
                    if i == 0:
                        c = [float(output[0]),float(output[1]),float(output[2])]
                    elif i == 1:
                        a = [float(output[0]),float(output[1]),float(output[2])]
                    else:
                        b = [float(output[0]),float(output[1]),float(output[2])]
                if c[0] == a[0] and a[0] == b[0] and c[1] == a[1] and a[1] == b[1]:
                    cycle_points = 10
                    init_cycle_points = int(cycle_points/2)
                    actinia = subwater_vessel_radius+subwater_vessel_radius
                    actinia_addition = ship_length/(ship_length / float(subwater_vessel_radius * 4))
                    z_depth = c[2]
                    points_cycle = []
                    while actinia <= ship_length:
                        theta = math.radians(360.0 / float(cycle_points))
                        for  j in range(0, cycle_points):
                            x = refLatitude + actinia * cos(j * theta)
                            y = refLongitude + actinia * sin(j * theta)
                            points_cycle.append([x,y])
                        cycle_points = cycle_points + init_cycle_points
                        actinia = actinia + actinia_addition
                    points_cycle_ = np.array(points_cycle)
                    ax.scatter(points_cycle_[:, 0], points_cycle_[:, 1], z_depth, s = 4, color = 'green')
                
                elif int(c[0]) == 0 and int(c[1]) == 0 and int(c[2]) == 0:
                    cycle_points = 8
                    init_cycle_points = int(cycle_points/2)
                    actinia = subwater_vessel_radius+subwater_vessel_radius
                    actinia_addition = 100#ship_length/(ship_length / float(subwater_vessel_radius * 4))
                    z_depth = a[2]
                    points_cycle = []

                    while actinia <= ship_length:
                        theta = math.radians(180.0 / float(cycle_points))
                        for  j in range(0, cycle_points):
                            x = refLatitude + actinia * cos(j * theta)
                            y = refLongitude + actinia * sin(j * theta)
                            points_cycle.append([x,y])
                        cycle_points = cycle_points + init_cycle_points
                        actinia = actinia + actinia_addition
                    points_cycle_ = np.array(points_cycle)
                    ax.scatter(points_cycle_[:, 0], points_cycle_[:, 1], z_depth, s = 4, color = 'green')
                    
                    cycle_points = 8
                    actinia = subwater_vessel_radius+subwater_vessel_radius
                    init_cycle_points = int(cycle_points/2)
                    points_cycle2 = []
                    while actinia <= ship_length:
                        theta = math.radians(180.0 / float(cycle_points))
                        for  j in range(0, cycle_points):
                            x = refLatitude + actinia * cos(j * theta + math.radians(180.0))
                            y = refLongitude + actinia * sin(j * theta + math.radians(180.0))
                            points_cycle2.append([x,y])
                        cycle_points = cycle_points + init_cycle_points
                        actinia = actinia + actinia_addition
                    points_cycle_2 = np.array(points_cycle2)
                    ax.scatter(points_cycle_2[:, 0], points_cycle_2[:, 1], z_depth, s = 4, color = 'red')
                else:
                    ax.plot([c[0], a[0]], [c[1],a[1]], [c[2],a[2]],color = 'b')
                    ax.plot([b[0], a[0]], [b[1],a[1]], [b[2],a[2]],color = 'b')
                    ax.plot([b[0], c[0]], [b[1],c[1]], [b[2],c[2]],color = 'b')

                    perpendicular = orthoProjection(b[0],b[1],a[0],a[1],c[0],c[1])

                    d = distance(perpendicular[0],perpendicular[1],c[0],c[1])
                    if d <=0 :
                        d = 1

                    t = radius/d
                    xt,yt = (1-t)*c[0]+t*perpendicular[0], (1-t)*c[1]+t*perpendicular[1]

                    ortho.append((xt,yt))
                    
                    chunks_left = []
                    chunks_right = []
                    
                    theta_chunk_left = angle_between_two_point(c[0], c[1], a[0], a[1])
                    theta_chunk_right = angle_between_two_point(c[0], c[1], b[0], b[1])
                    
                    x_left = c[0]
                    y_left = c[1]
                    
                    x_right = c[0]
                    y_right = c[1]
                    
                    z_depth = c[2]
                 
                    for i in range(0, int(chunks)):
                        chunks_left.append([x_left,y_left])
                        x_left,y_left = point_pos(x_left, y_left, subwater_vessel_radius, theta_chunk_left)
                        
                        chunks_right.append([x_right,y_right])
                        x_right,y_right = point_pos(x_right, y_right, subwater_vessel_radius, theta_chunk_right)

                    chunks_left_ = np.array(chunks_left)
                    ax.scatter(chunks_left_[:, 0], chunks_left_[:, 1], z_depth, s = 4, color = 'green')
                    
                    chunks_right_ = np.array(chunks_right)
                    ax.scatter(chunks_right_[:, 0], chunks_right_[:, 1], z_depth, s = 10, color = 'red')                       
    start = 0
    end = 3
    X = np.array(X_)

    orth = np.array(ortho)

    #ax.scatter(X[:, 0], X[:, 1],0, s = 10, color = Y[:])  
    #ax.scatter(orth[:, 0], orth[:, 1],0, s = 2, color = 'black') 
    ax.set_xlabel('X Label')
    ax.set_ylabel('Y Label')
    ax.set_zlabel('Z Label')
    return fig, ax,(sectors_sur + sectors_sub),orth,refLatitude,refLongitude,ship_length
    
movement = read_movement_file()
print()
fig,ax,sectors,orth,refLatitude,refLongitude,radius = desigh_eniviroment()
start_animation(ax, fig, sectors,orth,movement,refLatitude,refLongitude,radius)
