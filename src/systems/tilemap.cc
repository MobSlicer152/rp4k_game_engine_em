#include "systems/tilemap.h"

tilemap_system::tilemap_system(void)
{
}

tilemap_system::~tilemap_system(void)
{
}

void tilemap_system::tick(ECS::World *world, float delta)
{
	if (!states::get_paused()) {
		engine::get_inst().world->each<struct tilemap>(
			[&](ECS::Entity *entity,
			    ECS::ComponentHandle<struct tilemap> map) -> void {
				if (sf::Mouse::isButtonPressed(
					    sf::Mouse::Left)) {
					add_tile_on_click(true, map);
					printf("New tile's entity ID: %zu\n",
					       entity->getEntityId());
				} else if (sf::Mouse::isButtonPressed(
						   sf::Mouse::Right)) {
					add_tile_on_click(false, map);
					printf("New no-collision tile's entity ID: %zu\n",
					       entity->getEntityId());
				}

				if (button_map::get_map()["SAVE"]->clicked) {
					map->save_map("tilemap_test.txt");
					button_map::get_map()["SAVE"]->clicked =
						false;
					printf("Tile map saved\n");
				}

				if (button_map::get_map()["LOAD"]->clicked) {
					map->load_map("tilemap_test.txt");
					button_map::get_map()["LOAD"]->clicked =
						false;
					printf("Tile map loaded\n");
				}
			});
	}
}

void tilemap_system::add_tile_on_click(bool has_collision,
				       ECS::ComponentHandle<struct tilemap> map)
{
	/*
	 * Reference for window pointer that is used below to determine active
	 *  cursor position for adding tiles
	 */
	sf::RenderWindow *wnd;
	sf::Vector2f mouse_pos;
	sf::Vector2i mouse_pos_grid(
		static_cast<int>(mouse_pos.x / map->grid_size),
		static_cast<int>(mouse_pos.y / map->grid_size));

	wnd = engine::get_inst().win;
	mouse_pos = wnd->mapPixelToCoords(sf::Mouse::getPosition(*wnd));
	map->add_tile(mouse_pos_grid.x, mouse_pos_grid.y, 0, has_collision);
}
