//
// Created by capi1500 on 13/07/18.
//

#include "collectible.hpp"
#include <src/Game/game.hpp>

CollectibleProperties::CollectibleProperties(){
}

CollectibleProperties::CollectibleProperties(PhysicObjectProperties physicObjectProperties, std::string what, int count, sf::Time boostTime) : PhysicObjectProperties(physicObjectProperties), what(what), boostTime(boostTime), count(count){
}

void CollectibleProperties::setPhysicObjectProperties(PhysicObjectProperties physicObjectProperties){
	type = physicObjectProperties.type;
	shape = physicObjectProperties.shape;
	density = physicObjectProperties.density;
	friction = physicObjectProperties.friction;
	angle = physicObjectProperties.angle;
	velocity = physicObjectProperties.velocity;
}

CollectibleProperties CollectibleProperties::getCollectibleProperties(){
	return CollectibleProperties(getPhysicObjectProperties(), what, count, boostTime);
}

CollectibleProperties& Collectible::getCollectibleProperties(){
	return collectibleProperties;
}

void Collectible::pass(sf::Time elapsedTime){
	PhysicObject::pass(elapsedTime);
	for(auto i = gameRef.getWorld().getEntities().begin(); i != gameRef.getWorld().getEntities().end(); i++){
		if(getGlobalBounds().intersects(i->second->getGlobalBounds())){
			gameRef.getEventManager().addEvent(Event("collectSth", getName(), i->second->getName()));
		}
	}
}

bool Collectible::canBeCollected(){
	return localTime >= sf::milliseconds(100);
}

Collectible::Collectible(Game& gameRef, CollectibleProperties collectibleProperties) : PhysicObject(gameRef, collectibleProperties.getPhysicObjectProperties()), collectibleProperties(collectibleProperties){
	className = ObjectClass::Collectible;
	// Box2D stuff
	getBody()->SetFixedRotation(true);
	b2Filter filter;
	filter.categoryBits = 1;
	filter.maskBits = 2;
	getBody()->GetFixtureList()->SetFilterData(filter);
}

