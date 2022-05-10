#pragma once


class Enum 
{
public:
	enum class OwnerType {
		Player,
		Enemy
	};

	enum class BulletType {
		NormalPlayer,
		NormalEnemy,
		Boss,
	};
};