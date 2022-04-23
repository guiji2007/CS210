import re
import string

def DisplayMenu():
    print("Enter 1: Produce a list of all items purchased in a given day along with the number of times each item was purchased.")
    print("Enter 2: Produce a number representing how many times a specific item was purchased in a given day.")
    print("Enter 3: Produce a text-based histogram listing all items purchased in a given day, along with a representation of the number of times each item was purchased.")
    return 0

def PrintGrocery(): 
    file = open("GroceryList.txt")    # open the txt file and read the file contents

    contents = file.read().splitlines() # get rid of lines after read the elements from file
    groceryList = []    # create a list to store non duplicate grocery list
    groceryDict ={}     # create a dictionary to store the grocery and its number of occurence
    for i in contents:  # loop through the read file and add elements to grocery list and create keys for the dictionary
        if i not in groceryList:
            groceryList.append(i)
            groceryDict[i] = 0
   
    for i in contents:  # nested loop to count the number of occurence of each element in the list
        for j in groceryList:
            if i == j:
                groceryDict[i] +=1
    for key in groceryDict: # loop through the dictionary and print key and value
        print(key, ":", groceryDict[key])  
    
    file.close()
   
    return 0;

def PrintGroceryItem(groceryItem):
    num1 = 0
    file = open("GroceryList.txt")    

    contents = file.read().splitlines()
     
    for i in contents:  # loop to count the number of occurence of the specific item in the list
        if i == groceryItem:
            num1+=1
    print(groceryItem, ":", num1)

    file.close()
    return 0;

def WriteFrequencyFile():
    file1 = open("GroceryList.txt", "r")    # open the txt file and read the file contents
    file2 = open("frequency.dat","w") # open a new file named "frequency.dat"

    contents = file1.read().splitlines() # get rid of lines after read the elements from file
    groceryList = []    # create a list to store non duplicate grocery list
    groceryDict ={}     # create a dictionary to store the grocery and its number of occurence
    for i in contents:  # loop through the read file and add elements to grocery list and create keys for the dictionary
        if i not in groceryList:
            groceryList.append(i)
            groceryDict[i] = 0
    for i in contents:  # nested loop to count the number of occurence of each element in the list
        for j in groceryList:
            if i == j:
                groceryDict[i] +=1
    file1.close()
    for key in groceryDict: # loop through the dictionary and write the key and its value to frequency.dat
        file2.write(key)
        file2.write(" ")
        file2.write(str(groceryDict[key])) 
        file2.write(" ")
       
    
    file2.close()
    
   
    return 0;
    

