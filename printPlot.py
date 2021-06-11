import pandas as pd
import matplotlib.pyplot as plt
import sys

ClassOne = pd.read_csv("class1.csv")
ClassTwo = pd.read_csv("class2.csv")

w = list(ClassOne['featureONE'])
x = list(ClassOne['featureTWO'])

y = list(ClassTwo['featureONE'])
z = list(ClassTwo['featureTWO'])

plt.scatter(w, x, label = "Class 1", color= "blue")
plt.scatter(y, z, label = "Class 2", color = 'orange')

if(len(sys.argv) == 4):
    plt.xlabel('Feature ' + sys.argv[1])
    plt.ylabel('Feature ' + sys.argv[2])
    plt.title('Personal Data Set #' + sys.argv[3])
else:
    plt.xlabel('Feature ONE')
    plt.ylabel('Feature TWO')
    plt.title('Data Set')
    
plt.legend()

plt.show()