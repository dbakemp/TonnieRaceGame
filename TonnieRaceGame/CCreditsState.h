#ifndef CCREDITSSTATE_H
#define CCREDITSSTATE_H

#include <vector>
#include "SDL.h"
#include "CGameState.h"
#include <vlc/vlc.h>

class CCreditsState : public CGameState
{
public:
	void init();
	void init(CEngine* engine);
	void clean();

	void pause();
	void resume();

	void handleEvents(CEngine* engine);
	void update(CEngine* engine);
	void draw(CEngine* engine);
	void input(CEngine* engine, SDL_Event* event);

	CCreditsState(CEngine* engine);

private:
	libvlc_instance_t *inst;
	libvlc_media_player_t *mp;
	libvlc_media_t *m;
};
#endif
