import math

class Player:

    def __init__(self, depthLimit, isPlayerOne):

        self.isPlayerOne = isPlayerOne
        self.depthLimit = depthLimit

    # TODO
    # Returns a heuristic for the board position
    # Good positions for 0 pieces should be positive and good positions for 1 pieces
    # should be negative
    # this is really bad but whatever

    def heuristicHelper(i, j, board):
        piece = board[i][j]
        try:
            if board[i + 1][j] == piece and board[i + 2][j] == piece and board[i + 3][j] == piece:
                return 1000
        except:
            pass

        try:
            if board[i + 1][j] == piece and board[i + 2][j] == piece:
                return 100
        except:
            pass

        try:
            if board[i + 1][j] == piece:
                return 10
        except:
            pass

    def heuristic(self, board):
        counter = 0
        if len(board.board) == 0:
            return 0
        else:
            for i in range(board.WIDTH):
                for j in range(board.HEIGHT):
                    counter = counter + self.heuristicHelper(i, j, board)
            return counter


class PlayerMM(Player):
    def __init__(self, depthLimit, isPlayerOne):
        super().__init__(depthLimit, isPlayerOne)

    #TODO
    #returns the optimal column to move in by implementing the Minimax algorithm

    def findMove(self, board):
        result, move = self.miniMax(board, self.depthLimit, self.isPlayerOne)
        return move

    def miniMax(self, board, depth, Max):
        newState = board.isTerminal()
        if newState is not -1:
            if newState == 0:
                return 0, -1
            elif newState == 1:
                return 1000, -1
            elif newState == 2:
                return -1000, -1
        elif depth == 0:
            return self.heuristic(board), -1
        newChildren = board.children()
        if Max:
            finalResult = -math.inf
            replace = lambda x: x > finalResult
        else:
            finalResult = math.inf
            replace = lambda x: x < finalResult
        finalMove = -1
        for child in newChildren:
            childMove, childBoard = child
            tmp = self.miniMax(childBoard, depth - 1, not Max)[0]
            if replace(tmp):
                finalResult = tmp
                finalMove = childMove
        return finalResult, finalMove


class PlayerAB(Player):

    def __init__(self, depthLimit, isPlayerOne):
        super().__init__(depthLimit, isPlayerOne)


    #TODO
    #returns the optimal column to move in by implementing the Alpha-Beta algorithm

    def findMove(self, board):
        result, move = self.alphaBeta(board, self.depthLimit, -math.inf, math.inf, self.isPlayerOne)
        return move

    def alphaBeta(self, board, depth, alpha, beta, Max):
        newState = board.isTerminal()
        if newState is not -1:
            if newState == 0:
                return 0, -1
            elif newState == 1:
                return 1000, -1
            elif newState == 2:
                return -1000, -1
        elif depth == 0:
            return self.heuristic(board), -1
        newChildren = board.children()
        if Max:
            finalResult = -math.inf
            replace = lambda x: x > finalResult
        else:
            finalResult = math.inf
            replace = lambda x: x < finalResult
        finalMove = -1
        for child in newChildren:
            childMove, childBoard = child
            tmp = self.alphaBeta(childBoard, depth - 1, alpha, beta, not Max)[0]
            if replace(tmp):
                finalResult = tmp
                finalMove = childMove
            if Max:
                alpha = max(alpha, tmp)
            else:
                beta = min(beta, tmp)
            if alpha >= beta:
                break
        return finalResult, finalMove


class PlayerABDP(Player):

    def __init__(self, depthLimit, isPlayerOne):
        super().__init__(depthLimit, isPlayerOne)

        self.resolved = {}

    #TODO
    #returns the optimal column to move in by implementing the Alpha-Beta algorithm with dynamic programming
    def findMove(self, board):
        pass



#######################################################
###########Example Subclass for Testing
#######################################################

#This will inherit your findMove from above, but will override the heuristic function with
#a new one; you can swap out the type of player by changing X in "class TestPlayer(X):"
class TestPlayer(PlayerMM):

    def __init__(self, depthLimit, isPlayerOne):
        super().__init__(depthLimit, isPlayerOne)

    #define your new heuristic here
    def heurisitic(self):
        def heuristic(self, board):
            def Streak(i, j, board):
                piece = board[i][j]
                try:
                    if board[i + 1][j] == piece and board[i + 2][j] == piece and board[i + 3][j] == piece:
                        return 1000
                except:
                    pass

                try:
                    if board[i + 1][j] == piece and board[i + 2][j] == piece:
                        return 100
                except:
                    pass

                try:
                    if board[i + 1][j] == piece:
                        return 10
                except:
                    pass

            counter = 0
            if len(board.board) == 0:
                return 0
            else:
                for i in range(board.WIDTH):
                    for j in range(board.HEIGHT):
                        counter = counter + Streak(i, j, board)
                return counter