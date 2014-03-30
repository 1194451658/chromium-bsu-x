
#include "GunFactory.h"
#include "shotMethod/LateralShot.h"

static GunFactory* _sharedInstance = NULL;

GunFactory::GunFactory()
{
}

GunFactory* GunFactory::sharedInstance()
{
	if(_sharedInstance == NULL)
	{
		_sharedInstance = new GunFactory();
	}

	return _sharedInstance;
}

Gun* GunFactory::createGun(const char* gunName)
{
	Gun* gun;

	//if(cmp(gunName, "heroAmmo00_lateralShot") == 0)
	{
		// create ammo
		HeroAmmo00Config config;
		Ammo* ammoPrototype = Ammo::create(config.ammoDef);

		// create shot method
		CCPoint relativePos = CCPoint(10,0);
		ShotMethod* shotMethod = LateralShotMethod::create(relativePos);

		// create gun
		gun = Gun::create(ammoPrototype, shotMethod);

		//return gun;
	}

	return gun;
}
