#include "combat.hpp"

#include "colors.hpp"
#include "rng.hpp"

namespace {
    constexpr int missChance = 10;
    constexpr int critChance = 10;

    std::string subject(const World& world, const Entity& e) {
        return &e == &world.player() ? "You" : "The " + e.name;
    }
    std::string object(const World& world, const Entity& e) {
        return &e == &world.player() ? "You" : "The" + e.name;
    }
}

void performAttack(World &world, Entity &attacker, Entity &defender, std::mt19937 &rng) {
    const bool byPlayer = (&attacker == &world.player());
    const std::string who = subject(world, attacker);
    const std::string whom = subject(world, defender);
    const int roll = randInt(rng, 1 , 100);
    if (roll <= missChance) {
        world.say(who + (byPlayer ? " miss ": " misses ") + whom + ".", ColDefault);
        return;
    }
    const bool crit = roll > 100 - critChance;
    int damage = attacker.attack + randInt(rng, -1, 1) - defender.defense;
    damage = std::max(1, damage);
    if (crit) {
        damage *= 2;
    }
    defender.hp -= damage;
    world.hits.push_back({defender.x,defender.y});
    if (crit) {
        world.say(who + (byPlayer ? " strike " : " strikes ") + whom + " critically for " + std::to_string(damage) + "!" , ColYellow);
    }else {
        world.say(who + (byPlayer ? " hit " : " hits ") + whom + " for " + std::to_string(damage) + ".", byPlayer ? ColGreen : ColRed);
    }
    if (defender.hp <= 0) {
        world.say(who + (byPlayer ? " kill " : " kills ") + whom + "!", ColYellow);
    }
}

bool playerMoveOrAttack(World &world, int dx, int dy, std::mt19937 &rng) {
    Entity& player = world.player();
    Entity* target = world.entityAt(player.x + dx, player.y + dy);
    if (target != nullptr && target != &player) {
        performAttack(world, player, *target, rng);
        return true;
    }
    return world.tryMove(player, dx ,dy);
}
