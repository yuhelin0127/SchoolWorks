#######################     Max Product Problem     ###########################

# The Max Product Problem is stated as follows:

# Given a rope of length n (where n > 2), cut the rope into different parts of 
# lengths less than n such that the product of all the lengths is the 
# maximum possible. 

# i.e. the max product of a rope of length 10 is 3 * 3 * 4 = 36 ... (3 + 3 + 4 = 10)
# ...  the max product of a rope of length 5 is 2 * 3 = 6  ... (2 + 3 = 5)

# This can be written as:
# maxProduct(n) = max(i * (n - i), maxProduct(n - i) * i) for all i in {1, 2, 3 .. n}

##############################################################################

class MaxProductFinder:

    def __init__(self):
        pass
    def findMaxProduct(self, n):
        if n == 0 or n == 1: 
            return 0
        max_product = 0
        for i in range(1, n - 1):
            max_product = max(max_product, max(i * (n - i), self.findMaxProduct(n - i) * i))
        return max_product

    B = {}

    def findMaxProductDP(self, n):
        if n == 1 or n == 0:
            return 0
        if n in self.B:
            return self.B[n]
        max_product = 0
        for i in range(1, n - 1):
            max_product = max(max_product, max(i * (n - i), self.findMaxProductDP(n - i) * i))
        self.B[n] = max_product
        return max_product

if __name__ == "__main__":
    f = MaxProductFinder()
    print(f.findMaxProductDP(151))