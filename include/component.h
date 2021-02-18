#pragma once

#ifndef COMPONENT_H
#define COMPONENT_H 1

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#include <SFML/Graphics.hpp>

#include "ecs.h"

#include "interface/tile.h"

struct animator {
	ECS_DECLARE_TYPE;

	int sprite_width;
	int sprite_height;

	int total_columns;
	int total_rows;

	int current_column;
	int current_row;

	float current_time;
	float next_frame_time;

	char facing_right : 1;

	animator(int width, int height, float frame_delay, int new_columns,
		 int new_rows)
	{
		this->sprite_width = width;
		this->sprite_height = height;

		this->current_column = 0;
		this->current_row = 0;

		this->total_columns = new_columns;
		this->total_rows = new_rows;

		this->next_frame_time = frame_delay;

		this->current_time = 0;

		this->facing_right = true;
	}
};

struct sprite_2d {
	ECS_DECLARE_TYPE;

	sf::Sprite self;
	std::string texture_path;
	int width;
	int height;

	sprite_2d(std::string texture_path)
	{
		this->texture_path = texture_path;
	}
};
ECS_DEFINE_TYPE(sprite);

struct transform {
	ECS_DECLARE_TYPE;

	float x;
	float y;

	float x_speed;
	float y_speed;

	transform(float x, float y)
	{
		this->x = x;
		this->y = y;
	}

	void update_speed(float x_speed, float y_speed)
	{
		this->x_speed = x_speed;
		this->y_speed = y_speed;
	}

	void move(void)
	{
		this->x += this->x_speed;
		this->y += this->y_speed;
	}
};
ECS_DEFINE_TYPE(transform);

struct input_controller {
	ECS_DECLARE_TYPE;

	char input_active : 1;
	char w : 1;
	char a : 1;
	char s : 1;
	char d : 1;

	input_controller(void)
	{
		this->input_active = true;

		this->w = false;
		this->a = false;
		this->s = false;
		this->d = false;
	}
};
ECS_DEFINE_TYPE(input_controller);

struct box_collider {
    public:
	ECS_DECLARE_TYPE;

	int left_edge;
	int right_edge;
	int top_edge;
	int bottom_edge;

	box_collider(void)
	{
		memset(this, '\0', sizeof(box_collider));
	}

	void update(int x_side, int y_side, int width, int height)
	{
		left_edge = x_side;
		right_edge = x_side + width;

		top_edge = y_side;
		bottom_edge = y_side + height;
	}
};
ECS_DEFINE_TYPE(box_collider);

struct tag {
    public:
	ECS_DECLARE_TYPE;

	std::vector<std::string> names;

	tag()
	{
	}

	void add(std::string tag)
	{
		names.push_back(tag);
	}
};
ECS_DEFINE_TYPE(tag);

struct tilemap {
    public:
	ECS_DECLARE_TYPE;

	float grid_size;
	uint32_t grid_size_u;
	uint32_t layers;

	sf::Vector2u max_size;
	sf::RectangleShape collision_box;

	/*
	 * Map structure
	 * 
	 * 1. Column of vectors
	 * 2. Row of vectors
	 * 3. Collection of tiles
	 */
	std::vector<std::vector<std::vector<tile *>>> map;

	tilemap(void)
	{
		size_t x;
		size_t y;
		size_t z;

		this->grid_size = 50.0f;

		/* Return a value of new type, convert float to unsigned integer */
		this->grid_size_u = static_cast<uint32_t>(this->grid_size);

		/* Number of tiles (size of tiles determined by grid size) */
		this->max_size.x = 20;
		this->max_size.y = 20;
		this->layers = 1;
		this->map.resize(this->max_size.x);

		for (x = 0; x < this->max_size.x; x++) {
			this->map.push_back(std::vector<std::vector<tile *>>());

			for (y = 0; y < this->max_size.y; y++) {
				this->map[x].resize(this->max_size.y);
				this->map[x].push_back(std::vector<tile *>());

				for (z = 0; z < this->layers; z++) {
					this->map[x][y].resize(this->layers);
					this->map[x][y].push_back(NULL);
				}
			}
		}

		
	}
};
ECS_DEFINE_TYPE(tilemap);

#endif
