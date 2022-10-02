#include <gtest/gtest.h>
#include <string>

#include "Utils.h"

TEST(UtilsTest, VerifyTokenizeStringIntoUniqueWords) {
    const char DELIMITER = ' ';
    {
        std::string input;
        EXPECT_EQ(0, utils::TokenizeStringIntoUniqueWords(input, DELIMITER).size());
    }
    {
        std::string input = "     ";
        EXPECT_EQ(0, utils::TokenizeStringIntoUniqueWords(input, DELIMITER).size());
    }
    {
        std::string input = " ";
        EXPECT_EQ(0, utils::TokenizeStringIntoUniqueWords(input, DELIMITER).size());
    }
    {
        std::string input = "a horse and a dog";
        const auto& output = utils::TokenizeStringIntoUniqueWords(input, DELIMITER);
        EXPECT_EQ(4, output.size());
        EXPECT_TRUE(output.contains("a"));
        EXPECT_TRUE(output.contains("horse"));
        EXPECT_TRUE(output.contains("and"));
        EXPECT_TRUE(output.contains("dog"));
    }
    {
        std::string input = "   a horse and a dog";
        const auto& output = utils::TokenizeStringIntoUniqueWords(input, DELIMITER);
        EXPECT_EQ(4, output.size());
        EXPECT_TRUE(output.contains("a"));
        EXPECT_TRUE(output.contains("horse"));
        EXPECT_TRUE(output.contains("and"));
        EXPECT_TRUE(output.contains("dog"));
    }
    {
        std::string input = "   a  horse  and a   dog ";
        const auto& output = utils::TokenizeStringIntoUniqueWords(input, DELIMITER);
        EXPECT_EQ(4, output.size());
        EXPECT_TRUE(output.contains("a"));
        EXPECT_TRUE(output.contains("horse"));
        EXPECT_TRUE(output.contains("and"));
        EXPECT_TRUE(output.contains("dog"));
    }
    {
        std::string input = "   a  a a";
        const auto& output = utils::TokenizeStringIntoUniqueWords(input, DELIMITER);
        EXPECT_EQ(1, output.size());
        EXPECT_TRUE(output.contains("a"));
    }
    {
        std::string input = "a   a  a a a   ";
        const auto& output = utils::TokenizeStringIntoUniqueWords(input, DELIMITER);
        EXPECT_EQ(1, output.size());
        EXPECT_TRUE(output.contains("a"));
    }
    {
        std::string input = "horse  a a";
        const auto& output = utils::TokenizeStringIntoUniqueWords(input, DELIMITER);
        EXPECT_EQ(2, output.size());
        EXPECT_TRUE(output.contains("a"));
        EXPECT_TRUE(output.contains("horse"));
    }
}