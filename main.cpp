#include <iostream>
#include <vector>
/*
	function DFS(i, j, k = 0) {
		if k == len(word) return TRUE
		if board[i][j] != word[k] return FALSE

		board[i][j] = '!' // Invalid character to prevent going back a traversed path

		if  ( DFS(i, j-1, k+1)
			 OR DFS(i, j+1, k+1)
			 OR DFS(i+1, j, k+1)
			 OR DFS(i-1, j, k+1) )
		   return TRUE

		board[i][j] = word[k] // backtracking and restoring the value
	}

	for (i = 0; i < m; i++)
		for (j = 0; j < n; j++)
			if DFS(i, j) return TRUE

	return FALSE
}
*/
struct Coord
{
	int x, y;
};
class Solution
{
	char left {};
	char right {};
	char up {};
	char down {};
	char currChar {};

	std::vector<Coord> busyCoords;
	std::vector<char> choosingSide {'u', 'r', 'd', 'l'};
	std::vector<Coord> startCoords;
public:
	bool isBusyCoord(Coord inCurrentCoord)
	{
		for (int i {}; i < busyCoords.size(); ++i)
		{
			if (inCurrentCoord.x == busyCoords[i].x && inCurrentCoord.y == busyCoords[i].y)
			{
				return true;
			}
		}
		return false;
	}

	void setStartPos(std::vector<std::vector<char>> &inBoard, std::string inWord)
	{
		for (int i {}; i < inBoard.size(); ++i)
		{
			for (int j {}; j < inBoard[i].size(); ++j)
			{
				if (inWord[0] == inBoard[i][j])
					startCoords.push_back(Coord(j, i));
			}
		}
	}

	int getNumberOptions(Coord inCoord)
	{
		return 0;
	}
	void setSides(std::vector<std::vector<char>> &inBoard, std::string inWord)
	{
		for (int i {}; i < inBoard.size(); ++i)
		{
			for (int j {}; j < inBoard[i].size(); ++j)
			{
				left = (j - 1 < 0) ? ' ' : inBoard[i][j - 1];
				right = (j + 1 <= inBoard[i].size() - 1) ? inBoard[i][j + 1] : ' ';
				up = (i > 0) ? inBoard[i - 1][j] : ' ';
				down = (i + 1 > inBoard.size() - 1) ? ' ' : inBoard[i + 1][j];
			}
		}
	}

	bool exist(std::vector<std::vector<char>> &inBoard, std::string inWord)
	{
		int foundIndex {};
		std::string boardWord;

		setStartPos(inBoard, inWord);
		setSides(inBoard, inWord);

		for (int c {}; c < startCoords.size(); ++c)
		{
			for (int j {startCoords[c].x}, i {startCoords[c].y}; true;)
			{

				currChar = inBoard[i][j];

				if (foundIndex == 0 && inWord[foundIndex] == currChar && isBusyCoord({i, j}))
				{
					busyCoords.push_back({i, j});
					++foundIndex;
				}
				if (inWord[foundIndex] == up && isBusyCoord({i, j}))
				{
					busyCoords.push_back({i, j});
					++foundIndex;
					--i;
				}
				if (inWord[foundIndex] == right && isBusyCoord({i, j}))
				{
					busyCoords.push_back({i, j});
					++foundIndex;
					++j;
				}
				if (inWord[foundIndex] == down && isBusyCoord({i, j}))
				{
					busyCoords.push_back({i, j});
					++foundIndex;
					++i;
				}
				if (inWord[foundIndex] == left && isBusyCoord({i, j}))
				{
					busyCoords.push_back({i, j});
					++foundIndex;
					--j;
				}

				if (foundIndex == inWord.size())
					goto exit;

				foundIndex = 0;
				break;
			}
		}

	exit: {}
		return true;
	}
};

int main(int argc, char **argv)
{
	auto solution = Solution();
	std::vector<std::vector<char>> board = {{'A', 'B', 'C', 'E'}, {'S', 'F', 'C', 'S'}, {'A', 'D', 'E', 'E'}};

	std::cout << solution.exist(board, "ABCCED") << std::endl;
	std::cout << solution.exist(board, "SEE") << std::endl;
	std::cout << solution.exist(board, "ABCB") << std::endl;
}
