//
// Created by capi1500 on 10/07/18.
//

#include "eventManager.hpp"
#include <src/Game/game.hpp>
#include <src/Weapon/weapon.hpp>
#include <src/Collectible/collectible.hpp>

void EventManager::addEvent(Event event){
	events.push(event);
}

void EventManager::handleEvents(sf::Event event){
	if(event.type == sf::Event::Closed){
		gameRef.getWindow().close();
	}
	else if(event.type == sf::Event::Resized){
		gameRef.getPlayer1View().setSize(sf::Vector2f(gameRef.getWindow().getSize().x, gameRef.getWindow().getSize().y / 2));
		gameRef.getPlayer2View().setSize(sf::Vector2f(gameRef.getWindow().getSize().x, gameRef.getWindow().getSize().y / 2));
		gameRef.getFullScreenView().setSize(sf::Vector2f(gameRef.getWindow().getSize().x, gameRef.getWindow().getSize().y / 2));
		gameRef.getCameraView().setSize(sf::Vector2f(gameRef.getWindow().getSize().x, gameRef.getWindow().getSize().y / 2));
	}
	else if(event.type == sf::Event::MouseButtonPressed){
		if(not gameRef.getMenuManager().getActive()->getMenuProperties().freeCamera){
			addEvent(Event("mouseButtonPressed"));
		}
		else{
			addEvent(Event("tileClicked"));
		}
	}
	else if(event.type == sf::Event::KeyPressed){
		if(event.key.code == sf::Keyboard::Escape){
			if(gameRef.getMenuManager().getActiveName() == "play"){
				addEvent(Event("changeMenu", "pause"));
			}
			else if(gameRef.getMenuManager().getActiveName() == "pause"){
				addEvent(Event("changeMenu", "play"));
			}
			else if(gameRef.getMenuManager().getActiveName() == "editor"){
				addEvent(Event("changeMenu", "editorPause"));
			}
			else if(gameRef.getMenuManager().getActiveName() == "editorPause"){
				addEvent(Event("changeMenu", "editor"));
			}
		}
		if(gameRef.getMenuManager().getActive()->getMenuProperties().gameRunning){
			if(event.key.code == sf::Keyboard::Q){
				addEvent(Event("equipPrevious", "player1"));
			}
			else if(event.key.code == sf::Keyboard::E){
				addEvent(Event("equipNext", "player1"));
			}
			else if(event.key.code == sf::Keyboard::U){
				addEvent(Event("equipPrevious", "player2"));
			}
			else if(event.key.code == sf::Keyboard::O){
				addEvent(Event("equipNext", "player2"));
			}
			else if(event.key.code == sf::Keyboard::Z){
				addEvent(Event("remove", "player1"));
			}
			else if(event.key.code == sf::Keyboard::M){
				addEvent(Event("remove", "player2"));
			}
			else if(event.key.code == sf::Keyboard::X){
				addEvent(Event("throw", "player1"));
			}
			else if(event.key.code == sf::Keyboard::Comma){
				addEvent(Event("throw", "player2"));
			}
		}
	}
	if(event.type == sf::Event::MouseWheelScrolled){
		if(gameRef.getMenuManager().getActive()->getMenuProperties().freeCamera){
			gameRef.zoom(event.mouseWheelScroll.delta);
		}
	}
}

void EventManager::handleEvents(){
	if(gameRef.getMenuManager().getActive()->getMenuProperties().gameRunning){
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::W)){
			addEvent(Event("jump", "player1"));
		}
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::I)){
			addEvent(Event("jump", "player2"));
		}
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::D)){
			addEvent(Event("moveLeft", "player1"));
		}
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::L)){
			addEvent(Event("moveLeft", "player2"));
		}
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::A)){
			addEvent(Event("moveRight", "player1"));
		}
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::J)){
			addEvent(Event("moveRight", "player2"));
		}
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::S)){
			addEvent(Event("moveDown", "player1"));
		}
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::K)){
			addEvent(Event("moveDown", "player2"));
		}
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::F)){
			addEvent(Event("bulletShot", "player1"));
		}
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::SemiColon)){
			addEvent(Event("bulletShot", "player2"));
		}
	}
	if(gameRef.getMenuManager().getActive()->getMenuProperties().freeCamera){
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::W)){
			addEvent(Event("cameraUp"));
		}
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::S)){
			addEvent(Event("cameraDown"));
		}
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::D)){
			addEvent(Event("cameraRight"));
		}
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::A)){
			addEvent(Event("cameraLeft"));
		}
		/*if(sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)){
			addEvent(Event("tileClicked"));
		}*/
	}
	Event toProcess;
	while(not events.empty()){
		toProcess = events.front();
		
		if(toProcess.what == "jump"){
			Entity * entity = dynamic_cast<Entity*>(gameRef.getWorld().getObject(toProcess.object1));
			if(entity->onGround()){
				entity->addVelocity(sf::Vector2f(0, -entity->getEntityProperties().jumpHeight));
				gameRef.getSoundManager().playSound("jump");
			}
		}
		else if(toProcess.what == "moveLeft"){
			Entity * entity = dynamic_cast<Entity*>(gameRef.getWorld().getObject(toProcess.object1));
			entity->addVelocity(sf::Vector2f(entity->getEntityProperties().movementSpeed, 0));
			entity->setFacing(true);
		}
		else if(toProcess.what == "moveRight"){
			Entity * entity = dynamic_cast<Entity*>(gameRef.getWorld().getObject(toProcess.object1));
			entity->addVelocity(sf::Vector2f(-entity->getEntityProperties().movementSpeed, 0));
			entity->setFacing(false);
		}
		else if(toProcess.what == "moveDown"){
			Entity * entity = dynamic_cast<Entity*>(gameRef.getWorld().getObject(toProcess.object1));
			entity->addVelocity(sf::Vector2f(0, entity->getEntityProperties().movementSpeed));
		}
		else if(toProcess.what == "equipNext"){
			if(not dynamic_cast<Entity*>(gameRef.getWorld().getObject(toProcess.object1))->getEntityProperties().isDead){
				dynamic_cast<Entity*>(gameRef.getWorld().getObject(toProcess.object1))->equipNext();
				gameRef.getSoundManager().playSound("eqChange");
			}
		}
		else if(toProcess.what == "equipPrevious"){
			if(not dynamic_cast<Entity*>(gameRef.getWorld().getObject(toProcess.object1))->getEntityProperties().isDead){
				dynamic_cast<Entity*>(gameRef.getWorld().getObject(toProcess.object1))->equipPrevious();
				gameRef.getSoundManager().playSound("eqChange");
			}
		}
		else if(toProcess.what == "bulletHit"){
			if(gameRef.getWorld().exists(toProcess.object1)){
				if(gameRef.getWorld().exists(toProcess.object2)){
					PhysicObject * object = dynamic_cast<PhysicObject*>(gameRef.getWorld().getObject(toProcess.object2));
					if(dynamic_cast<Bullet*>(gameRef.getWorld().getObject(toProcess.object1))->canHit() and (object->getClassName() == ObjectClass::Player or object->getClassName() == ObjectClass::Entity)){
						dynamic_cast<Entity*>(object)->gotHit(dynamic_cast<Bullet*>(gameRef.getWorld().getObject(toProcess.object1))->getBulletProperties().dmg);
						gameRef.getWorld().removeObject(toProcess.object1);
						gameRef.getSoundManager().playSound("hit");
					}
					else if(object->getClassName() == ObjectClass::WorldObject){
						gameRef.getWorld().removeObject(toProcess.object1);
					}
				}
				else if(toProcess.object2 == ""){
					gameRef.getWorld().removeObject(toProcess.object1);
				}
			}
		}
		else if(toProcess.what == "bulletShot"){
			Entity * object = dynamic_cast<Entity*>(gameRef.getWorld().getObject(toProcess.object1));
			if(object->ifCanShot()){
				object->shot();
				ObjectProperties objectProperties;
				objectProperties.texture = dynamic_cast<Weapon*>(object->getEquiped())->getWeaponProperties().bulletTexture;
				objectProperties.position = sf::Vector2f(object->getPosition().x + (object->getEntityProperties().isFacingLeft ? 1 : -1) * (gameRef.getTextureManager().getTexture(objectProperties.texture).getSize().x + object->getGlobalBounds().width / 2), object->getPosition().y);
				PhysicObjectProperties physicObjectProperties(objectProperties, PhysicObjectType::Dynamic, PhysicObjectShape::Box);
				WeaponProperties weaponProperties = dynamic_cast<Weapon*>(object->getEquiped())->getWeaponProperties();
				float bulletSpeed = dynamic_cast<Weapon*>(object->getEquiped())->getWeaponProperties().bulletSpeed;
				int bulletDmg = weaponProperties.dmg;
				if(object->haveBoost("dmgUp")){
					bulletDmg *= 2;
				}
				if(object->haveBoost("fasterShots")){
					bulletSpeed *= 2;
				}
				weaponProperties.bulletDistance *= defBlockSize; // block size
				physicObjectProperties.velocity = sf::Vector2f((object->getEntityProperties().isFacingLeft ? 1 : -1) * bulletSpeed, 0);
				gameRef.getWorld().addObject(new Bullet(gameRef, BulletProperties(physicObjectProperties, bulletSpeed, bulletDmg, weaponProperties.bulletDistance, objectProperties.position)));
				gameRef.getSoundManager().playSound(weaponProperties.shotSound);
			}
		}
		else if(toProcess.what == "collectSth"){
			if(gameRef.getWorld().exists(toProcess.object1)){
				Collectible * collected = dynamic_cast<Collectible*>(gameRef.getWorld().getObject(toProcess.object1));
				if(collected->canBeCollected()){
					if(gameRef.getWorld().getObject(toProcess.object2)->getClassName() == ObjectClass::Entity or gameRef.getWorld().getObject(toProcess.object2)->getClassName() == ObjectClass::Player){
						if(gameRef.getItemManager().exist(collected->getCollectibleProperties().what)){
							if(gameRef.getItemManager().getItem(collected->getCollectibleProperties().what)->getClassName() == ObjectClass::Item){
								dynamic_cast<Entity*>(gameRef.getWorld().getObject(toProcess.object2))->getEntityProperties().equipment.addItem(new Item(*gameRef.getItemManager().getItem(collected->getCollectibleProperties().what)));
							}
							else if(gameRef.getItemManager().getItem(collected->getCollectibleProperties().what)->getClassName() == ObjectClass::Weapon){
								dynamic_cast<Entity*>(gameRef.getWorld().getObject(toProcess.object2))->getEntityProperties().equipment.addItem(new Weapon(*dynamic_cast<Weapon*>(gameRef.getItemManager().getItem(collected->getCollectibleProperties().what)), collected->getCollectibleProperties().count, 0));
							}
						}
						else{
							dynamic_cast<Entity*>(gameRef.getWorld().getObject(toProcess.object2))->addBoost(collected->getCollectibleProperties().what, collected->getCollectibleProperties().boostTime);
						}
						gameRef.getWorld().removeObject(toProcess.object1);
						gameRef.getSoundManager().playSound("collect");
					}
				}
			}
		}
		else if(toProcess.what == "remove"){
			if(not dynamic_cast<Entity*>(gameRef.getWorld().getObject(toProcess.object1))->getEntityProperties().isDead and dynamic_cast<Entity*>(gameRef.getWorld().getObject(toProcess.object1))->getEntityProperties().equipment.canRemove()){
				dynamic_cast<Entity*>(gameRef.getWorld().getObject(toProcess.object1))->getEntityProperties().equipment.removeEquiped();
			}
		}
		else if(toProcess.what == "throw"){
			if(not dynamic_cast<Entity*>(gameRef.getWorld().getObject(toProcess.object1))->getEntityProperties().isDead and dynamic_cast<Entity*>(gameRef.getWorld().getObject(toProcess.object1))->getEntityProperties().equipment.canRemove()){
				sf::Vector2f position = gameRef.getWorld().getObject(toProcess.object1)->getPosition() + sf::Vector2f(5 * (dynamic_cast<Entity*>(gameRef.getWorld().getObject(toProcess.object1))->getEntityProperties().isFacingLeft ? 1 : -1), 0);
				Item* item = dynamic_cast<Entity*>(gameRef.getWorld().getObject(toProcess.object1))->getEntityProperties().equipment.getEquiped();
				std::string what = dynamic_cast<Entity*>(gameRef.getWorld().getObject(toProcess.object1))->getEntityProperties().equipment.getEquiped()->getName(), itemName = "collectibleW" + std::to_string(id++);
				if(item->getClassName() == ObjectClass::Weapon){
					gameRef.getWorld().addObject(new Collectible(gameRef, CollectibleProperties(PhysicObjectProperties(ObjectProperties(position, itemName, what), PhysicObjectType::Dynamic, PhysicObjectShape::Box, 0.3, 1, sf::Vector2f(100 * (dynamic_cast<Entity*>(gameRef.getWorld().getObject(toProcess.object1))->getEntityProperties().isFacingLeft ? 1 : -1), 0)), what, dynamic_cast<Weapon*>(item)->getWeaponProperties().ammo)));
				}
				else{
					gameRef.getWorld().addObject(new Collectible(gameRef, CollectibleProperties(PhysicObjectProperties(ObjectProperties(position, itemName, what), PhysicObjectType::Dynamic, PhysicObjectShape::Box, 0.3, 1, sf::Vector2f(100 * (dynamic_cast<Entity*>(gameRef.getWorld().getObject(toProcess.object1))->getEntityProperties().isFacingLeft ? 1 : -1), 0)), what)));
				}
				dynamic_cast<Entity*>(gameRef.getWorld().getObject(toProcess.object1))->getEntityProperties().equipment.removeEquiped();
			}
		}
		else if(toProcess.what == "changeMenu"){
			if(gameRef.getMenuManager().exitst(toProcess.object1)){
				if(gameRef.getMenuManager().getActive()->getMenuProperties().gameRunning and not gameRef.getMenuManager().getMenu(toProcess.object1)->getMenuProperties().gameRunning){
					gameRef.getLoader().save("Temp");
				}
				else if(gameRef.getMenuManager().getMenu(toProcess.object1)->getMenuProperties().gameRunning and not gameRef.getMenuManager().getActive()->getMenuProperties().gameRunning){
					gameRef.getLoader().load("Temp");
				}
				gameRef.getWindow().setMouseCursorVisible(toProcess.object1 != "play");
				gameRef.getMenuManager().setActive(toProcess.object1);
			}
		}
		else if(toProcess.what == "load"){
			gameRef.getLoader().load(toProcess.object1);
			gameRef.getWindow().setMouseCursorVisible(false);
			gameRef.getMenuManager().setActive("play");
		}
		else if(toProcess.what == "save"){
			gameRef.getLoader().save(toProcess.object1);
		}
		else if(toProcess.what == "newGame"){
			gameRef.getLoader().load("Default");
			gameRef.getWindow().setMouseCursorVisible(false);
			gameRef.getMenuManager().setActive("play");
		}
		else if(toProcess.what == "mouseButtonPressed"){
			gameRef.getMenuManager().getActive()->mouseClicked(sf::Vector2f(sf::Mouse::getPosition(gameRef.getWindow()).x, sf::Mouse::getPosition(gameRef.getWindow()).y));
		}
		else if(toProcess.what == "tileClicked"){
			Template temp = gameRef.getTemplateManager().getTemplate("ground");
			ObjectProperties objectProperties = ObjectProperties();
			PhysicObjectProperties physicObjectProperties = PhysicObjectProperties();
			ItemProperties itemProperties = ItemProperties();
			WeaponProperties weaponProperties = WeaponProperties();
			WorldObjectProperties worldObjectProperties = WorldObjectProperties();
			EntityProperties entityProperties = EntityProperties();
			PlayerProperties playerProperties = PlayerProperties();
			switch(temp.className){
				case ObjectClass::PhysicObject:
					objectProperties = *temp.properties;
					physicObjectProperties = *(dynamic_cast<PhysicObjectProperties*>(temp.properties));
					break;
				case ObjectClass::WorldObject:
					objectProperties = *temp.properties;
					physicObjectProperties = *(dynamic_cast<PhysicObjectProperties*>(temp.properties));
					worldObjectProperties = *(dynamic_cast<WorldObjectProperties*>(temp.properties));
					break;
			}
			objectProperties.position = gameRef.coordToPixel(gameRef.pixelToCoord(sf::Vector2f(sf::Mouse::getPosition(gameRef.getWindow()).x, sf::Mouse::getPosition(gameRef.getWindow()).y)));
			objectProperties.position.x -= defBlockSize / 2;
			objectProperties.position.y -= defBlockSize / 2;
			objectProperties.name = temp.properties->name + std::to_string(gameRef.getWorld().getObjects().size());
			switch(temp.className){
				case ObjectClass::PhysicObject:
					physicObjectProperties.setObjectProperties(objectProperties);
					gameRef.getWorld().addObject(new PhysicObject(gameRef, physicObjectProperties));
					break;
				case ObjectClass::WorldObject:
					worldObjectProperties.setObjectProperties(objectProperties);
					worldObjectProperties.setPhysicObjectProperties(physicObjectProperties);
					worldObjectProperties.type = PhysicObjectType::Static;
					gameRef.getWorld().addObject(new WorldObject(gameRef, worldObjectProperties));
					break;
			}
		}
		else if(toProcess.what == "exit"){
			gameRef.getWindow().close();
		}
		else if(toProcess.what == "cameraUp"){
			gameRef.getCameraView().move(0, -defaultCameraSpeed * gameRef.getZoom());
		}
		else if(toProcess.what == "cameraDown"){
			gameRef.getCameraView().move(0, defaultCameraSpeed * gameRef.getZoom());
		}
		else if(toProcess.what == "cameraRight"){
			gameRef.getCameraView().move(defaultCameraSpeed * gameRef.getZoom(), 0);
		}
		else if(toProcess.what == "cameraLeft"){
			gameRef.getCameraView().move(-defaultCameraSpeed * gameRef.getZoom(), 0);
		}
		events.pop();
	}
}

EventManager::EventManager(Game& game) : gameRef(game){
	id = 0;
}