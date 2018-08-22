# Decision Tree Regression

# Importing the libraries
import numpy as np
import matplotlib.pyplot as plt
import sys
import pandas as pd 
from firebase import firebase
from time import sleep
firebase = firebase.FirebaseApplication('https://stageete-5ecf1.firebaseio.com/', None)
# Importing the dataset
dataset = pd.read_csv('PV_failure_data.csv')
X = dataset.iloc[:, 1:4].values
y = dataset.iloc[:, 4].values

# Encoding the Dependent Variable
from sklearn.preprocessing import LabelEncoder
labelencoder_y = LabelEncoder()
y = labelencoder_y.fit_transform(y)

# Splitting the dataset into the Training set and Test set
"""from sklearn.cross_validation import train_test_split
X_train, X_test, y_train, y_test = train_test_split(X, y, test_size = 0.2, random_state = 0)"""

# Feature Scaling
"""from sklearn.preprocessing import StandardScaler
sc_X = StandardScaler()
X_train = sc_X.fit_transform(X_train)
X_test = sc_X.transform(X_test)
sc_y = StandardScaler()
y_train = sc_y.fit_transform(y_train)"""

# Fitting Decision Tree Regression to the dataset
from sklearn.tree import DecisionTreeRegressor
regressor = DecisionTreeRegressor(random_state = 0)
regressor.fit(X, y)

def update_firebase(y_pred):
  if y_pred is not None:
		                  sleep(5)
		                  print('updating to data base')
  else:
		 print('Failed to get reading. Try again!')
		 sleep(5)

if (float(sys.argv[1]) < 124500):
	print("No decision")
	exit(0)
elif(float(sys.argv[2]) == 0):
	print("Connection failure")
	exit(0)
elif(float(sys.argv[2]) < 2600):
	print("Total shading")
	exit(0)
else:
	for i in range(3,13):
		if(int(sys.argv[i]) < 16000):
	        	print("Partial shading of the panel "+str(i-2))
	        	y_pred='Ombrage partiel'
			
		else:
        	# Predicting a new result
        	    	y_pred = regressor.predict([[int(sys.argv[1]),int(sys.argv[2]),int(sys.argv[i])]])
        	    	if y_pred==2 :
        	        	y_pred = 'Erosion'
        	        	print(y_pred)
        	    	elif y_pred==1 :
        	        	y_pred = 'Normal'
        	        	print(y_pred) 
        	    	else: 
        	        	y_pred = 'Diode'
        	        	print(y_pred)
		firebase.put('/etat du panneau '+str(i-2),"Nature", y_pred)

# Visualising the Decision Tree Regression results (higher resolution)
