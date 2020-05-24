#ifndef ACTOR_H
#define ACTOR_H

#include <SDL.h>

class Actor
{
private:
	float m_fPosX;
	float m_fPosY;

	int m_iWidth;
	int m_iHeight;

	SDL_Rect m_soRect;

	SDL_Renderer* m_soRenderer;
	SDL_Texture* m_soTexture;

	void UpdateRect();

public:
	Actor(SDL_Renderer* renderer, const char* szFilepath);
	~Actor();

	float GetPosX();
	float GetPosY();
	int GetPosXInt();
	int GetPosYInt();

	void SetPosX(float fX);
	void SetPosY(float fY);
	void SetPosX(int iX);
	void SetPosY(int iY);
	void SetPos(float fX, float fY);
	void SetPos(int iX, int iY);

	void Move(float fX, float fY);
	void Move(int iX, int iY);

	int GetWidth();
	int GetHeight();
	void SetWidth(int iWidth);
	void SetHeight(int iHeight);

	void LoadTexture(const char* szFilepath);

	void Render();
};

#endif //ACTOR_H