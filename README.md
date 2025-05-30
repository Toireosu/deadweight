## Deadweight
You are a lone space traveler traversing the vast void, passing from spaceport to spaceport looking for freelance work. The game takes place entirely from the cockpit of your ship, where you navigate the shifting politics of rival guilds, empires, and republics. Deadweight is a narrative-driven RPG set in a gritty, 1980s-inspired retro-futuristic universe.

### Mechanics
You control your ship entirely from the cockpit using a command terminal. A galactic monitor displays known systems, planets, and their controlling factions. A separate interface shows your cargo capacity and current loadout. As you travel between planets, asteroids, and outposts, you can take on various jobs—legal or otherwise.
You'll need to manage what you carry carefully, as different territories have different laws. Transporting contraband can be lucrative, but getting caught has consequences. Your actions affect your standing with each faction; poor relations can make you a wanted criminal in hostile space.
At the start of the game, you choose a home state for your ship, which grants unique perks and shapes how you're treated across the galaxy. The political landscape is static, as the game unfolds over a short, continuous stretch of real-time.

### Art
The game features a retro-futuristic aesthetic inspired by 1980s sci-fi classics like Blade Runner and Alien. Visually, it combines 2D pixel art with early 2000s-style low-poly 3D. Pixel art is used for the cockpit interior, terminal interface, and NPCs, while 3D elements are used for travel animations, cargo visualization, and wireframe representations of planets and star systems on the galactic monitor.

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
- **Deadweight/**
  - `CMakeLists.txt` — Root CMake configuration
  - `README.md`
  - `.gitignore`
  - **assets/** — Game assets 
    - **textures/**
    - **models/**
    - **fonts/**
    - **audio/** — SFX, ambient music
    - **shaders/** — Shaders
    - **scripts/** — Dialogue, events, job templates
  - **src/** — C++ source code
    - `main.cpp` — Entry point
    - **core/** — Engine
    - **ui/** — UI
    - **systems/** — Gameplay systems (MVP-aligned)
    - **data/** — Game data models (components/entities)
    - **utils/** — Helper functions, logging, config loading