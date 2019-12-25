# Assignment 1
import math

#################################
# Problem 1
#################################
# Objectives:
# (1) Write a recursive function to compute the nth fibonacci number

def fib(n):
    if n == 0:
        return 0
    elif n == 1:
        return 1;
    else:
        return fib(n - 1) + fib(n - 2)



#################################
# Problem 2
#################################
# Objectives:
# (1) Write a function which returns a list of the first and last items in a given list

def firstLast(n):
    if (len(n) == 1):
        return n
    else:
        return [n[0], n[-1]]




#################################
# Problem 3
#################################
# Objectives:
# (1) Write a function which takes a matrix and returns the transpose of that matrix
# Note: A matrix is represented as a 2-d array: [[1,2,3],[4,5,6],[7,8,9]]


def transpose(matrix):
    result = []
    for i in range(len(matrix[0])):
        a = []
        for j in range(len(matrix)):
            matrix[j][i]
            a.append(matrix[j][i])
        result.append(a)
    return result




#################################
# Problem 4
#################################
# Objectives:
# (1) Write a function which takes two points of the same dimension, and finds the euclidean distance between them
# Note: A point is represented as a tuple: (0,0)

def euclidean(p1,p2):
    return math.sqrt(sum([(x - y) ** 2 for x, y in zip(p1, p2)]))





#################################
# Problem 5
#################################

# A Node is an object
# - value : Number
# - children : List of Nodes
class Node:
    def __init__(self, value, children):
        self.value = value
        self.children = children


exampleTree = Node(1,[Node(2,[]),Node(3,[Node(4,[Node(5,[]),Node(6,[Node(7,[])])])])])



# Objectives:
# (1) Write a function to calculate the sum of every node in a tree (iteratively)

def sumNodes(root):
    Sum = 0
    thislevel = [root]
    while thislevel:
        nextlevel = list()
        for n in thislevel:
            Sum += n.value
            for i in n.children:
                nextlevel.append(i)
        thislevel = nextlevel
    return Sum

# (2) Write a function to calculate the sum of every node in a tree (recursively)

def sumNodesRec(root):
    if (len(root.children) == 0): return root.value
    else:
        Sum = root.value
        for i in root.children:
            Sum += sumNodesRec(i)
        return Sum

#################################
# Problem 6
#################################
# Objectives:
# (1) Write a function compose, which takes an inner and outer function
# and returns a new function applying the inner then the outer function to a value

def compose(f_outer, f_inner):
    f = lambda x: f_outer(f_inner(x))
    return f





#################################
# Bonus
#################################
# Objectives:
# (1) Create a string which has each level of the tree on a new line

def treeToString(root):
    result = ""
    thislevel = [root]
    while thislevel:
        nextlevel = list()
        for n in thislevel:
            result += str(n.value)
            for i in n.children:
                nextlevel.append(i)
        result += "\n"
        thislevel = nextlevel
    return result

