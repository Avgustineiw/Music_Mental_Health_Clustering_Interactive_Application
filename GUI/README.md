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
##### _Implementation of a Model-View-Controller._
### External data handling
##### _Capability to read a .csv file (one particular dataset) and write .txt files (output files)._
### Error handling
##### _Use of “try” and ”catch” methods to handle errors which would otherwise crash the program/make it unusable_
### Object-oriented features
##### _1. Implementation of Setters and Getters for manipulating class properties._
##### _2. Overloading of operators for enhanced class functionality._
##### _3. Use of hierarchy to create a hierarchical structure of classes._
## Interface of the project
### The following actions can be performed with the interface:
#### Form #1
##### _Cluster by hierarchy - performs the clustering and moves to form #2_
##### _Cluster by medoids - performs the clustering and moves to form #2_
##### _Cluster by k-means - performs the clustering and moves to form #2_
##### _Documentation - opens a documentation file_
#### Form #2 
##### _Showcases the result of clustering via silhouette algorithm_
    Additionally, user can:
    Extract the picture
    Save it as .txt file
    Return to form #1 to choose a different clustering algorithm
    Compare clustering algorithms (on 3 txt files which were previously extracted using different clustering algorithms)
![Screenshot of a plan of the interface part 1](https://github.com/Lunciare/myproject_cpp2024/blob/master/1.1.1.jpg)
![Screenshot of a plan of the interface part 2](https://github.com/Lunciare/myproject_cpp2024/blob/master/2.1.jpg)
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
## Contribution of each of the members
#### Zinkin Zakhar: everything inside "Core" except SLINK (read data, respondent projection to 2D space, necessary classes for algorithms, two clustering algorithms, silhoette interpretation, logger). GUI second form graph visualization, buttons to save images and results into separate files, comparison of clustering methods. Many changes regarding connection of "Core" and GUI. Code documentation
#### Suvorova Alexandra: everything in GUI except aforementioned implementations. Two tables, the former showcases data from the survey, the latter shows data about clusterised points. Buttons to add/remove row and edit specific cells, ability to clear data. Buttons to choose a clustering algorithms as well as input the required number of clusters and iterations. This readme too was also written by her.
#### Blinov Vladimir: Hierarchy (SLINK) clustering, app manual
