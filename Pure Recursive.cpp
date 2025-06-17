class Solution {
public:
    const int mod = 1e9 + 7;  // Modulo to prevent integer overflow

    // Recursive helper function to count number of ways to form target
    long long hlo(string &target, unordered_map<long long, unordered_map<char, int>> &mp, int strindex, int colindex) {
        // Base case: If we have formed the entire target string
        if (strindex >= target.length())
            return 1;

        // Base case: If we have exhausted all columns in the word matrix but target is still left
        if (colindex >= mp.size())
            return 0;

        long long take = 0;

        // Check if current target character exists at this column
        if (mp[colindex].count(target[strindex])) {
            // Option to take current character: count * recurse for the next character and next column
            take = (mp[colindex][target[strindex]] * hlo(target, mp, strindex + 1, colindex + 1)) % mod;
        }

        // Option to skip this column and try forming target from the next column
        long long nottake = hlo(target, mp, strindex, colindex + 1) % mod;

        // Total ways is sum of both options
        return (take + nottake) % mod;
    }

    int numWays(vector<string> &words, string target) {
        // Preprocessing: Count frequency of each character at each column position
        unordered_map<long long, unordered_map<char, int>> mp;
        for (int i = 0; i < words.size(); i++) {
            for (int j = 0; j < words[i].length(); j++) {
                mp[j][words[i][j]]++;
            }
        }

        // Start recursive process from target index 0 and column index 0
        return hlo(target, mp, 0, 0);
    }
};
