import numpy as np
import sys
import matplotlib.pyplot as plt

    
def demo_kalman_xy2():    
    logs = str(sys.argv[1])
    file1 = open(logs, 'r') 
    Lines = file1.readlines() 
    t = []
    result = []
    observed_x = []
    observed_y = []

    fig, ax = plt.subplots()
    counter = 0
    
    predicted_x = []
    predicted_y = []
    
    for i in Lines:
        observed_x.append(float(i.split()[0]))
        observed_y.append(float(i.split()[1]))
        
        predicted_x.append(float(i.split()[2]))
        predicted_y.append(float(i.split()[3]))


    for meas in zip(observed_x, observed_y):
        ax.plot(float(meas[0]), float(meas[1]) , marker='o', color="r", linestyle='None')
        ax.text(float(meas[0]), float(meas[1]) ,str(counter))  
        counter = counter + 1
        
    counter = 0
    for meas2 in zip(predicted_x, predicted_y):
        ax.plot(float(meas2[0]), float(meas2[1]) , marker='o', color="b", linestyle='None')
        ax.text(float(meas2[0]), float(meas2[1]) ,str(counter))
        counter = counter + 1
        
    plt.plot(predicted_x, predicted_y, 'g-')
    plt.plot(observed_x, observed_y, 'r-')
    plt.show()

demo_kalman_xy2()
