#include "Actor.h"

#include <cmath>

#include "SDLMgmt.h"

Actor::Actor(SDL_Renderer* renderer, const char* szFilepath)
{
	m_fPosX = 0.0f;
	m_fPosY = 0.0f;

	m_iWidth = 0;
	m_iHeight = 0;

	m_soRect = { 0, 0, 0, 0 };

	if(SDL_WasInit(SDL_INIT_VIDEO) != SDL_INIT_VIDEO)
	{
		throw "Actor::Actor() - SDL not initialized";
	}

	m_soRenderer = renderer;

	if(m_soRenderer == NULL)
	{
		throw "Actor::Actor() - No renderer";
	}

	LoadTexture(szFilepath);
}

Actor::~Actor()
{
	if(m_soTexture != NULL)
	{
		SDL_DestroyTexture(m_soTexture);
		m_soTexture = NULL;
	}
}

float Actor::GetPosX()
{
	return m_fPosX;
}

float Actor::GetPosY()
{
	return m_fPosY;
}

int Actor::GetPosXInt()
{
	return (int)std::round(m_fPosX);
}

int Actor::GetPosYInt()
{
	return (int)std::round(m_fPosY);
}

void Actor::SetPosX(float fX)
{
	m_fPosX = fX;
	m_soRect.x = (int)std::round(fX);
}

void Actor::SetPosY(float fY)
{
	m_fPosY = fY;
	m_soRect.y = (int)std::round(fY);
}

void Actor::SetPosX(int iX)
{
	SetPosX((float)iX);
}

void Actor::SetPosY(int iY)
{
	SetPosY((float)iY);
}

void Actor::SetPos(float fX, float fY)
{
	SetPosX(fX);
	SetPosY(fY);
}

void Actor::SetPos(int iX, int iY)
{
	SetPosX(iX);
	SetPosY(iY);
}

void Actor::Move(float fX, float fY)
{
	SetPos(m_fPosX + fX, m_fPosY + fY);
}

void Actor::Move(int iX, int iY)
{
	Move((float)iX, (float)iY);
}

int Actor::GetWidth()
{
	return m_iWidth;
}

int Actor::GetHeight()
{
	return m_iHeight;
}

void Actor::SetWidth(int iWidth)
{
	m_iWidth = iWidth;
	m_soRect.w = iWidth;
}

void Actor::SetHeight(int iHeight)
{
	m_iHeight = iHeight;
	m_soRect.h = iHeight;
}

void Actor::LoadTexture(const char* szFilepath)
{
	m_soTexture = SDLLoadBMPtoTexture(m_soRenderer, szFilepath);

	int w;
	int h;

	SDL_QueryTexture(m_soTexture, NULL, NULL, &w, &h);

	SetWidth(w);
	SetHeight(h);
}

void Actor::Render()
{
	SDL_RenderCopy(m_soRenderer, m_soTexture, NULL, &m_soRect);
}