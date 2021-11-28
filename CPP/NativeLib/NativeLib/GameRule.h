#pragma once

// Input Text Size
const int MAX_GAMEOBJECT_NAME_SIZE = 32;

// Tile System
const float MAP_START_POS_X = 0;
const float MAP_START_POS_Y = 0;
const int DEFAULT_TILE_NUMBER_X = 128;
const int DEFAULT_TILE_NUMBER_Y = 128;
const float TILE_WIDTH = 32;
const float TILE_HEIGHT = 32;

// Tile
const int MAX_TILE_LAYER = 3;
 
// Time System
const int MINUTE_PER_HOUR = 60;
const int HOUR_PER_DAY = 24;
const int DAYS_PER_MONTH = 20;
const int MONTH_PER_YEAR = 8;
const int YEAR_MAXIMUM = 9999;

const int DEFAULT_START_YEAR = 1200;
const int DEFAULT_START_MONTH = 1;
const int DEFAULT_START_DAY = 1; 
const int DEFAULT_START_HOUR = 0;
const int DEFAULT_START_MINUTE = 0;

// Update
const float UPDATE_INTERVAL_TIME = .5;

// Physics
const float CHARACTER_MAX_VELOCITY = 2.0;

// Inventory
const int INVENTORY_X = 1;
const int INVENTORY_Y = 1;
const int ITEM_STACK_MAX = 10;

// Camera Move
const float CAMERA_MOVING_SPEED = 4.0;
const float CAMERA_MOVING_MOUSE_BOUNDARY = 2.0;
const float CAMERA_DEFAULT_ZOOM_DEGREE = 1.0;
// Event
const int EVENT_LOG_STACK_MAX = 1000;

// max force that can press to the character
// smaller - >smoother
const float CHARACTER_MAX_FORCE = 6;// 0.4;
const float CHARACTER_ARRIVE_RADIUS = 1.0f;
const float CHARACTER_SLOWING_RADIUS = 4.0f;

// AI
const float ASSIGN_TASK_INTERVAL_TIME = 3.0;
const float EXECUTE_TASK_INTERVAL_TIME = 0.02;

