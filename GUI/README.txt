Documentation for graphical user interface of Music & Mental Health dataset
===========================================================================

Description of the project
--------------------------
The program aims to clusterize data based on a person’s preferences in music and find correlation between their preferences and mental health.

During the analysis, it is also aimed to compare 3 distinct clustering methods in order to find differences between them and determine the best algorithm.

Description of a GUI
--------------------
Graphical user interface comprises two forms. Also there are two sections at the top of the application: 'File' and 'Documentation'. The former includes menu bar with options: 'Open' (allows a user to choose a file with dataset, if a wrong file is selected, the program will display an error-message), 'Save' (enables saving a file with the dataset to user's device in the format .csv), 'Save as...' (enables saving a file ДОПИСАТЬ), 'Exit' (closes an application).

Form 1
------
The first form includes a table with the dataset. By clicking on the headers of the columns, the user can sort the data in the ascending and descending order and revert the data back. 

By clicking on the corresponding buttons, the user can add a new row, remove an existing row, edit a field or clear the data.

Three sorting algorithms are available by tapping on options from the list with clusterization. The results are available on the next form.

Form 2
------
The second form includes a graphical result of the clusterization method, which was selected by user on the previous form. The result can be saved as a picture, extracted as .txt file.

Also there is a button 'Compare' which accepts 3 .txt files with clusterization results (obtained by user) and it outputs the best algorithm based on the user's data.

