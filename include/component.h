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

		this->collision_box.setSize(
			sf::Vector2f(this->grid_size, this->grid_size));
		this->collision_box.setFillColor(sf::Color(0, 255, 0, 255));
		this->collision_box.setOutlineColor(sf::Color(0, 0, 255, 255));
		this->collision_box.setOutlineThickness(-2.0f);
	}

	void add_tile(const int x, const int y, const int z, bool has_collision)
	{
		if (x > this->max_size.x || x < 0 || y > this->max_size.y ||
		    y < 0 || z > this->layers || z < 0)
			return;

		if (this->map[x][y][z] == nullptr) {
			this->map[x][y][z] = new struct tile(
				x, y, this->grid_size, has_collision);
			printf("Added tile\n");
		}
	}

	void clear(void)
	{
		size_t x;
		size_t y;
		size_t z;

		for (x = 0; x < this->max_size.x; x++) {
			for (y = 0; y < this->max_size.y; y++) {
				for (z = 0; z < this->layers; z++)
					delete this->map[x][y][z];

				this->map[x][y].clear();
			}

			this->map[x].clear();
		}

		this->map.clear();
	}

	void save_map(std::string path)
	{
		FILE *fp;
		size_t x;
		size_t y;
		size_t z;

		/* Open the file */
		fp = fopen(path.c_str(), "wb");
		if (!fp) {
			fprintf(stderr, "Error: failed to open file \'%s\': %s\n", path.c_str(), strerror(errno));
			return;
		}

		/*
		 * Write the details of the map into the file
		 * 
		 * Functions like fprintf have a variable-length
		 *  argument list, which means that they don't have a
		 *  fixed number of arguments. In fprintf's case,
		 *  the arguments depend on the second argument, which
		 *  is a format string, or a string that contains
		 *  special specifiers to say how to represent the corresponding
		 *  argument. %d means decimal, and %f means float.
		 */
		fprintf(fp, "%d %d\n%f\n%d\n;", this->max_size.x,
			this->max_size.y, this->grid_size, this->layers);

		for (x = 0; x < this->max_size.x; x++) {
			for (y = 0; y < this->max_size.y; y++) {
				for (z = 0; z < this->layers; z++) {
					if (!this->map[x][y][z])
						fprintf(stderr,
							"Error: failed to save file \"%s\"\n",
							path.data());

					/* %s is for const char * (std::string::c_str()), and %zu is for size_t */
					fprintf(fp, "%zu %zu %zu %s\n;", x, y,
						z,
						this->map[x][y][z]
							->to_string()
							.data());
				}
			}
		}

		fclose(fp);
	}

	void load_map(std::string path)
	{
		FILE *fp; /* File stream structure */
		size_t len; /* File length for allocating memory */
		char *buf;
		bool colliding;
		size_t x;
		size_t y;
		size_t z;

		/* Open file in read-only mode */
		fp = fopen(path.data(), "rb");
		if (!fp) {
			/*
			 * Print an error message, strerror gets a
			 *  human-readable error message indicating
			 *  why the function failed 
			 */
			fprintf(stderr, "Error: failed to open file: %s\n",
				strerror(errno));
			return;
		}

		/* Determine file length */
		fseek(fp, 0, SEEK_END); /* Go to end of file */
		len = ftell(fp); /*
				  * Get the current position in the file,
		                  *  which is also its length in this case
				  */
		fseek(fp, 0, SEEK_SET); /* Return to the start of the file */

		/*
		 * Allocate a buffer of len + 1 bytes to
		 *  store the contents of the file
		 */
		buf = (char *)calloc(len + 1, sizeof(char));
		if (!buf) {
			fprintf(stderr,
				"Error: failed to allocate buffer: %s\n",
				strerror(errno));
			return;
		}

		/* Now we can read the file's contents into buf, like so */
		fread(buf, sizeof(char), len, fp); /* 
						    * Argument 1 is the buffer to use,
						    *  argument 2 is the size of the chunks to read,
						    *  argument 3 is how many chunks to read,
						    *  and argument 4 is where to read from
						    */
		if (!buf) { /* The data couldn't be read if buf is nullptr */
			fprintf(stderr, "Error: failed to read file: %s\n",
				strerror(errno));
			return;
		}

		/* Terminate the buffer (which is len + 1 bytes long) */
		buf[len] = 0;

		/* Close the file */
		fclose(fp);

		/* 
		 * Now, we have the file's contents in a buffer
		 *  to read our information from
		 */
		colliding = false;

		/* buf[0] is the start of max_size.x as a string */
		this->max_size.x = atoi(
			buf); /* atoi converts ASCII (text) to an int and atof is for float */
		this->max_size.y = atoi(&buf[sizeof(
			uint32_t)]); /* This will be after the first float and the space after that */
		this->grid_size = atof(
			&buf[(sizeof(uint32_t) * 2) +
			     2]); /* This is after the second float and the newline */
		this->layers = atoi(&buf[(sizeof(uint32_t) * 2) +
					 sizeof(float) + 3]); /* And the last float */
		colliding = (buf[(sizeof(uint32_t) * 2) + (sizeof(float) * 2) + 3]) ? true : false;

		/* Now that we have our information, free buf */
		free(buf);

		/* Clear the current map */
		this->clear();

		/* Resize the map's x axis */
		this->map.resize(this->max_size.x, std::vector<std::vector<tile *>>());
		for (x = 0; x < this->max_size.x; x++) {
			for (y = 0; y < this->max_size.y; y++) {
				/* Resize the y axis */
				this->map[x].resize(this->max_size.y, std::vector<tile *>());

				for (z = 0; z < this->layers; z++)
					/* And the z axis */
					this->map[x][y].resize(this->layers, NULL);
			}
		}

		this->map[this->max_size.x][this->max_size.y][this->layers] = new tile(this->max_size.x, this->max_size.y, this->grid_size, colliding);
	}

	~tilemap(void)
	{
		this->clear();
	}
};
ECS_DEFINE_TYPE(tilemap);

#endif
