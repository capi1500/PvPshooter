//
// Created by capi1500 on 12/07/18.
//

#include "weapon.hpp"

WeaponProperties::WeaponProperties(){
	reloading = false;
	ammo = -1;
	bulletTexture = "bullet";
}

WeaponProperties::WeaponProperties(ItemProperties itemProperties, sf::Time delay, int dmg, int bulletSpeed, int ammo, sf::Time reloadSpeed, std::string bulletTexture) : ItemProperties(itemProperties), attackDelay(delay), dmg(dmg), bulletSpeed(bulletSpeed), maxAmmo(ammo), reloadSpeed(reloadSpeed), bulletTexture(bulletTexture){
	this->ammo = this->maxAmmo;
	reloading = false;
}

WeaponProperties WeaponProperties::getWeaponProperties(){
	return WeaponProperties(getItemProperties(), attackDelay, dmg, bulletSpeed, ammo, reloadSpeed, bulletTexture);
}

void WeaponProperties::setItemProperties(ItemProperties itemProperties){
	amount = itemProperties.amount;
	isWorldObject = itemProperties.isWorldObject;
}

WeaponProperties& Weapon::getWeaponProperties(){
	return weaponProperties;
}

bool Weapon::canShoot(){
	if(weaponProperties.reloading or weaponProperties.ammo <= 0){
		return false;
	}
	return true;
}

void Weapon::shoot(){
	weaponProperties.ammo -= 1;
}

void Weapon::pass(sf::Time elapsedTime){
	Item::pass(elapsedTime);
	timeSinceReloadStarted += elapsedTime;
	if(weaponProperties.ammo == 0 and not weaponProperties.reloading){
		timeSinceReloadStarted = sf::seconds(0);
		weaponProperties.reloading = true;
	}
	if(weaponProperties.reloading and timeSinceReloadStarted >= weaponProperties.reloadSpeed){
		weaponProperties.reloading = false;
		weaponProperties.ammo = weaponProperties.maxAmmo;
	}
}

Weapon::Weapon(Game& gameRef, WeaponProperties weaponProperties) : Item(gameRef, weaponProperties.getItemProperties()), weaponProperties(weaponProperties){
	className = ObjectClass::Weapon;
}