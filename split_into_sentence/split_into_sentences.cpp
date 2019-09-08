#include "test_runner.h"

#include <vector>

using namespace std;

// Объявляем Sentence<Token> для произвольного типа Token
// синонимом vector<Token>.
// Благодаря этому в качестве возвращаемого значения
// функции можно указать не малопонятный вектор векторов,
// а вектор предложений — vector<Sentence<Token>>.
template<typename Token>
using Sentence = vector<Token>;

// Класс Token имеет метод bool IsEndSentencePunctuation() const
template<typename Token>
vector<Sentence<Token>> SplitIntoSentences(vector<Token> tokens) {
    // Напишите реализацию функции, не копируя объекты типа Token

    vector<Sentence<Token>> result;
    Sentence <Token> sentence;

    for (size_t i = 0; i < tokens.size(); ++i) {
        if (tokens[i].IsEndSentencePunctuation() && sentence.empty()) {
            sentence.push_back(move(tokens[i]));
        } else if (tokens[i].IsEndSentencePunctuation() && !sentence.empty()) {
            if (sentence.back().IsEndSentencePunctuation()) {
                sentence.push_back(move(tokens[i]));
            } else {
                sentence.push_back(move(tokens[i]));
            }
        } else if (!tokens[i].IsEndSentencePunctuation() && !sentence.empty()) {
            if (sentence.back().IsEndSentencePunctuation()) {
                result.push_back(move(sentence));
                sentence.clear();
            }
            sentence.push_back(move(tokens[i]));
        } else if (!tokens[i].IsEndSentencePunctuation() && sentence.empty()) {
            sentence.push_back(move(tokens[i]));
        }
        if (i == tokens.size() - 1) {
            result.push_back(move(sentence));
        }
    }
    return result;
}


struct Token {
    string data;
    bool is_end_sentence_punctuation = false;

    bool IsEndSentencePunctuation() const {
        return is_end_sentence_punctuation;
    }

    bool operator==(const Token &other) const {
        return data == other.data && is_end_sentence_punctuation == other.is_end_sentence_punctuation;
    }


};

ostream &operator<<(ostream &stream, const Token &token) {
    return stream << token.data;
}

// Тест содержит копирования объектов класса TestToken.
// Для проверки отсутствия копирований в функции SplitIntoSentences
// необходимо написать отдельный тест.
void TestSplitting() {
    ASSERT_EQUAL(
        SplitIntoSentences(vector<Token>({{"Split"},
                                              {"into"},
                                              {"sentences"},
                                              {"!"}})),
        vector<Sentence<Token>>({
                                        {{"Split"}, {"into"}, {"sentences"}, {"!"}}
                                    })
    );

    ASSERT_EQUAL(
        SplitIntoSentences(vector<Token>({{"Split"},
                                              {"into"},
                                              {"sentences"},
                                              {"!", true}})),
        vector<Sentence<Token>>({
                                        {{"Split"}, {"into"}, {"sentences"}, {"!", true}}
                                    })
    );

    ASSERT_EQUAL(
        SplitIntoSentences(vector<Token>({{"Split"},
                                              {"into"},
                                              {"sentences"},
                                              {"!", true},
                                              {"!", true},
                                              {"Without"},
                                              {"copies"},
                                              {".", true}})),
        vector<Sentence<Token>>({
                                        {{"Split"},   {"into"},   {"sentences"}, {"!", true}, {"!", true}},
                                        {{"Without"}, {"copies"}, {".", true}},
                                    })
    );

    ASSERT_EQUAL(
        SplitIntoSentences(vector<Token>({{"!", true},{"Split"},
                                          {"into"},
                                          {"sentences"},
                                          {"!"}})),
        vector<Sentence<Token>>({
                                    {{"!", true}},
                                    {{"Split"}, {"into"}, {"sentences"}, {"!"}}
                                })
    );

    ASSERT_EQUAL(
        SplitIntoSentences(vector<Token>({{"!", true},
                                          {"!", true},
                                          {"Split"},
                                          {"into"},
                                          {"sentences"},
                                          {"!"}})),
        vector<Sentence<Token>>({
                                    {{"!", true}, {"!", true}},
                                    {{"Split"}, {"into"}, {"sentences"}, {"!"}}
                                })
    );

    ASSERT_EQUAL(
        SplitIntoSentences(vector<Token>({{"Split"},
                                          {"into"},
                                          {"sentences"},
                                          {"!", true},
                                          {"!", true}})),
        vector<Sentence<Token>>({
                                    {{"Split"}, {"into"}, {"sentences"}, {"!", true}, {"!", true}}
                                })
    );

    ASSERT_EQUAL(
        SplitIntoSentences(vector<Token>({{"Split"},
                                          {"into"},
                                          {"sentences"}})),
        vector<Sentence<Token>>({
                                    {{"Split"}, {"into"}, {"sentences"}}
        })
    );

    ASSERT_EQUAL(
        SplitIntoSentences(vector<Token>({{"!", true},
                                          {"Split"},
                                          {"into"},
                                          {"sentences"},
                                          {"!", true},
                                          {"!", true},
                                          {"!", true},
                                          {"!"},
                                          {"!", true}})),
        vector<Sentence<Token>>({
                                    {{"!", true}},
                                    {{"Split"}, {"into"}, {"sentences"}, {"!", true}, {"!", true}, {"!", true}},
                                    {{"!"}, {"!", true}}
                                })
    );

}

int main() {
    TestRunner tr;
    RUN_TEST(tr, TestSplitting);
    return 0;
}
