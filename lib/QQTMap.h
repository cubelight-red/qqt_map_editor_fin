#pragma once

#include <cstdint>
#include <utility>
#include <vector>

#include "EQQTGameMode.h"

class QQTMap
{
public:
  enum Layer { kTop, kGround };

  bool read(std::istream &is);
  bool write(std::ostream &os);
  bool isOutOfBound(int x, int y) const { return x < 0 || y < 0 || x >= _w || y >= _h; }
  int getMapElementId(int x, int y, Layer layer) const;
  std::pair<int, int> findOrigin(int x, int y, Layer layer);
  void setGameMode(EQQTGameMode mode) { _gameMode = mode; }
  EQQTGameMode getGameMode() const { return _gameMode; }
  int getWidth() const { return _w; }
  int getHeight() const { return _h; }
  void resize(int width, int height);
  int getNMaxPlayers() const { return _nMaxPlayers; }
  void setNMaxPlayers(int n) { _nMaxPlayers = n; }
  const auto &getSpawnPoints(int group) const { return _spawnPoints[group]; }
  int removeMapElementAt(int x, int y, Layer layer);
  bool putMapElementAt(int x, int y, int id, Layer layer);

private:
  int32_t _version{};
  int32_t _nMaxPlayers{};
  EQQTGameMode _gameMode{};
  uint16_t _w{};
  uint16_t _h{};
  std::vector<std::vector<int32_t>> _elementIds[2 /*layers*/];
  std::vector<std::pair<int32_t, int32_t>> _specialPoints;
  std::vector<std::pair<int32_t, int32_t>> _spawnPoints[2 /*groups*/];
};
