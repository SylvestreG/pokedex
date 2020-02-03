//
// Created by syl on 31/12/19.
//

#include <list>
#include <string>

class pokemon {
 private:
  uint32_t _id;
  std::string _name;
  std::list<std::string> _type;
  std::string _height;
  std::string _weight;

public:
  pokemon(std::string const& name);
  pokemon(uint32_t id);

  uint32_t get_id() const;
  void set_id(uint32_t id);
  const std::string &get_name() const;
  void set_name(const std::string &name);
  const std::list<std::string> &get_type() const;
  void set_type(const std::list<std::string> &type);
  const std::string &get_height() const;
  void set_height(const std::string &height);
  const std::string &get_weight() const;
  void set_weight(const std::string &weight);

  void display_as_text() noexcept;
};