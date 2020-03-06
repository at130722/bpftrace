#pragma once

#include <linux/types.h>
#include <string>
#include <map>
#include <unistd.h>
#include <unordered_set>
#include "types.h"

struct btf;
struct btf_type;

namespace bpftrace {

class BTF
{
  enum state
  {
    NODATA,
    OK,
  };

public:
  BTF();
  ~BTF();

  bool has_data(void) const;
  std::string c_def(std::unordered_set<std::string>& set);
  std::string type_of(const std::string& name, const std::string& field);
  std::string type_of(const btf_type* type, const std::string& field);
  void display_funcs(void) const;

  int resolve_args(std::string &func, std::map<std::string, SizedType> &variables, bool ret);

  bool has_function(std::string func);

private:
  SizedType get_stype(__u32 id);
  const struct btf_type *btf_type_skip_modifiers(const struct btf_type *t);

  struct btf* btf;
  enum state state = NODATA;
};

inline bool BTF::has_data(void) const
{
  return state == OK;
}

} // namespace bpftrace
