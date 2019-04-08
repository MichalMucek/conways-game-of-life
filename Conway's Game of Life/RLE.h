#pragma once
#include <string>


namespace runLengthEncoding
{
	std::string encode(std::string textToEncode);
	std::string decode(std::string encodedText);
	int getRunLengthDigitsCount(const std::string &encodedText, const int &firstSemicolonIndex);
	int getNextSemicolonIndex(const std::string &text, const int &startingTextCharacterIndex);
	int getEncodedTextNextCharacterIndex(int encodedTextCharacterIndex, const int &runLenghtDigitsCount);
	void appendCharactersToDecodedText(std::string &decodedText, char character, int runLength);
}