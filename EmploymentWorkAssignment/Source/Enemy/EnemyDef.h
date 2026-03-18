#ifndef  ENEMY_DEF_H


#define ENEMY_DEF_H

enum EnemyType
{
	CANNON,
	TURN_ENEMY_X,
	TURN_ENEMY_Z,
	PLUNGE_ENEMY,
	ENEMY_MAX_TYPE,
	ENEMY_NONE,
};

enum EnemyID
{

};

constexpr int ENEMY_WHIDTH = 2;
constexpr float ENEMY_SPEED = 0.05f;

#endif // ! ENEMY_DEF_H
