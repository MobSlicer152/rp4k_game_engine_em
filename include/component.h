#pragma once

#ifndef COMPONENT_H
#define COMPONENT_H 1

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#include <SFML/Graphics.hpp>

#include "ecs.h"

struct transform {
	ECS_DECLARE_TYPE;

	float x;
	float y;
	float rot;

	transform(float x, float y, float rot)
	{
		this->x = x;
		this->y = y;
		this->rot = rot;
	}
};
ECS_DEFINE_TYPE(transform);

struct sprite_2d {
	ECS_DECLARE_TYPE;

	sf::Sprite self;
	char *texture_path;
	int width;
	int height;

	sprite_2d(char *texture_path)
	{
		if (!texture_path) {
			errno = EINVAL;
			return;
		}

		this->texture_path = (char *)calloc(strlen(texture_path), sizeof(char));
		sprintf(this->texture_path, "%s", texture_path);
	}
};
ECS_DEFINE_TYPE(sprite);


#endif

