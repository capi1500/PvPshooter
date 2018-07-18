//
// Created by capi1500 on 10/07/18.
//

#ifndef COOPSHOOTER_LOADER_HPP
#define COOPSHOOTER_LOADER_HPP

#include <string>
#include <src/Object/object.hpp>
#include <src/PhysicObject/physicObject.hpp>
#include <src/Entity/entity.hpp>
#include <src/Player/player.hpp>
#include <src/Bullet/bullet.hpp>
#include <src/Weapon/weapon.hpp>
#include <src/WorldObject/worldObject.hpp>
#include <fstream>
#include <src/TemplateManager/templateManager.hpp>
#include <src/Collectible/collectible.hpp>

class Game;

class Loader{
	private:
		Game& gameRef;
		
		std::fstream file;
		
		sf::Vector2u blockSize;
		sf::Vector2f startingPos;
		int objectLoadedID;
		std::string templateName;
		Template temp;
		ObjectProperties objectProperties;
		PhysicObjectProperties physicObjectProperties;
		EntityProperties entityProperties;
		PlayerProperties playerProperties;
		BulletProperties bulletProperties;
		ItemProperties itemProperties;
		WeaponProperties weaponProperties;
		WorldObjectProperties worldObjectProperties;
		CollectibleProperties collectibleProperties;
		
		void objectload();
		void physicObjectload();
		void entityload();
		void playerload();
		void bulletload();
		void collectibleload();
		void itemload();
		void weaponload();
		void worldObjectload();
		
		void loadProperties(bool clean = true);
		void loadTemplate();
		
		void loadTemplate(std::string path);
		void loadTextures(std::string path);
		void loadPlayer(std::string path);
		void loadLevel(std::string path);
		void loadItems(std::string path);
		
		void objectsave(Object* object);
		void physicObjectsave(PhysicObject* physicObject);
		void entitysave(Entity* entity);
		void playersave(Player* player);
		void bulletsave(Bullet* bullet);
		void collectiblesave(Collectible* collectible);
		void itemsave(Item* item);
		void weaponsave(Weapon* weapon);
		void worldObjectsave(WorldObject* worldObject);
		
		void saveProperties(Object* object);
		
		void saveTextures(std::string path);
		void savePlayer(std::string path, std::string name);
		void saveLevel(std::string path);
		void saveItems(std::string path);
	public:
		void load(std::string path);
		void save(std::string path);
		
		Loader(Game& gameRef);
};

#endif //COOPSHOOTER_LOADER_HPP
