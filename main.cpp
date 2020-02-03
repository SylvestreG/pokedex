//
// Created by syl on 31/12/19.
//
#include <iostream>
#include <list>
#include <set>
#include <lyra/lyra.hpp>
#include "pokemon.hh"

using namespace lyra;

static auto up_if_true = [i=0](bool value) mutable -> int { if (value) i++; return i;};

static auto fill_pok_list = [](auto array, std::list<std::shared_ptr<pokemon>> & pok_list) -> void {
  for (auto& pok: array) {
    try {
      pok_list.push_back(std::make_shared<pokemon>(pok));
    } catch (std::runtime_error const &re) {
      std::cerr << re.what() << std::endl << std::endl;
    }
  }
};

static auto print_help = [](bool exit, std::string const &err = "") -> void {
  if (!err.empty())
    std::cerr << err << std::endl;
  std::cerr << "usage: ./pokedex [-h|--help] [-n|--name] [-i|--id]"
            << std::endl;
  if (exit)
    std::exit(EXIT_FAILURE);
};

std::set<std::string> split(const std::string &s, char delim) {
  std::stringstream ss(s);
  std::string item;
  std::set<std::string> elems;
  while (std::getline(ss, item, delim))
    elems.insert(std::move(item));
  return elems;
}

std::set<uint32_t> split_int(const std::string &s, char delim) {
  std::stringstream ss(s);
  std::string item;
  std::set<uint32_t> elems;
  while (std::getline(ss, item, delim))
    elems.insert(std::stoul(item));
  return elems;
}

int main(int argc, char **argv) {
  bool help{false};
  std::string names;
  std::string ids;

  auto cli = lyra::help(help)
      | lyra::opt(help)["-h"]["--help"]("help")
      | lyra::opt(names, "aaa,bbb,ccc")["-n"]["--name"]("list of pokemon names")
      | lyra::opt(ids, "x,y,z")["-i"]["--id"]("list of pokemon ids");

  auto result = cli.parse({argc, argv});
  if (!result) {
    print_help(true, result.errorMessage());
  }

  up_if_true(help);
  up_if_true(!names.empty());
  up_if_true(!ids.empty());

  if (up_if_true(false) != 1)
    print_help(true, "you need to pick one and only one argument");

  std::list<std::shared_ptr<pokemon>> pok_list;

  if (!names.empty()) {
    auto name_array = std::move(split(names, ','));
    fill_pok_list(name_array, pok_list);
  } else if (!ids.empty()) {
    try {
      auto id_array = std::move(split_int(ids, ','));
      fill_pok_list(id_array, pok_list);
    } catch (std::invalid_argument const& err) {
        print_help(true, "bad conversion from string to u32");
    }
  } else
    std::cout << cli;

  for (auto& p: pok_list) {
    p->display_as_text();
  }

  return EXIT_SUCCESS;
}