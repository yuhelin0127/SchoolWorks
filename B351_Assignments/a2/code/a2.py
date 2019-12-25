import csv
import itertools

class Board():

    ##########################################
    ####   Constructor
    ##########################################
    def __init__(self, filename):

        #initialize all of the variables
        self.n2 = 0
        self.n = 0
        self.spaces = 0
        self.board = None
        self.valsInRows = None
        self.valsInCols = None
        self.valsInBoxes = None
        self.unSolved = None

        #load the file and initialize the in-memory board with the data
        self.loadSudoku(filename)


    #loads the sudoku board from the given file
    def loadSudoku(self, filename):

        with open(filename) as csvFile:
            self.n = -1
            reader = csv.reader(csvFile)
            for row in reader:

                #Assign the n value and construct the approriately sized dependent data
                if self.n == -1:
                    self.n = int(len(row) ** (1/2))
                    if not self.n ** 2 == len(row):
                        raise Exception('Each row must have n^2 values! (See row 0)')
                    else:
                        self.n2 = len(row)
                        self.spaces = self.n ** 4
                        self.board = {}
                        self.valsInRows = [set() for _ in range(self.n2)]
                        self.valsInCols = [set() for _ in range(self.n2)]
                        self.valsInBoxes = [set() for _ in range(self.n2)]
                        self.unSolved = set(itertools.product(range(self.n2), range(self.n2)))

                #check if each row has the correct number of values
                else:
                    if len(row) != self.n2:
                        raise Exception('Each row mus\t have the same number of values. (See row ' + str(reader.line_num - 1) + ')')

                #add each value to the correct place in the board; record that the row, col, and box contains value
                for index, item in enumerate(row):
                    if not item == '':
                        self.board[(reader.line_num-1, index)] = int(item)
                        self.valsInRows[reader.line_num-1].add(int(item))
                        self.valsInCols[index].add(int(item))
                        self.valsInBoxes[self.rcToBox(reader.line_num-1, index)].add(int(item))
                        self.unSolved.remove((reader.line_num-1, index))

    ##########################################
    ####   Move Functions - YOUR IMPLEMENTATIONS GO HERE
    ##########################################

    #gets the unsolved space with the most current constraints
    def getMostConstrainedUnsolvedSpace(self):
        MostCUSpace = (0,0)                 # our MostConstrainedUnsolvedSpace
        ConsNum = 0
        for space in self.unSolved:
            Most = self.valsInRows[space[0]].union(self.valsInCols[space[1]])
            Most = Most.union(self.valsInBoxes[self.rcToBox(space[0], space[1])])
            Num = len(Most)
            if Num > ConsNum:
                ConsNum = Num
                MostCUSpace = space
        return MostCUSpace




    #returns True if the move is not blocked by any constraints
    def isValidMove(self,space,val):
        if val < 0 or val > self.n2:
            # The value should within 1 - n2
            return False
        if val in self.valsInRows[space[0]] or val in self.valsInCols[space[1]]:
            # The value should not in the space's row and space's column
            return False
        if val in self.valsInBoxes[self.rcToBox(space[0], space[1])]:
            # The value should not in the inner box as well
            return False
        if space not in self.unSolved:
            # Space should be in the unSolved set
            return False
        if space[1] < 0 or space[1] > self.n2 or space[0] < 0 or space[0] > self.n2:
            # Space should have the right row and column
            return False
        else:
            # Valid value!
            return True

    #makes a move, records that its in the row, col, and box, and removes the space from unSolved
    def makeMove(self, space, val):
        self.board[space] = val                # Update the value to the board
        self.valsInRows[space[0]].add(val)     # add the value to the right row
        self.valsInCols[space[1]].add(val)     # add the value to the right column
        self.valsInBoxes[self.rcToBox(space[0],space[1])].add(val)        # add the value to the right inner box
        self.unSolved.remove(space)            # remove the space from the unSolved set


    #removes the move, its record in its row, col, and box, and adds the space back to unSolved
    def removeMove(self, space, val):
        del self.board[space]                       # remove space from the board
        self.valsInRows[space[0]].remove(val)       # remove val from the right row
        self.valsInCols[space[1]].remove(val)       # remove val from the right column
        self.valsInBoxes[self.rcToBox(space[0], space[1])].remove(val)  # add the value to the right inner box
        self.unSolved.add(space)                    # add space back to the unSolved set

    ##########################################
    ####   Utility Functions
    ##########################################

    #converts a given row and column to its inner box number
    def rcToBox(self, row, col):
        return self.n * (row // self.n) + col // self.n


    #prints out a command line representation of the board
    def print(self):
        for r in range(self.n2):
            #add row divider
            if r % self.n == 0 and not r == 0:
                if self.n2 > 9:
                    print("  " + "----" * self.n2)
                else:
                    print("  " + "---" * self.n2)

            row = ""

            for c in range(self.n2):

                if (r,c) in self.board:
                    val = self.board[(r,c)]
                else:
                    val = None

                #add column divider
                if c % self.n == 0 and not c == 0:
                    row += " | "
                else:
                    row += "  "

                #add value placeholder
                if self.n2 > 9:
                    if val is None: row += "__"
                    else: row += "%2i" % val
                else:
                    if val is None: row += "_"
                    else: row += str(val)
            print(row)

class Solver:

    ##########################################
    ####   Constructor
    ##########################################
    def __init__(self,filename):
        self.board = Board(filename)
        self.solve()

    ##########################################
    ####   Solver
    ##########################################

    #recursively selects the most constrained unsolved space and attempts
    #to assign a value to it
    #
    #upon completion, it will leave the board in the solved state (or original
    #state if a solution does not exist)
    def solve(self):
        if len(self.board.unSolved) == 0:
            # if each space has a valid value, the puzzle is solved
            return True
        space = self.board.getMostConstrainedUnsolvedSpace()
        # start from the mostConstrainedUnsolvedSpace tuple
        for val in range(1, self.board.n2 + 1):
            # let's choose a value from 1 to n2 + 1 to see
            if self.board.isValidMove(space,val):
                # if the value is valid, make the move!
                self.board.makeMove(space,val)
                if self.solve():
                    # if the puzzel is solved, return true
                    return True
                else:
                    self.board.removeMove(space,val)
        return False


if __name__ == "__main__":

    #change this to the input file that you'd like to test
    s = Solver('tests/example.csv')
