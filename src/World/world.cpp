//
// Created by capi1500 on 10/07/18.
//

#include "world.hpp"
#include <src/Game/game.hpp>
#include <src/PhysicObject/physicObject.hpp>

void World::addObject(PhysicObject* obj){
	if(obj->getClassName() == ObjectClass::Bullet){
		dynamic_cast<PhysicObject*>(obj)->setName("bullet" + std::to_string(bulletID++));
		bullets[obj->getName()] = dynamic_cast<Bullet*>(obj);
		return;
	}
	object[obj->getName()] = obj;
	if(obj->getClassName() == ObjectClass::Entity or obj->getClassName() == ObjectClass::Player){
		entities[obj->getName()] = dynamic_cast<Entity*>(obj);
	}
}

void World::removeObject(std::string name){
	if(name.substr(0, 6) == "bullet"){
		if(bullets.find(name) != bullets.end()){
			bullets[name]->getBody()->DestroyFixture(bullets[name]->getBody()->GetFixtureList());
			gameRef.getPhysicWorld().DestroyBody(bullets[name]->getBody());
			bullets.erase(name);
		}
	}
	else{
		if(object.find(name) != object.end()){
			if(getObject(name)->getClassName() == ObjectClass::Entity or getObject(name)->getClassName() == ObjectClass::Player){
				entities.erase(name);
			}
			object[name]->getBody()->DestroyFixture(object[name]->getBody()->GetFixtureList());
			gameRef.getPhysicWorld().DestroyBody(object[name]->getBody());
			object.erase(name);
		}
	}
}

PhysicObject* World::getObject(std::string name){
	if(name.substr(0, 6) == "bullet"){
		return bullets[name];
	}
	return object[name];
}

bool World::egzists(std::string name){
	if(name.substr(0, 6) == "bullet"){
		return bullets.find(name) != bullets.end();
	}
	return object.find(name) != object.end();
}

std::map<std::string, PhysicObject*>& World::getObjects(){
	return object;
}

std::map<std::string, Entity*>& World::getEntities(){
	return entities;
}

void World::pass(std::string name, sf::Time elapsedTime){
	getObject(name)->pass(elapsedTime);
}

void World::passAll(sf::Time elapsedTime){
	for(auto it = object.begin(); it != object.end(); it++){
		it->second->pass(elapsedTime);
	}
	for(auto it = bullets.begin(); it != bullets.end(); it++){
		it->second->pass(elapsedTime);
	}
}

void World::draw(std::string name){
	getObject(name)->draw();
}

void World::drawAll(){
	for(auto it = object.begin(); it != object.end(); it++){
		it->second->draw();
	}
	for(auto it = bullets.begin(); it != bullets.end(); it++){
		it->second->draw();
	}
}

World::World(Game& gameRef) : gameRef(gameRef){
	bulletID = 0;
}