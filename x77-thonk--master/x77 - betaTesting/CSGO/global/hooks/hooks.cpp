#include "../../main.h"

void events::player_hurt_listener::start()
{
	i::eventmgr->add_listener(this, "weapon_fire", false);
	i::eventmgr->add_listener(this, "player_hurt", false);
}

void events::player_hurt_listener::stop()
{
	i::eventmgr->remove_listener(this);
}

void events::on_fire_event(igameevent* event)
{

	if (!i::engineclient->is_in_game() || !i::engineclient->is_connected() || !g::local || g::local->get_life_state() != LIFE_ALIVE) return;

	auto index = g::local->get_index();

	if (!strcmp(event->get_name(), "weapon_fire")) {

		auto id = i::engineclient->get_player_for_user_id(event->get_int("userid"));

		if (!id) return;

		if (id == index)
			g::shots_fired++;

	}
	/**/
	if (!strcmp(event->get_name(), "player_hurt")) {

		auto attacker = i::engineclient->get_player_for_user_id(event->get_int("attacker"));

		if (!attacker) return;

		if (attacker == index) {
			//
			v::hitmiss();

			//PlaySoundA(menu_sound, NULL, SND_ASYNC | SND_MEMORY);
			i::engineclient->execute_client_cmd("play buttons\\arena_switch_press_02.wav");

			// increment shots hit
			g::shots_hit++;

		}

	}

	

	

	if (!g::local || g::local->get_life_state() != LIFE_ALIVE) {
		g::shots_fired	= 0;
		g::shots_hit	= 0;
		g::shots_missed = 0;
	}
	
	// calculate shots missed
	if (g::shots_fired > 0)
		g::shots_missed = g::shots_fired - g::shots_hit;


	///////////////////////////////shot counter////////////////////////////////////////
	
	if (!strcmp(event->get_name(), "weapon_fire")) {

		auto id = i::engineclient->get_player_for_user_id(event->get_int("userid"));

		if (!id) return;

		if (id == index)
			g::shotf++;

	}
	
	if (!strcmp(event->get_name(), "player_hurt")) {

		auto attacker = i::engineclient->get_player_for_user_id(event->get_int("attacker"));

		if (!attacker) return;

		if (attacker == index) {
		
			//Add shot on hit
			g::shoth++;

		}

	}

	//Reset shots on death.//
	if (!g::local || g::local->get_life_state() != LIFE_ALIVE) {
		g::shotf = 0;
		g::shoth = 0;
		g::shotm = 0;
	}

	//Missed Shots
	g::shotm = g::shotf - g::shoth;
}

void cunt() {
	//inject sound
	if (DLL_PROCESS_ATTACH) {
		PlaySoundA(menu_sound, NULL, SND_ASYNC | SND_MEMORY);
	}
}

namespace h
{

	std::unique_ptr<vmt_hook> client_mode_hook{};
	std::unique_ptr<vmt_hook> client_hook{};
	std::unique_ptr<vmt_hook> panel_hook{};
	std::unique_ptr<vmt_hook> model_hook{};
	std::unique_ptr<vmt_hook> data_hook{};
}