#include "../Header/Ballistic.h"

Ballistic::Ballistic()
{}

Ballistic::Ballistic(const Projectile& currentProjectile, const int& numberOfShots, const int& typeTiroManager, const int& fireRatePeriod, const double& alteredFireRate):
    currentProjectile(currentProjectile),
    numberOfShots(numberOfShots),
    typeTiroManager(typeTiroManager),
    fireRatePeriod(fireRatePeriod),
    alteredFireRate(alteredFireRate)
    {}
