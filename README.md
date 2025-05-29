## Deadweight
You are a lone space traveler traversing the vast void, passing from spaceport to spaceport looking for freelance work. The main game takes place in the cockpit of the spaceship and revolves around the politics of the different guilds, empires and republics. RPG with 80s retro futuristic aesthetic. 

### Mechanics
You control your ship via a command terminal, there is a monitor showing known galaxies, stars and planets as well as who controls them. There is a display showing how much you can haul and how full your storage currently is. On different planets, asteroids and such you will be able to hunt for jobs to do. You will have to make sure that you are transporting goods that are legal in the different territories you are traversing or make sure you don't get caught with anything illegal. You will build relationships and reputation, a bad relationship with a certain state will make you wanted in their territory. At the beginning of the game you will be able to choose which state your ship is registered under giving you certain bonuses. The politics are static as this game should take place during a very short time i.e. real spent time is in-game time. You control the character via the mouse in the cockpit.

### Art
80s retro futuristic aesthetic inspired by works such as Blade Runner and Alien. Mixed graphics using both 2D pixel art and early 00's 3D. 3D will be used for animating when traveling, wireframe for showing cargo and the planets on the galaxy monitor. 2D will be used for the terminal, NPCs and the interior of the cockpit. 

### Influences
#### Film
* Blade Runner
* Alien
* Cowboy Bebop
* Firefly
* Outland (1981)
* The Expanse

#### Games
* Objects in Space
* FTL: Faster Than Light

#### Books
* Neuromancer

#### Art
* Simon Stålenhag
* Ian McQue
* Moebius
* Andreas Rocha


### MVP
* Cockpit with command terminal, galaxy monitor and politics display
* Terminal should show incomming jobs
* Commands: jump [planet/coordinates], scan [planet/coordinates], transact [job], comms [planet/faction] 
* Random events: asteroids (smaller randomly generated planets basically) and pirates (negotiate or dump cargo)
* Taking jobs on planets
* Some simple politics: i.e. some illegal cargo types, suspiciousness, some factions have border checks, 

### MVP CHECK

- [ ] Static star system map with at least 6 territories
- [ ] Terminal UI with basic commands: `jump`, `scan`, `transact`, `comms`, `balance`, `help`
- [ ] 6 cargo types (grain, ore, weapons, personel, chemicals, electronics)
- [ ] 3 factions with simple law/reputation systems (Confederacy, Syndicates, Union)
- [ ] One job on every territory, + 3 random job encounters
- [ ] Two random events (pirates & dwarf planets)
- [ ] Border check mechanic (risk scan, dump cargo)
- [ ] Functional cockpit (clickable)
- [ ] Simple reputation (i.e. less available jobs with bad reputation, bad reputation if failing jobs)

### STRETCH GOALS

- [ ] Character costumization (starting faction)
- [ ] Bounty / pursuit system if your caught smuggling 
- [ ] Faction lore 
- [ ] Death

### Timeline
| **Phase**              | **Deliverables**                                      |
|------------------------|--------------------------------------------------------|
| Setup & engine         | Raylib project skeleton, mock UI                      |
| Terminal & input       | Working command parser                                |
| Galaxy & navigation    | Star map, jump logic                                  |
| Cargo & jobs           | Storage system, job generator                         |
| Faction & events       | Reputation, border checks, pirates                    |
| Polish & integration   | Bugfixes, UI touch-up                                 |
| Stretch goals          | Character select, bounty system, lore integration     |

### Project Structure
/Deadweight
│
├── CMakeLists.txt           # Root CMake configuration
├── README.md
├── .gitignore
│
├── /build/                  # CMake build output (ignored in Git)
│
├── /assets/                 # Game assets (loaded at runtime)
│   ├── /textures/           # Cockpit UI, terminal graphics
│   ├── /models/             # 3D models, e.g. wireframe planets
│   ├── /fonts/              # Terminal/cockpit fonts
│   ├── /audio/              # SFX, ambient music
│   ├── /shaders/            # Optional shaders (e.g. CRT effects)
│   └── /scripts/            # Dialogue, events, or job templates
│
├── /src/                    # C++ source code
│   ├── main.cpp             # Entry point
│   ├── /core/               # Core engine parts
│   ├── /ui/                 # Terminal UI, galaxy monitor, cockpit
│   ├── /systems/            # Gameplay systems (MVP-aligned)
│   ├── /data/               # Game data models (components/entities)
│   └── /utils/              # Helper functions, logging, config loading