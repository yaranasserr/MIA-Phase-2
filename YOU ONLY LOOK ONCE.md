# YOU ONLY LOOK ONCE

```python
!pip install ultralytics
```

```python
from google.colab import drive
drive.mount('/content/drive')
```

```python
%cd /content/drive/MyDrive/task-8.3
```

```python
!yolo task=detect mode= train data=/content/drive/MyDrive/task-8.3/data.yaml epochs=100 imgsz=640
```

## **process:**

1-collecting dataset

2-peprocessing

3-training the model

4-driving the model

### 1-collecting dataset:

A machine learning dataset is **a data collection used to train the model**. A dataset acts as an example to teach the machine learning algorithm how to make predictions. We collected the dataset randomly in many positions to confirm that the machine will have suitable data to learn.

dataset link: 

[dataset - Google Drive](https://drive.google.com/drive/folders/1q1dsPLa7SCzZRCzQtPo2F1YIPQT0oltU?usp=sharing)

### **2-preprocessing:**

1. data set handling
2. image resizing
3. image augmentation

Pre-processing refers to the transformations applied to our data before feeding it to the algorithm. Data preprocessing is a technique that is used to convert the raw data into a clean data set.

first, using “labelImg” terminal we changed the raw photos to a clean data set that the computer could understand it. Next, data is separated into training and validating data. Then, the photo is resized in the code. Then, Image data augmentation is used to expand the training dataset to improve the model's performance and ability to generalize.

### 3-coding and importing dataset:

using Google Collab, the collected data was imported into Jupyter Notebook. then we ran the code and started training the model with the given information. The estimated time taken for the model training is approximately half an hour. 

train2 link:

[train2 - Google Drive](https://drive.google.com/drive/folders/1QEfVb9IJNLwiASyDcGMWegQuv96FmPcD?usp=sharing)

 

### 4-Driving the model:

applying the trained model on some examples to make sure that everything is ok!

```python
from ultralytics import YOLO
model=YOLO(r"C:\Users\Public\task-8.3\best.pt")
model.predict(source=r"C:\Users\Public\task-8.3\final.jpeg",show=True)
```

### weighting:

[best.pt](https://drive.google.com/file/d/1-tlubRb08TBSqG58YMlf_yJWrekLzzZw/view?usp=sharing)

![precision-confidence curve](YOU%20ONLY%20LOOK%20ONCE%2050d4d2808341412aad39e12798c744ed/P_curve.png)

precision-confidence curve

![precision-confidence matrix](YOU%20ONLY%20LOOK%20ONCE%2050d4d2808341412aad39e12798c744ed/confusion_matrix.png)

precision-confidence matrix