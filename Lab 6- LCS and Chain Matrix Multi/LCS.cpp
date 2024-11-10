#include <iostream>
#include <vector>
#include <string>
using namespace std;

// Function to find LCS between two strings of grades
string findLCS(string &grades1, string &grades2)
{
    int m = grades1.length();
    int n = grades2.length();

    // Create DP table
    vector<vector<int> > dp(m + 1, vector<int>(n + 1, 0)); // Note the space between > >

    // Fill dp table
    for (int i = 1; i <= m; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            if (grades1[i - 1] == grades2[j - 1])
            {
                dp[i][j] = dp[i - 1][j - 1] + 1;
            }
            else
            {
                dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
            }
        }
    }

    // Reconstruct LCS
    string lcs = "";
    int i = m, j = n;
    while (i > 0 && j > 0)
    {
        if (grades1[i - 1] == grades2[j - 1])
        {
            lcs = grades1[i - 1] + lcs;
            i--;
            j--;
        }
        else if (dp[i - 1][j] > dp[i][j - 1])
        {
            i--;
        }
        else
        {
            j--;
        }
    }

    return lcs;
}

// Function to find LCS among multiple strings
string findLCSMultiple(vector<string> &gradesList)
{
    if (gradesList.empty())
        return "";

    string result = gradesList[0];
    for (int i = 1; i < gradesList.size(); i++)
    {
        result = findLCS(result, gradesList[i]);
    }

    return result;
}


int main()
{
    int n = 20;                   // Number of students
    vector<string> studentGrades; // Initialize empty vector

    studentGrades.push_back("AABBCCBBCCDDCCBBAACC");
    studentGrades.push_back("ABBBCCBBCCDDCCBBBACC");
    studentGrades.push_back("AABACCBBCCDDCCBBAACC");
    studentGrades.push_back("AABBCCBBCCDDCCBBAACC");
    studentGrades.push_back("AABBCCABCCDDCCBBAACC");
    studentGrades.push_back("BBBBCCBBCCDDCCBBAACC");
    studentGrades.push_back("AABBCCBBCCDDCCBBAADD");
    studentGrades.push_back("AABBBCBBCCDDCCBBAACC");
    studentGrades.push_back("AABBCCBBCCDDCCBBAACC");
    studentGrades.push_back("AABBCCBBCCDDDCBBAACC");
    studentGrades.push_back("AABBCCBBCCDDCCBBAACC");
    studentGrades.push_back("AABBCCBBCCDDCCBBBACC");
    studentGrades.push_back("AABBCCBBCCDDCCBBAACC");
    studentGrades.push_back("AABBCCBBCCDDCCBBAACC");
    studentGrades.push_back("AABBCCBBCCDDCCBBAAAC");
    studentGrades.push_back("AABBCCBBCCDDCCBBAACC");
    studentGrades.push_back("AABBCCBBCCDDCCBBAACC");
    studentGrades.push_back("AABBCCBBCCDDCCBBAACC");
    studentGrades.push_back("AABBCCBBCCDDCCBBAACC");
    studentGrades.push_back("AABBCCBBCCDDCCBBAACC");

    string lcs = findLCSMultiple(studentGrades);

    cout << "Longest Common Subsequence of grades: " << lcs << endl;
    cout << "Length of LCS: " << lcs.length() << endl;

    return 0;
}


//     studentGrades2.push_back("BBCCDDCCBBCCDDBBCCDD");
// studentGrades2.push_back("BBCCDDCCBBCCDDBBCCDA");
// studentGrades2.push_back("BBCCDDCCBBCCDDBBCCDD");
// studentGrades2.push_back("BBCCDDCCBBCCDDBBCCDD");
// studentGrades2.push_back("BBCCDDCCBBCCDDBBCCAD");
// studentGrades2.push_back("BBCCDDCCBBCCDDBBCCDD");
// studentGrades2.push_back("BBCCDDCCBBCCDDBBCCDD");
// studentGrades2.push_back("BBCCDDCCBBCCDDBBCCDD");
// studentGrades2.push_back("BBCCDDCCBBCCDDBBCCBD");
// studentGrades2.push_back("BBCCDDCCBBCCDDBBCCDD");
// studentGrades2.push_back("BBCCDDCCBBCCDDBBCCDD");
// studentGrades2.push_back("BBCCDDCCBBCCDDBBCCDD");
// studentGrades2.push_back("BBCCDDCCBBCCDDBBCCCD");
// studentGrades2.push_back("BBCCDDCCBBCCDDBBCCDD");
// studentGrades2.push_back("BBCCDDCCBBCCDDBBCCDD");
// studentGrades2.push_back("BBCCDDCCBBCCDDBBCCDD");
// studentGrades2.push_back("BBCCDDCCBBCCDDBBCCDD");
// studentGrades2.push_back("BBCCDDCCBBCCDDBBCCAD");
// studentGrades2.push_back("BBCCDDCCBBCCDDBBCCDD");
// studentGrades2.push_back("BBCCDDCCBBCCDDBBCCDD");

// studentGrades3.push_back("AAAABBBBAAAABBBBAAAA");
// studentGrades3.push_back("AAAABBBBAAAABBBBAAAB");
// studentGrades3.push_back("AAAABBBBAAAABBBBAAAA");
// studentGrades3.push_back("AAAABBBBAAAABBBBAAAA");
// studentGrades3.push_back("AAAABBBBAAAABBBBAAAA");
// studentGrades3.push_back("AAAABBBBAAAABBBBAAAA");
// studentGrades3.push_back("AAAABBBBAAAABBBBAABA");
// studentGrades3.push_back("AAAABBBBAAAABBBBAAAA");
// studentGrades3.push_back("AAAABBBBAAAABBBBAAAA");
// studentGrades3.push_back("AAAABBBBAAAABBBBAAAA");
// studentGrades3.push_back("AAAABBBBAAAABBBBAAAA");
// studentGrades3.push_back("AAAABBBBAAAABBBBAAAA");
// studentGrades3.push_back("AAAABBBBAAAABBBBAAAA");
// studentGrades3.push_back("AAAABBBBAAAABBBBAAAA");
// studentGrades3.push_back("AAAABBBBAAAABBBBAAAA");
// studentGrades3.push_back("AAAABBBBAAAABBBBAAAA");
// studentGrades3.push_back("AAAABBBBAAAABBBBAAAA");
// studentGrades3.push_back("AAAABBBBAAAABBBBAAAA");
// studentGrades3.push_back("AAAABBBBAAAABBBBAAAA");
// studentGrades3.push_back("AAAABBBBAAAABBBBAAAA");

// studentGrades4.push_back("CCDDFFCCDDFFCCDDFFCC");
// studentGrades4.push_back("CCDDFFCCDDFFCCDDFFCC");
// studentGrades4.push_back("CCDDFFCCDDFFCCDDFFCC");
// studentGrades4.push_back("CCDDFFCCDDFFCCDDFFCC");
// studentGrades4.push_back("CCDDFFCCDDFFCCDDFFDC");
// studentGrades4.push_back("CCDDFFCCDDFFCCDDFFCC");
// studentGrades4.push_back("CCDDFFCCDDFFCCDDFFCC");
// studentGrades4.push_back("CCDDFFCCDDFFCCDDFFCC");
// studentGrades4.push_back("CCDDFFCCDDFFCCDDFFCC");
// studentGrades4.push_back("CCDDFFCCDDFFCCDDFFCC");
// studentGrades4.push_back("CCDDFFCCDDFFCCDDFFCC");
// studentGrades4.push_back("CCDDFFCCDDFFCCDDFFCC");
// studentGrades4.push_back("CCDDFFCCDDFFCCDDFFCC");
// studentGrades4.push_back("CCDDFFCCDDFFCCDDFFCC");
// studentGrades4.push_back("CCDDFFCCDDFFCCDDFFCC");
// studentGrades4.push_back("CCDDFFCCDDFFCCDDFFCC");
// studentGrades4.push_back("CCDDFFCCDDFFCCDDFFCC");
// studentGrades4.push_back("CCDDFFCCDDFFCCDDFFCC");
// studentGrades4.push_back("CCDDFFCCDDFFCCDDFFCC");
// studentGrades4.push_back("CCDDFFCCDDFFCCDDFFCC");

// studentGrades1.push_back("ABCDDCBAABCDDCBAABCD");
// studentGrades1.push_back("AABBCCDDAABBCCDDAABB");
// studentGrades1.push_back("BBCCDDAABBCCDDAABBCC");
// studentGrades1.push_back("CCDDAABBCCDDAABBCCDD");
// studentGrades1.push_back("DDAABBCCDDAABBCCDDAA");
// studentGrades1.push_back("AADDCCBBDDAACCBBDDAA");
// studentGrades1.push_back("BBCCAADDBBCCAADDBBCC");
// studentGrades1.push_back("CCBBDDAACCBBDDAACCBB");
// studentGrades1.push_back("DDCCBBAADDCCBBAADDCC");
// studentGrades1.push_back("AABBDDCCAABBDDCCAABB");
// studentGrades1.push_back("BBAADDCCBBAADDCCBBAA");
// studentGrades1.push_back("CCDDAABBCCDDAABBCCDD");
// studentGrades1.push_back("DDCCBBAADDCCBBAADDCC");
// studentGrades1.push_back("AACCBBDDAACCBBDDAACC");
// studentGrades1.push_back("BBDDAACCBBDDAACCBBDD");
// studentGrades1.push_back("CCAABBDDCCAABBDDCCAA");
// studentGrades1.push_back("DDBBCCAADDBBCCAADDBB");
// studentGrades1.push_back("AADDCCBBAADDCCBBAADD");
// studentGrades1.push_back("BBAACDDBBAACCDDBBAA");
// studentGrades1.push_back("CCBBDDAACCBBDDAACCBB");

/*studentGrades2.push_back("ABABABABCDCDCDCDABAB");
studentGrades2.push_back("CDCDCDABABABABCDCDCD");
studentGrades2.push_back("ABABCDCDABABCDCDABAB");
studentGrades2.push_back("CDCDABABCDCDABABCDCD");
studentGrades2.push_back("ABCDABCDABCDABCDABCD");
studentGrades2.push_back("CDABCDABCDABCDABCDAB");
studentGrades2.push_back("BCDABCDABCDABCDABCDA");
studentGrades2.push_back("DABCDABCDABCDABCDABC");
studentGrades2.push_back("ABCDDCBAABCDDCBAABCD");
studentGrades2.push_back("DCBAABCDDCBAABCDDCBA");
studentGrades2.push_back("CDABABCDCDABABCDCDAB");
studentGrades2.push_back("ABCDBACDABCDBACABABC");
studentGrades2.push_back("BCDABCDABCDABCDABCDA");
studentGrades2.push_back("CDABCDABCDABCDABCDAB");
studentGrades2.push_back("ABCDABCDABCDABCDABCD");
studentGrades2.push_back("CDABABCDCDABABCDCDAB");
studentGrades2.push_back("ABABCDCDABABCDCDABAB");
studentGrades2.push_back("CDCDABABCDCDABABCDCD");
studentGrades2.push_back("ABCDDCBAABCDDCBAABCD");
studentGrades2.push_back("DCBAABCDDCBAABCDDCBA