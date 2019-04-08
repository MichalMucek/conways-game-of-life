#include "RLE.h"


namespace runLengthEncoding
{
	const char SEMICOLON_CHARACTER = ';';

	std::string encode(std::string textToEncode)
	{
		std::string encodedText = "";

		char currentlyEncodedCharacter;
		int runLength;

		if (textToEncode.size() > 0)
		{
			currentlyEncodedCharacter = textToEncode[0];
			runLength = 1;

			for (int characterIndex = 1; characterIndex < (int) textToEncode.size(); characterIndex++)
			{
				if (currentlyEncodedCharacter != textToEncode[characterIndex])
				{
					encodedText += currentlyEncodedCharacter;

					if (runLength > 1)
						encodedText += SEMICOLON_CHARACTER + std::to_string(runLength) + SEMICOLON_CHARACTER;

					currentlyEncodedCharacter = textToEncode[characterIndex];
					runLength = 1;
				}
				else
					runLength++;
			}
		}

		return encodedText;
	}
	
	std::string decode(std::string encodedText)
	{
		std::string decodedText = "";

		char currentlyDecodedCharacter;
		int encodedTextCurrentlyDecodedCharacterIndex = 0;
		int semicolonIndex;
		int runLength;
		int runLengthDigitsCount;

		while (encodedTextCurrentlyDecodedCharacterIndex < (int) encodedText.size())
		{
			currentlyDecodedCharacter = encodedText[encodedTextCurrentlyDecodedCharacterIndex];

			if (encodedTextCurrentlyDecodedCharacterIndex != encodedText.size() - 1)
			{
				if (encodedText[encodedTextCurrentlyDecodedCharacterIndex + 1] == SEMICOLON_CHARACTER)
				{
					semicolonIndex = encodedTextCurrentlyDecodedCharacterIndex + 1;
					runLengthDigitsCount = getRunLengthDigitsCount(encodedText, semicolonIndex);

					runLength = std::stoi(
						encodedText.substr(
							semicolonIndex + 1,
							runLengthDigitsCount
						)
					);

					encodedTextCurrentlyDecodedCharacterIndex = getEncodedTextNextCharacterIndex(encodedTextCurrentlyDecodedCharacterIndex, runLengthDigitsCount);
				}
				else
				{
					runLength = 1;
					encodedTextCurrentlyDecodedCharacterIndex++;
				}
			}
			else
			{
				runLength = 1;
				encodedTextCurrentlyDecodedCharacterIndex++;
			}

			appendCharactersToDecodedText(decodedText, currentlyDecodedCharacter, runLength);
		}

		return decodedText;
	}

	int getRunLengthDigitsCount(const std::string &encodedText, const int &firstSemicolonIndex)
	{
		int secondSemicolonIndex = getNextSemicolonIndex(encodedText, firstSemicolonIndex);
		int runLengthDigitsCount = secondSemicolonIndex - firstSemicolonIndex - 1;

		return runLengthDigitsCount;
	}
	
	int getNextSemicolonIndex(const std::string &text, const int &startingTextCharacterIndex)
	{
		int nextSemicolonIndex;

		for (nextSemicolonIndex = startingTextCharacterIndex + 1;
			text[nextSemicolonIndex] != SEMICOLON_CHARACTER;
			nextSemicolonIndex++);

		return nextSemicolonIndex;
	}

	int getEncodedTextNextCharacterIndex(int encodedTextCharacterIndex, const int &runLenghtDigitsCount)
	{
		const int DISTANCE_TO_FIRST_SEMICOLON_FROM_CHARACTER = 1;
		const int DISTANCE_TO_NEXT_CHARACTER_FROM_RUN_LENGTH_LAST_DIGIT = 2;
		
		encodedTextCharacterIndex += DISTANCE_TO_FIRST_SEMICOLON_FROM_CHARACTER
			+ runLenghtDigitsCount + DISTANCE_TO_NEXT_CHARACTER_FROM_RUN_LENGTH_LAST_DIGIT;

		return encodedTextCharacterIndex;
	}

	void appendCharactersToDecodedText(std::string &decodedText, char character, int runLength)
	{
		for (int i = 0; i < runLength; i++)
			decodedText += character;
	}
}