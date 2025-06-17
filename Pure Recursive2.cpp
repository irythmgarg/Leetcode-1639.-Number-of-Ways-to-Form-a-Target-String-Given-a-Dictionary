class Solution {
public:
    const int mod = 1e9 + 7;  // Modulo value to avoid integer overflow

    // Recursive function to count the number of ways to form the target string
    long long hlo(string &target, vector<vector<int>>& mapping, int strindex, int colindex) {
        // ✅ Base case: If we've matched the entire target string
        if (strindex >= target.size()) return 1;

        // ❌ Base case: If we run out of columns in the word matrix before completing target
        if (colindex >= mapping[0].size()) return 0;

        long long take = 0;
        char ch = target[strindex];  // Current character to match in target

        // ✅ If current column contains the needed character
        if (mapping[ch - 'a'][colindex] > 0) {
            // Take the character from this column and move to next character and column
            take = (1LL * mapping[ch - 'a'][colindex] * 
                    hlo(target, mapping, strindex + 1, colindex + 1)) % mod;
        }

        // ❌ Skip this column and try to match the same character in the next column
        long long nottake = hlo(target, mapping, strindex, colindex + 1);

        // Total ways = ways by taking + ways by not taking
        return (take + nottake) % mod;
    }

    int numWays(vector<string>& words, string target) {
        int n = words[0].size();  // All words are guaranteed to have same length

        // mapping[char][column]: frequency of each character 'a' to 'z' at each column index
        vector<vector<int>> mapping(26, vector<int>(n, 0));

        // Populate the mapping array from the input words
        for (const string& word : words) {
            for (int col = 0; col < n; col++) {
                mapping[word[col] - 'a'][col]++;
            }
        }

        // Start the recursion from the 0th character of target and 0th column
        return hlo(target, mapping, 0, 0);
    }
};
