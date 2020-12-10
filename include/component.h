#pragma once

#ifndef COMPONENT_H
#define COMPONENT_H 1

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#include <SFML/Graphics.hpp>

#include "ecs.h"

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

	bool facing_right;

	animator(int width, int height, float frame_delay, int new_columns, int new_rows)
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

	transform(float x, float y)
	{
		this->x = x;
		this->y = y;
	}
};
ECS_DEFINE_TYPE(transform);


#endif

