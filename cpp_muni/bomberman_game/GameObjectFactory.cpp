#include "Bomb.h"
#include "Bonus.h"
#include "BonusItem.h"
#include "Flame.h"
#include "Player.h"
#include "Wall.h"

#include "GameObjectFactory.h"

GameObjectFactory::GameObjectFactory(Playground& /*playground*/) {
}

std::unique_ptr<Wall> GameObjectFactory::createBrick() const {
	// Brick is a destroyable wall.
	// It can be destroed by an explosion of a bomb.

	// Set those textures on the objects created there.
	TextureRef texture{ "brick_gray0.png" };
	std::unique_ptr<Wall> pl = std::make_unique<Wall>();
	Position p;
	pl->position(p);
	pl->texture(texture);
	pl->destroyable(true);
	pl->bonus(Bonus::None);
	return pl;
}

std::unique_ptr<Wall> GameObjectFactory::createStone() const {
	// Stone is a non-destroyable wall.
	TextureRef texture{ "stone2_gray0.png" };
	std::unique_ptr<Wall> pl = std::make_unique<Wall>();
	Position p;
	pl->position(p);
	pl->texture(texture);
	pl->destroyable(false);
	pl->bonus(Bonus::None);
	return pl;
}

std::unique_ptr<Flame> GameObjectFactory::createFlame() const {
	TextureRef texture{ "conjure_flame.png" };

	std::unique_ptr<Flame> pl = std::make_unique<Flame>();
	Position p;
	pl->position(p);
	pl->texture(texture);
	return pl;
}

std::unique_ptr<Player> GameObjectFactory::createPlayer() const {
	TextureRef texture{ "human.png" };
	std::unique_ptr<Player> pl = std::make_unique<Player>();
	Position p;
	pl->position(p);
	pl->texture(texture);
	return pl;
}

std::unique_ptr<Bomb> GameObjectFactory::createBomb() const {
	TextureRef texture{ "delayed_fireball.png" };
	std::unique_ptr<Bomb> pl = std::make_unique<Bomb>();
	Position p;
	pl->position(p);
	pl->texture(texture);
	return pl;
}

std::unique_ptr<BonusItem> GameObjectFactory::createBonusItem(Bonus bonus) const {
	TextureRef texture = [&] {
		switch (bonus) {
		case Bonus::Poison:
			return TextureRef{ "potion_bubbly.png" };
		default:
			return TextureRef{ "sticky_flame.png" };
		}
	}();

	std::unique_ptr<BonusItem> pl = std::make_unique<BonusItem>();
	Position p;
	pl->position(p);
	pl->texture(texture);
	pl->bonus(bonus);
	return pl;
}
