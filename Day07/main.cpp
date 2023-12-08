#include "aocHelper.hpp"

#include <regex>
#include <algorithm>

/**
 * Define the Instances of the String Manipulation classes
*/
TruncateString truncateString;
RemoveDuplicates removeDuplicates;
ClearEmptyRows clearEmptyRows;
ReplaceString replaceString;
ReplaceStringRegex replaceStringRegex;
InsertString insertString;
TokenizeData tokenizeData;

std::vector<std::vector<std::vector<std::string>>> tokenizedData;
void printTokenizedData(std::vector<std::vector<std::vector<std::string>>>& tokenizedData);
void processData(InputData& data);
void processDataPartTwo(InputData& data);

int main() {
    // Read the Data in using mode 1 from File "input_test.txt" -> TODO Exception and Mode Diff.
    InputData bernhard(1);
    InputData bernhard_part_two(2);
    
    //bernhard << "example.txt";
    bernhard << "puzzle_input.txt";

    //bernhard_part_two << "example.txt";
    bernhard_part_two << "puzzle_input.txt";

    std::vector<int> indices;
    
    // Print out actual readin Data
    std::cout << bernhard << std::endl;
    //std::cout << bernhard_part_two << std::endl;

    processData(bernhard);    
    
    processDataPartTwo(bernhard_part_two);

    //bernhard << tokenizeData(&tokenizedData, " ");

    //printTokenizedData(tokenizedData);

    return 0;
}

struct Hand {
    int bid;
    int cardRank;       // 0-6

    int handOffset;

    std::string cards;

    std::string cardOrder = "23456789TJQKA";

    Hand(int bid, std::string cards, bool part2 = false) : bid(bid), cards(cards) {
        handOffset = 0;
        if(part2)
            cardOrder = "J23456789TQKA";
        if(part2) 
            cardRank = this->getScoreJokerd();
        else
            cardRank = this->getScore();
    }

    int calculateWinningScore() {
        //std::cout << cards << ": " << bid << "*" << (cardRank + handOffset) << "\n";
        // Lol- all indices have to occur anyhow -> just use index of sorted hand...
        //return bid * (cardRank + handOffset);
        return bid * handOffset;
    }

    // Throw away thought of classical scoring 0-6, instead use frequency-based Scoringsystem
    int getScoreJokerd() {
        int jokerCount = std::count(cards.begin(), cards.end(), 'J');

        int frequencies[13] = {0};

        std::string tmp = cardOrder;
        std::reverse(tmp.begin(), tmp.end());

        for(int i = 0; i < cards.size(); i++)
            frequencies[static_cast<int>(tmp.find(cards[i]))]++;

        std::sort(frequencies, frequencies + 12);       // Omit the Joker during Sorting, as it is only byproduct

        frequencies[11] += jokerCount;                  // Number of highest amount of cards that is are not jokers gets increased by the Joker-Amount
        int tmpScore = (2 * frequencies[11]) - 2;       // Times 2 to beat Specials (FullHouse and 2 Pairs) - 2 For norming

        if(frequencies[10] == 2) {
            tmpScore++;             // if second most amount of cards was a pair as well increase the Score -> Special (Full House and 2 Pairs)
        }

        return tmpScore;
    }

    int getScore() {
        std::string scoreCards = cards;
        std::sort(scoreCards.begin(), scoreCards.end());

        // Top Down as Full House etc contain Pair
        if(scoreCards[0] == scoreCards[4]) {
            return 6; // Five of a kind
        }

        if(scoreCards[0] == scoreCards[3] || scoreCards[1] == scoreCards[4]) {
            return 5; // Four of a kind
        }

        if((scoreCards[0] == scoreCards[2] && scoreCards[3] == scoreCards[4]) ||
            (scoreCards[0] == scoreCards[1] && scoreCards[2] == scoreCards[4])) {
            return 4; // Full house
        }

        if(scoreCards[0] == scoreCards[2] || scoreCards[1] == scoreCards[3] || scoreCards[2] == scoreCards[4]) {
            return 3; // Three of a kind
        }

        if((scoreCards[0] == scoreCards[1] && scoreCards[2] == scoreCards[3]) ||
            (scoreCards[0] == scoreCards[1] && scoreCards[3] == scoreCards[4]) ||
            (scoreCards[1] == scoreCards[2] && scoreCards[3] == scoreCards[4])) {
            return 2; // Two pairs
        }

        if(scoreCards[0] == scoreCards[1] || scoreCards[1] == scoreCards[2] ||
            scoreCards[2] == scoreCards[3] || scoreCards[3] == scoreCards[4]) {
            return 1; // One pair
        }

        // If none of the above, it's a high card
        return 0;
    }

    bool operator<(const Hand& hand) const {
        if(cardRank != hand.cardRank) {
            return cardRank < hand.cardRank;
        }

        for(int i = 0; i < cards.size() && i < hand.cards.size(); i++) {
            if(cardOrder.find(cards[i]) != cardOrder.find(hand.cards[i])) {
                return cardOrder.find(cards[i]) < cardOrder.find(hand.cards[i]);
            }
        }

        // If all cards are equal, compare based on the length of the cards string
        return cards.size() < hand.cards.size();
    }
};

void processData(InputData& data) {
    std::vector<std::vector<std::vector<std::string>>> tokenizedData;
    data << tokenizeData(&tokenizedData, " ");
    printTokenizedData(tokenizedData);

    std::vector<std::vector<std::string>> myModifiedData = tokenizedData[0];

    std::vector<Hand> hands;

    for(std::vector<std::string>& elem : myModifiedData) {
        hands.push_back(Hand(stol(elem[1]), elem[0]));
    }

    int accumulator = 0;
    
    std::sort(hands.begin(), hands.end());

    int cardOffset = 0;

    for(int i = 0; i < hands.size(); i++) {
        //if(i < (hands.size() - 1) && hands[i].cardRank == hands[i + 1].cardRank)
        //    hands[i + 1].handOffset = ++cardOffset;
        //else
        //    cardOffset = 0;
        hands[i].handOffset = ++cardOffset;

        std::cout << hands[i].cards << "  " << hands[i].cardRank << " " << hands[i].handOffset << " " << hands[i].calculateWinningScore() << "\n";
        accumulator += hands[i].calculateWinningScore();
    }

    std::cout << "Your solution to part one is: " << accumulator << "\n";
}

void processDataPartTwo(InputData& data) {
    std::vector<std::vector<std::vector<std::string>>> tokenizedData;
    data << tokenizeData(&tokenizedData, " ");
    printTokenizedData(tokenizedData);

    std::vector<std::vector<std::string>> myModifiedData = tokenizedData[0];

    std::vector<Hand> hands;

    for(std::vector<std::string>& elem : myModifiedData) {
        hands.push_back(Hand(stol(elem[1]), elem[0], true));
    }

    int accumulator = 0;
    
    std::sort(hands.begin(), hands.end());

    int cardOffset = 0;

    for(int i = 0; i < hands.size(); i++) {
        hands[i].handOffset = ++cardOffset;

        std::cout << hands[i].cards << "  " << hands[i].cardRank << " " << hands[i].handOffset << " " << hands[i].calculateWinningScore() << "\n";
        accumulator += hands[i].calculateWinningScore();
    }

    std::cout << "Your solution to part two is: " << accumulator << "\n";
}

void printTokenizedData(std::vector<std::vector<std::vector<std::string>>>& tokenizedData) {
    for(std::vector<std::vector<std::string>> paragraph : tokenizedData) {
        for(std::vector<std::string> string : paragraph) {
            for(std::string token : string) {
                std::cout << token << "\t\t";
            }
            std::cout << "\n";
        }
        std::cout << "=== PARAGRAPH ===" << '\n';
    }
}

/**
 * Snippets
*/
// Sort Array
// std::sort(std::begin(array), std::end(array));

// String to Int
// stoi(string)