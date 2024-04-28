# Technical Assignment for project “Music and mental health”
## Group members
##### _Zinkin Zakhar 234-2_
##### _Blinov Vladimir 234-2_
##### _Suvorova Alexandra 234-2_
## Topic
#### _Development of an Interactive application for clustering data by one's preferences in music._
## Description of the project
##### _The program aims to clusterize data based on a person’s preferences in music and find correlation between their preferences and mental health._ 
##### _During the analysis, we also aim to compare 3 different clustering methods in order to find differences between them and determine the best method._
##### _The [dataset](https://www.kaggle.com/datasets/catherinerasgaitis/mxmh-survey-results/data) used in this project._
## Requirements
### Programming language
##### _The application will be developed using C++ and the Qt framework for the GUI._
##### _Code Style used: using namespace std, Google code style._
### Interface approach
##### _Develop a user interface that allows users to interact with the project in different ways._
##### _Interface will include 4 blocks with widgets such as input and output of data, options for clusterization algorithms and graphics view._  
### External data handling
##### _Capability to read .csv files (datasets) and write .txt files (output files)._
### Error handling
##### _Use of “try” and ”catch” methods to handle errors which would otherwise crash the program/make it unusable_
### Object-oriented features
##### _1. Implementation of Setters and Getters for manipulating class properties._
##### _2. Overloading of operators for enhanced class functionality._
##### _3. Use of hierarchy to create a hierarchical structure of classes._
## Interface of the project
### Implementation of a Model-View-Controller via: 
#### _1. Choosing a csv file_
#### _2. Choosing a clustering algorithm_
    Cluster by hierarchy
    Cluster by medoids
    Cluster by means
#### _3. Showcasing silhouette data_
#### _4. Extracting silhouette data into a separate file_
#### _5. Comparing silhouette files_
#### _6. Documentation_
### The following actions can be performed with the interface:
#### Interface #1
##### _Documentation - opens a documentation file_
##### _Open CSV - asks the user to open a .csv file and moves to interface #2_
##### _exit - closes the program_
#### Interface #2
##### _Cluster by hierarchy - performs the clustering and moves to interface #3_
##### _Cluster by medoids - performs the clustering and moves to interface #3_
##### _Cluster by k-means - performs the clustering and moves to interface #3_
#### Interface #3 
##### _Showcases the result of clustering via silhouette algorithm_
    Additionally, user can:
    Extract the picture
    Save it as .txt file
![Screenshot of a plan of the interface part 3](https://github.com/Lunciare/myproject_cpp2024/blob/master/3.jpg)
![Screenshot of a plan of the interface part 2](https://github.com/Lunciare/myproject_cpp2024/blob/master/2.jpg)
![Screenshot of a plan of the interface part 1](https://github.com/Lunciare/myproject_cpp2024/blob/master/1.jpg)
## Tasks in github project
#### _1. Project initialization_
    Set up the Git repository with a README and the initial project structure.
#### _2. Implement read from csv_
#### _3. Implement 3 clustering algorithms_
    Clustering by hierarchy
    Clustering by medoids
    Clustering by means
#### _4. Implement interpreting algorithm_
#### _5. Implement GUI_
#### _6. Write documentation_
