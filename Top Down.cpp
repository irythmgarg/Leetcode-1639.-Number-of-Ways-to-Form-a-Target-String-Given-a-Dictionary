class Solution {
public:
    const int mod = 1e9 + 7;  // Modulo to prevent overflow (as per problem constraints)
    int dp[1001][1001];       // DP table to memoize results: dp[strindex][colindex]

    // Recursive helper function with memoization
    long long hlo(string &target, vector<vector<int>>& mapping, int strindex, int colindex) {
        // ✅ Base case: if we've successfully matched all characters of target
        if (strindex >= target.size()) return 1;

        // ❌ Base case: if columns are exhausted before matching the entire target
        if (colindex >= mapping[0].size()) return 0;

        // 🔁 If this subproblem has already been solved, return the cached result
        if (dp[strindex][colindex] != -1)
            return dp[strindex][colindex];

        long long take = 0;
        char ch = target[strindex];  // Current character to match

        // ✅ If the character exists in the current column, calculate the take case
        if (mapping[ch - 'a'][colindex] > 0) {
            // Multiply the number of times the character appears at this column
            // by the result of the subproblem for next character and next column
            take = (1LL * mapping[ch - 'a'][colindex] * 
                    hlo(target, mapping, strindex + 1, colindex + 1)) % mod;
        }

        // ❌ Calculate the not-take case by skipping the current column
        long long nottake = hlo(target, mapping, strindex, colindex + 1);

        // 💾 Store the result in dp and return
        return dp[strindex][colindex] = (take + nottake) % mod;
    }

    int numWays(vector<string>& words, string target) {
        int n = words[0].size();  // Number of columns (all words are same length)

        // Initialize dp array with -1 (indicating unsolved subproblems)
        memset(dp, -1, sizeof(dp));

        // 🧾 Build a mapping of character frequencies per column
        // mapping[char][col] = number of times char appears in column col
        vector<vector<int>> mapping(26, vector<int>(n, 0));
        for (const string& word : words) {
            for (int col = 0; col < n; col++) {
                mapping[word[col] - 'a'][col]++;
            }
        }

        // 🧠 Start solving from the beginning of the target and column 0
        return hlo(target, mapping, 0, 0);
    }
};
