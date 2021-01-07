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

	char input_active:1;
	char w:1;
	char a:1;
	char s:1;
	char d:1;

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

#endif
