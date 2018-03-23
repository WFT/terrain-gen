
#include "TrGame.hpp"

TrGame::TrGame() {
  // Initialize
  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    printf("SDL could not initialize - SDL Error: %s\n", SDL_GetError());
    exit(1);
  }

  // Create window
  m_SDLWindow = SDL_CreateWindow("test_driving", SDL_WINDOWPOS_UNDEFINED,
                                 SDL_WINDOWPOS_UNDEFINED, sz(K_DISPLAY_SIZE_X),
                                 sz(K_DISPLAY_SIZE_Y), SDL_WINDOW_SHOWN);
  if (m_SDLWindow == NULL) {
    printf("Window could not be created - SDL Error: %s\n", SDL_GetError());
    exit(1);
  }

  // Create renderer for window
  m_SDLRenderer = SDL_CreateRenderer(m_SDLWindow, -1, SDL_RENDERER_ACCELERATED);
  if (m_SDLRenderer == NULL) {
    printf("Renderer could not be created - SDL Error: %s\n", SDL_GetError());
    exit(1);
  }

  SDL_SetRenderDrawBlendMode(m_SDLRenderer, SDL_BLENDMODE_BLEND);

  if (TTF_Init() == -1) {
    printf("TTF_Init: %s\n", TTF_GetError());
    exit(2);
  }

  // setup for rendering loop
  m_quit = false;

  // create texture for map
  m_mapTexture =
      SDL_CreateTexture(m_SDLRenderer, SDL_PIXELFORMAT_ARGB8888,
                        SDL_TEXTUREACCESS_STATIC, K_MAP_SIZE_X, K_MAP_SIZE_Y);

  m_map = new TrMap(K_MAP_SIZE_Y, K_MAP_SIZE_X);

  m_xOff = 0;
  m_yOff = 0;

  m_speed = 1;

  // initialize random number generator for rain
  m_xrandEngine = std::default_random_engine(m_xrandDevice());
  m_yrandEngine = std::default_random_engine(m_yrandDevice());
  // TODO: _X vs _Y??
  m_xrandDist = std::uniform_int_distribution<int>(0, K_MAP_SIZE_X);
  m_yrandDist = std::uniform_int_distribution<int>(0, K_MAP_SIZE_Y);

  // initialize framerate counter
  m_deltaTime = 0;
  m_frames = 0;
  m_frameRate = 30;
  // double  averageFrameTimeMilliseconds = 33.333;

  m_font = TTF_OpenFont("anirb.ttf", 26);
  if (!m_font) {
    printf("TTF_OpenFont: %s\n", TTF_GetError());
    // handle error
  }

  // setup game loop
  // m_gameState = new TrGameLoop(this);
  m_gameState = new TrMainMenuLoop(this);
}

TrGame::~TrGame() {
  // delete m_terrain;

  TTF_Quit();
  SDL_DestroyTexture(m_mapTexture);
  SDL_DestroyRenderer(m_SDLRenderer);
  SDL_DestroyWindow(m_SDLWindow);
  SDL_Quit();
}

void TrGame::handleKey(int SDLKey) {
  switch (SDLKey) {
    case SDLK_q:
      m_quit = true;
      break;
    case SDLK_LSHIFT:
      m_speed = 10;
      break;
    case SDLK_RSHIFT:
      m_speed = 1;
      break;
    case SDLK_UP:
      m_yOff -= c_pixelSize * m_speed;
      break;
    case SDLK_DOWN:
      m_yOff += c_pixelSize * m_speed;
      break;
    case SDLK_LEFT:
      m_xOff -= c_pixelSize * m_speed;
      break;
    case SDLK_RIGHT:
      m_xOff += c_pixelSize * m_speed;
      break;
  }
}

void TrGame::run() {
  while (!m_quit) {
    clock_t beginFrame = clock();

    // Update keysDown and buttonsDown
    handleInput();

    // Assuming that order of processing doesn't matter.
    for (auto it = m_keysDown.begin(); it != m_keysDown.end(); it++) {
      handleKey(*it);
    }

    SDL_UpdateTexture(m_mapTexture, NULL, m_map->m_color->m_data,
                      K_MAP_SIZE_X * sizeof(uint32_t));

    // clear screen
    SDL_SetRenderDrawColor(m_SDLRenderer, 0x00, 0x00, 0x00, 0xFF);
    SDL_RenderClear(m_SDLRenderer);

    // TODO: fix memory leak from not deleting old game states
    // Alternatively, place them somewhere so you can more easily keep track of
    // them
    if (m_gameState) {
      TrRenderLoop* loop = m_gameState->update(this);
      if (loop) {
        m_gameState = loop;
      }
      m_gameState->render(this);
    }

    // update screen
    SDL_RenderPresent(m_SDLRenderer);

    // do render stuff
    clock_t endFrame = clock();

    m_deltaTime += endFrame - beginFrame;
    m_frames++;

    // display FPS
    if (clockToMilliseconds(m_deltaTime) > 100.0) {  // every second
      m_frameRate = (double)m_frames;                // more stable
      m_frames = 0;
      m_deltaTime -= CLOCKS_PER_SEC;

      std::cout << "fps: " << m_frameRate << "        \r";
      std::flush(std::cout);
    }

    float calcMs = clockToMilliseconds(endFrame - beginFrame);
    if (calcMs < 16.6) {
      usleep(1000 * ((int)(16.6 - calcMs)));
    }
  }
}

void TrGame::handleInput() {
  while (SDL_PollEvent(&m_SDLEvent) != 0) {
    if (m_SDLEvent.type == SDL_QUIT) {
      m_quit = true;
    } else if (m_SDLEvent.type == SDL_KEYDOWN) {
      m_keysDown.insert(m_SDLEvent.key.keysym.sym);
    } else if (m_SDLEvent.type == SDL_KEYUP) {
      m_keysDown.erase(m_SDLEvent.key.keysym.sym);
    } else if (m_SDLEvent.type == SDL_MOUSEBUTTONDOWN) {
      m_buttonsDown.insert(m_SDLEvent.button.button);
    } else if (m_SDLEvent.type == SDL_MOUSEBUTTONUP) {
      m_buttonsDown.erase(m_SDLEvent.button.button);
    } else if (m_SDLEvent.type == SDL_MOUSEMOTION) {
      if (m_buttonsDown.count(SDL_BUTTON_LEFT) &&
          m_SDLEvent.motion.x < sz(K_DISPLAY_SIZE_X)) {
        int mouseX = m_SDLEvent.motion.x / c_pixelSize;
        int mouseY = m_SDLEvent.motion.y / c_pixelSize;
      }

      if (m_buttonsDown.count(SDL_BUTTON_RIGHT) &&
          m_SDLEvent.motion.x < sz(K_DISPLAY_SIZE_Y)) {
        int mouseX = m_SDLEvent.motion.x / c_pixelSize;
        int mouseY = m_SDLEvent.motion.y / c_pixelSize;
      }
    }
  }
}