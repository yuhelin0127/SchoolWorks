#######################        BOARD CLASS        ###########################
# The Board class is the data structure that holds the Connect 4 boards and the game operations

# The Connect 4 board is 7 cells wide and 6 cells tall

# The underlying data structure is a 2-d list
# The first dimension is the column; the second dimension is the row
# Note: each column ONLY contains pieces (no empty cell). Thus, the array is jagged.

# Every cell in the above list contains either a 0 or a 1. Player 1 is represented by 0 tiles, and Player
# 2 is represented by 1 tiles. Yes, this is confusing, but it helps with the efficiency of the code.
#
##############################################################################
class Board(object):

    #static class variables - shared across all instances
    HEIGHT = 6
    WIDTH = 7

    ########################   Constructor   ###############################
    #
    #
    #  No arguments --> Creates a brand new empty board
    #
    #  orig         --> If you pass an existing board as the orig argument,
    #                   this will create a copy of that board
    #
    #  hash         --> Constructs a board from an integer hash heuristic; to
    #                   be used in conjunction with the hash method
    #
    # *NOTE: orig and hash are mutually exclusive
    ########################################################################
    def __init__(self, orig=None, hash=None):

        #copy
        if(orig):
            self.board = [list(col) for col in orig.board]
            self.numMoves = orig.numMoves
            self.lastMove = orig.lastMove
            return

        #creates from hash - NOTE: Does not understand move order
        elif(hash):
            self.board = []
            self.numMoves = 0
            self.lastMove = None

            #convert to base 3
            digits = []
            while hash:
                digits.append(int(hash % 3))
                hash //= 3

            col = []
            
            for item in digits:
                
                #2 indicates new column
                if item == 2:
                    self.board.append(col)
                    col = []
                
                #otherwise directly append base number
                else:
                    col.append(item)
                    self.numMoves += 1
            return

        #create new
        else:
            self.board = [[] for x in range(self.WIDTH)]
            self.numMoves = 0
            self.lastMove = None
            return


    ########################################################################
    #                           Mutations
    ########################################################################

    # Puts a pirce in the appropriate column and checks to see if it was a winning move
    # Pieces are either 1 or 0; automatically decided
    # NOTE: does NOT check if the move is valid
    def makeMove(self, column):
        #update board data
        piece = self.numMoves % 2
        self.lastMove = (piece, column)
        self.numMoves += 1
        self.board[column].append(piece)


    ########################################################################
    #                           Observations
    ########################################################################

    # Generates a list of the valid children of the board
    # A child is of the form (move_to_make_child, child_object)
    def children(self):
        children = []
        for i in range(7):
            if len(self.board[i]) < 6:
                child = Board(self)
                child.makeMove(i)
                children.append((i, child))
        return children

    # TODO
    # Returns:
    #  -1 if game is not over
    #   0 if the game is a draw
    #   1 if player 1 wins
    #   2 if player 2 wins
    def isTerminal(self):
        for i in range(self.WIDTH):
            for j in range(self.HEIGHT):

                try:
                    if self.board[i][j] == self.board[i + 1][j] == self.board[i + 2][j] == self.board[i + 3][j]:
                        if self.board[i][j] == 0:
                            return 1
                        else:
                            return 2
                except:pass

                try:
                    if self.board[i][j] == self.board[i][j + 1] == self.board[i][j + 2] == self.board[i][j + 3]:
                        if self.board[i][j] == 0:
                            return 1
                        else:
                            return 2
                except:pass

                try:
                    if self.board[i][j] == self.board[i + 1][j + 1] == self.board[i + 2][j + 2] == self.board[i + 3][j + 3]:
                        if self.board[i][j] == 0:
                            return 1
                        else:
                            return 2
                except:pass

                try:
                    if self.board[i][j] == self.board[i + 1][j - 1] == self.board[i + 2][j - 2] == self.board[i + 3][j - 3] and j >= 3:
                        if self.board[i][j] == 0:
                            return 1
                        else:
                            return 2
                except:pass

        if self.isFull():  # Draw case
            return 0
        else:  # continue case
            return -1


    # Retuns a unique decimal number for each board object based on the
    # underlying data
    # NOTE: it is not important that you understand how this works
    def hash(self):

        power = 0
        hash = 0

        for column in self.board:

            # add 0 or 1 depending on piece
            for piece in column:
                hash += piece * (3 ** power)
                power += 1

            # add a 2 to indicate end of column
            hash += 2 * (3 ** power)
            power += 1

        return hash

    ########################################################################
    #                           Utilities
    ########################################################################

    # Return true iff the game is full
    def isFull(self):
        return self.numMoves == 42

    # Prints out a visual representation of the board
    # X's are 1's and 0's are 0s
    def print(self):
        print("")
        print("+" + "---+" * self.WIDTH)
        for rowNum in range(self.HEIGHT - 1, -1, -1):
            row = "|"
            for colNum in range(self.WIDTH):
                if len(self.board[colNum]) > rowNum:
                    row += " " + ('X' if self.board[colNum][rowNum] else 'O') + " |"
                else:
                    row += "   |"
            print(row)
            print("+" + "---+" * self.WIDTH)




