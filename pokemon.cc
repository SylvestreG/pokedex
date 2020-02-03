//
// Created by syl on 1/3/20.
//
#include "pokemon.hh"
#include <iostream>
#include <json11.hpp>
#include <restclient-cpp/connection.h>

using namespace json11;

auto get_pokemon_json = [](std::string const& pokemon) -> std::string {
  RestClient::init();

  RestClient::Connection con("https://pokeapi.glitch.me");
  con.SetTimeout(5);
  con.SetUserAgent("Pokedex (https://github.com/SylvestreG/pokedex, v0.1)");
  RestClient::HeaderFields headers;
  headers["Accept"] = "application/json";
  con.SetHeaders(headers);

  RestClient::Response r = con.get("/v1/pokemon/" + pokemon);

  if (r.code != 200)
    throw std::runtime_error("api does not exist for this pokemon: " + pokemon);

  RestClient::disable();

  return r.body;
};

auto fill_pokemon = [](std::string const& json, pokemon & p) -> void {
  std::string err;
  auto obj{Json::parse(json, err)};

  if (!err.empty())
    throw std::runtime_error("bad json format");


  std::list<std::string> types;
  for (auto t: obj[0]["types"].array_items()) {
    types.push_front(t.string_value());
  }
  uint32_t id{0};
  try {
    id = std::stoul(obj[0]["number"].string_value());
  }
  catch (...) {}

  p.set_name(obj[0]["name"].string_value());
  p.set_type(types);
  p.set_height(obj[0]["height"].string_value());
  p.set_weight(obj[0]["weight"].string_value());
  p.set_id(id);
};

pokemon::pokemon(std::string const& name) {
  fill_pokemon(get_pokemon_json(name), *this);
}

pokemon::pokemon(uint32_t id) {
  fill_pokemon(get_pokemon_json(std::to_string(id)), *this);
}

void pokemon::display_as_text() noexcept {
  std::cout << "Number:\t" << _id << std::endl;
  std::cout << "Name:\t" << _name << std::endl;;
  std::cout << "Types:\t";
  for (auto it{_type.begin()}, end{_type.end()}; it != end; ++it) {
    std::cout << *it;
    if (std::next(it) != end)
      std::cout << ", ";
    else
      std::cout << std::endl;
  }
  std::cout << "Height:\t" << _height << std::endl;
  std::cout << "Weight:\t" << _weight << std::endl;
  std::cout << std::endl;
}

uint32_t pokemon::get_id() const {
  return _id;
}

void pokemon::set_id(uint32_t id) {
  _id = id;
}

const std::string &pokemon::get_name() const {
  return _name;
}

void pokemon::set_name(const std::string &name) {
  _name = name;
}

const std::list<std::string> &pokemon::get_type() const {
  return _type;
}

void pokemon::set_type(const std::list<std::string> &type) {
  _type = type;
}

const std::string &pokemon::get_height() const {
  return _height;
}

void pokemon::set_height(const std::string &height) {
  _height = height;
}

const std::string &pokemon::get_weight() const {
  return _weight;
}

void pokemon::set_weight(const std::string &weight) {
  _weight = weight;
}
