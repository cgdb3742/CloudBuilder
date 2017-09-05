#include "InstructionBoardFlow.h"
#include "InstructionBoard.h"
#include "InstructionSquare.h"


InstructionBoardFlow::InstructionBoardFlow(GameContext & gameContext, InstructionBoard & board):
	GameEntity(gameContext),
	mBoard(board),
	mFlowPos(0.0f)
{
}


InstructionBoardFlow::~InstructionBoardFlow()
{
}

void InstructionBoardFlow::computeLinks()
{
	mLinkUp.clear();
	mLinkDown.clear();
	mLinkLeft.clear();
	mLinkRight.clear();

	mLinkUp = std::vector<std::vector<bool>>(mBoard.getWidth(), std::vector<bool>(mBoard.getHeight() - 1, false));
	mLinkDown = std::vector<std::vector<bool>>(mBoard.getWidth(), std::vector<bool>(mBoard.getHeight() - 1, false));
	mLinkLeft = std::vector<std::vector<bool>>(mBoard.getWidth() - 1, std::vector<bool>(mBoard.getHeight(), false));
	mLinkRight = std::vector<std::vector<bool>>(mBoard.getWidth() - 1, std::vector<bool>(mBoard.getHeight(), false));

	for (unsigned int i = 0; i < mBoard.getWidth(); i++)
	{
		for (unsigned int j = 0; j < mBoard.getHeight(); j++)
		{
			InstructionSquare& square = mBoard.get(i, j);

			if (i > 0)
			{
				if (square.isPossibleNextDir(Enums::eDir::Left))
				{
					mLinkLeft[i - 1][j] = true;
				}
			}

			if (i < mBoard.getWidth() - 1)
			{
				if (square.isPossibleNextDir(Enums::eDir::Right))
				{
					mLinkRight[i][j] = true;
				}
			}

			if (j > 0)
			{
				if (square.isPossibleNextDir(Enums::eDir::Up))
				{
					mLinkUp[i][j - 1] = true;
				}
			}

			if (j < mBoard.getHeight() - 1)
			{
				if (square.isPossibleNextDir(Enums::eDir::Down))
				{
					mLinkDown[i][j] = true;
				}
			}
		}
	}
}

void InstructionBoardFlow::updateCurrent(sf::Time dt)
{
	mFlowPos = fmod((mFlowPos + dt.asSeconds()), 1.0f);
}

void InstructionBoardFlow::drawCurrent(sf::RenderTarget & target)
{
	sf::Vector2f squareSize = mBoard.getSquareSize();
	float relativeThickness = 0.1f;

	//Step 1 : Draw links between InstructionSquares
	//Step 2 : Draw link directions
	for (unsigned int i = 0; i < mBoard.getWidth(); i++)
	{
		for (unsigned int j = 0; j < mBoard.getHeight(); j++)
		{
			if (mBoard.get(i, j).IsAssigned())
			{
				sf::RectangleShape linkCenter(squareSize * relativeThickness);
				linkCenter.setPosition(sf::Vector2f(mTopLeftCorner.x + squareSize.x * (static_cast<float>(i) + 0.5f - relativeThickness / 2.0f), mTopLeftCorner.y + squareSize.y * (static_cast<float>(j) + 0.5f - relativeThickness / 2.0f)));
				linkCenter.setFillColor(sf::Color(255, 255, 255, 127));
				target.draw(linkCenter);
			}

			if (i < mBoard.getWidth() - 1)
			{
				if (mLinkLeft[i][j] || mLinkRight[i][j])
				{
					sf::RectangleShape linkHorizontal(sf::Vector2f(squareSize.x * (1.0f - relativeThickness), squareSize.y * relativeThickness));
					linkHorizontal.setPosition(sf::Vector2f(mTopLeftCorner.x + squareSize.x * (static_cast<float>(i) + 0.5f + relativeThickness / 2.0f), mTopLeftCorner.y + squareSize.y * (static_cast<float>(j) + 0.5f - relativeThickness / 2.0f)));
					linkHorizontal.setFillColor(sf::Color(255, 255, 255, 127));
					target.draw(linkHorizontal);

					if (mLinkLeft[i][j])
					{
						sf::RectangleShape linkPos(squareSize * relativeThickness);
						linkPos.setPosition(sf::Vector2f(mTopLeftCorner.x + squareSize.x * (static_cast<float>(i) + 0.5f - relativeThickness / 2.0f + (1.0f - mFlowPos)), mTopLeftCorner.y + squareSize.y * (static_cast<float>(j) + 0.5f - relativeThickness / 2.0f)));
						linkPos.setFillColor(sf::Color(255, 255, 255));
						target.draw(linkPos);
					}

					if (mLinkRight[i][j])
					{
						sf::RectangleShape linkPos(squareSize * relativeThickness);
						linkPos.setPosition(sf::Vector2f(mTopLeftCorner.x + squareSize.x * (static_cast<float>(i) + 0.5f - relativeThickness / 2.0f + mFlowPos), mTopLeftCorner.y + squareSize.y * (static_cast<float>(j) + 0.5f - relativeThickness / 2.0f)));
						linkPos.setFillColor(sf::Color(255, 255, 255));
						target.draw(linkPos);
					}
				}
			}

			if (j < mBoard.getHeight() - 1)
			{
				if (mLinkUp[i][j] || mLinkDown[i][j])
				{
					sf::RectangleShape linkVertical(sf::Vector2f(squareSize.x * relativeThickness, squareSize.y * (1.0f - relativeThickness)));
					linkVertical.setPosition(sf::Vector2f(mTopLeftCorner.x + squareSize.x * (static_cast<float>(i) + 0.5f - relativeThickness / 2.0f), mTopLeftCorner.y + squareSize.y * (static_cast<float>(j) + 0.5f + relativeThickness / 2.0f)));
					linkVertical.setFillColor(sf::Color(255, 255, 255, 127));
					target.draw(linkVertical);

					if (mLinkUp[i][j])
					{
						sf::RectangleShape linkPos(squareSize * relativeThickness);
						linkPos.setPosition(sf::Vector2f(mTopLeftCorner.x + squareSize.x * (static_cast<float>(i) + 0.5f - relativeThickness / 2.0f), mTopLeftCorner.y + squareSize.y * (static_cast<float>(j) + 0.5f - relativeThickness / 2.0f + (1.0f - mFlowPos))));
						linkPos.setFillColor(sf::Color(255, 255, 255));
						target.draw(linkPos);
					}

					if (mLinkDown[i][j])
					{
						sf::RectangleShape linkPos(squareSize * relativeThickness);
						linkPos.setPosition(sf::Vector2f(mTopLeftCorner.x + squareSize.x * (static_cast<float>(i) + 0.5f - relativeThickness / 2.0f), mTopLeftCorner.y + squareSize.y * (static_cast<float>(j) + 0.5f - relativeThickness / 2.0f + mFlowPos)));
						linkPos.setFillColor(sf::Color(255, 255, 255));
						target.draw(linkPos);
					}
				}
			}
		}
	}
}
