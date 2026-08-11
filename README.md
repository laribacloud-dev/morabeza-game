# MORABEZA

**MORABEZA** is an open-world action/life sandbox inspired by Cape Verdean reality, culture, landscapes and everyday life.

> Built around Cape Verde. Designed as an original game universe.

## Project Status

**Phase:** 0 — Foundation  
**Milestone:** M0.2 — Praia Prototype Scene

The current code foundation provides:

- Third-person player controller
- Camera and movement
- World interaction interface
- Player interaction tracing
- `E` interaction input
- First mission contact actor
- Player money and reputation state
- Save-game state model
- GameMode wiring for MORABEZA player state

The next playable target is a focused fictionalized Praia scene:

- Urban streets and buildings
- Coastal/viewpoint landmark
- Basic lighting/day-night baseline
- First NPC/contact
- Interaction prompt
- Foundation for mission `VOLTA_INTRO`

## Technology

- Unreal Engine 5.6
- C++ for core gameplay systems
- Blueprints for rapid iteration and content authoring
- Git/GitHub for source control

## Repository Structure

```text
MORABEZA/
├── Config/
├── Content/
├── Docs/
├── Source/
│   └── MORABEZA/
├── .gitignore
├── MORABEZA.uproject
└── README.md
```

## Design Principles

1. Cape Verde is the setting and identity of the game, not a skin applied to another game's formula.
2. The first release prioritizes a small, dense, believable world over a huge empty map.
3. Systems are designed to scale from a vertical slice into a larger open world.
4. Fictional characters, organizations and businesses will be used where necessary to avoid misrepresenting real entities.
5. The game remains an original IP and does not copy GTA characters, missions, assets, branding or storylines.

## First Definition of Done

Launch → spawn in Praia → walk → enter a vehicle → drive → interact with an NPC → receive a mission → complete it → earn money → save → reload.

## Current Milestone

**M0.2 — Build Praia prototype scene** is tracked in GitHub Issue #1.

The Unreal Engine project must be opened locally to create and validate the binary map/assets (`.umap`, `.uasset`) that cannot be meaningfully authored through GitHub's text-file API alone.

## License

License to be determined before public distribution. All original MORABEZA assets and source remain controlled by the project owner until a formal license is added.
