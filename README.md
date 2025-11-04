[![Review Assignment Due Date](https://classroom.github.com/assets/deadline-readme-button-22041afd0340ce965d47ae6ef1cefeee28c7c493a6346c4f15d667ab976d596c.svg)](https://classroom.github.com/a/7RAFczHS)
# Project 4 - HashTable

Project description can be found [in the repo](Project4_HashTable.pdf)

Place your complexity analysis below.

insert:\
**It would be O(n^3) since there is 2 nested for loops in the big for loop. It could go on for the lentgh of input 3 times
which would be O(n^3)**
remove: \
**it's O(n) because each for loop would be O(n). It's like that because it could go on forever until the length
of the list is met**\
contains: \
**it's O(n) because each for loop would be O(n). It's like that because it could go on forever until the length
of the list is met. It's also the same as remove and get since they're all almost the same**\
get:\
**it's O(n) because each for loop would be O(n). It's like that because it could go on forever until the length
of the list is met. It's also the same as contains and remove since they're all almost the same**\
operator[]:\
**it's O(n) because each for loop would be O(n). It's like that because it could go on forever until the length
of the list is met. Like every method in this project its basically the same so the time complexity would also be 
the same**
---