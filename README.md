## Mason Grosko ePortfolio

### Table of contents
* [Self reflection](#self-reflection)
* [Code review](#code-review)
* [Android application enhancement](#android-application-enhancement)
* [Binary search tree algorithm enhancement](#binary-search-tree-algorithm-enhancement)
* [MongoDB financial data enhancement](#mongodb-financial-data-enhancement)

### Self reflection
Throughout my schooling at SNHU I was able to experience many different aspects of computer science. The area that intrigued me the most was the realm of data science. There have been claims that data is modern day gold, and the problem is that people just do not know how to monetize it. Data science is trying to make data easily accessible to more people by simplifying the steps involved. I think the aspect of creating the tools to make the process easier is an interesting field I would like to get into. Developing the software that the data scientists would rely on is where I will set my sights for my career. 

To achieve this goal, I will have to rely heavily on what I learned in my schooling as developing software that will be used at the level will require in depth understanding of working as a team through code reviews while having a security mindset that anticipates software exploits and vulnerabilities, going through iterations of software design and engineering, creating and utilizing different algorithms and data structures and an in depth understanding of working with databases. I have touched on all these areas throughout my years with SNHU and have used this ePortfolio as an ability to highlight some of those areas.

For working as a team, we performed a project where we created a class jukebox project where each one of the 20+ students came together to create a data structure that took a list of soundtracks and student information and allowed it to interact with a central user interface. The code review process involved going through other student’s code and looking for security vulnerabilities, code inefficiencies as well as code structure formalities. Another class we had was all about reverse engineering code as a form of code review. This involved taking a binary file converting it to assembly and building back out a c++ version of the source code. This process was extensive and allowed for a focus on security when it came to code. To highlight the skills developed in this area I have included a code review of three of my own artifacts for enhancement within this ePortfolio. I go in depth looking for code inefficiencies and code vulnerabilities and even find a few areas that are not so obviously security flaws but assure the programs are resilient to misuse such as user input verification as well default case statements that do nothing to prevent accidental access.

For going through iterations of software design and engineering, I worked heavily on an android mobile application for a class that built out an inventory management system. The system required many iterations and is still in progress. I have made consistent progress on the project by finding areas for enhancement, laying out a design and following through. I have included and enhancement to the application within this ePortfolio.

For creating and utilizing different algorithms and data structures, I have had many classes going through the different data structures but the one class that sticks out to me was learning how to create searchable lists. We went through many different searching algorithms and applied them to our own custom structs with c++. The algorithm that stuck out to me the most was a binary search tree algorithm that was able to quickly sift through bid information for an auction. It uses a custom struct as the data structure and my own implementation of the bst on it. I have included an enhancement to the algorithm within the ePortfolio.

Finally, I have had the opportunity to gain familiarity with different databases. I have worked in a SQL class learning all the basic database management functions as well as how to query data using mySQL. However, the class that intrigued me the most was the course around noSQL databases, particularly MongoDB. This newer form of data structure seems incredibly robust and for large scale data seems to save of size drastically. I have incorporated an enhancement to some of my Python code used for working with a financial data strored in a MongoDB database as part of the ePortfolio.

All in all, this course and degree have done a lot to highlight the many different areas of software engineering and have given me a solid foundation to build on in the future.

### [Code review](https://1drv.ms/u/s!AmJiGxXF2nWng8FzsqqR1-vF4HDKzQ?e=XbZaRZ)
Before starting the project for CS 499 and adding enhancements to the different artifacts, I went through and performed an in-depth code review. This code review goes through each of the three artifacts and looks for common mistakes and areas for improvements. One area of focus was on security.

### [Android application enhancement](https://github.com/masongrosko/inventory_management_app/pull/1)
#### A. Briefly describe the artifact. What is it? When was it created?
  
The included artifact is an android mobile application that allows users to keep track of inventory through the use of a simple to use interface. The application was originally created in November 2020 for CS 360.


#### B.	Justify the inclusion of the artifact in your ePortfolio. Why did you select this item? What specific components of the artifact showcase your skills and abilities in software development? How was the artifact improved?

I selected this artifact to include in the in ePortfolio as it demonstrates my understanding of Java at a high level as well as showing my ability to create a user interface, create an android application and to work with SQL to manage an internal database. The custom user interface shows my ability to create user friendly interfaces, the underlying inventory management database files along with the table helper classes show my ability to utilize data in an effective manor, the adaptor class shows my ability to work with dynamically changing data, the three different activity classes show my ability to link different aspects together in a sensible and intuitive manor. The artifact was improved in this course by 6 changes, the first was updating the project name as found in the code review, the second was performing the recommended linting, the third was making sure that the cursors were closed after all the SQL interactions, the fourth was making sure the default action would prevent access and data overwriting in the case of someone bypassing a check, the fifth change was preventing users from adding in null data to the inventory and finally the inventory view now updates dynamically as the underlying data changes.


#### C.	Did you meet the course objectives you planned to meet with this enhancement in Module One? Do you have any updates to your outcome-coverage plans?

Yes, the planned enhancement was to have the inventory view update dynamically with data changes and that has been achieved. The increment, decrement and delete button now all have immediate feedback.


#### D.	Reflect on the process of enhancing and/or modifying the artifact. What did you learn as you were creating it and improving it? What challenges did you face?
 
While creating the application I learned all about working with product for a user. This application was built with the understanding that the end goal was to publish it to the Google Play store, so working through designing a product with an end user in mind was a great experience. I learned about creating a touch friendly UI, making sure the design style fit best practices while still being user friendly. I also learned how Android classes work in general, it was not something I had worked on before and I learned a lot about a new platform that I hope to use more in the future. Improving the artifact, I learned a lot about the code review process. Going through each step of what I did to make sure it works as intended. I also learned how to search for specific things with Android. StackOverflow has always been friendly to me, but I found all my issues to be very specific this time around, so it required some interesting searches as well as a deeper understanding of how the code works. The challenges involved were much the same with any new platform, big learning curves all over. The biggest challenge was that I had a not great understanding of how all the classes interacted with each other. It meant I had to read a lot of different resources and watch many videos to feel competent in making my own changes.

### [Binary search tree algorithm enhancement](https://github.com/masongrosko/masongrosko.github.io/blob/master/binary_search_tree/after/BinarySearchTree.cpp)
#### A.	Briefly describe the artifact. What is it? When was it created?
  
The included artifact used C++ to create a data structure that stored bid information and allowed the user to search for a certain id number quickly using a binary search tree algorithm. The script was originally created in February 2020 for CS 260.

#### B.	Justify the inclusion of the artifact in your ePortfolio. Why did you select this item? What specific components of the artifact showcase your skills and abilities in software development? How was the artifact improved?
  
I selected this artifact to include in the in ePortfolio as it demonstrates my understanding of C++ at a high level as well as showing my ability to apply a sorting algorithm to data structures of my own creation. The data structures within the script show my understanding of constructing and deconstructing custom data structures as well as my ability to communicate between them, the algorithm shows my ability to follow and apply complex logic in a meaningful way. The artifact was improved in this course by 3 changes, the first correcting a memory leakage found in the code review, the second was adding the ability to list all bids in dollar amount order, the third was creating the ability to list all bids within a certain range of amounts. All of these use the binary search tree algorithm as their basis.


#### C.	Did you meet the course objectives you planned to meet with this enhancement in Module One? Do you have any updates to your outcome-coverage plans?
  
Yes, the planned enhancement was to add the ability to search for bids by something other than id, specifically the initial idea was to search by bid value in a certain range, which was accomplished.


#### D.	Reflect on the process of enhancing and/or modifying the artifact. What did you learn as you were creating it and improving it? What challenges did you face?
 
While creating the artifact I learned all about working with custom data structures and with sorting algorithms. Learning how to communicate between data structures through pointers was something I had little experience in prior to working through this project. While improving the project I learned more about memory management as the initial version had a memory leak error. I also learned about using multiple sorting algorithms at the same time, especially interesting for a binary search tree as this means creating multiple trees that can communicate with each other on a base level. The biggest challenge in updating the code was making sure that when I removed a bid from one tree that bid had to be removed from the other tree as well. 

### [MongoDB financial data enhancement](https://github.com/masongrosko/masongrosko.github.io/blob/master/mongo_db/after/milestone_four_after.py)
#### A.	Briefly describe the artifact. What is it? When was it created?
  
The included artifact used Python and MongoDB to create a nosql database with easy to use REST API commands. The script was originally created in October 2020 for CS 340.

#### B.	Justify the inclusion of the artifact in your ePortfolio. Why did you select this item? What specific components of the artifact showcase your skills and abilities in software development? How was the artifact improved?
  
I selected this artifact to include in the in ePortfolio as it demonstrates my understanding of Python at a high level as well as showing my ability to work with complex querying and interaction with NoSQL databases. The functions within the Python file show my grasp of rest api as well as the ability to interact with local server creation. The interaction from pymongo show levels starting from basic CRUD operationsall the way to aggregation functions.

#### C.	Did you meet the course objectives you planned to meet with this enhancement in Module One? Do you have any updates to your outcome-coverage plans?
  
Yes, the planned enhancement was to add the ability to sort entries by ratio functions in particular the dividend adjusted PEG ratio, that has been completed.

#### D.	Reflect on the process of enhancing and/or modifying the artifact. What did you learn as you were creating it and improving it? What challenges did you face?
  
While creating the artifact I learned all about working with custom rest apis and with nosql databases. I have worked extensively in SQL so learning how to work with mongodb was an interesting experience. While improving the project I learned more about complex interactions with the database. Learning how to do a multi-step aggregation was something I had been a bit afraid of in the past, but the dividend adjusted PEG ratio does a four-step aggregation and does it quite well! I also lost the actual data as it was stored on a virtual machine, so I had to recreate a minimum viable dataset to accomplish my goal.

