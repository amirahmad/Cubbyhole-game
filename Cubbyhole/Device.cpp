// ---------------------------------------------------------
//
// file name : Device.cpp'
// summary : This class is created for initializing window
// Data : 12/4/2018
// Author : Amir Ardroudi
//
// ---------------------------------------------------------

#include <iostream>
#include <Windows.h>

#include "Device.h"
#include "TextureManager.h"
#include "GameObject.h"
#include "Map.h"

GameObject* pPlayer;
Map* pmap;

namespace Game
{
	SDL_Renderer* Device::m_pRenderer = nullptr;

	//! Constructor
	Device::Device() : m_pWindow(nullptr), m_bIsRunning(true)
	{}

	//! Destructor
	Device::~Device()
	{
		m_pWindow = nullptr;
		m_pRenderer = nullptr;
	}

	// Initialize window
	void Device::InitWindow(const char*  title, int xPosWindow, int yPosWindow,
							int width, int height, bool fullscreen)
	{
		int flags = 0;

		if (fullscreen)
		{
			flags = SDL_WINDOW_FULLSCREEN;
		}

		//if subsystem initialized successfully 
		if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
		{
			std::cout << "Subsystems inizialized!" << std::endl;

			m_pWindow = SDL_CreateWindow(title, xPosWindow, yPosWindow, width, height, flags);
			if (m_pWindow)
			{
				std::cout << "Window created!" << std::endl;
			}

			m_pRenderer = SDL_CreateRenderer(m_pWindow , -1, 0);

			if (m_pRenderer)
			{
				SDL_SetRenderDrawColor(m_pRenderer, 255, 255, 255, 255);
				std::cout << "Renderer created!" << std::endl;
			}

			m_bIsRunning = true;
		}
		else
		{
			m_bIsRunning = false;
		}
		// creating player gameObject
		pPlayer = new GameObject("assets/Penis.png", 32, 32);
		pmap = new Map();
	}

	void Device::HandleEvents()
	{
		SDL_Event event;
		SDL_PollEvent(&event);

		switch (event.type)
		{
		case SDL_QUIT:
			m_bIsRunning = false;
			break;

		default:
			break; 
		}
	}

	void Device::Render()
	{
		// clear our renderer
		SDL_RenderClear(m_pRenderer);
		pmap->DrawMap();
		pPlayer->Render();

		SDL_RenderPresent(m_pRenderer);
	}
	void Device::Update()
	{
		pPlayer->Update();
		//pmap->LoadMap();
	}

	void Device::Clean()
	{
		SDL_DestroyWindow(m_pWindow);
		SDL_DestroyRenderer(m_pRenderer);
		SDL_Quit();

		std::cout << "game cleaned!" << std::endl;
	}

	bool Device::Running()
	{
		return m_bIsRunning;
	}

} // Game