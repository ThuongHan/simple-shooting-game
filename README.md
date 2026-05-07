[Watch demo](/Users/mateuszsusmarski/Documents/Repositories/virusgame/demo.mp4)

# 1. Shooting Mechanism ss

The player can shoot bullets in the direction the are facing and also there is a cooling system so that we shoot approximately 3 bullets per second.

# 2. Scoring System

- Destroying a normal virus gives +1 points
- Destroying a BigVirus gives +2 points
- Colliding with a virus decreases score - collision with BigVirus : -2 points - collosion with virus : -1 points
  The score is displayed on the screen (top left), and the game ends when:
- player wins if score > 20
- player losses if score < 0

# 3. BigVirus (new unit type, implemented in BigVirus.h)

A new virus is added:

- Bigger and slower than normal viruses
- Has 5 hp (5 bullets to kill it)
- Gain 2 points when killed

BigVirus is derived from Virus

# 4. Collision System

- Bullets damage or destroy viruses if distances are close
- BigVirus requires 5 hits but gives you 2 points to the score
- Player also lose points when colliding with viruses (lose 1 if normal viurs and lose 2 points when colliding with BigVirus)

-- Note: the game always starts with a score of 10. From there it can go up or down.

## Description of decisions related to SOLID principles by student

My code structure ...
