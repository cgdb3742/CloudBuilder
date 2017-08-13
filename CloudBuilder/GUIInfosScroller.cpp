#include "GUIInfosScroller.h"
#include "GUIInfosContainer.h"



GUIInfosScroller::GUIInfosScroller(GUIInfosContainer & container, int dir, sf::Vector2f positionRatio):
	GUIButton(positionRatio),
	mContainer(container),
	mDir(dir)
{
	mShape.setPointCount(3);
	mBasicShape.setPointCount(3);

	if (dir > 0)
	{
		mBasicShape.setPoint(0, sf::Vector2f(0.0f, 0.0f));
		mBasicShape.setPoint(1, sf::Vector2f(1.0f, 0.0f));
		mBasicShape.setPoint(2, sf::Vector2f(0.5f, 1.0f));
	}
	else
	{
		mBasicShape.setPoint(0, sf::Vector2f(0.0f, 1.0f));
		mBasicShape.setPoint(1, sf::Vector2f(1.0f, 1.0f));
		mBasicShape.setPoint(2, sf::Vector2f(0.5f, 0.0f));
	}
}


GUIInfosScroller::~GUIInfosScroller()
{
}

void GUIInfosScroller::scroll()
{
	if (mDir < 0)
	{
		mContainer.scrollUp();
	}
	else
	{
		mContainer.scrollDown();
	}
}

void GUIInfosScroller::clicked()
{
	scroll();
}

//void GUIInfosScroller::handleEventCurrent(const sf::Event & event)
//{
//	switch (event.type)
//	{
//	case sf::Event::MouseButtonReleased:
//		if (event.mouseButton.button == sf::Mouse::Button::Left && event.mouseButton.x > mTopLeftCorner.x && event.mouseButton.x < mTopLeftCorner.x + mBoundingBox.x && event.mouseButton.y > mTopLeftCorner.y && event.mouseButton.y < mTopLeftCorner.y + mBoundingBox.y)
//		{
//			if (containsPoint(sf::Vector2f(event.mouseButton.x, event.mouseButton.y)))
//			{
//				scroll();
//			}
//		}
//		break;
//	}
//}

void GUIInfosScroller::drawCurrent(sf::RenderTarget & target)
{
	if ((mDir < 0 && mContainer.canScrollUp()) || (mDir > 0 && mContainer.canScrollDown()))
	{
		//sf::RectangleShape button(mBoundingBox);
		//button.setPosition(mTopLeftCorner);
		//button.setFillColor(sf::Color(0, 255, 0, 0));
		//button.setOutlineThickness(1.0f);
		//button.setFillColor(sf::Color(0, 191, 0));
		//target.draw(button);

		sf::ConvexShape toDraw(mShape);
		toDraw.setFillColor(sf::Color(0, 191, 0));
		toDraw.setOutlineThickness(1.0f);
		toDraw.setOutlineColor(sf::Color(0, 255, 0));
		target.draw(toDraw);
	}
}

void GUIInfosScroller::setPositionCurrent(sf::Vector2f minCorner, sf::Vector2f maxBox)
{
	GUIButton::setPositionCurrent(minCorner, maxBox);

	mShape = mBasicShape;
	for (unsigned int i = 0; i < mShape.getPointCount(); i++)
	{
		sf::Vector2f p = mShape.getPoint(i);
		p.x *= mBoundingBox.x;
		p.y *= mBoundingBox.y;
		p += mTopLeftCorner;
		mShape.setPoint(i, p);
	}
}

bool GUIInfosScroller::containsPoint(sf::Vector2f point)
{
	//Rapid check for obvious cases
	if (point.x <= mTopLeftCorner.x || point.x >= mTopLeftCorner.x + mBoundingBox.x || point.y <= mTopLeftCorner.y || point.y >= mTopLeftCorner.y + mBoundingBox.y)
	{
		return false;
	}

	int previous_side = 0;
	unsigned int n = mShape.getPointCount();

	for (unsigned int i = 0; i < n; i++)
	{
		sf::Vector2f p1 = mShape.getPoint(i);
		sf::Vector2f p2 = mShape.getPoint((i + 1) % n);
		sf::Vector2f aff_seg = p2 - p1;
		sf::Vector2f aff_point = point - p1;
		float cross_product = (aff_seg.x * aff_point.y) - (aff_seg.y * aff_point.x);
		int current_side = 0;
		if (cross_product < 0)
		{
			current_side = -1;
		}
		else if (cross_product > 0)
		{
			current_side = 1;
		}

		if (current_side == 0)
		{
			return false;
		}
		else if (previous_side == 0)
		{
			previous_side = current_side;
		}
		else if (current_side != previous_side)
		{
			return false;
		}
	}

	return true;
}
