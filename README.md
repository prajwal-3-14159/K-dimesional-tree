# K-dimesional-tree
this is a C++ implementation of K-d trees

About K-d trees and their applications: 
  About k-d trees, It's a tree data structure where all nodes are k-dimensional data structure and 
  k-d trees themselves partiton the k-dimesional space to make a search query faster in given k-d space.
  applications of k-d trees, It's primary application is it increases the speed of finding the 
  k-nearest neighbours. for further reference: https://en.wikipedia.org/wiki/K-d_tree
  
About the implementaton:
  It's made in C++ and cmake, default value of k is set as k=3 (it can be changed), we used rand() function 
  to generate 100 random points. We also wrote a function to find knn points, in given radious r.
