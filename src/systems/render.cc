#include "systems/render.h"
#include "ecs.h"

render_system::render_system(void)
{
}

render_system::~render_system(void)
{
}

void render_system::tick(ECS::World *world, float delta)
{
	if (!states::get_paused()) {
		/* Clear the window */
		engine::get_inst().win->clear();

		world->each<struct transform, struct sprite_2d>(
			/* Lambda function to be run on each entity */
			[&](ECS::Entity *ent,
			    ECS::ComponentHandle<struct transform> trans,
			    ECS::ComponentHandle<struct sprite_2d> sprite)
				-> void {
				/* Add a texture to the map */
				if (this->texture_map.count(
					    sprite->texture_path) < 1)
					this->texture_map[sprite->texture_path] =
						load_texture(
							sprite->texture_path);

				/* Load the texture if it doesn't exist */
				if (!sprite->self.getTexture()) {
					sprite->self.setTexture(
						*this->texture_map
							 [sprite->texture_path]);
					sprite->width =
						sprite->self.getGlobalBounds()
							.width;
					sprite->height =
						sprite->self.getGlobalBounds()
							.height;
				}

				/* Draw */
				sprite->self.setPosition(trans->x, trans->y);
				engine::get_inst().win->draw(sprite->self);
			});

		world->each<
			struct tilemap>([&](ECS::Entity *,
					    ECS::ComponentHandle<struct tilemap>
						    map) -> void {
			size_t x;
			size_t y;
			size_t z;
			sf::RenderWindow *wnd;

			wnd = engine::get_inst().win;

			/*
				 * Loop through each tile and render onto the 
				 *  engine's window instance. Note that this is
				 *  looping through a vector which stores a
				 *  vector which stores the tile
				 */
			for (x = 0; x < map->map.size(); x++) {
				for (y = 0; y < map->map[x].size(); y++) {
					for (z = 0; z < map->map[x][y].size();
					     z++) {
						if (!map->map[x][y][z])
							return;

						wnd->draw(
							map->map[x][y][z]->area);
						if (map->map[x][y][z]
							    ->get_collision()) {
							map->collision_box.setPosition(
								map->map[x][y][z]
									->get_pos());
							wnd->draw(
								map->collision_box);
						}
					}
				}
			}
		});

		/* Update */
		engine::get_inst().win->display();
	}
}

sf::Texture *render_system::load_texture(std::string texture_file)
{
	sf::Texture *texture = new sf::Texture();

	if (!texture->loadFromFile(texture_file)) {
		fprintf(stderr,
			"Unable to load file \'%s\'\n(Press Enter to exit)\n",
			texture_file.data());
		int c = getchar();
		exit(-1);
	}

	return texture;
}
