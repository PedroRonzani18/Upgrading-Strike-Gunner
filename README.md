# Strike-Gunner-CTC

## 🎮 Play Now (Windows)
You don't need to compile the game to play! 
**[Click here to download the latest Windows release (.zip)](https://github.com/PedroRonzani18/Upgrading-Strike-Gunner/releases/latest)**.

*Instructions: Download the file, extract the folder, and double-click `StrikeGunner.exe`.*

---

## 🛠️ Initial Information
- This game was developed as a Project for a Computer Graphics class.
- Operating system used: Linux (Ubuntu / Fedora).
- Main language: C++

## 🐧 Necessary Libs on Linux
If you wish to compile the game yourself on Linux, you will need the following libraries:

* Freeglut: `sudo apt-get install freeglut3-dev`
* SOIL: `sudo apt-get install libsoil-dev`
* SDL: `sudo apt-get install -y libsdl2-mixer-dev`

## ⚙️ How to compile and execute (Linux)
- Compile: `make all`
- Run separately: after compiling, use `./Bin/ctc`
- Compile and run: `make run`
- Clear: `make clear`

---

## ⌨️ Keyboard Controls

### Controls in Menu
- **W**: Moves up
- **S**: Moves down
- **SPACE**: Enters selected option
- **ESC**: Closes the game
   
### Controls in Help (Ajuda)
- **SPACE**: Goes back to menu
- **ESC**: Closes the game

### Controls in Level
- **W**: Moves player up  
- **A**: Moves player left  
- **S**: Moves player down
- **D**: Moves player right  
- **SPACE**: Shoots projectiles
- **ESC**: Closes the game

---

## 🚀 Relevant Observations
1. When an enemy dies, there is a probability (set as the enemy's attribute) of dropping an item that upgrades the player's weapon.
2. Possible upgrades:
   - Damage increase
   - Increases fire rate
   - Increases HP (MAX: 4)
   - Increases number of shots released in a cycle (1, 2, 3)
   - Changes the projectile's model (default, collides with walls, follows an enemy)
3. The game ends when the player kills the boss, or when they die (loses all 4 lives).
4. There may or may not be something waiting for you after the credits...

### Thank you for your attention, and good game!
