# import necessary libraries and functions
import numpy as np #here to convert images to array
import pandas as pd
from glob import glob #for reeding multiple images all together
import matplotlib.pyplot as plt


from keras.layers import Dense, InputLayer
from keras.models import Sequential

from sklearn.model_selection import train_test_split

#create random number generator
seed = 108
rng = np.random.RandomState(seed)

img_path = 'Emergency_Vehicles/'
data = pd.read_csv(img_path+'train.csv')

print(data.sample(10))

data.emergency_or_not.value_counts(normalize=True)

#loading images and storing them in for of numpy array i.e metric

#empty list to store images
X = []
#iterating over each image
for img_name in data.image_names:
    # loading image using its name
    test_img_path = 'Emergency_Vehicles/train/'
    img = plt.imread(test_img_path + img_name)
    # saving each image in list
    X.append(img)

#converting list of images into array and saving into X
X = np.array(X)

#storing target variable in separate variable
y = data.emergency_or_not.values

print(X.shape)

fig,ax = plt.subplots(nrows=1,ncols=5,figsize=(20,20))
for i in range(5):
    ax[i].imshow(X[i*400])
    ax[i].axis('off')

# converting 3 dimensional image to 1 dimensional image
X = X.reshape(X.shape[0],224*224*3) #(number of images,new_shape of each image)
print(X.shape)

print(X.min(), X.max())
X = X / X.max()
X.min(), X.max()

X_train,X_test,y_train,y_test = train_test_split(X,y,test_size=0.3,random_state=seed)

print((X_train.shape,y_train.shape),(X_test.shape,y_test.shape))

print(X_train.shape[1])

model=Sequential()

model.add(InputLayer(input_shape=(X_train.shape[1]))) #

model.add(Dense(100,activation='sigmoid'))
model.add(Dense(units=1,activation='sigmoid')) #binary classification problem so output neuron is 1

# summary of the model
print(model.summary())

model.compile(loss='binary_crossentropy',optimizer='sgd',metrics=['accuracy'])

model_history = model.fit(X_train,y_train,epochs=50,batch_size=128,validation_data=(X_test,y_test))

# getting predictions in form of class as well as probabilities
#predictions = model.predict_classes(X_test)[:, 0] # class form of output

prediction_probabilities = model.predict(X_test)[:,0] #prob form of output

prediction_int = (prediction_probabilities >= 0.5).astype("int32")

from sklearn.metrics import accuracy_score

print('Accuracy on validation set:', accuracy_score(y_test,prediction_int), '%')

plt.plot(model_history.history['loss'])
plt.plot(model_history.history['val_loss'])
plt.title('model loss')
plt.ylabel('loss')
plt.xlabel('epoch')
plt.legend(['train','validation'], loc='upper right')
plt.show()

#summarizing history for accuracy
plt.plot(model_history.history['accuracy'])
plt.plot(model_history.history['val_accuracy'])
plt.title('model accuracy')
plt.ylabel('accuracy')
plt.xlabel('epoch')
plt.legend(['train', 'validation'], loc='upper left')
plt.show()

# pull out the original images from data which correspond to the validation data
_, valid_vehicles, _, valid_y = train_test_split(data.image_names.values,y,test_size=0.3,random_state=seed) # using original data i.e. not preprocessed one

# get a random index to plot image randomly
index = rng.choice(range(len(valid_vehicles)))

# get the corresponding image name and probability
img_name = valid_vehicles[index]
prob = (prediction_probabilities * 100).astype(int)[index]

# read the image
img = plt.imread('Emergency_Vehicles/test/23.jpg')

# print probability and actual class
print('Model is', prob , '% sure that this is emergency')
print('And actual class is ', valid_y[index])

# plot image
plt.imshow(img)
plt.show()