# CMP105 2026 Final Submission
# Adventure of a Handy Dino

short description

Controls:
* A/D to move left/right
* L to dash (once unlocked), paired with WASD for 8 directional movement
* F to shoot a fireball
* H to do a melee attack
* Enter to interact (only used on final door)
* Escape to pause

# Student Details

**Name:** Marcy Liddle

**Team:** Project Caterpie

**Course:** _CGT_

**Abertay id:** 2400826

# Changelist
The changes you have made since the group submission.

## Player Abilities:
  * The player can now do a melee kick attack & shoot fireballs. These can be leveled up to do more damage.
  * The player can now unlock a 8-directional dash move that allows them to travel greater distances for platforming.

## Enemy npcs: 
 * Slimes that move back & forth / towards the player that will damage on contact and can be killed by the player's melee and ranged attacks.
 * Dragon boss that shoots fireballs towards the player that can only be hurt and killed if the player is a certain level. Defeating it reveals a door to win & end the game. 

## Data-Driven Level loading
   * The level geometry is now loaded in from file.
   * This also includes enemy positioning, as well as collectables that help the player & obstacles that must be overcome to progress.


# Known Bugs
List any issues you are aware of and how to avoid them
* Dash movement, especially with multiple in quick succession, can sometimes clip through platforms if moving directly through
  



# Proposal from March

## Game Extended
Dino Handyman
author(s)
Supplied Project

## Brief Overview of game 

"Adventure of a Handy Dino" will be a metroidvania set in a small world populated with platforming challenges, enemies & at least 1 boss fight. Throughout the game, the player will find abilities; such as a dash and a grapple for mobility and upgrades to their attacks that allow them to break through obstacles; that they will need to progress and beat the game. The world should be created using tilemaps and a data-driven level loading system, and the rooms will designed in a way that encourages backtracking to use any new abilities to get past obstacles that were previously roadblocks. At the end of the game, the time taken to beat the game as well as the amount of deaths will be displayed and written to file, as well as their best time & least amount of deaths.
  
## :white_check_mark: Must Have Features

* :white_check_mark: Enemies that move towards the player when they are close and attack to deal damage to the player that can also be damaged, killed & despawned by :
* :white_check_mark:  The player will have 2 different types of attacks, a melee and a projectile that can be upgraded to deal more damage and break destructable terrain.
*  :white_check_mark: The player will have a limited amount of health that can be decreased by enemies and traps & increased by pick-ups, and when it reaches 0 the game will allow them to go back to the start / last place they saved.

## :white_check_mark: Should Have Features

* :white_check_mark: Metroidvania-like progression system (upgrades for the attacks) as well as movement-based abilities;  at least a dash for moving greater distances in any direction; unlocked through pickups hidden throughout the:
* :white_check_mark: Game world: Data-driven enviroment consisting of screens with collectables hidden behind obstacles you will need abilities to get through. It shoud also have a limited amount of save points to act as respawn points and record the abilities that the player has currently.
* ✅ At least 1 boss fight to find and defeat with the aid of unlocked abilities to beat the game.
* ✅ The ability to pause the game with a transparent overlay and menu & resume exactly as was before.
*  :white_check_mark: UI that shows: the amount of health the player has left: moved up in priority

## Could Have Features

* A speedrun mode with a timer & possibly timesplits that are visible on a Heads-Up Display.
* UI also shows any ✔️ ability cooldowns & the objectives.
* Controller support: in addition to keyboard, the game could also be played with other controllers. 
* The "aimable grappling skill to reach even further" from my original proposal has been moved down in priority.

## Wish to Have Features

* A rogue-like mode with a procedurally generated world and randomly allocated abilities. If the abilities leave the player stuck, they will instead fight a boss to progress.
* A local and/or online multiplayer race mode based on the speedrun mode that pits players against each other to beat the game in the least amount of time.

