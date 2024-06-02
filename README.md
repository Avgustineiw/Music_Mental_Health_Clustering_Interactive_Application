# User Manual for an interactive application for clustering data. Project "Music and mental health"
## Interface oveview
### First of all, the app consists of two main tabs:
####    1. Tab 1 - Data input and clustering
####    2. Tab 2 - Data output and cluster visualization
### TAB #1 interface: Data input and clustering
![Screenshot of a plan of the interface part 1](https://github.com/Avgustineiw/Project_cpp/blob/FinnTheHuman/TAB1.2.png)
#### This tab allows you to input your data, manage it and perform clustering operations.
#### Features：
#### 1. Data table:
The majority of the space is occupied by the input data that displays the dataset
#### 2.Data management buttons：
On the right there are several buttons that allow the user to modify the data and to clusterize it:
##### Modifying data:
   1. _Add Row: Adds a new row to the data table._
   2. _Remove Row: Removes selected row from the data table._
   3. _Edit Cell: Allows editing of a specific cell in the data table._
   4. _Clear Data: Clears all the data in the data table._
##### Clustering options:
#####     You can select the clustering method by choosing:
   1. _Sort by Hierarchy_
   2. _Sort by Medoids_
   3. _Sort by Means_
#####     You can also edit the clustering parametrs:
   1. _Number of Clusters: Input the desired number of clusters._
   2. _Number of Iterations: Input the number of iterations for the clustering algorithm._

##### Clusterize Button: Executes the clustering process based on selected parameters.

### TAB #2 interface: Data output and cluster visualization
![Screenshot of a plan of the interface part 1](https://github.com/Avgustineiw/Project_cpp/blob/FinnTheHuman/TAB2.2.png)
#### _Shows the result of clustering_
#### Features：
#### 1. Clustered data table：
The majority of the space is occupied by the output data presented in a form of a colored scatter plot and a table with the following columns:
   1. _X Coordinate: X-axis value of the data point._
   2. _Y Coordinate: Y-axis value of the data point._
   3. _Cluster: Cluster number the data point belongs to._
##### The scatter plot provides the user with such information as:
   1. _Visual representation of the clusters._
   2. _Color-coded by cluster data points._
#### 2. Buttons：
On the left there are several buttons that allow the user to work with the output data:
##### Modifying data：
   1. _Save Image: Extracts the scatter plot as an image (allows the user to choose the destination of the saved file)._
   2. _Save Results: Saves the clustered data results as txt file (allows the user to choose the destination of the saved file)._
   3. _Compare Methods: Allows user to compare different clustering methods (user should choose three output files saved by "Save Results" button)._

## How to use the app
#### 1. Input data：
When the application starts, the tab 1 is opened:
   1. _Make sure tab 1 is opened._
   2. _Use the data table to change your dataset. You can add, remove, or edit rows via buttons._
#### 2. Select clustering parameters：
   1. _Choose a clustering method from the available options (clusterize by hierarchy, means, medoids)._
   2. _Enter the number of clusters you want to create._
   3. _Enter the number of iterations for the clustering algorithm_
   4. _Click the "Clusterize" button to perform the clustering._
#### 3. View and Save Results：
   1. _Navigate to tab 2 to view and save the results._
   4. _Use the "Save Image" and "Save Results" buttons to save the output data (after clicked, choose the path to save the file)._
   5. _Use the "Compare Methods" button to compare different clustering methods (after clicked, choose three files saved by button "Save Results")._

## Summary
Using the following instuctions, user should be able to effectively use the Music & Mental Health interactive application to analyze and visualize the data.





