#pragma once
// The player's skin (Skins.cpp): a ped model of the game, one of the mod's skin packs (coop\skinpacks) or one of the
// player's own (coop\skins, entities/skin), worn instead of CJ. The F4 window (pages/skins-menu) chooses it; it is kept
// in coop.ini, put on again in each game, and the other players see it as they see any model of ours (Progress,
// G_PLAYER_LOOK). In a cutscene it stands in for CJ.
#include <cstdint>
#include <string>
#include <vector>

namespace coop::skins {

enum Group : uint8_t { SA, PACKS, OWN, GROUPS };

struct Skin {
    int model = 0;     // the game's ped model (0 for an own skin: its number is given when it loads; 0 for a story
                       // character too: it goes into a special slot, 290-299, when it is worn or shown)
    Group group = SA;
    std::string name;  // as the list shows it: the model's name in the game's files, an own skin's file name
    std::string file;  // an own skin's name (its files in coop\skins), a pack's "pack/name", empty for the game's
    std::string pack;  // a pack's skin: the title over its pack's rows (its name and its authors)
    int id = -1;          // the SA tab's: its number as SA-MP has it (0 CJ, 1-311 without 74), -1 for the others
    std::string special;  // a story character's model name ("sweet"): loaded by name into a special slot
};

const char* GroupName(Group g);
// SA-MP's skins in its numbers (0 CJ, 1-311 without 74: the game's people by model, the story's characters by name),
// then the packs' skins and the player's own
const std::vector<Skin>& List();
// the own skins' and the packs' folders read anew (the window opens)
void Rescan();
// the model it is in, an own skin loaded now; -1: it would not load (why says why)
int ModelOf(const Skin& s, std::string* why = nullptr);
// the one our player wears by choice
bool IsChosen(const Skin& s);
bool AnyChosen();
// why our player cannot change now, empty: it can
std::string WhyNot();
// puts it on now and keeps it (null: CJ again); false: why says why
bool Wear(const Skin* s, std::string& why);
// the window closed: the own skins it loaded to show and nobody wears are taken out of memory
void LetUnusedGo();
// the window's preview shows this model now (-1: none): a story character it showed before is let go
void Previewed(int model);

}  // namespace coop::skins
