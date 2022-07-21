#include <iostream>

#include <string>
#include <unordered_set>
#include <unordered_map>

std::unordered_map<std::string, size_t> memo;

size_t countWords(const std::unordered_set<std::string>& allWords,
                  const std::string& curWord, const size_t first, const size_t last)
{
    if(first >= last) return 0;

    std::string curSubstr = curWord.substr(first, last-first);

    if(memo.find(curSubstr) != memo.end()) return memo[curSubstr];

    size_t curMax = 0;

    if(allWords.find(curSubstr) != allWords.end()) ++curMax;

    for(size_t len = 1; len < last-first; len++)
    {
        size_t left = countWords(allWords, curWord, first, first+len);
        size_t right = countWords(allWords, curWord, first+len, last);

        if(left && right && left+right > curMax)
            curMax = left + right;
    }

    return memo[curSubstr] = curMax;
}

std::string findLargest(const std::unordered_set<std::string>& allWords)
{
    std::string maxWord;
    size_t maxCount = 0;

    for(auto curWord : allWords)
    {
        size_t curCount = countWords(allWords, curWord, 0, curWord.size());

        if((curCount > maxCount) || (curCount == maxCount && curWord.size() > maxWord.size()))
        {
            maxCount = curCount;
            maxWord = curWord;
        }
    }

    return maxWord;
}

int main()
{

    std::string res = findLargest({{"cat"}, {"banana"}, {"dog"}, {"nana"}, {"walk"}, {"walker"}, {"dogwalker"}, {"dogwalker"}});
    std::cout << "===================\nRES = " << res << '\n';
    return 0;
}
