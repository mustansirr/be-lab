import sys

class Queens:
    def __init__(self, n):
        self.n = n
        self.board = [-1] * n
        self.solutions = []

    def __is_safe(self, row: int, col: int) -> bool:
        for i in range(row):
            if (self.board[i] == col or 
                self.board[i] - i == col - row or 
                self.board[i] + i == row + col):
                return False
        return True

    def __place_queens(self):
        def backtrack(row: int):
            if row == self.n:
                self.solutions.append(self.board[:])  # Store a copy of the board
                return

            for col in range(self.n):
                if self.__is_safe(row, col):
                    self.board[row] = col
                    backtrack(row + 1)
                    self.board[row] = -1
        backtrack(0)

    def place_n_show(self):
        self.__place_queens()

        # Display all solutions
        print(f"Total Solutions: {len(self.solutions)}\n")

        for idx, solution in enumerate(self.solutions, 1):
            print(f"Solution {idx}:")
            
            board = [["." for _ in range(self.n)] for _ in range(self.n)]
            for row, col in enumerate(solution):
                board[row][col] = "Q"

            for row in board:
                print(" ".join(row))
            print("\n")

if __name__ == "__main__":
    if len(sys.argv) != 2:
        exit("Usage: python csp.py <n>")

    n = int(sys.argv[1])

    queens = Queens(n)
    queens.place_n_show()