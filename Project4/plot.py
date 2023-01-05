#plot timesteps 
import os
import sys
from numpy import *
from matplotlib.pyplot import *
#pull data from directory 'data'
directory = 'data'

remove = int(sys.argv[1])
T = [] #an array containing temperatures for different time steps
t = [] #time step labels
for filename in os.listdir(directory):
    #iterate through rows
    if(filename != "r.csv"):
        #parse lines
        templist = filename.split("_")
        layup = int(filename[-2])
        templist = templist[-1].split(".")
        t.append(int(templist[0]))
        T_t = loadtxt("data/"+filename,skiprows = 1, delimiter = ",",dtype = float)
        T.append(T_t.T)
        if(remove == 1):
            os.remove("data/"+filename)

T = array(T)
#create array from data
layup = int(sys.argv[2])
#create list of r steps
r = loadtxt("data/r.csv",delimiter=',');
r = r.T
if(remove == 1):
    os.remove("data/r.csv")
#delete data from directory
for i in range(len(T)):
    #iterate through time steps and plot temperature data
    plot(r,T[i,layup],label=str(t[i]))

legend()
#input title, which will title the plot and the file
name = str(input("Title: "))
#plot will be titled with input
title(name)
ylabel("Temperature (K)")
xlabel("Distance (m)")
#save figure with as 'name'.png
savefig(name, dpi=1000)
show()

