//
// Created by capi1500 on 10/07/18.
//

#include "loader.hpp"
#include <src/Game/game.hpp>
#include <fstream>
#include <src/Button/button.hpp>
#include <src/Menu/menu.hpp>

void Loader::objectload(){
	std::string input;
	file >> input;
	while(input != "}"){
		if(input == "position"){
			file >> objectProperties.position.x >> objectProperties.position.y;
			objectProperties.position.x += startingPos.x;
			objectProperties.position.y += startingPos.y;
			objectProperties.position.x *= blockSize.x;
			objectProperties.position.y *= blockSize.y;
		}
		else if(input == "name"){
			file >> objectProperties.name;
		}
		else if(input == "texture"){
			file >> objectProperties.texture;
		}
		file >> input;
	}
}

void Loader::physicObjectload(){
	std::string input;
	file >> input;
	while(input != "}"){
		if(input == "type"){
			file >> input;
			if(input == "dynamic"){
				physicObjectProperties.type = PhysicObjectType::Dynamic;
			}
			else if(input == "kinematic"){
				physicObjectProperties.type = PhysicObjectType::Kinematic;
			}
			else if(input == "static"){
				physicObjectProperties.type = PhysicObjectType::Static;
			}
		}
		else if(input == "shape"){
			file >> input;
			if(input == "box"){
				physicObjectProperties.shape = PhysicObjectShape::Box;
			}
			else if(input == "circle"){
				physicObjectProperties.shape = PhysicObjectShape::Circle;
			}
		}
		else if(input == "density"){
			file >> physicObjectProperties.density;
		}
		else if(input == "friction"){
			file >> physicObjectProperties.friction;
		}
		else if(input == "angle"){
			file >> physicObjectProperties.angle;
			physicObjectProperties.angle *= b2_pi / 180;
		}
		else if(input == "velocity"){
			file >> physicObjectProperties.velocity.x >> physicObjectProperties.velocity.y;
		}
		file >> input;
	}
}

void Loader::entityload(){
	std::string input;
	file >> input;
	while(input != "}"){
		if(input == "maxHP"){
			file >> entityProperties.maxHP;
		}
		else if(input == "HP"){
			file >> entityProperties.HP;
		}
		else if(input == "jumpHeight"){
			file >> entityProperties.jumpHeight;
		}
		else if(input == "movementSpeed"){
			file >> entityProperties.movementSpeed;
		}
		else if(input == "isFacingLeft"){
			file >> input;
			if(input == "true"){
				entityProperties.isFacingLeft = true;
			}
			else{
				entityProperties.isFacingLeft = false;
			}
		}
		else if(input == "equiped"){
			int help;
			file >> help;
			entityProperties.equipment.equip(help);
		}
		else if(input == "EQ{"){
			file >> input;
			int ammount;
			while(input != "}"){
				file >> ammount;
				if(gameRef.getItemManager().getItem(input)->getClassName() == ObjectClass::Weapon){
					int time;
					file >> time;
					entityProperties.equipment.addItem(new Weapon(*dynamic_cast<Weapon*>(gameRef.getItemManager().getItem(input)), ammount, time), 1);
				}
				else{
					entityProperties.equipment.addItem(new Item(*gameRef.getItemManager().getItem(input)), ammount);
				}
				file >> input;
			}
		}
		file >> input;
	}
}

void Loader::playerload(){
	std::string input;
	file >> input;
	while(input != "}"){
		if(input == "textureBase"){
			file >> playerProperties.textureBase;
		}
		else if(input == "textureHair"){
			file >> playerProperties.textureHair;
		}
		else if(input == "textureBoots"){
			file >> playerProperties.textureBoots;
		}
		else if(input == "textureLegs"){
			file >> playerProperties.textureLegs;
		}
		else if(input == "textureGloves"){
			file >> playerProperties.textureGloves;
		}
		else if(input == "textureBody"){
			file >> playerProperties.textureBody;
		}
		else if(input == "textureHandRight"){
			file >> playerProperties.textureHandRight;
		}
		else if(input == "textureCloak"){
			file >> playerProperties.textureCloak;
		}
		file >> input;
	}
}

void Loader::itemload(){
	std::string input;
	file >> input;
	while(input != "}"){
		if(input == "ammount"){
			file >> itemProperties.amount;
		}
		else if(input == "worldObject"){
			file >> input;
			if(input == "true"){
				itemProperties.isWorldObject = true;
			}
			else{
				itemProperties.isWorldObject = false;
			}
		}
		else if(input == "textureOnEquip"){
			file >> itemProperties.textureOnEquip;
		}
		else if(input == "spawnable"){
			file >> input;
			if(input == "true"){
				weaponProperties.isSpawnable = true;
			}
			else{
				weaponProperties.isSpawnable = false;
			}
		}
		file >> input;
	}
}

void Loader::weaponload(){
	std::string input;
	int time;
	file >> input;
	while(input != "}"){
		if(input == "attackDelay"){
			file >> time;
			weaponProperties.attackDelay = sf::milliseconds(time);
		}
		else if(input == "reloadSpeed"){
			file >> time;
			weaponProperties.reloadSpeed = sf::milliseconds(time);
		}
		else if(input == "bulletSpeed"){
			file >> weaponProperties.bulletSpeed;
		}
		else if(input == "dmg"){
			file >> weaponProperties.dmg;
		}
		else if(input == "maxAmmo"){
			file >> weaponProperties.maxAmmo;
		}
		else if(input == "ammo"){
			file >> weaponProperties.ammo;
		}
		else if(input == "reloading"){
			file >> input;
			if(input == "true"){
				weaponProperties.reloading = true;
			}
			else{
				weaponProperties.reloading = false;
			}
		}
		else if(input == "bulletTexture"){
			file >> weaponProperties.bulletTexture;
		}
		else if(input == "bulletDistance"){
			file >> weaponProperties.bulletDistance;
		}
		else if(input == "shotSound"){
			file >> weaponProperties.shotSound;
		}
		file >> input;
	}
}

void Loader::worldObjectload(){
	std::string input;
	file >> input;
	while(input != "}"){
		file >> input;
	}
}

void Loader::collectibleload(){
	std::string input;
	int time;
	file >> input;
	while(input != "}"){
		if(input == "what"){
			file >> collectibleProperties.what;
		}
		else if(input == "boostTime"){
			file >> time;
			collectibleProperties.boostTime = sf::milliseconds(time);
		}
		file >> input;
	}
}

void Loader::bulletload(){
	std::string input;
	file >> input;
	while(input != "}"){
		if(input == "speed"){
			file >> bulletProperties.speed;
		}
		else if(input == "dmg"){
			file >> bulletProperties.dmg;
		}
		else if(input == "isFacingLeft"){
			file >> input;
			if(input == "true"){
				bulletProperties.isFacingLeft = true;
			}
			else{
				bulletProperties.isFacingLeft = false;
			}
		}
		else if(input == "distance"){
			file >> bulletProperties.distance;
			bulletProperties.distance *= blockSize.x;
		}
		else if(input == "startPosition"){
			file >> bulletProperties.startPosition.x >> bulletProperties.startPosition.y;
			bulletProperties.startPosition.x *= blockSize.x;
			bulletProperties.startPosition.y *= blockSize.y;
		}
		file >> input;
	}
}

void Loader::menuload(){
	std::string input;
	file >> input;
	while(input != "}"){
		if(input == "name"){
			file >> menuProperties.name;
		}
		else if(input == "Labels{"){
			file >> input;
			while(input != "}"){
				if(input == "Label{"){
					labelload();
					menuProperties.addLabel(new Label(gameRef, labelProperties));
				}
				else if(input == "Button{"){
					buttonload();
					menuProperties.addLabel(new Button(gameRef, buttonProperties));
				}
				file >> input;
			}
		}
		else if(input == "gameRunning"){
			file >> input;
			if(input == "true"){
				menuProperties.gameRunning = true;
			}
			else{
				menuProperties.gameRunning = false;
			}
		}
		else if(input == "gameDraw"){
			file >> input;
			if(input == "true"){
				menuProperties.gameDraw = true;
			}
			else{
				menuProperties.gameDraw	= false;
			}
		}
		else if(input == "splitScreen"){
			file >> input;
			if(input == "true"){
				menuProperties.splitScreen = true;
			}
			else{
				menuProperties.splitScreen = false;
			}
		}
		else if(input == "freeCamera"){
			file >> input;
			if(input == "true"){
				menuProperties.freeCamera = true;
			}
			else{
				menuProperties.freeCamera = false;
			}
		}
		file >> input;
	}
}

void Loader::labelload(){
	labelProperties = LabelProperties();
	std::string input;
	file >> input;
	while(input != "}"){
		if(input == "texture"){
			file >> labelProperties.texture;
		}
		else if(input == "displayText"){
			file >> input;
			if(input == "true"){
				labelProperties.displayText = true;
			}
			else{
				labelProperties.displayText = false;
			}
		}
		else if(input == "text"){
			labelProperties.name = loadFormatedString();
		}
		file >> input;
	}
}

void Loader::buttonload(){
	buttonProperties = ButtonProperties();
	std::string input;
	file >> input;
	while(input != "}"){
		if(input == "texture"){
			file >> labelProperties.texture;
		}
		else if(input == "displayText"){
			file >> input;
			if(input == "true"){
				buttonProperties.displayText = true;
			}
			else{
				buttonProperties.displayText = false;
			}
		}
		else if(input == "Event{"){
			eventload();
			buttonProperties.onClick = event;
		}
		else if(input == "text"){
			buttonProperties.name = loadFormatedString();
		}
		file >> input;
	}
}

void Loader::eventload(){
	std::string input;
	file >> input;
	while(input != "}"){
		if(input == "what"){
			file >> event.what;
		}
		else if(input == "par1"){
			file >> event.object1;
		}
		else if(input == "par2"){
			file >> event.object2;
		}
		file >> input;
	}
}

void Loader::loadProperties(bool clean){
	if(clean){
		objectProperties = ObjectProperties();
		physicObjectProperties = PhysicObjectProperties();
		itemProperties = ItemProperties();
		weaponProperties = WeaponProperties();
		worldObjectProperties = WorldObjectProperties();
		entityProperties = EntityProperties();
		entityProperties.equipment.init(gameRef);
		playerProperties = PlayerProperties();
		playerProperties.equipment.init(gameRef);
		collectibleProperties = CollectibleProperties();
	}
	std::string input;
	file >> input;
	while(input != "}"){
		if(input == "ObjectProperties{"){
			objectload();
		}
		else if(input == "PhysicObjectProperties{"){
			physicObjectload();
		}
		else if(input == "EntityProperties{"){
			entityload();
		}
		else if(input == "ItemProperties{"){
			itemload();
		}
		else if(input == "WeaponProperties{"){
			weaponload();
		}
		else if(input == "PlayerProperties{"){
			playerload();
		}
		else if(input == "CollectibleProperties{"){
			collectibleload();
		}
		else if(input == "BulletProperties{"){
			bulletload();
		}
		file >> input;
	}
}

void Loader::loadTemplate(){
	std::string input;
	file >> input;
	while(input != "}"){
		if(input == "name"){
			file >> templateName;
		}
		else if(input == "PhysicObject{"){
			loadProperties();
			physicObjectProperties.setObjectProperties(objectProperties);
			temp.className = ObjectClass::PhysicObject;
			temp.properties = new PhysicObjectProperties(physicObjectProperties);
		}
		else if(input == "WorldObject{"){
			loadProperties();
			worldObjectProperties.setObjectProperties(objectProperties);
			worldObjectProperties.setPhysicObjectProperties(physicObjectProperties);
			worldObjectProperties.type = PhysicObjectType::Static;
			temp.className = ObjectClass::WorldObject;
			temp.properties = new WorldObjectProperties(worldObjectProperties);
		}
		file >> input;
	}
}

void Loader::loadLevel(std::string path){
	file.open(path);
	if(not file.is_open()){
		throw std::string("ERROR cannot open file '" + path + "'!");
	}
	std::string input;
	while(file >> input){
		if(input == "blockSize"){
			file >> blockSize.x >> blockSize.y;
		}
		else if(input == "startPos"){
			file >> startingPos.x >> startingPos.y;
		}
		else if(input == "time"){
			float help;
			file >> help;
			gameRef.setTime(sf::seconds(help));
		}
		else if(input == "PhysicObject{"){
			loadProperties();
			physicObjectProperties.setObjectProperties(objectProperties);
			gameRef.getWorld().addObject(new PhysicObject(gameRef, physicObjectProperties));
		}
		else if(input == "WorldObject{"){
			loadProperties();
			worldObjectProperties.setObjectProperties(objectProperties);
			worldObjectProperties.setPhysicObjectProperties(physicObjectProperties);
			worldObjectProperties.type = PhysicObjectType::Static;
			gameRef.getWorld().addObject(new WorldObject(gameRef, worldObjectProperties));
		}
		else if(input == "Bullet{"){
			loadProperties();
			bulletProperties.setObjectProperties(objectProperties);
			bulletProperties.setPhysicBulletProperties(physicObjectProperties);
			gameRef.getWorld().addObject(new Bullet(gameRef, bulletProperties));
		}
		else if(input == "Collectible{"){
			loadProperties();
			collectibleProperties.setObjectProperties(objectProperties);
			collectibleProperties.setPhysicObjectProperties(physicObjectProperties);
			gameRef.getWorld().addObject(new Collectible(gameRef, collectibleProperties));
		}
		else if(input == "Temp"){
			file >> input;
			temp = gameRef.getTemplateManager().getTemplate(input);
			objectProperties = ObjectProperties();
			physicObjectProperties = PhysicObjectProperties();
			itemProperties = ItemProperties();
			weaponProperties = WeaponProperties();
			worldObjectProperties = WorldObjectProperties();
			entityProperties = EntityProperties();
			playerProperties = PlayerProperties();
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
			objectProperties.name = temp.properties->name + std::to_string(objectLoadedID++);
			loadProperties(false);
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
		else if(input == "Spawn{"){
			file >> input;
			if(input == "position"){
				file >> objectProperties.position.x >> objectProperties.position.y;
				objectProperties.position.x += startingPos.x;
				objectProperties.position.y += startingPos.y;
				objectProperties.position.x *= blockSize.x;
				objectProperties.position.y *= blockSize.y;
				gameRef.getWorld().addSpawnPoint(objectProperties.position);
			}
		}
	}
	file.close();
}

void Loader::loadPlayer(std::string path){
	file.open(path);
	if(not file.is_open()){
		throw std::string("ERROR cannot open file '" + path + "'!");
	}
	std::string input;
	file >> input;
	loadProperties();
	playerProperties.setObjectProperties(objectProperties);
	playerProperties.setPhysicObjectProperties(physicObjectProperties);
	playerProperties.setEntityProperties(entityProperties);
	gameRef.getWorld().addObject(new Player(gameRef, playerProperties));
	file.close();
}

void Loader::loadTextures(std::string path){
	file.open(path);
	if(not file.is_open()){
		throw std::string("ERROR cannot open file '" + path + "'!");
	}
	std::string input, name;
	while(file >> input){
		file >> name;
		std::string input2;
		file >> input2;
		sf::Texture helpTexture;
		helpTexture.loadFromFile(input);
		sf::FloatRect helpRect = sf::Sprite(helpTexture).getGlobalBounds();
		sf::IntRect rect(helpRect.left, helpRect.top, helpRect.width, helpRect.height);
		if(input2 != ";"){
			rect.left = atoi(input2.c_str());
			file >> rect.top;
			file >> rect.width;
			file >> rect.height;
			file >> input2;
		}
		gameRef.getTextureManager().addTexture(input, name, rect);
	}
	file.close();
}

void Loader::loadSounds(std::string path){
	file.open(path);
	if(not file.is_open()){
		throw std::string("ERROR cannot open file '" + path + "'!");
	}
	std::string input, name;
	while(file >> input){
		file >> name;
		gameRef.getSoundManager().addSound(input, name);
	}
	file.close();
}

void Loader::loadItems(std::string path){
	file.open(path);
	if(not file.is_open()){
		throw std::string("ERROR cannot open file '" + path + "'!");
	}
	std::string input, name;
	while(file >> input){
		if(input == "Item{"){
			loadProperties();
			itemProperties.setObjectProperties(objectProperties);
			gameRef.getItemManager().addItem(new Item(gameRef, itemProperties));
		}
		else if(input == "Weapon{"){
			loadProperties();
			weaponProperties.setObjectProperties(objectProperties);
			weaponProperties.setItemProperties(itemProperties);
			if(weaponProperties.ammo == -1){
				weaponProperties.ammo = weaponProperties.maxAmmo;
			}
			gameRef.getItemManager().addItem(new Weapon(gameRef, weaponProperties));
		}
	}
	file.close();
}

void Loader::loadTemplate(std::string path){
	file.open(path);
	if(not file.is_open()){
		throw std::string("ERROR cannot open file '" + path + "'!");
	}
	std::string input, name;
	while(file >> input){
		if(input == "Template{"){
			loadTemplate();
			gameRef.getTemplateManager().addTemplate(templateName, temp);
		}
	}
	file.close();
}

void Loader::loadMenu(std::string path){
	file.open(path);
	if(not file.is_open()){
		throw std::string("ERROR cannot open file '" + path + "'!");
	}
	std::string input;
	while(file >> input){
		if(input == "Menu{"){
			menuProperties = MenuProperties();
			menuload();
			gameRef.getMenuManager().addMenu(menuProperties.name, new Menu(gameRef, menuProperties));
			for(auto i : menuProperties.labels){
				if(i->getClassName() == ObjectClass::Label){
					gameRef.getMenuManager().getMenu(menuProperties.name)->addLabel(new Label(gameRef, i->getLabelProperties()));
				}
				else if(i->getClassName() == ObjectClass::Button){
					gameRef.getMenuManager().getMenu(menuProperties.name)->addLabel(new Button(gameRef, dynamic_cast<Button*>(i)->getButtonProperties()));
				}
			}
			gameRef.getMenuManager().getMenu(menuProperties.name)->getMenuProperties().gameDraw = menuProperties.gameDraw;
			gameRef.getMenuManager().getMenu(menuProperties.name)->getMenuProperties().gameRunning = menuProperties.gameRunning;
			gameRef.getMenuManager().getMenu(menuProperties.name)->getMenuProperties().opacity = menuProperties.opacity;
			gameRef.getMenuManager().getMenu(menuProperties.name)->getMenuProperties().menuHeight = menuProperties.menuHeight;
			gameRef.getMenuManager().getMenu(menuProperties.name)->getMenuProperties().splitScreen = menuProperties.splitScreen;
			gameRef.getMenuManager().getMenu(menuProperties.name)->getMenuProperties().freeCamera = menuProperties.freeCamera;
		}
		else if(input == "active"){
			file >> input;
			gameRef.getMenuManager().setActive(input);
		}
	}
	file.close();
}

std::string Loader::loadFormatedString(){
	std::string out;
	char input;
	do{
		input = file.get();
	}while(input != '"');
	input = file.get();
	while(input != '"'){
		out += input;
		input = file.get();
	}
	return out;
}

void Loader::load(std::string path){
	objectLoadedID = 0;
	gameRef.getWorld().removeAll();
	try{
		loadLevel("Saves/" + path + "/level.sv");
		loadPlayer("Saves/" + path + "/player1.sv");
		loadPlayer("Saves/" + path + "/player2.sv");
	} catch(std::string err){
		printf("%s\n", err.c_str());
	}
}

void Loader::initLoad(){
	try{
		loadTemplate("Saves/template.sv");
		loadTextures("Saves/textures.sv");
		loadSounds("Saves/sounds.sv");
		loadMenu("Saves/menu.sv");
		loadItems("Saves/items.sv");
	} catch(std::string err){
		printf("%s\n", err.c_str());
	}
	
}

void Loader::objectsave(Object* object){
	file << "\tObjectProperties{\n";
	file << "\t\tposition " << static_cast<float>(object->getObjectProperties().position.x) / blockSize.x << " " << static_cast<float>(object->getObjectProperties().position.y)  / blockSize.y << "\n";
	file << "\t\tname " << object->getObjectProperties().name << "\n";
	file << "\t\ttexture " << object->getObjectProperties().texture << "\n";
	file << "\t}\n";
}

void Loader::physicObjectsave(PhysicObject* physicObject){
	file << "\tPhysicObjectProperties{\n";
	file << "\t\ttype ";
	switch(physicObject->getPhysicObjectProperties().type){
		case PhysicObjectType::Dynamic:
			file << "dynamic";
			break;
		case PhysicObjectType::Kinematic:
			file << "kinematic";
			break;
		case PhysicObjectType::Static:
			file << "static";
			break;
	}
	file << "\n";
	file << "\t\tshape ";
	switch(physicObject->getPhysicObjectProperties().shape){
		case PhysicObjectShape::Box:
			file << "box";
			break;
		case PhysicObjectShape::Circle:
			file << "circle";
			break;
	}
	file << "\n";
	file << "\t\tdensity " << physicObject->getPhysicObjectProperties().density << "\n";
	file << "\t\tfriction " << physicObject->getPhysicObjectProperties().friction << "\n";
	file << "\t\tangle " << physicObject->getPhysicObjectProperties().angle * 180 / b2_pi << "\n";
	file << "\t\tvelocity " << physicObject->getPhysicObjectProperties().velocity.x << " " << physicObject->getPhysicObjectProperties().velocity.y << "\n";
	file << "\t}\n";
}

void Loader::entitysave(Entity* entity){
	file << "\tEntityProperties{\n";
	file << "\t\tmaxHP " << entity->getEntityProperties().maxHP << "\n";
	file << "\t\tHP " << entity->getEntityProperties().HP << "\n";
	file << "\t\tjumpHeight " << entity->getEntityProperties().jumpHeight << "\n";
	file << "\t\tmovementSpeed " << entity->getEntityProperties().movementSpeed << "\n";
	file << "\t\tisFacingLeft " << (entity->getEntityProperties().isFacingLeft ? "true" : "false") << "\n";
	file << "\t\tequiped " << entity->getEntityProperties().equipment.getEquipedId() << "\n";
	file << "\t\tEQ{\n";
	for(auto i : entity->getEquipment()){
		if(i.first->getClassName() == ObjectClass::Weapon){
			file << "\t\t\t" << i.first->getName() << " " << dynamic_cast<Weapon*>(i.first)->getWeaponProperties().ammo << " " << dynamic_cast<Weapon*>(i.first)->getWeaponProperties().timeSinceReloadStarted.asMilliseconds() << "\n";
		}
		else{
			file << "\t\t\t" << i.first->getName() << " " << i.second << "\n";
		}
	}
	file << "\t\t}\n";
	file << "\t}\n";
}

void Loader::playersave(Player* player){
	file << "\tPlayerProperties{\n";
	file << "\t\ttextureBase " << player->getPlayerProperties().textureBase << "\n";
	file << "\t\ttextureHair " << player->getPlayerProperties().textureHair << "\n";
	file << "\t\ttextureBoots " << player->getPlayerProperties().textureBoots << "\n";
	file << "\t\ttextureLegs " << player->getPlayerProperties().textureLegs << "\n";
	file << "\t\ttextureGloves " << player->getPlayerProperties().textureGloves << "\n";
	file << "\t\ttextureBody " << player->getPlayerProperties().textureBody << "\n";
	file << "\t\ttextureHandRight " << player->getPlayerProperties().textureHandRight << "\n";
	file << "\t\ttextureCloak " << player->getPlayerProperties().textureCloak << "\n";
	file << "\t\ttextureBeard " << player->getPlayerProperties().textureBeard << "\n";
	file << "\t}\n";
}

void Loader::collectiblesave(Collectible* collectible){
	file << "\tCollectibleProperties{\n";
	file << "\t\twhat " << collectible->getCollectibleProperties().what << "\n";
	file << "\t\tboostTime " << collectible->getCollectibleProperties().boostTime.asMilliseconds() << "\n";
	file << "\t}\n";
}

void Loader::bulletsave(Bullet* bullet){
	file << "\tBulletProperties{\n";
	file << "\t\tspeed " << bullet->getBulletProperties().speed << "\n";
	file << "\t\tdmg " << bullet->getBulletProperties().dmg << "\n";
	file << "\t\tisFacingLeft " << (bullet->getBulletProperties().isFacingLeft ? "true" : "false") << "\n";
	file << "\t\tdistance " << bullet->getBulletProperties().distance / blockSize.x << "\n";
	file << "\t\tstartPosition " << bullet->getBulletProperties().startPosition.x / blockSize.x << " " << bullet->getBulletProperties().startPosition.y / blockSize.y << "\n";
	file << "\t}\n";
}

void Loader::itemsave(Item* item){
	file << "\tItemProperties{\n";
	file << "\t\tamount " << item->getItemProperties().amount << "\n";
	file << "\t\tisWorldObject " << (item->getItemProperties().isWorldObject ? "true" : "false") << "\n";
	file << "\t\ttextureOnEquip " << item->getItemProperties().textureOnEquip << "\n";
	file << "\t\tspawnable " << (item->getItemProperties().isSpawnable ? "true" : "false") << "\n";
	file << "\t}\n";
}

void Loader::weaponsave(Weapon* weapon){
	file << "\tWeaponProperties{\n";
	file << "\t\tattackDelay " << weapon->getWeaponProperties().attackDelay.asMilliseconds() << "\n";
	file << "\t\tbulletSpeed " << weapon->getWeaponProperties().bulletSpeed << "\n";
	file << "\t\tdmg " << weapon->getWeaponProperties().dmg << "\n";
	file << "\t\treloadSpeed " << weapon->getWeaponProperties().reloadSpeed.asMilliseconds() << "\n";
	file << "\t\tmaxAmmo " << weapon->getWeaponProperties().maxAmmo << "\n";
	file << "\t\tammo " << weapon->getWeaponProperties().ammo << "\n";
	file << "\t\tbulletTexture " << weapon->getWeaponProperties().bulletTexture << "\n";
	file << "\t\tbulletDistance " << weapon->getWeaponProperties().bulletDistance / blockSize.x << "\n";
	file << "\t\treloading " << (weapon->getWeaponProperties().reloading ? "true" : "false") << "\n";
	file << "\t\tshotSound " << weapon->getWeaponProperties().shotSound << "\n";
	file << "\t}\n";
}

void Loader::worldObjectsave(WorldObject* worldObject){
	file << "\tWorldObjectProperties{\n";
	file << "\t}\n";
}

void Loader::saveTextures(std::string path){
	file.open(path, std::fstream::out | std::fstream::trunc);
	if(not file.is_open()){
		throw "ERROR cannot open file '" + path + "'!";
	}
	sf::IntRect helpRect;
	for(auto i = gameRef.getTextureManager().getTexturePaths().begin(); i != gameRef.getTextureManager().getTexturePaths().end(); i++){
		file << i->second << " " << i->first << " ";
		helpRect = gameRef.getTextureManager().getArea(i->first);
		file << helpRect.left << " ";
		file << helpRect.top << " ";
		file << helpRect.width << " ";
		file << helpRect.height << " ;\n";
	}
	file.close();
}

void Loader::saveSounds(std::string path){
	file.open(path, std::fstream::out | std::fstream::trunc);
	if(not file.is_open()){
		throw "ERROR cannot open file '" + path + "'!";
	}
	for(auto i = gameRef.getSoundManager().getPaths().begin(); i != gameRef.getSoundManager().getPaths().end(); i++){
		file << i->first << " " << i->second << "\n";
	}
	file.close();
}

void Loader::saveItems(std::string path){
	file.open(path, std::fstream::out | std::fstream::trunc);
	if(not file.is_open()){
		throw "ERROR cannot open file '" + path + "'!";
	}
	for(auto i = gameRef.getItemManager().getItems().begin(); i != gameRef.getItemManager().getItems().end(); i++){
		if(i->second->getClassName() == ObjectClass::Item){
			file << "Item{\n";
			objectsave(i->second);
			itemsave(i->second);
			file << "}\n";
		}
		else if(i->second->getClassName() == ObjectClass::Weapon){
			file << "Weapon{\n";
			objectsave(i->second);
			itemsave(i->second);
			weaponsave(dynamic_cast<Weapon*>(i->second));
			file << "}\n";
		}
	}
	file.close();
}

void Loader::saveLevel(std::string path){
	file.open(path, std::fstream::out | std::fstream::trunc);
	if(not file.is_open()){
		throw "ERROR cannot open file '" + path + "'!";
	}
	file << "blockSize " << blockSize.x << " " << blockSize.y << "\n";
	file << "startPos 0 0\n";
	file << "time " << gameRef.getTime().asSeconds() << "\n";
	for(auto i = gameRef.getWorld().getObjects().begin(); i != gameRef.getWorld().getObjects().end(); i++){
		if(i->second->getClassName() == ObjectClass::PhysicObject){
			file << "PhysicObject{\n";
			objectsave(i->second);
			physicObjectsave(i->second);
			file << "}\n";
		}
		else if(i->second->getClassName() == ObjectClass::WorldObject){
			file << "WorldObject{\n";
			objectsave(i->second);
			physicObjectsave(i->second);
			worldObjectsave(dynamic_cast<WorldObject*>(i->second));
			file << "}\n";
		}
		else if(i->second->getClassName() == ObjectClass::Bullet){
			file << "Bullet{\n";
			objectsave(i->second);
			physicObjectsave(i->second);
			bulletsave(dynamic_cast<Bullet*>(i->second));
			file << "}\n";
		}
		else if(i->second->getClassName() == ObjectClass::Collectible){
			file << "Collectible{\n";
			objectsave(i->second);
			physicObjectsave(i->second);
			collectiblesave(dynamic_cast<Collectible*>(i->second));
			file << "}\n";
		}
	}
	for(auto i = gameRef.getWorld().getBullets().begin(); i != gameRef.getWorld().getBullets().end(); i++){
		file << "Bullet{\n";
		objectsave(i->second);
		physicObjectsave(i->second);
		bulletsave(i->second);
		file << "}\n";
	}
	for(auto i : gameRef.getWorld().getSpawns()){
		file << "Spawn{\n";
		file << "\tposition " << static_cast<float>(i.x) / blockSize.x << " " << static_cast<float>(i.y) / blockSize.y << "\n";
		file << "}\n";
	}
	file.close();
}

void Loader::savePlayer(std::string path, std::string name){
	file.open(path, std::fstream::out | std::fstream::trunc);
	if(not file.is_open()){
		throw "ERROR cannot open file '" + path + "'!";
	}
	file << "Player{\n";
	objectsave(gameRef.getWorld().getObject(name));
	physicObjectsave(gameRef.getWorld().getObject(name));
	entitysave(dynamic_cast<Entity*>(gameRef.getWorld().getObject(name)));
	playersave(dynamic_cast<Player*>(gameRef.getWorld().getObject(name)));
	file << "}\n";
	file.close();
}

void Loader::save(std::string path){
	objectLoadedID = 0;
	try{
		system(("rm -r Saves/" + path + "/").c_str());
		system(("mkdir Saves/" + path + "/").c_str());
		saveLevel("Saves/" + path + "/level.sv");
		savePlayer("Saves/" + path + "/player1.sv", "player1");
		savePlayer("Saves/" + path + "/player2.sv", "player2");
	} catch(std::string err){
		printf("%s\n", err.c_str());
	}
}

Loader::Loader(Game& gameRef) : gameRef(gameRef){
	startingPos.x = 0;
	startingPos.y = 0;
	blockSize.x = 33;
	blockSize.y = 33;
}
