#ifndef PLAYER_HPP
#define PLAYER_HPP

namespace player { // The players progress in the game, to be serialized into a file and deserialized when the user
  // plays again.
  std::string userName{};
  std::string password{};
  double experience{0};

  bool internetUnlocked{};
  bool passwordCracker{};
};

#endif
