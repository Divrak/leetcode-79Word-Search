#include <iostream>
#include <vector>

class Solution {
 public:
  bool exist(std::vector<std::vector<char>>& board, std::string word) {
    for (int i = 0; i < board.size(); ++i)
      for (int j = 0; j < board[0].size(); ++j)
        if (dfs(board, word, i, j, 0))
          return true;
    return false;
  }

 private:
  bool dfs(std::vector<std::vector<char>>& board, const std::string& word, int i, int j,
           int s) {
    if (i < 0 || i == board.size() || j < 0 || j == board[0].size())
      return false;
    if (board[i][j] != word[s] || board[i][j] == '*')
      return false;
    if (s == word.length() - 1)
      return true;

    const char cache = board[i][j];
    board[i][j] = '*';
    const bool isExist = dfs(board, word, i + 1, j, s + 1) ||
                         dfs(board, word, i - 1, j, s + 1) ||
                         dfs(board, word, i, j + 1, s + 1) ||
                         dfs(board, word, i, j - 1, s + 1);
    board[i][j] = cache;

    return isExist;
  }
};
int main (int argc, char **argv)
{
	auto solution = Solution();
	std::vector<std::vector<char>> board = {{'A', 'B', 'C', 'E'}, {'S', 'F', 'C', 'S'}, {'A', 'D', 'E', 'E'}};

	std::cout << solution.exist(board, "ABCCED") << std::endl;
	std::cout << solution.exist(board, "SEE") << std::endl;
	std::cout << solution.exist(board, "ABCB") << std::endl;
}