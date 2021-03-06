//
// Created by capi1500 on 11/07/18.
//

#include "physicObject.hpp"
#include <src/Game/game.hpp>

PhysicObjectProperties::PhysicObjectProperties(){
	friction = 0.3f;
	density = 1.f;
	velocity = sf::Vector2f(0, 0);
	angle = 0;
	shape = PhysicObjectShape::Box;
	type = PhysicObjectType::Dynamic;
}

PhysicObjectProperties::PhysicObjectProperties(ObjectProperties objectProperties, PhysicObjectType physicObjectType, PhysicObjectShape physicObjectShape, float friction, float density, sf::Vector2f velocity, float angle) : ObjectProperties(objectProperties),
		type(physicObjectType),
		shape(physicObjectShape),
		velocity(velocity),
		friction(friction),
		density(density),
		angle(angle){
}

PhysicObjectProperties PhysicObjectProperties::getPhysicObjectProperties(){
	return PhysicObjectProperties(getObjectProperties(), type, shape, friction, density, velocity, angle);
}

void PhysicObjectProperties::setObjectProperties(ObjectProperties& objectProperties){
	position = objectProperties.position;
	name = objectProperties.name;
	texture = objectProperties.texture;
}

PhysicObjectProperties& PhysicObject::getPhysicObjectProperties(){
	physicObjectProperties.angle = bodyPtr->GetAngle() * 180 / b2_pi;
	physicObjectProperties.position = getPosition();
	physicObjectProperties.velocity = sf::Vector2f(meterToPixel(bodyPtr->GetLinearVelocity().x), meterToPixel(bodyPtr->GetLinearVelocity().y));
	return physicObjectProperties;
}

b2Body* PhysicObject::getBody(){
	return bodyPtr;
}

void PhysicObject::pass(sf::Time elapsedTime){
	Object::pass(elapsedTime);
	setPosition(meterToPixel(bodyPtr->GetPosition().x), meterToPixel(bodyPtr->GetPosition().y));
	setRotation(bodyPtr->GetAngle() * 180 / b2_pi);
	physicObjectProperties.angle = bodyPtr->GetAngle() * 180 / b2_pi;
	physicObjectProperties.position = getCentre();
	physicObjectProperties.velocity = sf::Vector2f(meterToPixel(bodyPtr->GetLinearVelocity().x), meterToPixel(bodyPtr->GetLinearVelocity().y));
}

void PhysicObject::addVelocity(sf::Vector2f velocity){
	bodyPtr->ApplyLinearImpulseToCenter(b2Vec2(pixelToMeter(velocity.x), pixelToMeter(velocity.y)), true);
}

void PhysicObject::setName(std::string name){
	physicObjectProperties.name = name;
	objectProperties.name = name;
	bodyPtr->SetUserData(new std::string(getName()));
}

PhysicObject::PhysicObject(Game& game, PhysicObjectProperties properties) : Object(game, properties.getObjectProperties()),
		physicObjectProperties(properties){
	// Creating Box2D object to simulate physics
	b2BodyDef bodyDef;
	if(properties.type == PhysicObjectType::Dynamic){
		bodyDef.type = b2_dynamicBody;
	}
	else if(properties.type == PhysicObjectType::Kinematic){
		bodyDef.type = b2_kinematicBody;
		bodyDef.active = false;
	}
	bodyDef.position.Set(pixelToMeter(getCentre().x), pixelToMeter(getCentre().y));
	bodyDef.angle = properties.angle * b2_pi / 180;
	bodyDef.linearVelocity = b2Vec2(pixelToMeter(properties.velocity.x), pixelToMeter(properties.velocity.y));
	bodyPtr = gameRef.getPhysicWorld().CreateBody(&bodyDef);
	b2FixtureDef fixtureDef;
	b2CircleShape circleShape;
	b2PolygonShape polygonShape;
	if(properties.shape == PhysicObjectShape::Box){
		polygonShape.SetAsBox(pixelToMeter(getGlobalBounds().width / 2), pixelToMeter(getGlobalBounds().height / 2));
		fixtureDef.shape = &polygonShape;
	}
	else if(properties.shape == PhysicObjectShape::Circle){
		circleShape.m_radius = pixelToMeter(std::max(getGlobalBounds().width / 2, getGlobalBounds().height / 2));
		fixtureDef.shape = &circleShape;
	}
	fixtureDef.filter.categoryBits = 2;
	fixtureDef.filter.maskBits = 3;
	fixtureDef.restitution = 0;
	if(properties.type == PhysicObjectType::Dynamic or properties.type == PhysicObjectType::Kinematic){
		fixtureDef.friction = properties.friction;
		fixtureDef.density = properties.density;
	}
	bodyPtr->CreateFixture(&fixtureDef);
	bodyPtr->SetUserData(new std::string(getName()));
	// Coop Shooter Stuff
	className = ObjectClass::PhysicObject;
	pass(sf::milliseconds(0));
}

PhysicObject::~PhysicObject(){
	bodyPtr->DestroyFixture(bodyPtr->GetFixtureList());
	gameRef.getPhysicWorld().DestroyBody(bodyPtr);
}